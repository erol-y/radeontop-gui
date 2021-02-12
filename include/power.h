/*
	Copyright (C) 2018 Erol Yesilyurt

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

#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

#include <wx/fileconf.h>

#define POWER_BAT0_PATH             wxT("/sys/class/power_supply/BAT0")
#define POWER_BAT0_FILE_NAME        wxT("uevent")
#define POWER_BAT0_FILE_WITH_PATH   wxT("/sys/class/power_supply/BAT0/uevent")

enum {
    POWER_SUPPLY_NAME   = 0,
    POWER_SUPPLY_STATUS,
    POWER_SUPPLY_PRESENT,
    POWER_SUPPLY_TECHNOLOGY,
    POWER_SUPPLY_CYCLE_COUNT,
    POWER_SUPPLY_VOLTAGE_MIN_DESIGN,
    POWER_SUPPLY_VOLTAGE_NOW,
    POWER_SUPPLY_CURRENT_NOW,
    POWER_SUPPLY_CHARGE_FULL_DESIGN,
    POWER_SUPPLY_CHARGE_FULL,
    POWER_SUPPLY_CHARGE_NOW,
    POWER_SUPPLY_CAPACITY,
    POWER_SUPPLY_CAPACITY_LEVEL,
    POWER_SUPPLY_MODEL_NAME,
    POWER_SUPPLY_MANUFACTURER,
    POWER_SUPPLY_SERIAL_NUMBER,
    NO_MORE_ENUM
};

static const char * PowerKeys[] = {
    [POWER_SUPPLY_NAME] =               "POWER_SUPPLY_NAME",
    [POWER_SUPPLY_STATUS] =             "POWER_SUPPLY_STATUS",
    [POWER_SUPPLY_PRESENT] =            "POWER_SUPPLY_PRESENT",
    [POWER_SUPPLY_TECHNOLOGY] =         "POWER_SUPPLY_TECHNOLOGY",
    [POWER_SUPPLY_CYCLE_COUNT] =        "POWER_SUPPLY_CYCLE_COUNT",
    [POWER_SUPPLY_VOLTAGE_MIN_DESIGN] = "POWER_SUPPLY_VOLTAGE_MIN_DESIGN",
    [POWER_SUPPLY_VOLTAGE_NOW] =        "POWER_SUPPLY_VOLTAGE_NOW",
    [POWER_SUPPLY_CURRENT_NOW] =        "POWER_SUPPLY_CURRENT_NOW",
    [POWER_SUPPLY_CHARGE_FULL_DESIGN] = "POWER_SUPPLY_CHARGE_FULL_DESIGN",
    [POWER_SUPPLY_CHARGE_FULL] =        "POWER_SUPPLY_CHARGE_FULL",
    [POWER_SUPPLY_CHARGE_NOW] =         "POWER_SUPPLY_CHARGE_NOW",
    [POWER_SUPPLY_CAPACITY] =           "POWER_SUPPLY_CAPACITY",
    [POWER_SUPPLY_CAPACITY_LEVEL] =     "POWER_SUPPLY_CAPACITY_LEVEL",
    [POWER_SUPPLY_MODEL_NAME] =         "POWER_SUPPLY_MODEL_NAME",
    [POWER_SUPPLY_MANUFACTURER] =       "POWER_SUPPLY_MANUFACTURER",
    [POWER_SUPPLY_SERIAL_NUMBER] =      "POWER_SUPPLY_SERIAL_NUMBER",
    [NO_MORE_ENUM] =                    ""
};

enum ChargeStatus{
    BAT_STAT_CHARGE,
    BAT_STAT_DISCHARGE,
    BAT_STAT_UNKNOWN
};

///NOWs
struct BatteryVariables
{
    int voltage;                    //POWER_SUPPLY_VOLTAGE_NOW
    int current;                    //POWER_SUPPLY_CURRENT_NOW
    int charge;                     //POWER_SUPPLY_CHARGE_NOW
    ChargeStatus e_status;

};

struct BatteryInfo
{
    wxString name;                  //POWER_SUPPLY_NAME
    wxString status;                //POWER_SUPPLY_STATUS
    int present;                    //POWER_SUPPLY_PRESENT
    wxString technology;            //POWER_SUPPLY_TECHNOLOGY
    int cycles;                     //POWER_SUPPLY_CYCLE_COUNT
    int volt_min;                   //POWER_SUPPLY_VOLTAGE_MIN_DESIGN
    int charge_at_label;            //POWER_SUPPLY_CHARGE_FULL_DESIGN
    int charge_real;                //POWER_SUPPLY_CHARGE_FULL
    int capacity_percent;           //POWER_SUPPLY_CAPACITY
    wxString health;                //POWER_SUPPLY_CAPACITY_LEVEL
    wxString model_name;            //POWER_SUPPLY_MODEL_NAME
    wxString manufacturer;          //POWER_SUPPLY_MANUFACTURER
    wxString serial;                //POWER_SUPPLY_SERIAL_NUMBER
    struct BatteryVariables vars;
};

class PowerSupply
{
public:
    static bool HasBattery() { return wxFileName::DirExists(POWER_BAT0_PATH); }

    bool isError() const { return m_error; }
    ChargeStatus GetBatteryStatus() const;
    bool GetBatteryVars(BatteryVariables *);
    void GetBatteryInfo(BatteryInfo *);
    int CalcBatChargeTime();

    template <typename T>
    bool Read(int e, T *val) const
    {
        bool b;
        b = conf->Read(PowerKeys[e], val);
        return b;
    }

    template <typename T>
    bool Read(int e, T *val, const T& defVal) const
    {
        bool b;
        b = conf->Read(PowerKeys[e], val);
        if(!b)
        {
            *val = defVal;
        }

        return b;
    }

    PowerSupply();
    ~PowerSupply();

private:
    wxFileConfig * conf;
    bool m_error;

    wxDECLARE_NO_COPY_CLASS(PowerSupply);
};

#endif // POWER_H_INCLUDED
