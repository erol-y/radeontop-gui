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

#ifndef RDT_GUIMAIN_H
#define RDT_GUIMAIN_H

#ifndef VER_H
#include "version.h"
#endif // VER_H

#include <iostream>
#include <map>
#include <string>

#include "rdt_guiApp.h"
#include "GUIFrame.h"
#include <wx/msgdlg.h>
#include <wx/log.h>
#include "radeontop.h"
#include "cputop.h"

class rdt_guiFrame: public GUIFrame
{
    public:
        class radeontop::rdtop * rdt;
        radeontop::_m_drm_version m_drm_ver;

        void mSetTimerVal(int, bool);
        void SetMenuPresent();
        void DestroyDialogWindow(wxDialog *);

        rdt_guiFrame(wxFrame *frame);
        ~rdt_guiFrame();

    private:
        int msec;
        bool is_radeontop_ok;
        wxSize Sizer1Size;

        class QDialog * qd;
        class CpuDialog * cd;

        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

        virtual void OnSize(wxSizeEvent& event);
        virtual void UpdateVal(wxTimerEvent& event);

        virtual void OnViewStats_gui(wxCommandEvent& event);
        virtual void OnViewStats_ee(wxCommandEvent& event);
        virtual void OnViewStats_vgt(wxCommandEvent& event);
        virtual void OnViewStats_ta(wxCommandEvent& event);
        virtual void OnViewStats_tc(wxCommandEvent& event);
        virtual void OnViewStats_sx(wxCommandEvent& event);
        virtual void OnViewStats_sh(wxCommandEvent& event);
        virtual void OnViewStats_spi(wxCommandEvent& event);
        virtual void OnViewStats_smx(wxCommandEvent& event);
        virtual void OnViewStats_sc(wxCommandEvent& event);
        virtual void OnViewStats_pa(wxCommandEvent& event);
        virtual void OnViewStats_db(wxCommandEvent& event);
        virtual void OnViewStats_cb(wxCommandEvent& event);
        virtual void OnViewStats_cr(wxCommandEvent& event);
        virtual void OnViewStats_vram(wxCommandEvent& event);
        virtual void OnViewStats_gtt(wxCommandEvent& event);

        virtual void OnQuery(wxCommandEvent& event);
        virtual void OnCpuQuery(wxCommandEvent& event);
};

class QDialog: public QueryDialog
{
    public:
        QDialog(wxWindow *);
        ~QDialog();

    private:
        rdt_guiFrame * rdtFrame;
        //int QueryMap[32];

    protected:
        virtual void OnQueryClose(wxCloseEvent& event);
        virtual void OnQChoiceR(wxCommandEvent& event);
        virtual void OnQChoiceA(wxCommandEvent& event);
};

class CpuDialog: public CpuQueryDialog
{
    public:
        CpuDialog(wxWindow *);
        ~CpuDialog();
    private:
        rdt_guiFrame * rdtFrame;
        cputop::cpufreq * cfq;

        std::map<wxStaticText *, wxGauge *> mapCpuWindowElements;
        std::map<unsigned char, std::map<wxStaticText *, wxGauge *>::iterator> mapCPU;
        std::map<unsigned char, unsigned long> mapAvg;
        bool isAvg;
        unsigned int cAvg;

    protected:
        virtual void OnChoiceCpuLimit(wxCommandEvent& event);
        virtual void OnCheckBoxAvg(wxCommandEvent& event);
        virtual void OnCpuDialogClose(wxCloseEvent& event);
        virtual void UpdateCpuVal(wxTimerEvent& event);
};
#endif // RDT_GUIMAIN_H
