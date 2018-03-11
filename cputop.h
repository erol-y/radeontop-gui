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

#include <iostream>
#include <cpufreq.h>

namespace cputop {


class cpufreq
{
public:
    unsigned char GetCpuCount();
    unsigned long GetFrequency(unsigned char cpu);
    bool GetFreqLimits(unsigned char, unsigned long *, unsigned long *);

private:
    bool isRoot;
    unsigned char CpuCount;
    void RealGetCpuCount();


public:
    cpufreq();
    ~cpufreq();
};


}
