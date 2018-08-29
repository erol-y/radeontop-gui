///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Aug  4 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );

	mbar->Append( fileMenu, wxT("&File") );

	settingmenu = new wxMenu();
	menuRefRate = new wxMenuItem( settingmenu, wxID_ANY, wxString( wxT("&Refresh Rate") ) + wxT('\t') + wxT("Alt+F5"), wxEmptyString, wxITEM_NORMAL );
	settingmenu->Append( menuRefRate );

	mbar->Append( settingmenu, wxT("&Settings") );

	viewmenu = new wxMenu();
	menuview_stats = new wxMenu();
	wxMenuItem* menuview_statsItem = new wxMenuItem( viewmenu, wxID_ANY, wxT("Stats"), wxEmptyString, wxITEM_NORMAL, menuview_stats );
	mviewstats_gui = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Graphics Pipe") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_gui );
	mviewstats_gui->Check( true );

	mviewstats_ee = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Event Engine") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_ee );

	mviewstats_vgt = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Vertex Group") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_vgt );
	mviewstats_vgt->Check( true );

	mviewstats_ta = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Texture Addresser") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_ta );

	mviewstats_tc = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Texture Cache") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_tc );

	mviewstats_sx = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Shader Export") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_sx );

	mviewstats_sh = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Sequencer Inst.") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_sh );

	mviewstats_spi = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Shader Int.") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_spi );

	mviewstats_smx = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Shader Memory Exchange") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_smx );

	mviewstats_sc = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Scan Conv.") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_sc );

	mviewstats_pa = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Primitive Asm.") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_pa );
	mviewstats_pa->Check( true );

	mviewstats_db = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Depth Block") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_db );

	mviewstats_cb = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Color Block") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_cb );

	mviewstats_cr = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Clip Rectangle") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_cr );

	mviewstats_vram = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("VRAM") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_vram );
	mviewstats_vram->Check( true );

	mviewstats_gtt = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("GTT") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_gtt );
	mviewstats_gtt->Check( true );

	viewmenu->Append( menuview_statsItem );

	mviewQuery = new wxMenuItem( viewmenu, wxID_ANY, wxString( wxT("Query") ) , wxEmptyString, wxITEM_CHECK );
	viewmenu->Append( mviewQuery );

	mviewCPU = new wxMenuItem( viewmenu, wxID_ANY, wxString( wxT("CPU") ) , wxEmptyString, wxITEM_CHECK );
	viewmenu->Append( mviewCPU );

	mbar->Append( viewmenu, wxT("&View") );

	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );

	mbar->Append( helpMenu, wxT("&Help") );

	this->SetMenuBar( mbar );

	statusBar = this->CreateStatusBar( 2, 0, wxID_ANY );
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText_gpu_load = new wxStaticText( this, wxID_ANY, wxT("GPU Load"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_gpu_load->Wrap( -1 );
	m_staticText_gpu_load->Hide();

	bSizer1->Add( m_staticText_gpu_load, 0, wxALL, 5 );

	m_gauge_gpu_load = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_gpu_load->SetValue( 0 );
	m_gauge_gpu_load->Hide();

	bSizer1->Add( m_gauge_gpu_load, 0, wxALL|wxEXPAND, 5 );

	m_staticText_gui = new wxStaticText( this, wxID_ANY, wxT("Graphics Pipe"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_gui->Wrap( -1 );
	bSizer1->Add( m_staticText_gui, 0, wxALL, 5 );

	m_gauge_gui = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_gui->SetValue( 0 );
	bSizer1->Add( m_gauge_gui, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	m_staticText_ee = new wxStaticText( this, wxID_ANY, wxT("Event Engine"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_ee->Wrap( -1 );
	m_staticText_ee->Hide();

	bSizer1->Add( m_staticText_ee, 0, wxALL, 5 );

	m_gauge_ee = new wxGauge( this, wxID_ANY, 100, wxPoint( -1,-1 ), wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_ee->SetValue( 0 );
	m_gauge_ee->Hide();

	bSizer1->Add( m_gauge_ee, 0, wxALL|wxEXPAND, 5 );

	m_staticText_vgt = new wxStaticText( this, wxID_ANY, wxT("Vertex Grouper + Tesselator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_vgt->Wrap( -1 );
	bSizer1->Add( m_staticText_vgt, 0, wxALL, 5 );

	m_gauge_vgt = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_vgt->SetValue( 0 );
	bSizer1->Add( m_gauge_vgt, 0, wxALL|wxEXPAND, 5 );

	m_staticText_ta = new wxStaticText( this, wxID_ANY, wxT("Texture Addresser"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_ta->Wrap( -1 );
	m_staticText_ta->Hide();

	bSizer1->Add( m_staticText_ta, 0, wxALL, 5 );

	m_gauge_ta = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_ta->SetValue( 0 );
	m_gauge_ta->Hide();

	bSizer1->Add( m_gauge_ta, 0, wxALL|wxEXPAND, 5 );

	m_staticText_tc = new wxStaticText( this, wxID_ANY, wxT("Texture Cache"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tc->Wrap( -1 );
	m_staticText_tc->Hide();

	bSizer1->Add( m_staticText_tc, 0, wxALL, 5 );

	m_gauge_tc = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_tc->SetValue( 0 );
	m_gauge_tc->Hide();

	bSizer1->Add( m_gauge_tc, 0, wxALL|wxEXPAND, 5 );

	m_staticText_sx = new wxStaticText( this, wxID_ANY, wxT("Shader Export"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_sx->Wrap( -1 );
	m_staticText_sx->Hide();

	bSizer1->Add( m_staticText_sx, 0, wxALL, 5 );

	m_gauge_sx = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_sx->SetValue( 0 );
	m_gauge_sx->Hide();

	bSizer1->Add( m_gauge_sx, 0, wxALL|wxEXPAND, 5 );

	m_staticText_sh = new wxStaticText( this, wxID_ANY, wxT("Sequencer Instruction Cache"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_sh->Wrap( -1 );
	m_staticText_sh->Hide();

	bSizer1->Add( m_staticText_sh, 0, wxALL, 5 );

	m_gauge_sh = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_sh->SetValue( 0 );
	m_gauge_sh->Hide();

	bSizer1->Add( m_gauge_sh, 0, wxALL|wxEXPAND, 5 );

	m_staticText_spi = new wxStaticText( this, wxID_ANY, wxT("Shader Interpolator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_spi->Wrap( -1 );
	m_staticText_spi->Hide();

	bSizer1->Add( m_staticText_spi, 0, wxALL, 5 );

	m_gauge_spi = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_spi->SetValue( 0 );
	m_gauge_spi->Hide();

	bSizer1->Add( m_gauge_spi, 0, wxALL|wxEXPAND, 5 );

	m_staticText_smx = new wxStaticText( this, wxID_ANY, wxT("Shader Memory Exchange"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_smx->Wrap( -1 );
	m_staticText_smx->Hide();

	bSizer1->Add( m_staticText_smx, 0, wxALL, 5 );

	m_gauge_smx = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_smx->SetValue( 0 );
	m_gauge_smx->Hide();

	bSizer1->Add( m_gauge_smx, 0, wxALL|wxEXPAND, 5 );

	m_staticText_sc = new wxStaticText( this, wxID_ANY, wxT("Scan Converter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_sc->Wrap( -1 );
	m_staticText_sc->Hide();

	bSizer1->Add( m_staticText_sc, 0, wxALL, 5 );

	m_gauge_sc = new wxGauge( this, wxID_ANY, 100, wxPoint( -1,-1 ), wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_sc->SetValue( 0 );
	m_gauge_sc->Hide();

	bSizer1->Add( m_gauge_sc, 0, wxALL|wxEXPAND, 5 );

	m_staticText_pa = new wxStaticText( this, wxID_ANY, wxT("Primitive Assembly"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_pa->Wrap( -1 );
	bSizer1->Add( m_staticText_pa, 0, wxALL, 5 );

	m_gauge_pa = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_pa->SetValue( 0 );
	bSizer1->Add( m_gauge_pa, 0, wxALL|wxEXPAND, 5 );

	m_staticText_db = new wxStaticText( this, wxID_ANY, wxT("Depth Block"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_db->Wrap( -1 );
	m_staticText_db->Hide();

	bSizer1->Add( m_staticText_db, 0, wxALL, 5 );

	m_gauge_db = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_db->SetValue( 0 );
	m_gauge_db->Hide();

	bSizer1->Add( m_gauge_db, 0, wxALL|wxEXPAND, 5 );

	m_staticText_cb = new wxStaticText( this, wxID_ANY, wxT("Color Block"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_cb->Wrap( -1 );
	m_staticText_cb->Hide();

	bSizer1->Add( m_staticText_cb, 0, wxALL, 5 );

	m_gauge_cb = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL|wxVSCROLL );
	m_gauge_cb->SetValue( 0 );
	m_gauge_cb->Hide();

	bSizer1->Add( m_gauge_cb, 0, wxALL|wxEXPAND, 5 );

	m_staticText_cr = new wxStaticText( this, wxID_ANY, wxT("Clip Rectangle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_cr->Wrap( -1 );
	m_staticText_cr->Hide();

	bSizer1->Add( m_staticText_cr, 0, wxALL, 5 );

	m_gauge_cr = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_cr->SetValue( 0 );
	m_gauge_cr->Hide();

	bSizer1->Add( m_gauge_cr, 0, wxALL|wxEXPAND, 5 );

	m_staticText_vram = new wxStaticText( this, wxID_ANY, wxT("VRAM"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_vram->Wrap( -1 );
	bSizer1->Add( m_staticText_vram, 0, wxALL, 5 );

	m_gauge_vram = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_vram->SetValue( 0 );
	bSizer1->Add( m_gauge_vram, 0, wxALL|wxEXPAND, 5 );

	m_staticText_gtt = new wxStaticText( this, wxID_ANY, wxT("GTT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_gtt->Wrap( -1 );
	bSizer1->Add( m_staticText_gtt, 0, wxALL, 5 );

	m_gauge_gtt = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_gtt->SetValue( 0 );
	bSizer1->Add( m_gauge_gtt, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_timer1.SetOwner( this, wxID_ANY );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnSize ) );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, menuFileQuit->GetId());
	settingmenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRefRate ), this, menuRefRate->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gui ), this, mviewstats_gui->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ee ), this, mviewstats_ee->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vgt ), this, mviewstats_vgt->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ta ), this, mviewstats_ta->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_tc ), this, mviewstats_tc->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sx ), this, mviewstats_sx->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sh ), this, mviewstats_sh->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_spi ), this, mviewstats_spi->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_smx ), this, mviewstats_smx->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sc ), this, mviewstats_sc->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_pa ), this, mviewstats_pa->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_db ), this, mviewstats_db->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cb ), this, mviewstats_cb->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cr ), this, mviewstats_cr->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vram ), this, mviewstats_vram->GetId());
	menuview_stats->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gtt ), this, mviewstats_gtt->GetId());
	viewmenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuery ), this, mviewQuery->GetId());
	viewmenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCpuQuery ), this, mviewCPU->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ), this, menuHelpAbout->GetId());
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::UpdateVal ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnSize ) );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::UpdateVal ) );

}

QueryDialog::QueryDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxString QchoiceRadeonChoices[] = { wxEmptyString, wxT("CLOCK_CRYSTAL_FREQ"), wxT("NUM_TILE_PIPES"), wxT("MAX_SE"), wxT("MAX_SH_PER_SE"), wxT("MAX_SCLK"), wxT("VCE_FW_VERSION"), wxT("VCE_FB_VERSION"), wxT("ACTIVE_CU_COUNT"), wxT("CURRENT_GPU_TEMP") };
	int QchoiceRadeonNChoices = sizeof( QchoiceRadeonChoices ) / sizeof( wxString );
	QchoiceRadeon = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, QchoiceRadeonNChoices, QchoiceRadeonChoices, 0 );
	QchoiceRadeon->SetSelection( 0 );
	bSizer2->Add( QchoiceRadeon, 0, wxALL, 5 );

	wxString QchoiceAMDChoices[] = { wxEmptyString, wxT("Sensors"), wxT("Hardware"), wxT("UVD"), wxT("VCE") };
	int QchoiceAMDNChoices = sizeof( QchoiceAMDChoices ) / sizeof( wxString );
	QchoiceAMD = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, QchoiceAMDNChoices, QchoiceAMDChoices, 0 );
	QchoiceAMD->SetSelection( 0 );
	bSizer2->Add( QchoiceAMD, 0, wxALL, 5 );

	QtextCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( QtextCtrl1, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( QueryDialog::OnQueryClose ) );
	QchoiceRadeon->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoiceR ), NULL, this );
	QchoiceAMD->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoiceA ), NULL, this );
}

QueryDialog::~QueryDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( QueryDialog::OnQueryClose ) );
	QchoiceRadeon->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoiceR ), NULL, this );
	QchoiceAMD->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoiceA ), NULL, this );

}

CpuQueryDialog::CpuQueryDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 420,140 ), wxDefaultSize );

	topSizer = new wxBoxSizer( wxVERTICAL );

	choiceSizer = new wxFlexGridSizer( 0, 4, 0, 0 );
	choiceSizer->SetFlexibleDirection( wxHORIZONTAL );
	choiceSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_staticText_limit = new wxStaticText( this, wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_limit->Wrap( -1 );
	choiceSizer->Add( m_staticText_limit, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice_limitChoices[] = { wxT("ALL"), wxT("NONE") };
	int m_choice_limitNChoices = sizeof( m_choice_limitChoices ) / sizeof( wxString );
	m_choice_limit = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_limitNChoices, m_choice_limitChoices, 0 );
	m_choice_limit->SetSelection( 0 );
	choiceSizer->Add( m_choice_limit, 1, wxALL|wxEXPAND, 5 );


	choiceSizer->Add( 120, 0, 1, wxEXPAND, 5 );

	m_checkBox_avg = new wxCheckBox( this, wxID_ANY, wxT("Avarage"), wxDefaultPosition, wxDefaultSize, 0 );
	choiceSizer->Add( m_checkBox_avg, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	topSizer->Add( choiceSizer, 1, wxALL|wxEXPAND, 5 );

	m_staticText_reduced = new wxStaticText( this, wxID_ANY, wxT("Reduced"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_reduced->Wrap( -1 );
	topSizer->Add( m_staticText_reduced, 0, wxALL, 5 );

	m_gauge_reduced = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_reduced->SetValue( 0 );
	topSizer->Add( m_gauge_reduced, 0, wxALL|wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	topSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	middleSizer = new wxBoxSizer( wxVERTICAL );

	middleSizer->SetMinSize( wxSize( -1,300 ) );
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	scrolledSizer = new wxBoxSizer( wxVERTICAL );


	m_scrolledWindow1->SetSizer( scrolledSizer );
	m_scrolledWindow1->Layout();
	scrolledSizer->Fit( m_scrolledWindow1 );
	middleSizer->Add( m_scrolledWindow1, 1, wxEXPAND | wxALL, 5 );


	topSizer->Add( middleSizer, 1, wxEXPAND, 5 );


	this->SetSizer( topSizer );
	this->Layout();
	timer_cpu.SetOwner( this, wxID_ANY );
	timer_cpu.Start( 600 );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CpuQueryDialog::OnCpuDialogClose ) );
	m_choice_limit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CpuQueryDialog::OnChoiceCpuLimit ), NULL, this );
	m_checkBox_avg->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CpuQueryDialog::OnCheckBoxAvg ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CpuQueryDialog::UpdateCpuVal ) );
}

CpuQueryDialog::~CpuQueryDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CpuQueryDialog::OnCpuDialogClose ) );
	m_choice_limit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CpuQueryDialog::OnChoiceCpuLimit ), NULL, this );
	m_checkBox_avg->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CpuQueryDialog::OnCheckBoxAvg ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CpuQueryDialog::UpdateCpuVal ) );

}

DialogRR::DialogRR( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	textCtrlRefRate = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( textCtrlRefRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("milisecond"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer7->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	buttonSet = new wxButton( this, wxID_ANY, wxT("Set"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( buttonSet, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );

	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("(1 second = 1000 msecond)\nLess value = more CPU cycles"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer6->Add( m_staticText23, 0, wxALL, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	buttonSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogRR::OnSetVal ), NULL, this );
}

DialogRR::~DialogRR()
{
	// Disconnect Events
	buttonSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DialogRR::OnSetVal ), NULL, this );

}
