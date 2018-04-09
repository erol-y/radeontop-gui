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

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include "rdt_guiMain.h"


rdt_guiFrame::rdt_guiFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    rdt = NULL;
    qd = NULL;
    msec = -1;
    memset(&m_drm_ver, 0, sizeof(m_drm_ver));
    Sizer1Size = bSizer1->GetSize();
}

rdt_guiFrame::~rdt_guiFrame()
{
}

void rdt_guiFrame::SetMenuPresent()
{
    statusBar->SetStatusText(rdt->get_family_name(), 0);
    statusBar->FitInside();

    //R600
    struct radeontop::bits_t r6bits = rdt->get_bits();
    if(!r6bits.tc)
        this->mviewstats_tc->Enable(false);
    if(!r6bits.smx)
        this->mviewstats_smx->Enable(false);
    if(!r6bits.cr)
        this->mviewstats_cr->Enable(false);
}

void rdt_guiFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
    wxUnusedVar(event);
}

void rdt_guiFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
    wxUnusedVar(event);
}

void rdt_guiFrame::OnAbout(wxCommandEvent &event)
{
    wxString title = wxT("Radeontop GUI");
    wxMessageBox(wxString::Format("%s %s", title, _(VERSION)), title);
    wxUnusedVar(event);
}

void rdt_guiFrame::OnSize(wxSizeEvent& event)
{
    Sizer1Size = bSizer1->GetSize();
    event.Skip();
}

void rdt_guiFrame::mSetTimerVal(int _sec, bool bStart = false)
{
    msec = _sec;
    if(bStart)
        m_timer1.Start(_sec);
}

void rdt_guiFrame::UpdateVal(wxTimerEvent& event)
{
#define _ShowVal(a,b,c,d) a = 100.0 * (float) radeontop::results->a / rdt->get_ticks(); \
        b->SetLabel(wxString::Format("%s:      %6.2f%%", d, a)); \
        c->SetValue((int) a);


    float gui;
    _ShowVal(gui, m_staticText_gui, m_gauge_gui, wxT("Graphics Pipe"))
    //float gui = 100.0 * (float) radeontop::results->gui / rdt->get_ticks();
    //m_staticText_gui->SetLabel(wxString::Format("Graphics Pipe:      %6.2f%%", gui));
    //m_gauge_gui->SetValue((int)gui);

    float ee;
    _ShowVal(ee, m_staticText_ee, m_gauge_ee, wxT("Event Engine"))

    float vgt;
    _ShowVal(vgt, m_staticText_vgt, m_gauge_vgt, wxT("Vertex Grouper + Tesselator"))

    float ta;
    _ShowVal(ta, m_staticText_ta, m_gauge_ta, wxT("Texture Addresser"))

    if(rdt->get_bits().tc)
    {
        float tc;
        _ShowVal(tc, m_staticText_tc, m_gauge_tc, wxT("Texture Cache"))
    }

    float sx;
    _ShowVal(sx, m_staticText_sx, m_gauge_sx, wxT("Shader Export"))

    float sh;
    _ShowVal(sh, m_staticText_sh, m_gauge_sh, wxT("Sequencer Instruction Cache"))

    float spi;
    _ShowVal(spi, m_staticText_spi, m_gauge_spi, wxT("Shader Interpolator"))

    if(rdt->get_bits().smx)
    {
        float smx;
        _ShowVal(smx, m_staticText_smx, m_gauge_smx, wxT("Shader Memory Exchange"))
    }

    float sc;
    _ShowVal(sc, m_staticText_sc, m_gauge_sc, wxT("Scan Converter"))

    float pa;
    _ShowVal(pa, m_staticText_pa, m_gauge_pa, wxT("Primitive Assembly"))

    float db;
    _ShowVal(db, m_staticText_db, m_gauge_db, wxT("Depth Block"))

    float cb;
    _ShowVal(cb, m_staticText_cb, m_gauge_cb, wxT("Color Block"))

    if(rdt->get_bits().cr)
    {
        float cr;
        _ShowVal(cr, m_staticText_cr, m_gauge_cr, wxT("Clip Rectangle"))
    }
#undef _ShowVal

    m_staticText_vram->SetLabel(wxString::Format("VRAM  Total: %dM   /   Used: %dM",
                                             (int)(rdt->vramsize / 1024 / 1024),
                                             (int)(radeontop::results->vram / 1024 / 1024)));

    m_gauge_vram->SetRange(rdt->vramsize / 1024 / 1024);
    m_gauge_vram->SetValue((int)(radeontop::results->vram > rdt->vramsize) ?
                                rdt->vramsize : radeontop::results->vram / 1024 / 1024);

    m_staticText_gtt->SetLabel(wxString::Format("GTT  Total: %dM   /   Used: %dM",
                                                (int)(rdt->gttsize / 1024 / 1024),
                                                (int)(radeontop::results->gtt / 1024 / 1024)));

    m_gauge_gtt->SetRange((int) (rdt->gttsize / 1024 / 1024));
    m_gauge_gtt->SetValue((unsigned int)(radeontop::results->gtt > rdt->gttsize) ?
                          rdt->gttsize : (radeontop::results->gtt / 1024 / 1024));


    statusBar->SetStatusText(wxString::Format("core: %dMhz / vmem: %dMhz",
                                              (int)radeontop::results->sclk, (int)radeontop::results->mclk),1);

    event.Skip();
}

#define _OnViewSelect(a,b) if(event.IsChecked()) \
                                { a->Show(); \
                                b->Show(); \
                                bSizer1->SetMinSize(Sizer1Size.GetWidth(), -1); \
                                this->Fit(); \
                                this->Layout(); } \
                            else if(!event.IsChecked()) \
                                { a->Show(false); \
                                b->Show(false); \
                                bSizer1->SetMinSize(Sizer1Size.GetWidth(), -1); \
                                this->Fit(); \
                                this->Layout(); }


void rdt_guiFrame::OnViewStats_gui(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_gui, m_gauge_gui)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_ee(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_ee, m_gauge_ee)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_vgt(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_vgt, m_gauge_vgt)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_ta(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_ta, m_gauge_ta)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_tc(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_tc, m_gauge_tc)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_sx(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_sx, m_gauge_sx)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_sh(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_sh, m_gauge_sh)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_spi(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_spi, m_gauge_spi)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_smx(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_smx, m_gauge_smx)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_sc(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_sc, m_gauge_sc)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_pa(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_pa, m_gauge_pa)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_db(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_db, m_gauge_db)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_cb(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_cb, m_gauge_cb)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_cr(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_cr, m_gauge_cr)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_vram(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_vram, m_gauge_vram)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_gtt(wxCommandEvent& event)
{
    _OnViewSelect(m_staticText_gtt, m_gauge_gtt)
    event.Skip();
}
#undef _OnViewSelect

void rdt_guiFrame::DestroyDialogWindow(wxDialog * wxid)
{
    if(wxid == qd)
    {
        qd->Show(false);
        delete qd;
        mviewQuery->Check(false);
    }
    else if(wxid == cd)
    {
        cd->Show(false);
        delete cd;
        mviewCPU->Check(false);
    }

}

void rdt_guiFrame::OnQuery(wxCommandEvent& event)
{
    if(event.IsChecked())
    {
        this->qd = new QDialog(this);
        qd->Show(true);
    }
    else if(!event.IsChecked())
    {
        qd->Show(false);
        delete qd;
        this->mviewQuery->Check(false);
    }

    event.Skip();
}


QDialog::QDialog(wxWindow * parent)
    : QueryDialog(parent)
{
    rdtFrame = (rdt_guiFrame *) parent;
    wxLog::SetActiveTarget(new wxLogTextCtrl(QtextCtrl1));

    wxLogMessage("Bus: %s", rdtFrame->rdt->get_str_busid());
    wxLogMessage("%s", rdtFrame->rdt->get_str_devid());
    wxLogMessage("Path: %s",rdtFrame->rdt->get_str_devpath());
    wxLogMessage("Driver: %s  %u.%u.%u\n",
                 rdtFrame->rdt->get_drm_name(),
                 rdtFrame->m_drm_ver.version_major,
                 rdtFrame->m_drm_ver.version_minor,
                 rdtFrame->m_drm_ver.version_patchlevel);

    if(rdtFrame->rdt != NULL && !rdtFrame->rdt->haserror())
    {
        if (strcmp(rdtFrame->rdt->get_drm_name(), "radeon") == 0)
        {
            QchoiceAMD->Hide();
            bSizer2->Remove((wxSizer*) QchoiceAMD);
        }
        else if(strcmp(rdtFrame->rdt->get_drm_name(), "amdgpu") == 0)
        {
            QchoiceRadeon->Hide();
        }
    }
    else
    {
        QchoiceAMD->Hide();
        QchoiceRadeon->Enable(false);
    }
}

QDialog::~QDialog()
{

}

void QDialog::OnQueryClose(wxCloseEvent& event)
{
    rdtFrame->DestroyDialogWindow(this);
    wxUnusedVar(event);
}

void QDialog::OnQChoiceR(wxCommandEvent& event)
{
    if (strcmp(rdtFrame->rdt->get_drm_name(), "radeon") == 0)
    {
        unsigned long val = 0;

        switch(QchoiceRadeon->GetSelection())
        {
        case 1: //CLOCK_CRYSTAL_FREQ
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_CLOCK_CRYSTAL_FREQ, &val))
                {
                    wxLogMessage("Crystal Frequency: %u Hz (%u kHz)", (unsigned)val, unsigned (val/1000));
                }
                //else Error message
                break;
            }
        case 2: //NUM_TILE_PIPES
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_NUM_TILE_PIPES, &val))
                    wxLogMessage("Tile Pipes count: %u", (unsigned)val);
                //else
                break;
            }
        case 3: //RADEON_INFO_MAX_SE
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_MAX_SE, &val))
                    wxLogMessage("Number of Shader Engines: %u", (unsigned)val);
                //else
                break;
            }
        case 4: //MAX_SH_PER_SE
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_MAX_SH_PER_SE, &val))
                    wxLogMessage("Number of shaders per engine: %u", (unsigned)val);

                break;
            }
        case 5: //MAX_SCLK
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_MAX_SCLK, &val))
                    wxLogMessage("Maximum source clock: %u kHz (%u mHz)", (unsigned)val, unsigned(val/1000));

                break;
            }
        case 6: //VCE_FW_VERSION
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_VCE_FW_VERSION, &val))
                    wxLogMessage("VCE firmware version: %u", (unsigned)val);

                break;
            }
        case 7: //VCE_FB_VERSION
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_VCE_FB_VERSION, &val))
                    wxLogMessage("VCE FB Version: %u", (unsigned)val);

                break;
            }
        case 8: //ACTIVE_CU_COUNT
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_ACTIVE_CU_COUNT, &val))
                    wxLogMessage("Active Compute Unit count: %u", (unsigned)val);

                break;
            }
        case 9: //CURRENT_GPU_TEMP
            {
                if(!rdtFrame->rdt->GetQueryR(RADEON_INFO_CURRENT_GPU_TEMP, &val))
                    wxLogMessage("GPU Temperature: %u", (unsigned)val);

                break;
            }
        default:
            break;
        }
    }

    wxUnusedVar(event);
}

void QDialog::OnQChoiceA(wxCommandEvent& event)
{
    class radeontop::m_amdgpu_info * amd = new radeontop::m_amdgpu_info(rdtFrame->rdt->get_drm_handle());

    //TODO: Edit labels as readable as much
    switch(QchoiceAMD->GetSelection())
    {
        case 1: //SENSORS
            {
                struct radeontop::m_amdgpu_sensor * sensor = new radeontop::m_amdgpu_sensor();

                amd->ReadSensor(sensor, 0);

                wxLogMessage("GPU:%d\nMEM:%d\nTemp:%d\nLoad:%d\nPower:%d\nVDDNB:%d\nVDDGFX:%d\n",
                             sensor->gfx_sclk,
                             sensor->gfx_mclk,
                             sensor->gpu_temp /100, /* get temperature in millidegrees C */
                             sensor->gpu_load,
                             sensor->gpu_avg_power,
                             sensor->vddnb,
                             sensor->vddgfx);

                delete sensor;
            } break;
        case 2: //HARDWARE
            {
                radeontop::amdgpu_dev_info info;

                if(!amd->GetDevInfo(&info))
                {
                    wxLogMessage("Could not get device info!");
                    break;
                }

                wxLogMessage("Chip Revision: %.2X , External Revision: %.2X",
                             info.chip_rev, info.external_rev);

                wxLogMessage("num_cu_per_sh: %d", info.num_cu_per_sh);
                wxLogMessage("Shader Arrays per Engine: %d , Shader Engines: %d",
                             info.num_shader_engines, info.num_shader_arrays_per_engine);

                wxLogMessage("cu_active_number: %d", info.cu_active_number);
                wxLogMessage("gpu_counter_freq: %dMHz", (int)info.gpu_counter_freq / 1000);
                wxLogMessage("max_engine_clock: %dMHz", (int)info.max_engine_clock / 1000);
                wxLogMessage("max_memory_clock: %dMHz", (int)info.max_memory_clock / 1000);

                std::string s("???");
                switch(info.vram_type)
                {
                case VRAM_TYPE_UNKNOWN: { s.assign("UNKNOWN"); } break;
                case VRAM_TYPE_GDDR1: { s.assign("GDDR1"); } break;
                case VRAM_TYPE_DDR2: { s.assign("DDR2"); } break;
                case VRAM_TYPE_GDDR3: { s.assign("GDDR3"); } break;
                case VRAM_TYPE_GDDR4: { s.assign("GDDR4"); } break;
                case VRAM_TYPE_GDDR5: { s.assign("GDDR5"); } break;
                case VRAM_TYPE_HBM: { s.assign("HBM"); } break;
                case VRAM_TYPE_DDR3: { s.assign("DDR3"); } break;
                }
                wxLogMessage("VRAM Type: \"%s\"", s.c_str());

                wxLogMessage("vram_bit_width: %d", info.vram_bit_width);

                wxLogMessage("ce_ram_size: %dKb", (unsigned)info.ce_ram_size / 1024);
                wxLogMessage("num_tcc_blocks: %d", info.num_tcc_blocks);
                wxLogMessage("gs_vgt_table_depth: %d", info.gs_vgt_table_depth);
                wxLogMessage("gs_prim_buffer_depth: %d", info.gs_prim_buffer_depth);
                wxLogMessage("max_gs_waves_per_vgt: %d", info.max_gs_waves_per_vgt);

            } break;
        case 3: // UVD
            {
                radeontop::amdgpu_uvd_handles uvd;
                memset(&uvd, 0, sizeof(uvd));
                radeontop::amdgpu_uvd_handles * p = &uvd;
                amd->GetQueryA(AMDGPU_INFO_NUM_HANDLES, (unsigned long long*)p, sizeof(uvd));

                if(p == NULL)
                    break;

                wxLogMessage("Used:%d -- Max:%d",
                             uvd.uvd_used_handles, uvd.uvd_max_handles);

            } break;
        case 4: // VCE
            {
                unsigned char c;
                c = amd->GetClockTable().size();
                //wxLogMessage("VCE table entry count: %d", c);
                wxString s;
                s << wxString::Format("VCE table entry count: %d\n", c);
                for(unsigned char i = 0; i < c; ++i)
                    s << wxString::Format("\t%u --> sclk:%u  eclk:%u  mclk:%u\n",
                                          i+1,
                                          amd->GetClockTable()[i].sclk,
                                          amd->GetClockTable()[i].eclk,
                                          amd->GetClockTable()[i].mclk);

                wxLogMessage(s);

            } break;

    }

    delete amd;
    wxUnusedVar(event);
}

void rdt_guiFrame::OnCpuQuery(wxCommandEvent& event)
{
    if(event.IsChecked())
    {
        this->cd = new CpuDialog(this);
        cd->Show();
    }
    else if(!event.IsChecked())
    {
        cd->Show(false);
        delete cd;
        this->mviewCPU->Check(false);
    }
    else
    {
        event.Skip();
    }

}

void CpuDialog::OnCpuDialogClose(wxCloseEvent& event)
{
    rdtFrame->DestroyDialogWindow(this);
     wxUnusedVar(event);
}

CpuDialog::CpuDialog(wxWindow * parent)
    :CpuQueryDialog(parent)
{
    rdtFrame = (rdt_guiFrame *) parent;
    cfq = new cputop::cpufreq();

    unsigned char c = cfq->GetCpuCount();

    printf("CpuCount: %d\n", c);

    for(unsigned char i = 0; i < c; ++i)
    {
        wxString s(wxString::Format("CPU-%d", i));
        wxStaticText * st;
        st = new wxStaticText(this, wxID_ANY, wxT("CPU"));
        st->SetLabel(s);
        st->Wrap(-1);
        CpuSizer->Add(st, 0, wxALL, 5);

        wxGauge * ga;
        ga = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
        ga->SetValue(0);
        CpuSizer->Add(ga, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );

        mapCpuWindowElements.insert(std::make_pair(st, ga));
        mapCPU.insert(std::make_pair(i, mapCpuWindowElements.find(st)));
    }
}

CpuDialog::~CpuDialog()
{
    delete cfq;
}

void CpuDialog::UpdateCpuVal(wxTimerEvent& event)
{
    std::map<unsigned char, std::map<wxStaticText *, wxGauge *>::iterator>::iterator itr;
    unsigned char cc = cfq->GetCpuCount();
    unsigned char i = 0;
    unsigned long min = 0;
    unsigned long max = 0;
    unsigned long j = 0;

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
        itr->second->first->SetLabel(wxString::Format("CPU-%d \t %.2fGHZ", i, (float)j /1.0e6));
        itr->second->second->SetRange( j <= max? (max - min): (j - min) ); // Core boost
        itr->second->second->SetValue( ( j <= min? 0: (j-min) ) );
    }

    wxUnusedVar(event);
}


