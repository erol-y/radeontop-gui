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

#include "../include/rdt_guiMain.h"
#include "../include/conf.h"

static ConfigFile * cfg = NULL;

void PowerWindow::OnPowerClose(wxCloseEvent& event)
{
    rdt_guiFrame * f = (rdt_guiFrame *)GetParent();
    f->DestroyDialogWindow(this);

    wxUnusedVar(event);
}

PowerWindow::PowerWindow(wxWindow * parent)
    : PowerFrame(parent)
{
    this->pconf = new PowerSupply();
    this->BatteryInit();
    this->Show();
}

PowerWindow::~PowerWindow()
{
    if(pconf != NULL)
        delete pconf;

    cfg = ConfigFile::GetConfigFile();
    if(cfg != NULL)
    {
        wxSize s = this->GetSize();
        if(ConfigFile::GetConfigFile() != NULL)
        {
            cfg->cfgWrite(ConfKeyEnums::PWR_GUI_SIZER_X, s.GetX());
            cfg->cfgWrite(ConfKeyEnums::PWR_GUI_SIZER_Y, s.GetY());
        }
    }
}

void PowerWindow::BatteryInit()
{
    if(this->pconf->isError() == true)
    {
        this->SetStatusText(wxT("There is no power data!"), 0);
        return;
    }

    int x, y;
    if(ConfigFile::GetConfigFile() != NULL)
    {
        if(cfg->cfgRead(ConfKeyEnums::PWR_GUI_SIZER_X, &x) &&
            cfg->cfgRead(ConfKeyEnums::PWR_GUI_SIZER_Y, &y))
        {
            SetSize(x,y);
        }
    }

    this->milisec = 1000;
    m_timer_pf.Start(milisec);

    pconf->GetBatteryInfo(&this->bi);

    SetStatusText(bi.manufacturer + wxT(" ") + bi.model_name, 0);
    SetStatusText(wxT("STATUS: ") + bi.status, 1);
    SetStatusText(wxT("HEALTH: ") + bi.health, 2);

    Layout();
}

static int AvgCurr = 0, AvgCurr_delta = 0;

void PowerWindow::UpdatePowerFrame(wxTimerEvent& event)
{
    BatteryVariables bv = {};
    wxString label("Capacity:\t");
    int prcnt;
    float m_volt;
    float m_curr;

    // Every time, it must re-construct the wxFileConfig!
    if(pconf != NULL)
        delete pconf;
    pconf = new PowerSupply();

    pconf->GetBatteryVars(&bv);

    int ful, stat;
    ful = bi.charge_real;
    stat = bv.charge;
    if(stat == ful) // it seems full.
        {label.append("~100%");}

    if(stat <= ful/4 /*25%*/)
        { m_staticText_rate->SetForegroundColour( wxColour(wxT("RED")) ); }
    else if(stat < (ful * 4/5) /*80%*/)
        { m_staticText_rate->SetForegroundColour( wxColour(wxT("BLACK")) ); }
    else
        { m_staticText_rate->SetForegroundColour( wxColour(wxT("GREEN")) ); }

    pconf->Read(POWER_SUPPLY_CAPACITY, &prcnt, 0);
    label.append(wxString::Format("%d %%", prcnt));

    int sec = pconf->CalcBatChargeTime();
    if(sec > 0)
        label.append(wxString::Format("\t%d:%.2d", sec/60, sec%60));

     m_staticText_rate->SetLabel(label);
     m_gauge_rate->SetValue(prcnt);

     wxString m_status;
     pconf->Read(POWER_SUPPLY_STATUS, &m_status, wxString("UNKNOWN"));
     SetStatusText(wxT("STATUS: ") + m_status, 1);

    tc_Current->SetValue( wxString::Format("%dmA", bv.current/1000) );
    // It calculates avarage current only while discharging.
    if(bv.e_status == ChargeStatus::BAT_STAT_DISCHARGE)
    {
        if(AvgCurr == 0)
        {
            AvgCurr = bv.current;
        }
        else
        {
            AvgCurr_delta = AvgCurr + bv.current;
            AvgCurr = AvgCurr_delta /2;
        }
        tc_CurrentAvg->SetValue(wxString::Format("%dmA", AvgCurr/1000));
        st_CurrentAvg->Show();
        tc_CurrentAvg->Show();
    }
    else
    {
        st_CurrentAvg->Show(false);
        tc_CurrentAvg->Show(false);
    }

    m_volt = bv.voltage / 1.0e6;
    tc_Voltage->SetValue(wxString::Format("%.3fV", m_volt));

    // Power
    m_curr = bv.current / 1.0e6;
    tc_Power->SetValue(wxString::Format("%.3fW", m_volt * m_curr));

     wxUnusedVar(event);
}
