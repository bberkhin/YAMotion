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


//Bitmaps
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
	IntGCodeThread(AppFrame *handler)
		: wxThread(wxTHREAD_DETACHED)
	{

		m_pHandler = handler;
		penv = new EnvironmentSimple();
		pexec = new ExecutorLogWnd(m_pHandler);
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
};


class SimulateGCodeThread : public wxThread
{
public:
	SimulateGCodeThread(AppFrame *handler)
		: wxThread(wxTHREAD_DETACHED)
	{

		m_pHandler = handler;
		penv = new EnvironmentSimple();
		pexec = new ExecutorView(m_pHandler);
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
};


//----------------------------------------------------------------------------
// AppFrame
//----------------------------------------------------------------------------


wxBEGIN_EVENT_TABLE (AppFrame, wxFrame)
    // common
    EVT_CLOSE (                      AppFrame::OnClose)
    // file
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
    EVT_CONTEXT_MENU(                AppFrame::OnContextMenu)
//GCode
	EVT_MENU(ID_GCODE_CHECK, AppFrame::OnCheck)
	EVT_MENU(ID_GCODE_SIMULATE, AppFrame::OnSimulate)

	EVT_UPDATE_UI(ID_GCODE_CHECK, AppFrame::OnUpdateCheck)
	EVT_UPDATE_UI(ID_GCODE_SIMULATE, AppFrame::OnUpdateSimulate)

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
	m_view->InitGL();
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


    wxCommandEvent evt;
    OnFileClose (evt);
    if (m_edit && m_edit->Modified()) {
        if (event.CanVeto()) event.Veto (true);
        return;
    }
    Destroy();
}

void AppFrame::OnAbout (wxCommandEvent &WXUNUSED(event)) {
    AppAbout dlg(this);
}

void AppFrame::OnExit (wxCommandEvent &WXUNUSED(event)) {
    Close (true);
}




// file event handlers
void AppFrame::OnFileOpen (wxCommandEvent &WXUNUSED(event)) 
{

	if (!m_edit) return;
    wxString fname;
    wxFileDialog dlg (this, "Open file", wxEmptyString, wxEmptyString, "Any file (*)|*",
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() != wxID_OK) return;
    fname = dlg.GetPath ();
    FileOpen (fname);
}

void AppFrame::OnFileSave (wxCommandEvent &WXUNUSED(event)) 
{
    if (!m_edit) return;
    if (!m_edit->Modified()) {
        wxMessageBox (_("There is nothing to save!"), _("Save file"),
                      wxOK | wxICON_EXCLAMATION);
        return;
    }
    m_edit->SaveFile ();
	UpdateTitle();
}

void AppFrame::OnFileSaveAs (wxCommandEvent &WXUNUSED(event)) {
    if (!m_edit) return;
    wxString filename = wxEmptyString;
    wxFileDialog dlg (this, "Save file", wxEmptyString, wxEmptyString, "Any file (*)|*", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() != wxID_OK) return;
    filename = dlg.GetPath();
    m_edit->SaveFile (filename);
	UpdateTitle();
}

void AppFrame::OnFileClose (wxCommandEvent &WXUNUSED(event)) {
    if (!m_edit) return;
    if (m_edit->Modified()) {
        if (wxMessageBox (_("Text is not saved, save before closing?"), _("Close"),
                          wxYES_NO | wxICON_QUESTION) == wxYES) {
            m_edit->SaveFile();
            if (m_edit->Modified()) {
                wxMessageBox (_("Text could not be saved!"), _("Close abort"),
                              wxOK | wxICON_EXCLAMATION);
                return;
            }
        }
    }
    m_edit->SetFilename (wxEmptyString);
    m_edit->ClearAll();
    m_edit->SetSavePoint();
	UpdateTitle();
}

// properties event handlers
void AppFrame::OnProperties (wxCommandEvent &WXUNUSED(event)) {
    if (!m_edit) return;
    EditProperties dlg(m_edit, 0);
}

// edit events
void AppFrame::OnEdit (wxCommandEvent &event) {
    if (m_edit) m_edit->GetEventHandler()->ProcessEvent (event);
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

	// Edit menu
	wxMenu *menuGCode = new wxMenu;
	menuGCode->Append(ID_GCODE_CHECK, _("&Check"));
	menuGCode->Append(ID_GCODE_SIMULATE, _("&Simulate"));
 
     // Help menu
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append (wxID_ABOUT, _("&About ..\tCtrl+D"));

    // construct menu
    m_menuBar->Append (menuFile, _("&File"));
    m_menuBar->Append (menuEdit, _("&Edit"));
    m_menuBar->Append (menuView, _("&View"));
	m_menuBar->Append(menuGCode, _("&GCode"));
    m_menuBar->Append (menuHelp, _("&Help"));
    SetMenuBar (m_menuBar);
}

wxToolBar *AppFrame::CreateToolBar()
{
	wxToolBar* toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER | wxTB_NOALIGN);

	toolBar->AddTool(wxID_OPEN, wxEmptyString, wxBitmap(open_xpm), _("Open"));
	toolBar->AddTool(wxID_SAVE, wxEmptyString, wxBitmap(save_xpm), _("Save"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Cut"));
	toolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Cut"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_CUT, wxEmptyString, wxBitmap(cut_xpm), _("Cut"));
	toolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy"));
	toolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste"));
	toolBar->AddSeparator();
	toolBar->AddTool(ID_GCODE_CHECK, wxEmptyString, wxBitmap(check_xpm), _("Check"));
	toolBar->AddTool(ID_GCODE_SIMULATE, wxEmptyString, wxBitmap(find_xpm), _("Simulate"));

//	toolBar->Realize();
	return toolBar;
}

void AppFrame::FileOpen (wxString fname)
{
    wxFileName w(fname); w.Normalize(); fname = w.GetFullPath();
    m_edit->LoadFile (fname);
    m_edit->SelectNone();
	UpdateTitle();

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

//ExecutorLog exec;
//EnvironmentSimple env;
//GCodeInterpreter ipret(&env, &exec);
//if (argc == 2)
//{
//	ipret.read_file(argv[1]);
//	ipret.execute_file(&exec);
//}
//






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
	wxString buf;
	if (m_pHandler)
	{
		wxCriticalSectionLocker locker(m_pHandler->critsect);
		buf = m_pHandler->GetText();
	}
	if(ppret)
		ppret->execute_file(buf.c_str());
	
	wxQueueEvent(m_pHandler, new wxThreadEvent(wxEVT_THREAD, CHECK_GCODE_COMPLETE));
	return NULL;
}


SimulateGCodeThread::~SimulateGCodeThread()
{
	wxCriticalSectionLocker enter(m_pHandler->critsect);
	// the thread is being destroyed; make sure not to leave dangling pointers around
	m_pHandler->m_view->setTrack(getTack());
	m_pHandler->m_view->setBox(getBox());

	m_pHandler->simulateThread = NULL;
	if (penv)delete penv;
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode SimulateGCodeThread::Entry()
{
	wxString buf;
	if (m_pHandler)
	{
		wxCriticalSectionLocker locker(m_pHandler->critsect);
		buf = m_pHandler->GetText();
	}
	if (ppret)
		ppret->execute_file(buf.c_str());

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


void  AppFrame::OnCheck(wxCommandEvent &event)
{
	if (!m_edit) return;
	m_hlbox->Clear();

	checkThread = new IntGCodeThread(this);
	if (checkThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Can't create the thread!");
		delete checkThread;
		checkThread = NULL;
	}
	return;
}

void  AppFrame::OnSimulate(wxCommandEvent &event)
{
	if (!m_edit || !m_view) return;
	m_hlbox->Clear();

	simulateThread = new SimulateGCodeThread(this);
	if (simulateThread->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError("Can't create the thread!");
		delete simulateThread;
		simulateThread = NULL;
	}
	return;
}
