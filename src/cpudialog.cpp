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

#include "rdt_guiMain.h"
#include "conf.h"

static ConfigFile * cfg = NULL;

void CpuDialog::OnCpuDialogClose(wxCloseEvent& event)
{
    rdtFrame->DestroyDialogWindow(this);
     wxUnusedVar(event);
}

CpuDialog::CpuDialog(wxWindow * parent)
    : CpuQueryDialog(parent)
{
    this->rdtFrame = (rdt_guiFrame *) parent;
    this->cfq = new cputop::cpufreq();
    unsigned char cc = cfq->GetCpuCount();

    this->timer_cpu.Start(this->rdtFrame->GetTimerVal());

    cfg = ConfigFile::GetConfigFile();
    cfg->cfgRead(ConfKeyEnums::CPU_GUI_SHOW_AVARAGE, &isAvg, false);
    m_checkBox_avg->SetValue(isAvg);
    wxCommandEvent e(wxEVT_COMMAND_CHECKBOX_CLICKED);
    OnCheckBoxAvg(e);

    int width, height;
    if( cfg->cfgRead(ConfKeyEnums::CPU_GUI_SIZER_X, &width) &&
        cfg->cfgRead(ConfKeyEnums::CPU_GUI_SIZER_Y, &height) )
    {
        this->SetSize(width, height);

        m_scrolledWindow1->Layout();
    }

    for(unsigned char i = 0; i < cc; ++i)
    {
        wxStaticText * st = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxString::Format("CPU-%d", i), wxDefaultPosition, wxDefaultSize, 0 );
        st->Wrap(-1);
        scrolledSizer->Add( st, 0, wxALL, 5 );


        wxGauge * ga;
        ga = new wxGauge(m_scrolledWindow1, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL|wxGA_SMOOTH );
        ga->SetValue(0);
        ga->SetMinSize( wxSize( -1,15 ) );

        scrolledSizer->Add( ga, 0, wxALL|wxEXPAND, 5 );

        mapCpuWindowElements.insert(std::make_pair(st, ga));
        mapCPU.insert(std::make_pair(i, mapCpuWindowElements.find(st)));
    }

    unsigned char x = 0;
    if(cc >= 4)
    {
        m_choice_limit->Append("4");
        short t = cc-4;
        x = 2;
        while( t > 0 )
        {
            m_choice_limit->Append(wxString::Format("%d", x*4));
            t = t-4;
            if(t < 4+1)
                break;
            x = x+1;
        }

    }

    int y = 0;
    if( cfg->cfgRead(ConfKeyEnums::CPU_GUI_LIMIT_COUNT, &y, 0) )
    {
        if( (unsigned char)y > x ) y = 1;
        m_choice_limit->SetSelection(y);
        m_choice_limit->SendSelectionChangedEvent(wxEVT_COMMAND_CHOICE_SELECTED);
    }
    else
    {
        m_choice_limit->SetSelection( cc >= 4? 2: 0 ); //Initial behavior: show all, if cc less than 4.
        m_choice_limit->SendSelectionChangedEvent(wxEVT_COMMAND_CHOICE_SELECTED);
    }

}

void CpuDialog::OnChoiceCpuLimit(wxCommandEvent& event)
{
    unsigned char cc = cfq->GetCpuCount();
    unsigned char y = m_choice_limit->GetSelection();
    std::map<unsigned char, std::map<wxStaticText *, wxGauge *>::iterator>::iterator itr;

    if(y == 0) //Show all
        y = cc;
    else if(y == 1) //Show none
        y = 0;
    else
        y = (y - 1) * 4;

    for(; cc > y; --cc)
    {
        itr = mapCPU.find(cc-1);
        if(itr == mapCPU.end())
            break;
        itr->second->first->Hide();
        itr->second->second->Hide();
    }

    for(; y > 0; --y)
    {
        itr = mapCPU.find(y-1);
        if(itr == mapCPU.end())
            break;
        itr->second->first->Show();
        itr->second->second->Show();
    }
    this->Layout();
    cfg->cfgWrite(ConfKeyEnums::CPU_GUI_LIMIT_COUNT, m_choice_limit->GetSelection());

    wxUnusedVar(event);
}

void CpuDialog::OnCheckBoxAvg(wxCommandEvent& event)
{
    this->isAvg = m_checkBox_avg->IsChecked();
    if(isAvg)
    {
        if(mapAvg.begin() == mapAvg.end()) //This condition is always true :)
        {
            this->cAvg = 2;
            unsigned char cc = cfq->GetCpuCount();
            for(unsigned char i = 0; i < cc; ++i)
                mapAvg.insert(std::make_pair( i, cfq->GetFrequency(i) ));
        }
    }
    else
    {
        mapAvg.clear();
    }

    cfg->cfgWrite(ConfKeyEnums::CPU_GUI_SHOW_AVARAGE, isAvg);
    wxUnusedVar(event);
}

void CpuDialog::UpdateCpuVal(wxTimerEvent& event)
{
    std::map<unsigned char, std::map<wxStaticText *, wxGauge *>::iterator>::iterator itr;
    std::map<unsigned char, unsigned long>::iterator itrAvg;
    unsigned char cc = cfq->GetCpuCount();
    unsigned char i = 0;
    unsigned long min = 0;
    unsigned long max = 0;
    unsigned long j = 0;
    unsigned long r = 0;

    for(; i < cc; ++i)
    {
        if(!cfq->GetFreqLimits(i, &min, &max))
        {
            //Simple debug output.
            printf("ERROR! GetFreqLimits(cpu = %d)\n", i);
            break;
        }

        itr = mapCPU.find(i);
        if(itr == mapCPU.end())
        {
            printf("ERROR! CPU:%d not mapped.\n", i);
            break;
        }

        j = cfq->GetFrequency(i);
        if(this->isAvg)
        {
            itrAvg = mapAvg.find(i);
            if(itrAvg == mapAvg.end())
            {
                printf("ERROR! CPU:%d not mapped. Func:%s Line:%d\n", i, __FUNCTION__, __LINE__);
                return;
            }
            unsigned long t = 0;
            t = itrAvg->second;
            t = (t + j);
            if(i == (cc -1))
                this->cAvg++;
            itrAvg->second = t;
            t = t / cAvg;
            r = r + t;
            itr->second->first->SetLabel(wxString::Format("CPU-%d\t %.2fGHZ", i, (float)t /1.0e6));
            itr->second->second->SetRange( t <= max? (max - min): (t - min) );
            itr->second->second->SetValue( ( t <= min? 0: (t-min) ) );
        }
        else //Realtime
        {
            r = r + j;
            itr->second->first->SetLabel(wxString::Format("CPU-%d \t %.2fGHZ", i, (float)j /1.0e6));
            itr->second->second->SetRange( j <= max? (max - min): (j - min) ); // Core boost
            itr->second->second->SetValue( ( j <= min? 0: (j-min) ) );
        }
    }

    r = (unsigned long) ((float)r / (float)i);
    m_staticText_reduced->SetLabel(wxString::Format("Reduced:\t %.2fGHz", (float)r / 1.0e6));
    m_gauge_reduced->SetRange( r <= max? (max - min): (r - min) );
    m_gauge_reduced->SetValue( r <= min? 0: (r-min) );

    wxUnusedVar(event);
}

void CpuDialog::SetTimerVal(int _sec)
{
    timer_cpu.Stop();
    timer_cpu.Start(_sec);
}

CpuDialog::~CpuDialog()
{
    wxSize s = this->GetSize();
    if(ConfigFile::GetConfigFile() != NULL)
    {
        cfg->cfgWrite(ConfKeyEnums::CPU_GUI_SIZER_X, s.GetX());
        cfg->cfgWrite(ConfKeyEnums::CPU_GUI_SIZER_Y, s.GetY());
    }
    delete cfq;
}
