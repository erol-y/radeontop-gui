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

#include "radeontop.h"


namespace radeontop {

rdtop::rdtop()
{
    bits = {};
    vramsize = 0;
    gttsize = 0;
    use_ioctl = 0;
    drm_fd = 0;
    family = 0;
    Ticks = 120;
    m_err = false;
    AmdGpuDriver = _AmdGpuDriver::not_amd;

}

rdtop::~rdtop()
{
    if(drm_fd > 0)
        drmClose(drm_fd);
}

bool rdtop::haserror() const
{
    return m_err;
}

bool rdtop::init_rdtop()
{
    unsigned int pciaddr = init_pci(0,0);
    if(haserror())
        return false;

    family = getfamily(pciaddr);
    if(!family)
    {
        std::cout << "Unknown Radeon card. <= R500 won't work, new cards might." << std::endl;
        m_err = true; // But won't return false!
    }

    initbits(family);
    collect();

    while(!results)
		usleep(16000);


    return true;
}

int rdtop::get_drm_value(int fd, unsigned request, uint32_t *out)
{
    int retval;

    if(AmdGpuDriver == _AmdGpuDriver::radeon)
    {
        struct drm_radeon_info info = {};
        info.value = (unsigned long)out;
        info.request = request;
        retval = drmCommandWriteRead(fd, DRM_RADEON_INFO, &info, sizeof(info));
        return !retval;
    }
	else if(AmdGpuDriver == _AmdGpuDriver::amdgpu)
    {
        struct drm_amdgpu_info info = {};
        info.return_pointer = (unsigned long)out;
        info.return_size = sizeof(*out);
        info.query = request;
        retval = drmCommandWriteRead(fd, DRM_AMDGPU_INFO, &info, sizeof(info));
        return !retval;
    }

	return -1;
}

unsigned int rdtop::readgrbm()
{
    if (use_ioctl) {
		uint32_t reg = GRBM_STATUS;
		get_drm_value(drm_fd, RADEON_INFO_READ_REG, &reg);
		return reg;
	} else {
	    return * (const unsigned int *) ((unsigned long)area + 0x10);
	}
}

void rdtop::set_driver_enum(const char * drm_name)
{
    if(strcmp(drm_name, "radeon") == 0)
        AmdGpuDriver = _AmdGpuDriver::radeon;
    else if(strcmp(drm_name, "amdgpu") == 0)
        AmdGpuDriver = _AmdGpuDriver::amdgpu;
    else
        AmdGpuDriver = _AmdGpuDriver::not_amd;
}

const char * rdtop::get_family_name() const
{
    return family_str[family];
}

void rdtop::get_drm_version(struct _m_drm_version * drm_ver)
{
    memcpy(drm_ver, &m_drm_version, sizeof(m_drm_version));
}

int rdtop::GetQueryR(unsigned long CommandIndex, void * data)
{
    int ret = -1;
    struct drm_radeon_info info;
    memset(&info, 0, sizeof(info));

    info.value = (unsigned long)data;
    info.request = CommandIndex;

    ret = drmCommandWriteRead(drm_fd, DRM_RADEON_INFO, &info, sizeof(info));

    return ret;

}

#ifdef ENABLE_AMDGPU

/**
    If subquery greater than zero (single mode), function returns queried value.
    Else, first parameter (pointer to struct) not null, it fills struct's elements
    and returns zero.
*/
unsigned long long m_amdgpu_info::ReadSensor(m_amdgpu_sensor *s, int subquery)
{
    unsigned long long val = 0;
    struct drm_amdgpu_info info;
    info.query = AMDGPU_INFO_SENSOR;

    if(subquery > 0) // Single Mode
    {
        info.sensor_info.type = subquery;
        info.return_pointer = (unsigned long long) &val;
        info.return_size = sizeof(val);

        drmCommandWriteRead(hDRM, DRM_AMDGPU_INFO, &info, sizeof(info));
        return val;
    }
    else if(s != NULL) // Batch Mode (Call "single mode" recursively)
    {
        s->gfx_sclk = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_GFX_SCLK);
        s->gfx_mclk = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_GFX_MCLK);
        s->gpu_temp = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_GPU_TEMP);
        s->gpu_load = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_GPU_LOAD);
        s->gpu_avg_power = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_GPU_AVG_POWER);
        s->vddnb = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_VDDNB);
        s->vddgfx = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_VDDGFX);
#ifdef AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK
        s->pstate_sclk = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK);
        s->pstate_mclk = this->ReadSensor(NULL, AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK);
#endif // AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK

        return 0; // it should return 0.
    }

    return -1; // Something went wrong!
}

bool m_amdgpu_info::GetDevInfo(amdgpu_dev_info * info)
{
    int ret = 0;
    drm_amdgpu_info i;
    i.return_pointer = (unsigned long long)info;
    i.return_size = sizeof(*info);
    i.query = AMDGPU_INFO_DEV_INFO;
    memset(info, 0, sizeof(*info));

    ret = drmCommandWriteRead(hDRM, DRM_AMDGPU_INFO, &i, sizeof(i));

    return (ret?false:true);
}

void m_amdgpu_info::GetQueryA(int query, unsigned long long * p, unsigned ret_size)
{
    int ret = 0;
    drm_amdgpu_info i;
    memset(&i, 0, sizeof(i));

    i.return_pointer = *p;
    i.return_size = ret_size;
    i.query = query;

    ret = drmCommandWriteRead(hDRM, DRM_AMDGPU_INFO, &i, sizeof(i));

    if(ret != 0)
       p = NULL;

    return;
}

std::map<unsigned char, drm_amdgpu_info_vce_clock_table_entry> m_amdgpu_info::GetClockTable(bool refresh)
{
    if(this->vce_clock_table.begin() == this->vce_clock_table.end() || refresh)
    {
        if(refresh)
            vce_clock_table.clear();

        struct drm_amdgpu_info_vce_clock_table table;
        memset(&table, 0, sizeof(table));
        struct drm_amdgpu_info info;
        memset(&info, 0, sizeof(info));
        info.return_pointer = (unsigned long long)&table;
        info.return_size = sizeof(table);
        info.query = AMDGPU_INFO_VCE_CLOCK_TABLE;

        drmCommandWriteRead(hDRM, DRM_AMDGPU_INFO, &info, sizeof(info));

        for(unsigned char i = 0; i < table.num_valid_entries; ++i)
            vce_clock_table.insert(std::make_pair(i, table.entries[i]));
    }

    return vce_clock_table;
}

bool m_amdgpu_info::fusion_flag()
{
#ifdef ENABLE_AMDGPU
    amdgpu_dev_info info = {};
    if(GetDevInfo(&info))
        if(info.ids_flags == AMDGPU_IDS_FLAGS_FUSION)
            return true;
#endif // ENABLE_AMDGPU
    return false;
}

// Constructor
m_amdgpu_info::m_amdgpu_info(int handle)
    : hDRM(handle)
{
}

// Destructor
m_amdgpu_info::~m_amdgpu_info()
{
}
#endif // ENABLE_AMDGPU
}

