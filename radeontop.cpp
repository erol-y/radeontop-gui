/*
	Copyright (C) 2012 Lauri Kasanen

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
    //bits = 0;
    vramsize = 0;
    gttsize = 0;
    use_ioctl = 0;
    family = 0;
    ticks = 120;
    m_err = false;

}

rdtop::~rdtop()
{

}

bool rdtop::haserror()
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
    collect(&ticks, this);

    while(!results)
		usleep(16000);


    return true;
}

int rdtop::get_drm_value(int fd, unsigned request, uint32_t *out)
{
    struct drm_radeon_info info;
    int retval;

    memset(&info, 0, sizeof(info));

	info.value = (unsigned long)out;
	info.request = request;

	retval = drmCommandWriteRead(fd, DRM_RADEON_INFO, &info, sizeof(info));
	return !retval;
}

unsigned int rdtop::readgrbm()
{
    if (use_ioctl) {
		uint32_t reg = 0x8010;
		get_drm_value(drm_fd, RADEON_INFO_READ_REG, &reg);
		return reg;
	} else {
	    return * (const unsigned int *) (area + 0x10);
	}
}


const char * const rdtop::get_family_name()
{
    return family_str[family];
}

}

