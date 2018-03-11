///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 14 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

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
	
	viewmenu = new wxMenu();
	menuview_stats = new wxMenu();
	wxMenuItem* menuview_statsItem = new wxMenuItem( viewmenu, wxID_ANY, wxT("Stats"), wxEmptyString, wxITEM_NORMAL, menuview_stats );
	mviewstats_gui = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Graphics Pipe") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_gui );
	mviewstats_gui->Check( true );
	
	mviewstats_ee = new wxMenuItem( menuview_stats, wxID_ANY, wxString( wxT("Event Engine") ) , wxEmptyString, wxITEM_CHECK );
	menuview_stats->Append( mviewstats_ee );
	mviewstats_ee->Check( true );
	
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
	
	mbar->Append( viewmenu, wxT("&view") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxEmptyString, wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 2, 0, wxID_ANY );
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText_gui = new wxStaticText( this, wxID_ANY, wxT("Graphics Pipe"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_gui->Wrap( -1 );
	bSizer1->Add( m_staticText_gui, 0, wxALL, 5 );
	
	m_gauge_gui = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_gui->SetValue( 0 ); 
	bSizer1->Add( m_gauge_gui, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	m_staticText_ee = new wxStaticText( this, wxID_ANY, wxT("Event Engine"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_ee->Wrap( -1 );
	bSizer1->Add( m_staticText_ee, 0, wxALL, 5 );
	
	m_gauge_ee = new wxGauge( this, wxID_ANY, 100, wxPoint( -1,-1 ), wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_ee->SetValue( 0 ); 
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
	m_staticText_pa->Hide();
	
	bSizer1->Add( m_staticText_pa, 0, wxALL, 5 );
	
	m_gauge_pa = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL );
	m_gauge_pa->SetValue( 0 ); 
	m_gauge_pa->Hide();
	
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
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( mviewstats_gui->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gui ) );
	this->Connect( mviewstats_ee->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ee ) );
	this->Connect( mviewstats_vgt->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vgt ) );
	this->Connect( mviewstats_ta->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ta ) );
	this->Connect( mviewstats_tc->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_tc ) );
	this->Connect( mviewstats_sx->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sx ) );
	this->Connect( mviewstats_sh->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sh ) );
	this->Connect( mviewstats_spi->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_spi ) );
	this->Connect( mviewstats_smx->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_smx ) );
	this->Connect( mviewstats_sc->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sc ) );
	this->Connect( mviewstats_pa->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_pa ) );
	this->Connect( mviewstats_db->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_db ) );
	this->Connect( mviewstats_cb->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cb ) );
	this->Connect( mviewstats_cr->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cr ) );
	this->Connect( mviewstats_vram->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vram ) );
	this->Connect( mviewstats_gtt->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gtt ) );
	this->Connect( mviewQuery->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuery ) );
	this->Connect( mviewCPU->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCpuQuery ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::UpdateVal ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnSize ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gui ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ee ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vgt ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_ta ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_tc ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sx ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sh ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_spi ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_smx ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_sc ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_pa ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_db ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cb ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_cr ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_vram ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnViewStats_gtt ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuery ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnCpuQuery ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
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
	
	wxArrayString QchoiceAMDChoices;
	QchoiceAMD = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, QchoiceAMDChoices, 0 );
	QchoiceAMD->SetSelection( 0 );
	bSizer2->Add( QchoiceAMD, 0, wxALL, 5 );
	
	QtextCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( QtextCtrl1, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( QueryDialog::OnQueryClose ) );
	QchoiceRadeon->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoice ), NULL, this );
}

QueryDialog::~QueryDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( QueryDialog::OnQueryClose ) );
	QchoiceRadeon->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( QueryDialog::OnQChoice ), NULL, this );
	
}

CpuQueryDialog::CpuQueryDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	CpuSizer = new wxBoxSizer( wxVERTICAL );
	
	
	this->SetSizer( CpuSizer );
	this->Layout();
	timer_cpu.SetOwner( this, wxID_ANY );
	timer_cpu.Start( 750 );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CpuQueryDialog::OnCpuDialogClose ) );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CpuQueryDialog::UpdateCpuVal ) );
}

CpuQueryDialog::~CpuQueryDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CpuQueryDialog::OnCpuDialogClose ) );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( CpuQueryDialog::UpdateCpuVal ) );
	
}
