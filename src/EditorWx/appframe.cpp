#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include "wx/htmllbox.h"
#include "wx/splitter.h"
#include "wx/event.h"
#include <wx/thread.h>


//! application headers
#include "appdefs.h"       // Prefs
#include "defsext.h"     // Additional definitions
#include "edit.h"        // Edit module
#include "ViewGCode.h"

#include "about.h"
#include "propertiesdlg.h"
#include "appframe.h"       // Prefs
#include "environmentsimple.h"
#include "executorlog.h"
#include "ExecutorView.h"
#include "GCodeInterpreter.h"
#include "macrosesdlg.h"
#include "macrosparamdlg.h"
#include "standartpaths.h"

//Bitmaps
#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/find.xpm"
#include "bitmaps/check.xpm"
#include "bitmaps/undo.xpm"
#include "bitmaps/redo.xpm"





using namespace Interpreter;

//----------------------------------------------------------------------------
// resources
//----------------------------------------------------------------------------

// the application icon (under Windows it is in resources)
#ifndef wxHAS_IMAGES_IN_RESOURCES
//    #include "../sample.xpm"
#endif


class IntGCodeThread : public wxThread
{
public:
	IntGCodeThread(AppFrame *handler, wxString &fname_)
		: fname(fname_), wxThread(wxTHREAD_DETACHED)
	{

		m_pHandler = handler;
		penv = new EnvironmentSimple();
		pexec = new ExecutorLogWnd(m_pHandler, true);
		plogger = new LoggerWnd(m_pHandler);
		ppret = new GCodeInterpreter(penv, pexec, plogger);

	}
	~IntGCodeThread();
private:


protected:
	virtual wxThread::ExitCode Entry();
	AppFrame *m_pHandler;
	EnvironmentSimple *penv;
	ExecutorLogWnd *pexec;
	LoggerWnd *plogger;
	GCodeInterpreter *ppret;
	wxString fname;
};


class SimulateGCodeThread : public wxThread
{
public:
	SimulateGCodeThread(AppFrame *handler, wxString &fname_)
		: fname(fname_), wxThread(wxTHREAD_DETACHED)
	{

		m_pHandler = handler;
		penv = new EnvironmentSimple();
		pexec = new ExecutorView(plogger);
		plogger = new LoggerWnd(m_pHandler);
		ppret = new GCodeInterpreter(penv, pexec, plogger);

	}
	~SimulateGCodeThread();

	std::vector<TrackPoint> *getTack() { return pexec->getTrack(); }
	CoordsBox getBox() { return pexec->getBox(); }

protected:
	virtual wxThread::ExitCode Entry();
	AppFrame *m_pHandler;
	EnvironmentSimple *penv;
	ExecutorView *pexec;
	LoggerWnd *plogger;
	GCodeInterpreter *ppret;
	wxString fname;
};


//----------------------------------------------------------------------------
// AppFrame
//----------------------------------------------------------------------------


wxBEGIN_EVENT_TABLE (AppFrame, wxFrame)
    // common
    EVT_CLOSE (                      AppFrame::OnClose)
    // file
	EVT_MENU(wxID_NEW, AppFrame::OnFileNew)
    EVT_MENU (wxID_OPEN,             AppFrame::OnFileOpen)
    EVT_MENU (wxID_SAVE,             AppFrame::OnFileSave)
    EVT_MENU (wxID_SAVEAS,           AppFrame::OnFileSaveAs)
    EVT_MENU (wxID_CLOSE,            AppFrame::OnFileClose)
    // properties
    EVT_MENU (myID_PROPERTIES,       AppFrame::OnProperties)
    // print and exit
    EVT_MENU (wxID_EXIT,             AppFrame::OnExit)
    // Menu items with standard IDs forwarded to the editor.
    EVT_MENU (wxID_CLEAR,            AppFrame::OnEdit)
    EVT_MENU (wxID_CUT,              AppFrame::OnEdit)
    EVT_MENU (wxID_COPY,             AppFrame::OnEdit)
    EVT_MENU (wxID_PASTE,            AppFrame::OnEdit)
    EVT_MENU (wxID_SELECTALL,        AppFrame::OnEdit)
    EVT_MENU (wxID_REDO,             AppFrame::OnEdit)
    EVT_MENU (wxID_UNDO,             AppFrame::OnEdit)
    EVT_MENU (wxID_FIND,             AppFrame::OnEdit)
    // And all our edit-related menu commands.
    EVT_MENU_RANGE (myID_EDIT_FIRST, myID_EDIT_LAST,
                                     AppFrame::OnEdit)
    // help
    EVT_MENU (wxID_ABOUT,            AppFrame::OnAbout)
  //  EVT_CONTEXT_MENU(                AppFrame::OnContextMenu)
//GCode
	EVT_MENU(ID_GCODE_CHECK, AppFrame::OnCheck)
	EVT_MENU(ID_GCODE_SIMULATE, AppFrame::OnSimulate)
	EVT_MENU(ID_GCODE_CONVERTGCMC, AppFrame::OnConvertGcmc)

	EVT_UPDATE_UI(ID_GCODE_CHECK, AppFrame::OnUpdateCheck)
	EVT_UPDATE_UI(ID_GCODE_SIMULATE, AppFrame::OnUpdateSimulate)
	EVT_UPDATE_UI(ID_GCODE_CONVERTGCMC, AppFrame::OnUpdateConvertGcmc)

	

	
	EVT_MENU_RANGE(myID_SETVIEWFIRST, myID_SETVIEWLAST, AppFrame::On3DView)
	

	EVT_THREAD(CHECK_GCODE_UPDATE, AppFrame::OnThreadUpdate)
	EVT_THREAD(CHECK_GCODE_COMPLETE, AppFrame::OnThreadCompletion)


	EVT_THREAD(CHECK_SIMULATE_UPDATE, AppFrame::OnSimulateUpdate)
	EVT_THREAD(CHECK_SIMULATE_COMPLETE, AppFrame::OnSimulateCompletion)

	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_UPDATE, AppFrame::OnThreadUpdate)
	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_COMPLETED, AppFrame::OnThreadCompletion)
	
wxEND_EVENT_TABLE ()


AppFrame::AppFrame (const wxString &title)
        : wxFrame ((wxFrame *)NULL, wxID_ANY, title, wxDefaultPosition, wxSize(750,550),
                    wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
    SetIcon(wxICON(sample));
	checkThread = NULL;
	simulateThread = NULL;
	
	// initialize important variables
    m_edit = NULL;
	
    // set icon and background
    SetTitle (APP_NAME);
    SetBackgroundColour ("WHITE");

    // create menu
    m_menuBar = new wxMenuBar;
    CreateMenu ();

  	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);
	wxToolBar *toolBar= CreateToolBar();
	sizer->Add(toolBar, 0, wxEXPAND);
	toolBar->Realize();

	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	sizer->Add(splitter, 1, wxEXPAND);
	splitter->SetSashGravity(1.0);

	wxSplitterWindow* splitterV = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	splitterV->SetSashGravity(1.0);


	// open first page
	m_edit = new Edit(splitterV, wxID_ANY);

	//int gl_attrib[20] =	{ WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
		//				WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1, WX_GL_DOUBLEBUFFER, GL_NONE };

	m_view = new ViewGCode(splitterV, wxID_ANY/*, gl_attrib*/ );
	
	m_hlbox = new wxSimpleHtmlListBox(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		0, NULL, wxLB_MULTIPLE);

	splitter->SplitHorizontally(splitterV, m_hlbox,  -100);
	splitterV->SplitVertically(m_edit, m_view, -300 );

	Layout();
	splitter->UpdateSize();
	splitterV->UpdateSize();

	m_edit->SetFocus();
	m_view->initializeGL();
	//m_view->SetFocus();
}

AppFrame::~AppFrame () {
}

// common event handlers
void AppFrame::OnClose (wxCloseEvent &event)
{

	{
		wxCriticalSectionLocker enter(critsect);
		if (checkThread)         // does the thread still exist?
		{
			checkThread->Delete();
		}
		if (simulateThread)
		{
			simulateThread->Delete();
		}
	}       // exit from the critical section to give the thread
			// the possibility to enter its destructor
			// (which is guarded with m_pThreadCS critical section!)
	while (1)
	{
		{ // was the ~MyThread() function executed?
			wxCriticalSectionLocker enter(critsect);
			if (!checkThread && !simulateThread ) break;
		}
		// wait for thread completion
		wxThread::This()->Sleep(1);
	}

   
	DoFileSave( true, false );
 //   if (m_edit && m_edit->Modified()) 
	//{
 //       if (event.CanVeto()) event.Veto (true);
 //       return;
 //   }
    Destroy();
}

void AppFrame::OnAbout (wxCommandEvent &WXUNUSED(event)) {
    AppAbout dlg(this);
}

void AppFrame::OnExit (wxCommandEvent &WXUNUSED(event)) {
    Close (true);
}

bool AppFrame::DoFileSave(bool askToSave, bool bSaveAs )
{
	if (!m_edit) return false;
	if ( !m_edit->Modified() )
		return true;

	// Ask need to save
	if (askToSave)
	{
		int rez = wxMessageBox(_("Text is not saved, save before closing?"), _("Save file"),
			wxYES_NO | wxCANCEL | wxICON_QUESTION);
		if (rez == wxCANCEL)
			return false;
		else if (rez == wxNO)
			return true;
	}
	// Need save
	wxString fname = m_edit->GetFilename();
	if (bSaveAs || fname.empty())
	{
		wxString filename = wxEmptyString;
		wxFileDialog dlg(this, "Save file As", wxEmptyString, wxEmptyString, "GCode Files (*.ngc)|*.ngc", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() != wxID_OK)
			return false;
		filename = dlg.GetPath();
		m_edit->SaveFile(filename);
	}
	else //  fname exist && not save as  - just save
	{
		m_edit->SaveFile();
		if (m_edit->Modified())
		{
			wxMessageBox(_("Text could not be saved!"), _("Close abort"),
				wxOK | wxICON_EXCLAMATION);
			return false;
		}
	}
	return true;
}


void AppFrame::FileChanged()
{
	UpdateTitle();
	m_hlbox->Clear();
	m_view->clear();
}

void AppFrame::OnFileNew(wxCommandEvent &WXUNUSED(event))
{
	if ( !DoFileSave(true, false) )
	{
		return;
	}
	m_edit->NewFile();
	FileChanged();
}

// file event handlers
void AppFrame::OnFileOpen (wxCommandEvent &WXUNUSED(event)) 
{

	if ( !DoFileSave(true, false))
		return;
    
	wxString fname;
    wxFileDialog dlg (this, "Open file", wxEmptyString, wxEmptyString, "Any file (*)|*",
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() != wxID_OK) return;
    fname = dlg.GetPath ();
    FileOpen (fname);
}

void AppFrame::OnFileSave (wxCommandEvent &WXUNUSED(event)) 
{
	DoFileSave( false, false );
    UpdateTitle();
}

void AppFrame::OnFileSaveAs(wxCommandEvent &WXUNUSED(event))
{
	DoFileSave(false, true);
	UpdateTitle();
}

void AppFrame::OnFileClose (wxCommandEvent &event) 
{
	OnFileNew(event);
}

// properties event handlers
void AppFrame::OnProperties (wxCommandEvent &WXUNUSED(event)) {
    if (!m_edit) return;
    //EditProperties dlg(m_edit, 0);
	Macroses msc;
	std::wstring path = StandartPaths::Get()->GetMacrosPath();
	msc.parse_dir(path.c_str(), true);
	MacrosesDlg dlg(&msc, this);	
	int indx = dlg.GetSelected();
	if (indx < 0 || indx >= msc.count() )
		return;
	
	MacrosDesc &desc = msc.get(indx);

	MacrosParamDlg dlgparam(&desc, this);
	if (dlgparam.ShowModal() != wxID_OK)
		return;



	wxString  args = msc.build_commad_line(indx);

	std::wstring src_fname = StandartPaths::Get()->GetMacrosPath( desc.gcmcfile.c_str() );
	std::wstring dst_fname = StandartPaths::Get()->GetTemporaryPath(L"tmp.nc");
	
	int code = RunGcmc(src_fname.c_str(), dst_fname.c_str(), args.c_str());

	if (code != 0) // error
		return;
	

	m_edit->PasteFile( dst_fname );
}

// edit events
void AppFrame::OnEdit (wxCommandEvent &event) {
    if (m_edit) m_edit->GetEventHandler()->ProcessEvent (event);
}

void AppFrame::On3DView(wxCommandEvent &event) {
	if (m_view) m_view->GetEventHandler()->ProcessEvent(event);
}

void AppFrame::OnContextMenu(wxContextMenuEvent& evt)
{
    wxPoint point = evt.GetPosition();
    // If from keyboard
    if ( point.x == -1 && point.y == -1 )
    {
        wxSize size = GetSize();
        point.x = size.x / 2;
        point.y = size.y / 2;
    }
    else
    {
        point = ScreenToClient(point);
    }

    wxMenu menu;
    menu.Append(wxID_ABOUT, "&About");
    menu.Append(wxID_EXIT, "E&xit");
    PopupMenu(&menu, point);
}

// private functions
void AppFrame::CreateMenu ()
{
    // File menu
    wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_NEW, _("&New ..\tCtrl+O"));
    menuFile->Append (wxID_OPEN, _("&Open ..\tCtrl+O"));
    menuFile->Append (wxID_SAVE, _("&Save\tCtrl+S"));
    menuFile->Append (wxID_SAVEAS, _("Save &as ..\tCtrl+Shift+S"));
    menuFile->Append (wxID_CLOSE, _("&Close\tCtrl+W"));
    menuFile->AppendSeparator();
    menuFile->Append (myID_PROPERTIES, _("Proper&ties ..\tCtrl+I"));
    menuFile->AppendSeparator();
    menuFile->Append (wxID_PRINT_SETUP, _("Print Set&up .."));
    menuFile->Append (wxID_PREVIEW, _("Print Pre&view\tCtrl+Shift+P"));
    menuFile->Append (wxID_PRINT, _("&Print ..\tCtrl+P"));
    menuFile->AppendSeparator();
    menuFile->Append (wxID_EXIT, _("&Quit\tCtrl+Q"));



	// change case submenu
	wxMenu *menuChangeCase = new wxMenu;
	menuChangeCase->Append(myID_CHANGEUPPER, _("&Upper case"));
	menuChangeCase->Append(myID_CHANGELOWER, _("&Lower case"));

	// convert EOL submenu
	wxMenu *menuConvertEOL = new wxMenu;
	menuConvertEOL->Append(myID_CONVERTCR, _("CR (&Linux)"));
	menuConvertEOL->Append(myID_CONVERTCRLF, _("CR+LF (&Windows)"));
	menuConvertEOL->Append(myID_CONVERTLF, _("LF (&Macintosh)"));

    // Edit menu
    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append (wxID_UNDO, _("&Undo\tCtrl+Z"));
    menuEdit->Append (wxID_REDO, _("&Redo\tCtrl+Shift+Z"));
    menuEdit->AppendSeparator();
    menuEdit->Append (wxID_CUT, _("Cu&t\tCtrl+X"));
    menuEdit->Append (wxID_COPY, _("&Copy\tCtrl+C"));
    menuEdit->Append (wxID_PASTE, _("&Paste\tCtrl+V"));
    menuEdit->Append (wxID_CLEAR, _("&Delete\tDel"));
    menuEdit->AppendSeparator();
    menuEdit->Append (wxID_FIND, _("&Find\tCtrl+F"));
    menuEdit->Enable (wxID_FIND, false);
    menuEdit->Append (myID_FINDNEXT, _("Find &next\tF3"));
    menuEdit->Enable (myID_FINDNEXT, false);
    menuEdit->Append (myID_REPLACE, _("&Replace\tCtrl+H"));
    menuEdit->Enable (myID_REPLACE, false);
    menuEdit->Append (myID_REPLACENEXT, _("Replace &again\tShift+F4"));
    menuEdit->Enable (myID_REPLACENEXT, false);
    menuEdit->AppendSeparator();
    menuEdit->Append (wxID_SELECTALL, _("&Select all\tCtrl+A"));
    menuEdit->Append (myID_SELECTLINE, _("Select &line\tCtrl+L"));
	menuEdit->AppendSeparator();
	menuEdit->Append(myID_CHANGECASE, _("Change &case to .."), menuChangeCase);
	menuEdit->Append(myID_CONVERTEOL, _("Convert line &endings to .."), menuConvertEOL);
	menuEdit->AppendSeparator();
	menuEdit->AppendCheckItem(myID_READONLY, _("&Readonly mode"));
	   	

    // highlight submenu
    wxMenu *menuHighlight = new wxMenu;
    int Nr;
    for (Nr = 0; Nr < g_LanguagePrefsSize; Nr++) {
        menuHighlight->Append (myID_HIGHLIGHTFIRST + Nr,
                             g_LanguagePrefs [Nr].name);
    }

    // charset submenu
    wxMenu *menuCharset = new wxMenu;
    menuCharset->Append (myID_CHARSETANSI, _("&ANSI (Windows)"));
    menuCharset->Append (myID_CHARSETMAC, _("&MAC (Macintosh)"));

    // View menu
    wxMenu *menuView = new wxMenu;
    menuView->Append (myID_HIGHLIGHTLANG, _("&Highlight language .."), menuHighlight);
    menuView->AppendSeparator();
    menuView->AppendCheckItem (myID_DISPLAYEOL, _("Show line &endings"));
    menuView->AppendCheckItem (myID_INDENTGUIDE, _("Show &indent guides"));
    menuView->AppendCheckItem (myID_LINENUMBER, _("Show line &numbers"));
    menuView->AppendCheckItem (myID_WHITESPACE, _("Show white&space"));
    menuView->AppendSeparator();
    menuView->Append (myID_USECHARSET, _("Use &code page of .."), menuCharset);

	menuView->FindChildItem(myID_LINENUMBER)->Check(true);

	// Edit menu
	wxMenu *menuGCode = new wxMenu;
	menuGCode->Append(ID_GCODE_CHECK, _("&Check"));
	menuGCode->Append(ID_GCODE_SIMULATE, _("&Simulate"));
	menuGCode->Append(ID_GCODE_CONVERTGCMC, _("&Convert Gcmc"));


	// 3dView menu
	wxMenu *menu3D = new wxMenu;
	menu3D->Append(myID_SETVIEWFIRST + 6, _("&Isometric"));
	menu3D->Append(myID_SETVIEWFIRST,	  _("&Top"));
	menu3D->Append(myID_SETVIEWFIRST+1,   _("&Bottom"));
	menu3D->Append(myID_SETVIEWFIRST+2,   _("&Left"));
	menu3D->Append(myID_SETVIEWFIRST+3,   _("&Right"));
	menu3D->Append(myID_SETVIEWFIRST+4,   _("&Front"));
	menu3D->Append(myID_SETVIEWFIRST+5,   _("&Back"));
	
	
	 
     // Help menu
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append (wxID_ABOUT, _("&About ..\tCtrl+D"));

    // construct menu
    m_menuBar->Append (menuFile, _("&File"));
    m_menuBar->Append (menuEdit, _("&Edit"));
    m_menuBar->Append (menuView, _("&View"));
	m_menuBar->Append(menuGCode, _("&GCode"));
	m_menuBar->Append(menu3D, _("&3DView"));
    m_menuBar->Append (menuHelp, _("&Help"));
    SetMenuBar (m_menuBar);
}

wxToolBar *AppFrame::CreateToolBar()
{
	wxToolBar* toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER | wxTB_NOALIGN);

	toolBar->AddTool(wxID_NEW, wxEmptyString, wxBitmap(new_xpm), _("New"));
	toolBar->AddTool(wxID_OPEN, wxEmptyString, wxBitmap(open_xpm), _("Open"));
	toolBar->AddTool(wxID_SAVE, wxEmptyString, wxBitmap(save_xpm), _("Save"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Cut"));
	toolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Cut"));
	toolBar->AddSeparator();
	toolBar->AddTool(myID_PROPERTIES, wxEmptyString, wxBitmap(cut_xpm), _("Macroses"));
	toolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy"));
	toolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste"));
	toolBar->AddSeparator();
	toolBar->AddTool(ID_GCODE_CHECK, wxEmptyString, wxBitmap(check_xpm), _("Check"));
	toolBar->AddTool(ID_GCODE_SIMULATE, wxEmptyString, wxBitmap(find_xpm), _("Simulate"));
	toolBar->AddTool(ID_GCODE_CONVERTGCMC, wxEmptyString, wxBitmap(new_xpm), _("Convert"));
	
//	toolBar->Realize();
	return toolBar;
}

void AppFrame::FileOpen (wxString fname)
{
    wxFileName w(fname); w.Normalize(); fname = w.GetFullPath();
    m_edit->LoadFile (fname);
    m_edit->SelectNone();
	FileChanged();
}




void AppFrame::UpdateTitle()
{
	wxString title;
	if (m_edit)
	{
		wxFileName w(m_edit->GetFilename());
		title = w.GetFullName();
		if (m_edit->Modified())
			title += "*";
	}

	if (!title.IsEmpty())
	{
		title += " - ";
		title += APP_NAME;
	}
	else
		title = APP_NAME;
	SetTitle(title);

}

wxRect AppFrame::DeterminePrintSize () {

    wxSize scr = wxGetDisplaySize();

    // determine position and size (shifting 16 left and down)
    wxRect rect = GetRect();
    rect.x += 16;
    rect.y += 16;
    rect.width = wxMin (rect.width, (scr.x - rect.x));
    rect.height = wxMin (rect.height, (scr.x - rect.y));

    return rect;
}



void AppFrame::OnUpdateCheck(wxUpdateUIEvent& event)
{
	if (checkThread && checkThread->IsRunning() )
		event.Enable(false);
	else
		event.Enable(true);
}

void AppFrame::OnUpdateSimulate(wxUpdateUIEvent& event)
{
	if (simulateThread && simulateThread->IsRunning())
		event.Enable(false);
	else
		event.Enable(true);
}


IntGCodeThread::~IntGCodeThread()
{
	wxCriticalSectionLocker enter(m_pHandler->critsect);
	// the thread is being destroyed; make sure not to leave dangling pointers around
	m_pHandler->checkThread = NULL;
	if(penv )delete penv;
	if(pexec) delete pexec;
	if(plogger) delete plogger;
	if(ppret) delete ppret;
}


wxThread::ExitCode IntGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file( fname.c_str() ) )
			return NULL;
		ppret->execute_file();
	}
	plogger->log(LOG_INFORMATION, "Feed Lenght: %f", pexec->get_feed_len());
	plogger->log(LOG_INFORMATION, "Traverce Lenght: %f", pexec->get_traverce_len());
	plogger->log(LOG_INFORMATION, "X Min: %f X Max %f", pexec->getBox().Min.x, pexec->getBox().Max.x);
	plogger->log(LOG_INFORMATION, "Y Min: %f Y Max %f", pexec->getBox().Min.y, pexec->getBox().Max.y);
	plogger->log(LOG_INFORMATION, "Z Min: %f Z Max %f", pexec->getBox().Min.z, pexec->getBox().Max.z);

	wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_COMPLETE));
	return NULL;
}


SimulateGCodeThread::~SimulateGCodeThread()
{
	wxCriticalSectionLocker enter(m_pHandler->critsect);
	// the thread is being destroyed; make sure not to leave dangling pointers around
	
	m_pHandler->m_view->setTrack( getTack() );
	m_pHandler->m_view->setBox(getBox());

	m_pHandler->simulateThread = NULL;
	if (penv)delete penv;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode SimulateGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.c_str()))
			return NULL;
		ppret->execute_file();
	}
	//output stat

	wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_THREAD, CHECK_SIMULATE_COMPLETE));
	return NULL;
}



wxString AppFrame::GetText()
{
	if (m_edit)
		return m_edit->GetText();
	else
		return wxString();
}

void AppFrame::OnThreadCompletion(wxThreadEvent&)
{
	wxString label("<font color=#008800>Checking completed</font>");
	if (m_hlbox)
	m_hlbox->Append(label);
}

void AppFrame::OnThreadUpdate(wxThreadEvent &ev)
{
	if (m_hlbox)
	{
		m_hlbox->Append(ev.GetString());
		m_hlbox->Update();
	}

}

void AppFrame::OnSimulateUpdate(wxThreadEvent &ev)
{
	if (m_hlbox)
		m_hlbox->Append(ev.GetString());
}

void AppFrame::OnSimulateCompletion(wxThreadEvent&)
{
	//drea
	wxCriticalSectionLocker enter(critsect);
	if (simulateThread && m_view )
	{
		m_view->setTrack(simulateThread->getTack());
		m_view->setBox(simulateThread->getBox());
	}
}

wxString AppFrame::GetSavedFileName()
{
	if ( !DoFileSave(false, false) )
		return wxString();
	return m_edit->GetFilename();
}

void  AppFrame::OnCheck(wxCommandEvent &event)
{
	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;	
	m_hlbox->Clear();
	checkThread = new IntGCodeThread(this, fname);
	if (checkThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Can't create the thread!");
		delete checkThread;
		checkThread = NULL;
	}
}

void  AppFrame::OnSimulate(wxCommandEvent &event)
{
	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;
	m_hlbox->Clear();

	simulateThread = new SimulateGCodeThread(this, fname);
	if (simulateThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Can't create the thread!");
		delete simulateThread;
		simulateThread = NULL;
	}
	return;
}

//static wxString GetDirFromFName( const wchar_t *src_fname, const char *add)
//{
////	std::filesystem::path p(src_fname);
////	std::wstring arg = p.parent_path();
//
//	wxString buf(src_fname);
//	wxString arg = buf.BeforeLast('/');
//	if (arg.IsEmpty())
//		arg = buf.BeforeLast('\\');
//	if (!arg.IsEmpty() && add)
//		arg += add;
//	return arg;
////}

bool AppFrame::CheckFileExist(const wchar_t *fname)
{
	if ( StandartPaths::Get()->CheckFileExist(fname) )
		return true;

	wxString inf = wxString::Format("<font color=#008800>File %s not found.</font>", fname );
	m_hlbox->Append(inf);
	return false;

}

int AppFrame::RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args)
{

	m_hlbox->Clear();
	// cheks files
	if (!CheckFileExist(src_fname))
		return 1;
	
	wxExecuteEnv env;
	//env.cwd = GetDirFromFName(src_fname, 0);
	env.cwd = L"C:\\Projects\\YAMotion\\YAMotion\\Data\\gcmc";//StandartPaths::Get()->GetDirFromFName(src_fname).c_str();

	wxString arg = StandartPaths::Get()->GetExecutablePath( L"gcmc_vc.exe" ).c_str();

	if (!CheckFileExist(arg))
		return 1;

	arg += " -o ";
	arg += "tmpp.nc";//dst_fname;
	arg += " ";
	if (args)
	arg += args;
	arg += " ";
	arg += src_fname;

	wxArrayString output;
	wxArrayString errors;

	
	wxString inf = wxString::Format("<font color=#008800>Process: %s is running...</font>", arg.c_str());
	m_hlbox->Append(inf);

	int code = wxExecute(arg, output, errors, wxEXEC_SYNC | wxEXEC_HIDE_CONSOLE, &env);
	m_hlbox->Append(errors);

	inf = wxString::Format("<font color=#008800>Process terminated with exit code %d</font>", code);
	m_hlbox->Append(inf);

	
	return code;

}


void AppFrame::OnConvertGcmc(wxCommandEvent &event)
{
	if (!DoFileSave(false, false))
		return;

	//-o g00.nc g0.gcmc
	// build command line

	
	wxString src_fname = m_edit->GetFilename();
	if (src_fname.IsEmpty())
		return;

	wxString dst_fname = src_fname.BeforeLast('.');
	if (dst_fname.IsEmpty())
		dst_fname = src_fname;
	dst_fname += wxString(".nc");

	int code = RunGcmc(src_fname, dst_fname, 0);
	   	 

	if ( code == 0 )// Ok
		FileOpen(dst_fname);


}


void AppFrame::OnUpdateConvertGcmc(wxUpdateUIEvent& event)
{
	const LanguageInfo * pl = m_edit->GetLanguageInfo();
	event.Enable(pl ? (strcmp(pl->name, g_LanguagePrefs[1].name) == 0) : false);
}




