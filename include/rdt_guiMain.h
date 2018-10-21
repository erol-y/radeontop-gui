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
#include "../version.h"
#endif // VER_H

#include <iostream>
#include <map>
#include <string>

#include <wx/msgdlg.h>
#include <wx/log.h>

#include "rdt_guiApp.h"
#include "../src/GUIFrame.h"
#include "radeontop.h"
#include "cputop.h"
#include "power.h"

class rdt_guiFrame: public GUIFrame
{
    public:
        void GetReady();
        radeontop::rdtop * GetRadeonHandler() const { return this->rdt; }
        radeontop::_m_drm_version GetDrmVerInfo() const { return this->m_drm_ver; }
        bool GetRadeontopState() const { return is_radeontop_ok; }
        void mSetTimerVal(int, bool = false);
        int GetTimerVal() const { return this->msec; }
        void DestroyDialogWindow(void *);

        rdt_guiFrame(wxFrame *frame);
        ~rdt_guiFrame();

    private:
        class radeontop::rdtop * rdt;
        radeontop::_m_drm_version m_drm_ver;

        void SetRadeontopState(bool bState) { is_radeontop_ok = bState; }
        void SetItemsToShow();
        void SetMenuPresent();

        int msec;
        bool is_radeontop_ok;

        class QDialog * qd;
        class CpuDialog * cd;
        class PowerWindow * pw;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        void OnSize(wxSizeEvent& event);
        void UpdateVal(wxTimerEvent& event);
        void OnRefRate(wxCommandEvent& event);
        void OnMenuSaveExit(wxCommandEvent& event);
        void OnMenuReset(wxCommandEvent& event);

        void OnViewStats_gui(wxCommandEvent& event);
        void OnViewStats_ee(wxCommandEvent& event);
        void OnViewStats_vgt(wxCommandEvent& event);
        void OnViewStats_ta(wxCommandEvent& event);
        void OnViewStats_tc(wxCommandEvent& event);
        void OnViewStats_sx(wxCommandEvent& event);
        void OnViewStats_sh(wxCommandEvent& event);
        void OnViewStats_spi(wxCommandEvent& event);
        void OnViewStats_smx(wxCommandEvent& event);
        void OnViewStats_sc(wxCommandEvent& event);
        void OnViewStats_pa(wxCommandEvent& event);
        void OnViewStats_db(wxCommandEvent& event);
        void OnViewStats_cb(wxCommandEvent& event);
        void OnViewStats_cr(wxCommandEvent& event);
        void OnViewStats_vram(wxCommandEvent& event);
        void OnViewStats_gtt(wxCommandEvent& event);

        void OnQuery(wxCommandEvent& event);
        void OnCpuQuery(wxCommandEvent& event);
        void OnPowerSelect(wxCommandEvent& event);
};

class QDialog: public QueryDialog
{
    public:
        QDialog(wxWindow *);
        ~QDialog();

        void OnQueryClose(wxCloseEvent& event);

    private:
        rdt_guiFrame * rdtFrame;

        void OnQChoiceR(wxCommandEvent& event);
        void OnQChoiceA(wxCommandEvent& event);
};

class CpuDialog: public CpuQueryDialog
{
    public:
        void SetTimerVal(int);

        CpuDialog(wxWindow *);
        ~CpuDialog();

        void OnCpuDialogClose(wxCloseEvent& event);

    private:
        rdt_guiFrame * rdtFrame;
        cputop::cpufreq * cfq;

        std::map<wxStaticText *, wxGauge *> mapCpuWindowElements;
        std::map<unsigned char, std::map<wxStaticText *, wxGauge *>::iterator> mapCPU;
        std::map<unsigned char, unsigned long> mapAvg;
        bool isAvg;
        unsigned int cAvg;

        void OnChoiceCpuLimit(wxCommandEvent& event);
        void OnCheckBoxAvg(wxCommandEvent& event);
        void UpdateCpuVal(wxTimerEvent& event);
};

class GUIRefreshRate: public DialogRR
{
    public:
        GUIRefreshRate(wxWindow *);
        ~GUIRefreshRate() {}

    private:
        rdt_guiFrame * rdtFrame;

        void OnSetVal( wxCommandEvent& event );
};

class PowerWindow: public PowerFrame
{
    public:
        static bool CanRun() { return PowerSupply::HasBattery(); }

        PowerWindow(wxWindow *);
        ~PowerWindow();

    private:
        PowerSupply * pconf;
        BatteryInfo bi;
        int milisec;

        void BatteryInit();
        void UpdatePowerFrame( wxTimerEvent& event );
        void OnPowerClose( wxCloseEvent& event );

};

#endif // RDT_GUIMAIN_H
