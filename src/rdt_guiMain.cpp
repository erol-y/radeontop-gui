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

#include "../include/rdt_guiMain.h"
#include "../include/conf.h"

static ConfigFile * cfg = NULL;

rdt_guiFrame::rdt_guiFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    rdt = NULL;
    qd = NULL;
    msec = -1;

    cfg = ConfigFile::GetConfigFile();
    if(cfg == NULL)
        { cfg = ConfigFile::OnInit(); }

    rdt = new radeontop::rdtop();
}

rdt_guiFrame::~rdt_guiFrame()
{
    wxSize s = bSizer1->GetMinSize();
    if(ConfigFile::GetConfigFile() != NULL)
    {
        cfg->cfgWrite( ConfKeyEnums::GEN_SIZER_X, s.GetX() );
        cfg->cfgWrite( ConfKeyEnums::GEN_SIZER_Y, s.GetY() );
    }
}

void rdt_guiFrame::GetReady()
{
    int interval;
    cfg->cfgRead(ConfKeyEnums::GEN_UPDATE_INTERVAL, &interval, 500);

    if(!rdt->init_rdtop())
    {
        this->SetRadeontopState(false);
        this->SetStatusText(_T("Radeontop not initialized!"), 0);
        mSetTimerVal(interval);
    }
    else
    {
        this->SetRadeontopState(true);
        rdt->get_drm_version(&this->m_drm_ver);
        mSetTimerVal(interval, true);
        this->SetMenuPresent();
    }

    int x, y;
    cfg->cfgRead(ConfKeyEnums::GEN_SIZER_X, &x, 470);
    cfg->cfgRead(ConfKeyEnums::GEN_SIZER_Y, &y, 325);
    bSizer1->SetMinSize(x, y);
    this->Fit();
    this->Layout();

    mviewPower->Enable(PowerWindow::CanRun());
    this->SetItemsToShow();

    this->Show();
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
    bSizer1->SetMinSize(GetSize().GetWidth(), -1);
    this->Fit();
    this->Layout();
    wxUnusedVar(event);
}

void rdt_guiFrame::SetItemsToShow()
{
    bool bVal;

    if(cfg == NULL)
        return;

    wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED);

    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_GUI, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_gui->Check(bVal);
        this->OnViewStats_gui(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_EE, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_ee->Check(bVal);
        this->OnViewStats_ee(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_VGT, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_vgt->Check(bVal);
        this->OnViewStats_vgt(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_TA, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_ta->Check(bVal);
        this->OnViewStats_ta(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_TC, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_tc->Check(bVal);
        this->OnViewStats_tc(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_SX, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_sx->Check(bVal);
        this->OnViewStats_sx(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_SH, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_sh->Check(bVal);
        this->OnViewStats_sh(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_SPI, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_spi->Check(bVal);
        this->OnViewStats_spi(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_SMX, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_smx->Check(bVal);
        this->OnViewStats_smx(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_SC, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_sc->Check(bVal);
        this->OnViewStats_sc(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_PA, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_pa->Check(bVal);
        this->OnViewStats_pa(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_DB, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_db->Check(bVal);
        this->OnViewStats_db(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_CB, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_cb->Check(bVal);
        this->OnViewStats_cb(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_CR, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_cr->Check(bVal);
        this->OnViewStats_cr(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_VRAM, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_vram->Check(bVal);
        this->OnViewStats_vram(event);
    }
    if(cfg->cfgRead(ConfKeyEnums::GPU_ITEM_GTT, &bVal))
    {
        event.SetInt( bVal? 1 : 0 );
        mviewstats_gtt->Check(bVal);
        this->OnViewStats_gtt(event);
    }
}

void rdt_guiFrame::OnRefRate(wxCommandEvent& event)
{
    GUIRefreshRate * grr = new GUIRefreshRate(this);
    int val = this->GetTimerVal();
    grr->textCtrlRefRate->SetValue(wxString::Format("%d", val));
    grr->Show();

    wxUnusedVar(event);
}

void rdt_guiFrame::OnMenuSaveExit(wxCommandEvent& event)
{
    cfg->bSave = event.IsChecked();
}

void rdt_guiFrame::OnMenuReset(wxCommandEvent& event)
{
    this->Show(false);

    wxCloseEvent ev;

    if(this->mviewQuery->IsChecked())
    {
        this->mviewQuery->Check(false);
        qd->OnQueryClose(ev);
    }

    if(this->mviewCPU->IsChecked())
    {
        this->mviewCPU->Check(false);
        cd->OnCpuDialogClose(ev);
    }

    if(cfg != NULL)
    {
        cfg->ResetConf();
    }

    this->GetReady();
    this->Show(true);

    wxUnusedVar(event);
}

void rdt_guiFrame::mSetTimerVal(int _sec, bool bStart)
{
    this->msec = _sec;
    if(bStart)
        m_timer1.Start(_sec);

    if(cd != NULL)
        cd->SetTimerVal(_sec);
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
                                              (int)radeontop::results->sclk,
                                              (int)radeontop::results->mclk),1);
    event.Skip();
}

#define _OnViewSelect(a,b) if(event.IsChecked())                                \
                            {   a->SetSize(GetSize().GetWidth(), -1);          \
                                b->SetSize(GetSize().GetWidth(), -1);          \
                                a->Show();                                      \
                                b->Show();                                      \
                                bSizer1->SetMinSize(GetSize().GetWidth(), -1);  \
                                this->Fit();                                    \
                                this->Layout();                                 \
                            }                                                   \
                            else if(!event.IsChecked())                         \
                            {   a->Show(false);                                 \
                                b->Show(false);                                 \
                                bSizer1->SetMinSize(GetSize().GetWidth(), -1);  \
                                this->Fit();                                    \
                                this->Layout();                                 \
                            }

#define SAVECONF(key) cfg->cfgWrite( key, event.IsChecked() );

void rdt_guiFrame::OnViewStats_gui(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_GUI)
    _OnViewSelect(m_staticText_gui, m_gauge_gui)
}

void rdt_guiFrame::OnViewStats_ee(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_EE)
    _OnViewSelect(m_staticText_ee, m_gauge_ee)
}

void rdt_guiFrame::OnViewStats_vgt(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_VGT)
    _OnViewSelect(m_staticText_vgt, m_gauge_vgt)
}

void rdt_guiFrame::OnViewStats_ta(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_TA)
    _OnViewSelect(m_staticText_ta, m_gauge_ta)
}

void rdt_guiFrame::OnViewStats_tc(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_TC)
    _OnViewSelect(m_staticText_tc, m_gauge_tc)
}

void rdt_guiFrame::OnViewStats_sx(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_SX)
    _OnViewSelect(m_staticText_sx, m_gauge_sx)
}

void rdt_guiFrame::OnViewStats_sh(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_SH)
    _OnViewSelect(m_staticText_sh, m_gauge_sh)
}

void rdt_guiFrame::OnViewStats_spi(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_SPI)
    _OnViewSelect(m_staticText_spi, m_gauge_spi)
    event.Skip();
}

void rdt_guiFrame::OnViewStats_smx(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_SMX)
    _OnViewSelect(m_staticText_smx, m_gauge_smx)
}

void rdt_guiFrame::OnViewStats_sc(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_SC)
    _OnViewSelect(m_staticText_sc, m_gauge_sc)
}

void rdt_guiFrame::OnViewStats_pa(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_PA)
    _OnViewSelect(m_staticText_pa, m_gauge_pa)
}

void rdt_guiFrame::OnViewStats_db(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_DB)
    _OnViewSelect(m_staticText_db, m_gauge_db)
}

void rdt_guiFrame::OnViewStats_cb(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_CB)
    _OnViewSelect(m_staticText_cb, m_gauge_cb)
}

void rdt_guiFrame::OnViewStats_cr(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_CR)
    _OnViewSelect(m_staticText_cr, m_gauge_cr)
}

void rdt_guiFrame::OnViewStats_vram(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_VRAM)
    _OnViewSelect(m_staticText_vram, m_gauge_vram)
}

void rdt_guiFrame::OnViewStats_gtt(wxCommandEvent& event)
{
    SAVECONF(ConfKeyEnums::GPU_ITEM_GTT)
    _OnViewSelect(m_staticText_gtt, m_gauge_gtt)
}

#undef SAVECONF
#undef _OnViewSelect

void rdt_guiFrame::DestroyDialogWindow(void * wxid)
{
    if(wxid == NULL)
        { return; }

    if(wxid == qd)
    {
        delete qd;
        qd = NULL;
        mviewQuery->Check(false);
    }
    else if(wxid == cd)
    {
        delete cd;
        cd = NULL;
        mviewCPU->Check(false);
    }
    else if(wxid == pw)
    {
        delete pw;
        pw = NULL;
        mviewPower->Check(false);
    }
}

/********************************************************/
void rdt_guiFrame::OnQuery(wxCommandEvent& event)
{
    if(event.IsChecked() == true)
    {
        this->qd = new QDialog(this);
        qd->Show(true);
    }
    else //if(event.IsChecked() == false)
    {
        this->DestroyDialogWindow(this->qd);
    }
}


QDialog::QDialog(wxWindow * parent)
    : QueryDialog(parent)
{
    this->rdtFrame = (rdt_guiFrame *) parent;
    wxLog::SetActiveTarget(new wxLogTextCtrl(QtextCtrl1));

    wxLogMessage("Bus: %s", rdtFrame->GetRadeonHandler()->get_str_busid());
    wxLogMessage("%s", rdtFrame->GetRadeonHandler()->get_str_devid());
    wxLogMessage("Path: %s",rdtFrame->GetRadeonHandler()->get_str_devpath());
    wxLogMessage("Driver: %s  %u.%u.%u\n",
                 rdtFrame->GetRadeonHandler()->get_drm_name(),
                 rdtFrame->GetDrmVerInfo().version_major,
                 rdtFrame->GetDrmVerInfo().version_minor,
                 rdtFrame->GetDrmVerInfo().version_patchlevel);

    if(rdtFrame->GetRadeonHandler() != NULL && !rdtFrame->GetRadeonHandler()->haserror())
    {
        if (strcmp(rdtFrame->GetRadeonHandler()->get_drm_name(), "radeon") == 0)
        {
            QchoiceAMD->Hide();
            bSizer2->Remove((wxSizer*) QchoiceAMD);
        }
        else if(strcmp(rdtFrame->GetRadeonHandler()->get_drm_name(), "amdgpu") == 0)
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
    if (strcmp(rdtFrame->GetRadeonHandler()->get_drm_name(), "radeon") == 0)
    {
        unsigned long val = 0;
        signed long sval = 0;

        switch(QchoiceRadeon->GetSelection())
        {
        case 1: //CLOCK_CRYSTAL_FREQ
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_CLOCK_CRYSTAL_FREQ, &val))
                {
                    wxLogMessage("Crystal Frequency: %u Hz (%u kHz)", (unsigned)val, unsigned (val/1000));
                }
                //else Error message
                break;
            }
        case 2: //NUM_TILE_PIPES
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_NUM_TILE_PIPES, &val))
                    wxLogMessage("Tile Pipes count: %u", (unsigned)val);
                //else
                break;
            }
        case 3: //RADEON_INFO_MAX_SE
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_MAX_SE, &val))
                    wxLogMessage("Number of Shader Engines: %u", (unsigned)val);
                //else
                break;
            }
        case 4: //MAX_SH_PER_SE
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_MAX_SH_PER_SE, &val))
                    wxLogMessage("Number of shaders per engine: %u", (unsigned)val);

                break;
            }
        case 5: //MAX_SCLK
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_MAX_SCLK, &val))
                    wxLogMessage("Maximum source clock: %u kHz (%u mHz)", (unsigned)val, unsigned(val/1000));

                break;
            }
        case 6: //VCE_FW_VERSION
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_VCE_FW_VERSION, &val))
                    wxLogMessage("VCE firmware version: %u", (unsigned)val);

                break;
            }
        case 7: //VCE_FB_VERSION
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_VCE_FB_VERSION, &val))
                    wxLogMessage("VCE FB Version: %u", (unsigned)val);

                break;
            }
        case 8: //ACTIVE_CU_COUNT
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_ACTIVE_CU_COUNT, &val))
                    wxLogMessage("Active Compute Unit count: %u", (unsigned)val);

                break;
            }
        case 9: //CURRENT_GPU_TEMP
            {
                if(!rdtFrame->GetRadeonHandler()->GetQueryR(RADEON_INFO_CURRENT_GPU_TEMP, &sval))
                    wxLogMessage("GPU Temperature: %d", (signed)sval);

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
#ifdef ENABLE_AMDGPU
    class radeontop::m_amdgpu_info * amd = new radeontop::m_amdgpu_info(rdtFrame->GetRadeonHandler()->get_drm_handle());

    /**TODO: Edit labels as readable as much */
    switch(QchoiceAMD->GetSelection())
    {
        case 1: //SENSORS
            {
                struct radeontop::m_amdgpu_sensor * sensor = new radeontop::m_amdgpu_sensor();

                amd->ReadSensor(sensor, 0);
#ifdef AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK
                wxLogMessage("GPU:%d\nMEM:%d\nTemp:%d\nLoad:%d\nPower:%d\nVDDNB:%d\nVDDGFX:%d\npstate_sclk:%d\npstate_mclk:%d\n",
                             sensor->gfx_sclk,
                             sensor->gfx_mclk,
                             sensor->gpu_temp /100, /* get temperature in millidegrees C */
                             sensor->gpu_load,
                             sensor->gpu_avg_power,
                             sensor->vddnb,
                             sensor->vddgfx,
                             sensor->pstate_sclk,
                             sensor->pstate_mclk);

#else
                wxLogMessage("GPU:%d\nMEM:%d\nTemp:%d\nLoad:%d\nPower:%d\nVDDNB:%d\nVDDGFX:%d\n",
                             sensor->gfx_sclk,
                             sensor->gfx_mclk,
                             sensor->gpu_temp /100, /* get temperature in millidegrees C */
                             sensor->gpu_load,
                             sensor->gpu_avg_power,
                             sensor->vddnb,
                             sensor->vddgfx);
#endif // AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK

                delete sensor;
            } break;
        case 2: //HARDWARE
            {
                radeontop::amdgpu_dev_info info;
                wxString w(">>>>> Device Info: <<<<<\n");

                if(!amd->GetDevInfo(&info))
                {
                    wxLogMessage("Could not get device info!");
                    break;
                }

                w << wxString::Format("Chip Revision: %.2X , External Revision: %.2X\n",
                                      info.chip_rev, info.external_rev);

                w << wxString::Format("num_cu_per_sh: %d\n", info.num_cu_per_sh);

                w << wxString::Format("Shader Arrays per Engine: %d , Shader Engines: %d\n",
                                      info.num_shader_engines, info.num_shader_arrays_per_engine);

                w << wxString::Format("cu_active_number: %d\n", info.cu_active_number);
                w << wxString::Format("gpu_counter_freq: %dMHz\n", (int)info.gpu_counter_freq / 1000);
                w << wxString::Format("max_engine_clock: %dMHz\n", (int)info.max_engine_clock / 1000);
                w << wxString::Format("max_memory_clock: %dMHz\n", (int)info.max_memory_clock / 1000);

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
                w << wxString::Format("VRAM Type: \"%s\"\n", s.c_str());

                w << wxString::Format("vram_bit_width: %d\n", info.vram_bit_width);

                w << wxString::Format("ce_ram_size: %dKb\n", (unsigned)info.ce_ram_size / 1024);
                w << wxString::Format("num_tcc_blocks: %d\n", info.num_tcc_blocks);
                w << wxString::Format("gs_vgt_table_depth: %d\n", info.gs_vgt_table_depth);
                w << wxString::Format("gs_prim_buffer_depth: %d\n", info.gs_prim_buffer_depth);
                w << wxString::Format("max_gs_waves_per_vgt: %d", info.max_gs_waves_per_vgt);
                wxLogMessage(w);

            } break;
        case 3: // UVD
            {
                radeontop::amdgpu_uvd_handles uvd;
                memset(&uvd, 0, sizeof(uvd));
                radeontop::amdgpu_uvd_handles * p = &uvd;
                amd->GetQueryA(AMDGPU_INFO_NUM_HANDLES, (unsigned long long*)p, sizeof(uvd));

                if(p == NULL)
                    break;

                wxLogMessage("UVD: Used:%d -- Max:%d\n", uvd.uvd_used_handles, uvd.uvd_max_handles);

            } break;
        case 4: // VCE
            {
                unsigned char c;
                c = amd->GetClockTable().size();
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
#endif // ENABLE_AMDGPU
    wxUnusedVar(event);
}

/********************************************************/
void rdt_guiFrame::OnCpuQuery(wxCommandEvent& event)
{
    if(event.IsChecked() == true)
    {
        this->cd = new CpuDialog(this);
        cd->Show();
    }
    else //if(!event.IsChecked())
    {
        this->DestroyDialogWindow(this->cd);
    }
}

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

/********************************************************/

GUIRefreshRate::GUIRefreshRate(wxWindow * parent)
    : DialogRR(parent)
{
    this->rdtFrame = (rdt_guiFrame *) parent;
}

void GUIRefreshRate::OnSetVal(wxCommandEvent& event)
{
    int val = 0;
    val = wxAtoi(textCtrlRefRate->GetValue());
    if(val > 0)
    {
        rdtFrame->mSetTimerVal(val);
        cfg->cfgWrite(ConfKeyEnums::GEN_UPDATE_INTERVAL, val);
    }

    delete this;
    wxUnusedVar(event);
}

/********************************************************/

void rdt_guiFrame::OnPowerSelect(wxCommandEvent& event)
{
    if(event.IsChecked())
    {
        this->pw = new PowerWindow(this);
        pw->Show();
    }
    else
    {
        DestroyDialogWindow(pw);
    }

    wxUnusedVar(event);
}

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

    wxSize s = this->GetSize();
    if(ConfigFile::GetConfigFile() != NULL)
    {
        cfg->cfgWrite(ConfKeyEnums::PWR_GUI_SIZER_X, s.GetX());
        cfg->cfgWrite(ConfKeyEnums::PWR_GUI_SIZER_Y, s.GetY());
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
