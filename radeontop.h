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

#ifndef RADEONTOP_H_INCLUDED
#define RADEONTOP_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <xf86drm.h>
#include <radeon_drm.h>
#ifdef ENABLE_AMDGPU
#include <amdgpu_drm.h>
#endif


namespace radeontop {

enum {
	GRBM_STATUS = 0x8010,
	MMAP_SIZE = 0x14
};

#ifndef RADEON_INFO_VRAM_USAGE
#define RADEON_INFO_VRAM_USAGE 0x1e
#endif
#ifndef RADEON_INFO_READ_REG
#define RADEON_INFO_READ_REG 0x24
#endif

extern const char * const family_str[];
extern struct bits_t * results;

struct bits_t {
	unsigned int ee;
	unsigned int vgt;
	unsigned int gui;
	unsigned int ta;
	unsigned int tc;
	unsigned int sx;
	unsigned int sh;
	unsigned int spi;
	unsigned int smx;
	unsigned int sc;
	unsigned int pa;
	unsigned int db;
	unsigned int cb;
	unsigned int cr;
	unsigned long long vram;
	unsigned long long gtt;
	unsigned int sclk;
	unsigned int mclk;
};


class rdtop
{
    public:
        //struct bits_t bits;
        unsigned long long vramsize;
        unsigned long long gttsize;

        bool haserror();
        bool init_rdtop();
        int get_ticks() const {return ticks;}
        struct bits_t get_bits() const {return bits;}
        const char * const get_family_name();
        unsigned int readgrbm();
        unsigned long long getvram();
        unsigned long long getgtt();
        unsigned int get_sclk();
        unsigned int get_mclk();

        rdtop();
        ~rdtop();

    private:
        bool m_err;
        struct bits_t bits;

        //detect.cpp
        unsigned int init_pci(unsigned char, const unsigned char);
        int getfamily(unsigned int);
        void initbits(int);
        int drm_fd;
        char drm_name[10];
        int use_ioctl;

        //radeon.cpp
        int get_drm_value(int, unsigned, uint32_t *);
        unsigned int readgrbm2();
        unsigned int ticks;
        const void * area;
        int family;
        //char * cardname;

        //auth.cpp
        void authenticate_drm(int);

        //ticks.cpp
        void collect(unsigned int *, void *);
        static void * collector(void *);

};

// bits

// chips
enum radeon_family {
	UNKNOWN_CHIP,
	R600,
	RV610,
	RV630,
	RV670,
	RV620,
	RV635,
	RS780,
	RS880,
	RV770,
	RV730,
	RV710,
	RV740,
	CEDAR,
	REDWOOD,
	JUNIPER,
	CYPRESS,
	HEMLOCK,
	PALM,
	SUMO,
	SUMO2,
	BARTS,
	TURKS,
	CAICOS,
	CAYMAN,
	ARUBA,
	TAHITI,
	PITCAIRN,
	VERDE,
	OLAND,
	HAINAN,
	BONAIRE,
	KABINI,
	MULLINS,
	KAVERI,
	HAWAII,
	TOPAZ,
	TONGA,
	FIJI,
	CARRIZO,
	STONEY,
	POLARIS11,
	POLARIS10,
	POLARIS12,
	VEGA10,
};


}
#endif // RADEONTOP_H_INCLUDED
