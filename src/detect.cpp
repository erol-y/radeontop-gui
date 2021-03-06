/*
	Copyright (C) 2012 Lauri Kasanen
	Copyright (C) 2017 Erol Yesilyurt

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <pciaccess.h>
#include <dirent.h>
#include "radeontop.h"

#define if_err(e, s) if(e) {m_err = true; std::cout << s << std::endl; return 0;}
#define if_n_err(e, s) if(!e) {m_err = true; std::cout << s << std::endl; return 0;}

namespace radeontop {

#define PCI_VENDOR_ATI  0x1002
#define DEV_FGLRX_PATH  "/dev/ati/card0"
#define DEV_AMDGPU_PATH "/dev/dri/card0"

static unsigned long long igpu_mclk = 0;

unsigned int rdtop::init_pci(short bus, const unsigned char forcemem __attribute__((unused)))
{
    int ret = pci_system_init();
    if_err(ret, "Failed to init pciaccess")

    struct pci_id_match match;

    match.vendor_id = PCI_VENDOR_ATI;
	match.device_id = PCI_MATCH_ANY;
	match.subvendor_id = PCI_MATCH_ANY;
	match.subdevice_id = PCI_MATCH_ANY;
	match.device_class = 0;
	match.device_class_mask = 0;
	match.match_data = 0;

    struct pci_device_iterator *iter = pci_id_match_iterator_create(&match);
	struct pci_device *dev = NULL;
	//char busid[32];
	memset(busid, 0, sizeof(busid));

	while ((dev = pci_device_next(iter))) {
		pci_device_probe(dev);
		if ((dev->device_class & 0x00ffff00) != 0x00030000 &&
			(dev->device_class & 0x00ffff00) != 0x00038000)
			continue;

		if (bus < 0 || bus == dev->bus)
		{
            snprintf(busid, sizeof(busid), "pci:%04x:%02x:%02x.%u",
				dev->domain, dev->bus, dev->dev, dev->func);

			break;
		}
	}

	pci_iterator_destroy(iter);

	if(dev != NULL)
    {
        snprintf(devid, sizeof(devid), "ven:%.4X dev:%.4X subven:%.4X subdev:%.4X",
                                          dev->vendor_id,
                                          dev->device_id,
                                          dev->subvendor_id,
                                          dev->subdevice_id);

        printf("%s\n\n", devid);
        printf("%s\n\n", busid);
    }
    else
    {
        memset(devid, 0, sizeof(devid));
        //printf("Can't find Radeon card\n");
        return 0;
    }

	const unsigned int device_id = dev->device_id;
	int reg = 2;
	if (getfamily(device_id) >= BONAIRE)
		reg = 5;

    if_n_err(dev->regions[reg].size, "Can't get the register area size")

    // DRM support for VRAM
    drm_fd = drmOpen(NULL, busid);
	if(drm_fd >= 0)
    {
		drmVersionPtr ver = drmGetVersion(drm_fd);
		if (strcmp(ver->name, "radeon") != 0 && strcmp(ver->name, "amdgpu") != 0)
        {
            strcpy(drm_name, ver->name);
			close(drm_fd);
			drm_fd = -1;
		}

		set_driver_enum(ver->name);
		if( access(DEV_FGLRX_PATH, F_OK) == 0 )
            snprintf(devpath, sizeof(devpath), DEV_FGLRX_PATH);
        else if( access(DEV_AMDGPU_PATH, F_OK) == 0 )
            snprintf(devpath, sizeof(devpath), DEV_AMDGPU_PATH);

		drmFreeVersion(ver);
	}
	else
    {
        snprintf(drm_name, sizeof(drm_name), "???");

        if( access(DEV_FGLRX_PATH, F_OK) == 0 )
        {
            drm_fd = open(DEV_FGLRX_PATH, O_RDWR);
            if(drm_fd > 0)
                set_driver_enum(drmGetVersion(drm_fd)->name);

            snprintf(devpath, sizeof(devpath), DEV_FGLRX_PATH);
        }
        else if( access(DEV_AMDGPU_PATH, F_OK) == 0 )
        {
            drm_fd = open(DEV_AMDGPU_PATH, O_RDWR);
            if(drm_fd > 0)
                set_driver_enum(drmGetVersion(drm_fd)->name);

            snprintf(devpath, sizeof(devpath), DEV_AMDGPU_PATH);
        }
    }

    //TODO: What is the equal of RADEON_INFO_READ_REG @amdgpu ?
    use_ioctl = 0;
    if(drm_fd >= 0)
    {
        authenticate_drm(drm_fd);
        uint32_t rreg = 0;
        if(this->AmdGpuDriver == _AmdGpuDriver::radeon)
            use_ioctl = get_drm_value(drm_fd, RADEON_INFO_READ_REG, &rreg);
        else if(this->AmdGpuDriver == _AmdGpuDriver::amdgpu)
            use_ioctl = 0;
    }

    if(!use_ioctl)
    {
        int mem = open("/dev/mem", O_RDONLY);
        if_err(mem < 0, "Cannot access GPU registers, are you root?")

        area = mmap(NULL, MMAP_SIZE, PROT_READ, MAP_PRIVATE, mem,
                dev->regions[reg].base_addr + 0x8000);

        if_err(area == MAP_FAILED, "mmap failed")
    }

	bits.vram = 0;
	bits.gtt = 0;

	if (drm_fd < 0)
	{
	    std::cout << "Failed to open DRM node, no VRAM support.\n";
	}
	else
    {
        drmDropMaster(drm_fd);
		drmVersionPtr ver = drmGetVersion(drm_fd);

		if (ver->version_major < 2 ||
			(ver->version_major == 2 && ver->version_minor < 36)) {
			printf(("Kernel too old for VRAM reporting.\n"));
			drmFreeVersion(ver);
			goto out;
		}

		strcpy(drm_name, ver->name);
		set_driver_enum(ver->name);
        m_drm_version.version_major = ver->version_major;
        m_drm_version.version_minor = ver->version_minor;
        m_drm_version.version_patchlevel = ver->version_patchlevel;

        drmFreeVersion(ver);

		// No version indicator, so we need to test once
		// We use different codepaths for radeon and amdgpu
		// We store vram_size and check below if the ret value is sane
		if (AmdGpuDriver == _AmdGpuDriver::radeon) {
			struct drm_radeon_gem_info gem;

			ret = drmCommandWriteRead(drm_fd, DRM_RADEON_GEM_INFO, &gem, sizeof(gem));
			vramsize = gem.vram_size;
			gttsize = gem.gart_size;
		} else if (AmdGpuDriver == _AmdGpuDriver::amdgpu) {
#ifdef ENABLE_AMDGPU
			struct drm_amdgpu_memory_info vram_gtt = {};

			struct drm_amdgpu_info request;
			memset(&request, 0, sizeof(request));
			request.return_pointer = (unsigned long) &vram_gtt;
			request.return_size = sizeof(vram_gtt);
			request.query = AMDGPU_INFO_MEMORY;

			ret = drmCommandWrite(drm_fd, DRM_AMDGPU_INFO, &request, sizeof(request));
			vramsize = vram_gtt.vram.total_heap_size;
			gttsize = vram_gtt.gtt.total_heap_size;
#else
			printf(("amdgpu DRM driver is used, but amdgpu VRAM size reporting is not enabled\n"));
#endif
		}
		if (ret) {
			printf(("Failed to get VRAM size, error %d\n"),
				ret);
			goto out;
		}

		ret = getvram();
		if (ret == 0) {
			if (AmdGpuDriver == _AmdGpuDriver::amdgpu) {
#ifndef ENABLE_AMDGPU
				printf(("amdgpu DRM driver is used, but amdgpu VRAM usage reporting is not enabled\n"));
#endif
			}
			printf(("Failed to get VRAM usage, kernel likely too old\n"));
			goto out;
		}

		bits.vram = 1;

		ret = getgtt();
		if (ret == 0) {
			if (AmdGpuDriver == _AmdGpuDriver::amdgpu) {
#ifndef ENABLE_AMDGPU
				printf(("amdgpu DRM driver is used, but amdgpu GTT usage reporting is not enabled\n"));
#endif
			}
			printf(("Failed to get GTT usage, kernel likely too old\n"));
			goto out;
		}

		bits.gtt = 1;

        /** integrated (a.h.a. fusion) GPU
        *   the driver returns zero.
        *   So, for once, we will read "max_memory_clock" info from device query method.
        */
        m_amdgpu_info inf(drm_fd);
        bFusion = inf.fusion_flag();
        if(bFusion)
        {
            amdgpu_dev_info query = {};
            inf.GetDevInfo(&query);
            igpu_mclk = query.max_memory_clock / 1000;
        }
    }

    out:

    pci_system_cleanup();

    return device_id;
}

int rdtop::getfamily(unsigned int id)
{
	switch(id) {
		#define CHIPSET(a,b,c) case a: return c;
		#include "r600_pci_ids.h"
		#undef CHIPSET
	}

	return 0;
}

unsigned long long rdtop::getvram()
{
    int ret = -1;
	unsigned long long val = 0;

	if (AmdGpuDriver == _AmdGpuDriver::radeon) {
		struct drm_radeon_info info;
		memset(&info, 0, sizeof(info));
		info.value = (unsigned long) &val;
		info.request = RADEON_INFO_VRAM_USAGE;

		ret = drmCommandWriteRead(drm_fd, DRM_RADEON_INFO, &info, sizeof(info));
	} else if (AmdGpuDriver == _AmdGpuDriver::amdgpu) {
#ifdef ENABLE_AMDGPU
		struct drm_amdgpu_info request;
		memset(&request, 0, sizeof(request));
		request.return_pointer = (unsigned long) &val;
		request.return_size = sizeof(val);
		request.query = AMDGPU_INFO_VRAM_USAGE;

		ret = drmCommandWrite(drm_fd, DRM_AMDGPU_INFO, &request, sizeof(request));
#endif
	}
	if (ret) return 0;

	return val;
}

unsigned long long rdtop::getgtt()
{
    int ret = -1;
	unsigned long long val = 0;

	if (AmdGpuDriver == _AmdGpuDriver::radeon) {
		struct drm_radeon_info info;
		memset(&info, 0, sizeof(info));
		info.value = (unsigned long) &val;
		info.request = RADEON_INFO_GTT_USAGE;

		ret = drmCommandWriteRead(drm_fd, DRM_RADEON_INFO, &info, sizeof(info));
	} else if (AmdGpuDriver == _AmdGpuDriver::amdgpu) {
#ifdef ENABLE_AMDGPU
		struct drm_amdgpu_info info;

		memset(&info, 0, sizeof(struct drm_amdgpu_info));
		info.query = AMDGPU_INFO_GTT_USAGE;
		info.return_pointer = (unsigned long)&val;
		info.return_size = sizeof(val);

		ret = drmCommandWriteRead(drm_fd, DRM_AMDGPU_INFO, &info, sizeof(info));
#endif
	}
	if (ret) return 0;

	return val;
}

unsigned int rdtop::get_sclk()
{
    int ret = -1;
	unsigned long long val = 0;

	if (AmdGpuDriver == _AmdGpuDriver::radeon)
    {
		struct drm_radeon_info info;
		memset(&info, 0, sizeof(info));
		info.value = (unsigned long) &val;
		info.request = RADEON_INFO_CURRENT_GPU_SCLK;

		ret = drmCommandWriteRead(drm_fd, DRM_RADEON_INFO, &info, sizeof(info));
	}
	else if (AmdGpuDriver == _AmdGpuDriver::amdgpu)
    {
#ifdef ENABLE_AMDGPU
		struct drm_amdgpu_info info;
		memset(&info, 0, sizeof(info));
		info.return_pointer = (unsigned long) &val;
		info.return_size = sizeof(val);
		info.query = AMDGPU_INFO_SENSOR;
		info.sensor_info.type = AMDGPU_INFO_SENSOR_GFX_SCLK;

		ret = drmCommandWriteRead(drm_fd, DRM_AMDGPU_INFO, &info, sizeof(info));
#endif
	}
	if (ret) return 0;

	return val;
}

unsigned int rdtop::get_mclk()
{
    int ret = -1;
	unsigned long long val = 0;

	if (AmdGpuDriver == _AmdGpuDriver::radeon)
    {
		struct drm_radeon_info info;
		memset(&info, 0, sizeof(info));
		info.value = (unsigned long) &val;
		info.request = RADEON_INFO_CURRENT_GPU_MCLK;

		ret = drmCommandWriteRead(drm_fd, DRM_RADEON_INFO, &info, sizeof(info));
	}
	else if (AmdGpuDriver == _AmdGpuDriver::amdgpu)
    {
#ifdef ENABLE_AMDGPU
		struct drm_amdgpu_info info;
		memset(&info, 0, sizeof(info));
		info.return_pointer = (unsigned long long) &val;
		info.return_size = sizeof(val);
		info.query = AMDGPU_INFO_SENSOR;
		info.sensor_info.type = AMDGPU_INFO_SENSOR_GFX_MCLK;

		ret = drmCommandWriteRead(drm_fd, DRM_AMDGPU_INFO, &info, sizeof(info));

		/** integrated (a.h.a. fusion) GPU */
		if(val == 0 && bFusion)
            return igpu_mclk;
#endif
	}
	if (ret) return 0;

	return val;
}


void rdtop::initbits(int fam)
{
    // The majority of these is the same from R600 to Southern Islands.

	bits.ee = (1U << 10);
	bits.vgt = (1U << 16) | (1U << 17);
	bits.ta = (1U << 14);
	bits.tc = (1U << 19);
	bits.sx = (1U << 20);
	bits.sh = (1U << 21);
	bits.spi = (1U << 22);
	bits.smx = (1U << 23);
	bits.sc = (1U << 24);
	bits.pa = (1U << 25);
	bits.db = (1U << 26);
	bits.cr = (1U << 27);
	bits.cb = (1U << 30);
	bits.gui = (1U << 31);

	// R600 has a different texture bit, and only R600 has the TC, CR, SMX bits
	if (fam < RV770) {
		bits.ta = (1U << 18);
	} else {
		bits.tc = 0;
		bits.cr = 0;
		bits.smx = 0;
	}
}

}

