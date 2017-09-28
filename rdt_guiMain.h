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


#include "rdt_guiApp.h"

#include "GUIFrame.h"
#include "wx/msgdlg.h"
#include "radeontop.h"

class rdt_guiFrame: public GUIFrame
{
    public:
        radeontop::rdtop * rdt;

        void mSetTimerVal(int, bool);
        void SetMenuPresent();

        rdt_guiFrame(wxFrame *frame);
        ~rdt_guiFrame();

    private:
        int msec;
        wxSize Sizer1Size;

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
};

#endif // RDT_GUIMAIN_H
