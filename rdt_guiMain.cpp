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
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_(""), 0);
    statusBar->SetStatusText("", 1);
#endif

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
}

void rdt_guiFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void rdt_guiFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxT("Radeontop GUI");
    wxMessageBox(msg, _("Welcome to..."));
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
#undef _ShowVal()

    m_staticText_vram->SetLabel(wxString::Format("VRAM  Total: %dM   /   Used: %dM",
                                             (int)(rdt->vramsize / 1024 / 1024),
                                             (int)(radeontop::results->vram / 1024 / 1024)));

    m_gauge_vram->SetRange(rdt->vramsize);
    m_gauge_vram->SetValue((int)(radeontop::results->vram > rdt->vramsize) ?
                                rdt->vramsize : radeontop::results->vram);

    m_staticText_gtt->SetLabel(wxString::Format("GTT  Total: %dM   /   Used: %dM",
                                                (int)(rdt->gttsize / 1024 / 1024),
                                                (int)(radeontop::results->gtt / 1024 / 1024)));

    m_gauge_gtt->SetRange(rdt->gttsize);
    m_gauge_gtt->SetValue((int)(radeontop::results->gtt > rdt->gttsize) ?
                          rdt->gttsize : radeontop::results->gtt);


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
#undef _OnViewSelect()





