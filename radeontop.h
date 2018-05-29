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
#include <map>
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

#ifdef ENABLE_AMDGPU
typedef struct drm_amdgpu_info_device amdgpu_dev_info;
typedef struct drm_amdgpu_info_num_handles amdgpu_uvd_handles;

#define VRAM_TYPE_UNKNOWN   AMDGPU_VRAM_TYPE_UNKNOWN
#define VRAM_TYPE_GDDR1     AMDGPU_VRAM_TYPE_GDDR1
#define VRAM_TYPE_DDR2      AMDGPU_VRAM_TYPE_DDR2
#define VRAM_TYPE_GDDR3     AMDGPU_VRAM_TYPE_GDDR3
#define VRAM_TYPE_GDDR4     AMDGPU_VRAM_TYPE_GDDR4
#define VRAM_TYPE_GDDR5     AMDGPU_VRAM_TYPE_GDDR5
#define VRAM_TYPE_HBM       AMDGPU_VRAM_TYPE_HBM
#define VRAM_TYPE_DDR3      AMDGPU_VRAM_TYPE_DDR3

#endif // ENABLE_AMDGPU

struct m_amdgpu_sensor
{
    unsigned int gfx_sclk;
    unsigned int gfx_mclk;
    int gpu_temp;
    unsigned int gpu_load;
    unsigned int gpu_avg_power;
    unsigned int vddnb;
    unsigned int vddgfx;
#ifdef AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK
    unsigned int pstate_sclk;
    unsigned int pstate_mclk;
    m_amdgpu_sensor()
        : gfx_sclk(0), gfx_mclk(0), gpu_temp(0), gpu_load(0), gpu_avg_power(0), vddnb(0), vddgfx(0),
        pstate_sclk(0), pstate_mclk(0)
        {}
#else
    m_amdgpu_sensor()
        : gfx_sclk(0), gfx_mclk(0), gpu_temp(0), gpu_load(0), gpu_avg_power(0), vddnb(0), vddgfx(0)
        {}
#endif // AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK

};

struct _m_drm_version
{
    int version_major;
    int version_minor;
    int version_patchlevel;
};

class m_amdgpu_info
{
public:
    unsigned long long ReadSensor(m_amdgpu_sensor *, int);
    bool GetDevInfo(amdgpu_dev_info *);
    void GetQueryA(int, unsigned long long *, unsigned); //Query, ret_addr, ret_size
    std::map<unsigned char, drm_amdgpu_info_vce_clock_table_entry> GetClockTable(bool = false); //bool refresh = false

    m_amdgpu_info(int);
    ~m_amdgpu_info();

private:
    int hDRM;
    std::map<unsigned char, drm_amdgpu_info_vce_clock_table_entry> vce_clock_table;

};

class rdtop
{
    public:
        unsigned long long vramsize;
        unsigned long long gttsize;

        bool haserror() const;
        bool init_rdtop();
        int get_ticks() { return ticks; }
        struct bits_t get_bits() const { return bits; }
        int get_drm_handle() const { return drm_fd; }
        const char * get_drm_name() const { return drm_name; }
        void get_drm_version(struct _m_drm_version *);
        const char * get_str_busid() const { return busid; }
        const char * get_str_devid() const { return devid; }
        const char * get_str_devpath() const { return devpath; }
        const char * get_family_name() const;
        unsigned int readgrbm();
        unsigned long long getvram();
        unsigned long long getgtt();
        unsigned int get_sclk();
        unsigned int get_mclk();
        int GetQueryR(unsigned long, void *);

        rdtop();
        ~rdtop();

    private:
        bool m_err;
        struct bits_t bits;
        struct _m_drm_version m_drm_version;

        //detect.cpp
        unsigned int init_pci(unsigned char, const unsigned char);
        int getfamily(unsigned int);
        void initbits(int);
        int drm_fd;
        char busid[32];
        char devid[64];
        char devpath[16];
        char drm_name[10];
        int use_ioctl;

        //radeon.cpp
        int get_drm_value(int, unsigned, uint32_t *);
        //unsigned int readgrbm2();
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
	RAVEN,
};


}
#endif // RADEONTOP_H_INCLUDED
