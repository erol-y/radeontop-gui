///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Aug  5 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/statline.h>
#include <wx/hyperlink.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/scrolwin.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* settingmenu;
		wxMenuItem* menuRefRate;
		wxMenuItem* mPciAddr;
		wxMenuItem* mSettingsSave;
		wxMenu* viewmenu;
		wxMenu* menuview_stats;
		wxMenuItem* mviewstats_gui;
		wxMenuItem* mviewstats_ee;
		wxMenuItem* mviewstats_vgt;
		wxMenuItem* mviewstats_ta;
		wxMenuItem* mviewstats_tc;
		wxMenuItem* mviewstats_sx;
		wxMenuItem* mviewstats_sh;
		wxMenuItem* mviewstats_spi;
		wxMenuItem* mviewstats_smx;
		wxMenuItem* mviewstats_sc;
		wxMenuItem* mviewstats_pa;
		wxMenuItem* mviewstats_db;
		wxMenuItem* mviewstats_cb;
		wxMenuItem* mviewstats_cr;
		wxMenuItem* mviewstats_vram;
		wxMenuItem* mviewstats_gtt;
		wxMenuItem* mviewQuery;
		wxMenuItem* mviewCPU;
		wxMenuItem* mviewPower;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxBoxSizer* bSizer1;
		wxStaticText* m_staticText_gpu_load;
		wxGauge* m_gauge_gpu_load;
		wxStaticText* m_staticText_gui;
		wxGauge* m_gauge_gui;
		wxStaticText* m_staticText_ee;
		wxGauge* m_gauge_ee;
		wxStaticText* m_staticText_vgt;
		wxGauge* m_gauge_vgt;
		wxStaticText* m_staticText_ta;
		wxGauge* m_gauge_ta;
		wxStaticText* m_staticText_tc;
		wxGauge* m_gauge_tc;
		wxStaticText* m_staticText_sx;
		wxGauge* m_gauge_sx;
		wxStaticText* m_staticText_sh;
		wxGauge* m_gauge_sh;
		wxStaticText* m_staticText_spi;
		wxGauge* m_gauge_spi;
		wxStaticText* m_staticText_smx;
		wxGauge* m_gauge_smx;
		wxStaticText* m_staticText_sc;
		wxGauge* m_gauge_sc;
		wxStaticText* m_staticText_pa;
		wxGauge* m_gauge_pa;
		wxStaticText* m_staticText_db;
		wxGauge* m_gauge_db;
		wxStaticText* m_staticText_cb;
		wxGauge* m_gauge_cb;
		wxStaticText* m_staticText_cr;
		wxGauge* m_gauge_cr;
		wxStaticText* m_staticText_vram;
		wxGauge* m_gauge_vram;
		wxStaticText* m_staticText_gtt;
		wxGauge* m_gauge_gtt;
		wxTimer m_timer1;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRefRate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetPciBus( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSaveExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_gui( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_ee( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_vgt( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_ta( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_tc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_sx( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_sh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_spi( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_smx( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_sc( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_pa( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_db( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_cb( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_cr( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_vram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnViewStats_gtt( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuery( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCpuQuery( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPowerSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateVal( wxTimerEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("radeontop GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 505,325 ), long style = wxDEFAULT_FRAME_STYLE|wxALWAYS_SHOW_SB|wxTAB_TRAVERSAL|wxVSCROLL );

		~GUIFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class panelAbout
///////////////////////////////////////////////////////////////////////////////
class panelAbout : public wxPanel
{
	private:

	protected:
		wxStaticText* m_staticText28;
		wxStaticLine* m_staticline3;
		wxHyperlinkCtrl* hyperlink_git;
		wxStaticLine* m_staticline4;
		wxButton* buttonAboutOK;

		// Virtual event handlers, overide them in your derived class
		virtual void OnAboutOK( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxStaticText* st_aboutThis;

		panelAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,190 ), long style = wxBORDER_SUNKEN|wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~panelAbout();

};

///////////////////////////////////////////////////////////////////////////////
/// Class QueryDialog
///////////////////////////////////////////////////////////////////////////////
class QueryDialog : public wxDialog
{
	private:

	protected:
		wxBoxSizer* bSizer2;
		wxChoice* QchoiceRadeon;
		wxChoice* QchoiceAMD;
		wxTextCtrl* QtextCtrl1;

		// Virtual event handlers, overide them in your derived class
		virtual void OnQueryClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQChoiceR( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQChoiceA( wxCommandEvent& event ) { event.Skip(); }


	public:

		QueryDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Query"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 457,363 ), long style = wxDEFAULT_DIALOG_STYLE );
		~QueryDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CpuQueryDialog
///////////////////////////////////////////////////////////////////////////////
class CpuQueryDialog : public wxDialog
{
	private:

	protected:
		wxBoxSizer* topSizer;
		wxFlexGridSizer* choiceSizer;
		wxStaticText* m_staticText_limit;
		wxChoice* m_choice_limit;
		wxCheckBox* m_checkBox_avg;
		wxStaticText* m_staticText_reduced;
		wxGauge* m_gauge_reduced;
		wxStaticLine* m_staticline1;
		wxBoxSizer* middleSizer;
		wxScrolledWindow* m_scrolledWindow1;
		wxBoxSizer* scrolledSizer;
		wxTimer timer_cpu;

		// Virtual event handlers, overide them in your derived class
		virtual void OnCpuDialogClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnChoiceCpuLimit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxAvg( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateCpuVal( wxTimerEvent& event ) { event.Skip(); }


	public:

		CpuQueryDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CPU"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 420,371 ), long style = wxDEFAULT_DIALOG_STYLE );
		~CpuQueryDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogRR
///////////////////////////////////////////////////////////////////////////////
class DialogRR : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText20;
		wxButton* buttonSet;
		wxStaticText* m_staticText23;

		// Virtual event handlers, overide them in your derived class
		virtual void OnSetVal( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* textCtrlRefRate;

		DialogRR( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Set Refresh Rate"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 255,124 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogRR();

};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogPCI
///////////////////////////////////////////////////////////////////////////////
class DialogPCI : public wxDialog
{
	private:

	protected:
		wxStaticText* txtBusCurrent;
		wxButton* m_btnPciAddr;

		// Virtual event handlers, overide them in your derived class
		virtual void OnSetPciBus( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* txtPciBus;

		DialogPCI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Set PCI Bus Address"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 237,133 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DialogPCI();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PowerFrame
///////////////////////////////////////////////////////////////////////////////
class PowerFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar2;
		wxStatusBar* m_statusBar2;
		wxBoxSizer* bSizerPF_top;
		wxStaticText* m_staticText_rate;
		wxGauge* m_gauge_rate;
		wxStaticLine* m_staticline2;
		wxStaticText* st_Current;
		wxTextCtrl* tc_Current;
		wxStaticText* st_CurrentAvg;
		wxTextCtrl* tc_CurrentAvg;
		wxStaticText* st_Voltage;
		wxTextCtrl* tc_Voltage;
		wxStaticText* st_Power;
		wxTextCtrl* tc_Power;
		wxTimer m_timer_pf;

		// Virtual event handlers, overide them in your derived class
		virtual void OnPowerClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void UpdatePowerFrame( wxTimerEvent& event ) { event.Skip(); }


	public:

		PowerFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~PowerFrame();

};

