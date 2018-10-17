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

#include "power.h"

ChargeStatus PowerSupply::GetBatteryStatus() const
{
    wxString status;
    Read(POWER_SUPPLY_STATUS, &status, wxString("UNKNOWN"));
    if(status == wxT("Charging"))
        return ChargeStatus::BAT_STAT_CHARGE;
    else if(status == wxT("Discharging"))
        return ChargeStatus::BAT_STAT_DISCHARGE;

    return ChargeStatus::BAT_STAT_UNKNOWN;
}

bool PowerSupply::GetBatteryVars(BatteryVariables * vars)
{
    bool b = true;
    wxString status;

    b &= this->Read(POWER_SUPPLY_VOLTAGE_NOW, &vars->voltage, 0);
    b &= this->Read(POWER_SUPPLY_CURRENT_NOW, &vars->current, 0);
    b &= this->Read(POWER_SUPPLY_CHARGE_NOW, &vars->charge, 0);

    vars->e_status = this->GetBatteryStatus();

    return b;
}

void PowerSupply::GetBatteryInfo(BatteryInfo * batInfo)
{
    Read(POWER_SUPPLY_NAME, &batInfo->name, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_STATUS, &batInfo->status, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_PRESENT, &batInfo->present, 0);
    Read(POWER_SUPPLY_TECHNOLOGY, &batInfo->technology, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_CYCLE_COUNT, &batInfo->cycles, 0);
    Read(POWER_SUPPLY_VOLTAGE_MIN_DESIGN, &batInfo->volt_min, 0);
    Read(POWER_SUPPLY_CHARGE_FULL_DESIGN, &batInfo->charge_at_label, 0);
    Read(POWER_SUPPLY_CHARGE_FULL, &batInfo->charge_real, 0);
    Read(POWER_SUPPLY_CAPACITY, &batInfo->capacity_percent, 0);
    Read(POWER_SUPPLY_CAPACITY_LEVEL, &batInfo->health, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_MODEL_NAME, &batInfo->model_name, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_MANUFACTURER, &batInfo->manufacturer, wxString("UNKNOWN"));
    Read(POWER_SUPPLY_SERIAL_NUMBER, &batInfo->serial, wxString("UNKNOWN"));
    GetBatteryVars(&batInfo->vars);

    return;
}

int PowerSupply::CalcBatChargeTime()
{
    BatteryVariables bv;
    if(GetBatteryVars(&bv) == false)
        return -1;

    int current = bv.current;
    int charge = bv.charge;
    int rsec = 0, sec;

    if(bv.e_status == ChargeStatus::BAT_STAT_CHARGE)
    {
        int m_real;
        Read(POWER_SUPPLY_CHARGE_FULL, &m_real, 0);
        rsec = (m_real - charge) * 60 * 60; //ampere-hour to ampere-seconds
    }
    else if(bv.e_status == ChargeStatus::BAT_STAT_DISCHARGE)
    {
        rsec = charge * 60 * 60;
    }

    if(rsec == 0 || current == 0)
        { sec = 0; }
    else
        { sec = rsec / current; }

    return sec;
}

PowerSupply::PowerSupply()
{
    m_error = false;
    conf = new wxFileConfig(wxEmptyString, wxEmptyString, POWER_BAT0_FILE_WITH_PATH);
    if(conf->GetNumberOfEntries() < 1)
    {
        m_error = true;
        return;
    }
    conf->SetRecordDefaults(false);
}

PowerSupply::~PowerSupply()
{
    delete conf;
}
