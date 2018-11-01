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
#include "conf.h"

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

    delete rdt;
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
    cfg->cfgRead(ConfKeyEnums::GEN_SIZER_X, &x, 505);
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
    AboutPage * about = new AboutPage(this);
    wxString title = wxString::Format("%s %s", wxT("radeontop GUI "), wxT(VERSION));
    about->st_aboutThis->SetLabel(title);
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
