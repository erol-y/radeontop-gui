/*
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

#include "cputop.h"


namespace cputop {

unsigned char cpufreq::GetCpuCount()
{
    this->RealGetCpuCount();
    return CpuCount;
}

void cpufreq::RealGetCpuCount()
{

    unsigned char i;

    for(i = 0; !cpufreq_cpu_exists(i); ++i) {}

    CpuCount = i;
}

unsigned long cpufreq::GetFrequency(unsigned char cpu)
{
    if(!isRoot)
        return cpufreq_get_freq_kernel(cpu);
    else
        return cpufreq_get_freq_hardware(cpu);
}

bool cpufreq::GetFreqLimits(unsigned char cpu, unsigned long * min, unsigned long * max)
{
    if(cpufreq_get_hardware_limits((unsigned int) cpu, min, max))
        return false;
    else
        return true;
}

cpufreq::cpufreq()
{
    cpufreq_get_freq_hardware(0)? isRoot = true :isRoot = false;
}

cpufreq::~cpufreq()
{

}

}
