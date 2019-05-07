#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include "wx/splitter.h"
#include "wx/event.h"
#include <wx/thread.h>
#include "wx/process.h"
#include "wx/txtstrm.h"


//! application headers
#include "app.h"
#include "appdefs.h"       // Prefs
#include "defsext.h"     // Additional definitions
#include "edit.h"        // Edit module
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
#include "logwindow.h"
#include "configdata.h"
#include "mathsimpledlg.h"
#include "mathexpressiondlg.h"
#include "welcomewnd.h"


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

#include "bitmaps/simulate.xpm"
#include "bitmaps/pause.xpm"
#include "bitmaps/stop.xpm"


#define YA_WRONG_N _("Wrong N value")



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
		pexec = new ExecutorLogWnd(m_pHandler, true);
		plogger = new LoggerWnd(m_pHandler);
		ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger);

	}
	~IntGCodeThread();
private:


protected:
	virtual wxThread::ExitCode Entry();
	AppFrame *m_pHandler;
	ExecutorLogWnd *pexec;
	LoggerWnd *plogger;
	GCodeInterpreter *ppret;
	wxString fname;
};


class SimulateGCodeThread : public wxThread
{
public:
	SimulateGCodeThread(AppFrame *handler, const wchar_t *fname_)
		: fname(fname_), wxThread(wxTHREAD_DETACHED)
	{

		m_pHandler = handler;
		pexec = new ExecutorView(plogger);
		plogger = new LoggerWnd(m_pHandler);
		ppret = new GCodeInterpreter(wxGetApp().GetEnvironment(), pexec, plogger);

	}
	~SimulateGCodeThread();

	std::vector<TrackPoint> *getTack() { return pexec->getTrack(); }
	CoordsBox getBox() { return pexec->getBox(); }

protected:
	virtual wxThread::ExitCode Entry();
	AppFrame *m_pHandler;	
	ExecutorView *pexec;
	LoggerWnd *plogger;
	GCodeInterpreter *ppret;
	wxString fname;
};


// A specialization of MyProcess for redirecting the output
class GcmcProcess : public wxProcess
{
public:
	GcmcProcess(AppFrame *parent, const wchar_t *dstfn, DoAfterConvertGcmc todo)
		: m_parent(parent), dst_file(dstfn), what_to_do(todo), wxProcess(parent)
	{
		Redirect();
	}
	virtual void OnTerminate(int pid, int status) wxOVERRIDE;
	virtual bool HasInput();
	
private:
	AppFrame *m_parent;
	DoAfterConvertGcmc what_to_do;
	std::wstring dst_file;
};

void GcmcProcess::OnTerminate(int pid, int status)
{
	// show the rest of the output
	while (HasInput())
		;

	m_parent->GcmcProcessTerminated(status, dst_file.c_str(), what_to_do );
}

bool GcmcProcess::HasInput()
{
	bool hasInput = false;

	if (IsInputAvailable())
	{
		wxTextInputStream tis(*GetInputStream());
		// this assumes that the output is always line buffered
		wxString msg;
		msg << tis.ReadLine();
		m_parent->AppendGcmcError(msg);
		hasInput = true;
	}

	if (IsErrorAvailable())
	{
		wxTextInputStream tis(*GetErrorStream());
		// this assumes that the output is always line buffered
		wxString msg;
		msg << tis.ReadLine();
		m_parent->AppendGcmcError(msg);
		hasInput = true;
	}
	return hasInput;
}

//----------------------------------------------------------------------------
// AppFrame
//----------------------------------------------------------------------------


wxBEGIN_EVENT_TABLE (AppFrame, wxFrame)
    // common
    EVT_CLOSE (                      AppFrame::OnClose)
	EVT_TIMER( wxID_ANY, AppFrame::OnTimer)
    // file

	EVT_MENU(wxID_NEW,				 AppFrame::OnFileNew)
	EVT_MENU(ID_NEWGCMC,			 AppFrame::OnFileNew)
    EVT_MENU (wxID_OPEN,             AppFrame::OnFileOpen)
    EVT_MENU (wxID_SAVE,             AppFrame::OnFileSave)
    EVT_MENU (wxID_SAVEAS,           AppFrame::OnFileSaveAs)
    EVT_MENU (wxID_CLOSE,            AppFrame::OnFileClose)
	EVT_MENU_RANGE(wxID_FILE, wxID_FILE9, AppFrame::OnOpenLastFile)
    // properties
    EVT_MENU (myID_PROPERTIES,       AppFrame::OnProperties)
	EVT_MENU (ID_MACROSES,			 AppFrame::OnMacroses)
	EVT_MENU(ID_MATHCALC,			 AppFrame::OnMathCalc)
	EVT_MENU(ID_MATHEXPRESSION, AppFrame::OnMathExpression)

    // print and exit
	EVT_MENU(wxID_EXIT, AppFrame::OnExit)
	// Menu items with standard IDs forwarded to the editor.
	EVT_MENU(wxID_CLEAR, AppFrame::OnEdit)
	EVT_MENU(wxID_CUT, AppFrame::OnEdit)
	EVT_MENU(wxID_COPY, AppFrame::OnEdit)
	EVT_MENU(wxID_PASTE, AppFrame::OnEdit)
	EVT_MENU(wxID_SELECTALL, AppFrame::OnEdit)
	EVT_MENU(wxID_REDO, AppFrame::OnEdit)
	EVT_MENU(wxID_UNDO, AppFrame::OnEdit)
	EVT_MENU(wxID_FIND, AppFrame::OnEdit)
	//EVT_MENU(myID_INDENTINC, AppFrame::OnEdit)
	// And all our edit-related menu commands.
	EVT_MENU_RANGE(myID_EDIT_FIRST, myID_EDIT_LAST, AppFrame::OnEdit)

	//menuEdit->Append(myID_INDENTINC, _("&Indent increase\tTab"));
//menuEdit->Append(myID_INDENTRED, _("I&ndent reduce\tShift+Tab"));


    // help
    EVT_MENU (wxID_ABOUT,            AppFrame::OnAbout)
	EVT_MENU(ID_DOWNLOADUPDATE,		AppFrame::OnDownloadUpdate)

  //  EVT_CONTEXT_MENU(                AppFrame::OnContextMenu)
//GCode
	EVT_MENU(ID_GCODE_CHECK, AppFrame::OnCheck)
	EVT_MENU(ID_GCODE_SIMULATE, AppFrame::OnSimulate)
	EVT_MENU(ID_GCODE_CONVERTGCMC, AppFrame::OnConvertGcmc)
	EVT_MENU(ID_GCODE_KILLGCMCPROCESS, AppFrame::OnKillGcmcProcess)

	EVT_UPDATE_UI(ID_GCODE_CHECK, AppFrame::OnUpdateCheck)
	EVT_UPDATE_UI(ID_GCODE_SIMULATE, AppFrame::OnUpdateSimulate)
	EVT_UPDATE_UI(ID_GCODE_CONVERTGCMC, AppFrame::OnUpdateConvertGcmc)
	EVT_UPDATE_UI(ID_GCODE_KILLGCMCPROCESS, AppFrame::OnUpdateKillGcmcProcess)

	EVT_MENU_RANGE(myID_3D_FIRST, myID_3D_LAST, AppFrame::On3DView)
	EVT_UPDATE_UI_RANGE(myID_3D_FIRST, myID_3D_LAST, AppFrame::On3DViewUpdate)
	

	EVT_THREAD(CHECK_GCODE_UPDATE, AppFrame::OnThreadUpdate)
	EVT_THREAD(CHECK_GCODE_COMPLETE, AppFrame::OnThreadCompletion)


	EVT_THREAD(CHECK_SIMULATE_UPDATE, AppFrame::OnSimulateUpdate)
	EVT_THREAD(CHECK_SIMULATE_COMPLETE, AppFrame::OnSimulateCompletion)

	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_UPDATE, AppFrame::OnThreadUpdate)
	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_COMPLETED, AppFrame::OnThreadCompletion)
	
wxEND_EVENT_TABLE ()


AppFrame::AppFrame (const wxString &title)
        : m_timer(this), wxFrame ((wxFrame *)NULL, wxID_ANY, title, wxDefaultPosition, wxSize(750,550),
                    wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
    SetIcon(wxICON(sample));
	checkThread = NULL;
	simulateThread = NULL;
	gcmcProcess = NULL;
	gcmc_running_in_sec = 0;
	
	// initialize important variables
    m_edit = NULL;
	
    // set icon and background
    SetTitle (APP_NAME);
    SetBackgroundColour ("WHITE");


	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
		config->ReadFileNames();

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

	m_view = new ViewGCode(this, splitterV, wxID_ANY/*, gl_attrib*/ );
	
	logwnd = new LogWindow(splitter, this, wxID_ANY);
	
	splitter->SplitHorizontally(splitterV, logwnd,  -100);
	splitterV->SplitVertically(m_edit, m_view, -300 );

	Layout();
	splitter->UpdateSize();
	splitterV->UpdateSize();

	m_edit->SetFocus();
	m_view->initializeGL();
	m_view->setSimulationSpeed(20);
	//m_view->SetFocus();


	


#ifdef DOWX_LOGGING
		//Open a log window, don't show it though
	wxLogWindow *m_LogWin = new wxLogWindow(this, "YAMotion Gcode Editor", true, false);
	wxLog::SetActiveTarget(m_LogWin);
#endif
	
	WelcomeWnd *welcome = new WelcomeWnd(this);
	welcome->ShowWelcome(true);

}

AppFrame::~AppFrame () 
{

}

// common event handlers
void AppFrame::OnTimer(wxTimerEvent &event) 
{ 
	static bool needToAsk = true;
	if (gcmc_running_in_sec == 0)
		needToAsk == true;

	wxTimer &tm = event.GetTimer();
	gcmc_running_in_sec++;

	SetTitle(wxString::Format(L"Process gcmc %d sec.", gcmc_running_in_sec));
	if (gcmcProcess && needToAsk && (gcmc_running_in_sec%60) == 0 )
	{
		int rez = wxMessageBox(_("GCMC is running very long time/ Would you like to kill the process?"), wxMessageBoxCaptionStr,
			wxYES_NO | wxICON_QUESTION);
		if (rez == wxYES)
			wxKill(gcmcProcess->GetPid(), wxSIGKILL, NULL, wxKILL_CHILDREN);
	}	
}
void AppFrame::OnClose (wxCloseEvent &event)
{
	if ( m_timer.IsRunning() )
		m_timer.Stop();
		
	m_view->processClosing();
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


	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
		config->WriteFileNames();

    Destroy();
}


void AppFrame::OnDownloadUpdate(wxCommandEvent &WXUNUSED(event)) 
{
	wxMessageBox("Download update");
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
	if ( !m_edit->Modified() && !bSaveAs )
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
		wxString filename = _("unnamed");
		wxString wildCard;
		if (m_edit->GetFileType() == FILETYPE_GCMC)
			wildCard = _("GCMC Files (*.gcmc)|*.gcmc");
		else
			wildCard = _("GCode Files (*.ngc)|*.ngc");

		wxFileDialog dlg(this, _("Save file As"), wxEmptyString, filename, wildCard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() != wxID_OK)
			return false;
		filename = dlg.GetPath();
		m_edit->SaveFile(filename);
		ConfigData *config;
		if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
			config->AddFileNameToSaveList(filename);
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
	logwnd->Clear();
	m_view->clear();
}

void AppFrame::OnFileNew(wxCommandEvent &event )
{
	if (DoFileSave(true, false))
	{
		m_edit->NewFile((event.GetId() == ID_NEWGCMC) ? FILETYPE_GCMC : FILETYPE_NC);
		FileChanged();
	}
}

// file event handlers
void AppFrame::OnFileOpen (wxCommandEvent &WXUNUSED(event)) 
{

	if ( !DoFileSave(true, false))
		return;
    
	wxString fname;
    wxFileDialog dlg (this, _("Open file"), wxEmptyString, wxEmptyString, _("Any file (*)|*"),
                      wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() != wxID_OK) return;
    fname = dlg.GetPath ();
    FileOpen (fname);
}

void AppFrame::OnOpenLastFile(wxCommandEvent &event)
{
	if (!DoFileSave(true, false))
		return;

	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
	{
		int n = event.GetId() - wxID_FILE;
		const FileNamesList &files = config->GetFiles();
		if (n >= 0 && n < static_cast<int>(files.size()) )
		{
			auto it = files.begin();
			for (int i = 0; i < n; i++, it++) ;
			FileOpen( *it );
			return;
		}

	}
// if somthing wrong call standart file open dialog;
	OnFileOpen(event);
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
void AppFrame::OnProperties(wxCommandEvent &WXUNUSED(event))
{
	PropertiesDlg dlg(this);
	if (dlg.NeedRestart())
	{
		if ( DoFileSave(true, false) )
			wxGetApp().Restart();
	}
}

void AppFrame::OnMacroses(wxCommandEvent &WXUNUSED(event))
{
    if (!m_edit) return;
    //EditProperties dlg(m_edit, 0);
	Macroses msc;
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
	
	RunGcmc(src_fname.c_str(), dst_fname.c_str(), args.c_str(), ConvertGcmcPasteFile);
}


void AppFrame::DoMathCalc( DoMathBase &mth )
{
	char strOut[MAX_GCODE_LINELEN];
	int line_start;
	int line_end;

	long from, to;

	if (mth.InSelected())
	{
		m_edit->GetSelection(&from, &to);
		if (from == to)
		{
			wxMessageBox(_("Uups there is no any selection"));
			return;
		}
		line_start = m_edit->LineFromPosition(from);
		line_end = m_edit->LineFromPosition(to);
	}
	else
	{
		line_start = 0;
		line_end = m_edit->GetLineCount() - 1;
	}

	for (int i = line_start; i <= line_end; i++)
	{
		wxString str = m_edit->GetLine(i);
		if (mth.Process(str.c_str(), strOut))
		{
			long from = m_edit->PositionFromLine(i);
			long to = from + str.length();
			m_edit->Replace(from, to, strOut);
		}
	}
	if (mth.InSelected())
	{
		to = m_edit->PositionFromLine(line_end + 1);
		m_edit->SetSelection(from, m_edit->PositionBefore(to));
	}

}

// properties event handlers
void AppFrame::OnMathCalc(wxCommandEvent &WXUNUSED(event))
{
	if (!m_edit) return;
	//EditProperties dlg(m_edit, 0);
	DoMathSimple mth;
	MathSimpleDlg dlg(&mth, this, m_edit->HasSelection() );
	if (dlg.ShowModal() != wxID_OK)
		return;
	DoMathCalc(mth);
}

// properties event handlers
void AppFrame::OnMathExpression(wxCommandEvent &WXUNUSED(event))
{
	if (!m_edit) return;

	try
	{
		DoMathExpression mth;
		MathExpressionDlg dlg(&mth, this, m_edit->HasSelection());
		if (dlg.ShowModal() != wxID_OK)
			return;
		DoMathCalc(mth);
	}
	catch (mu::Parser::exception_type &e)
	{
		wxString errMsg;
		errMsg += wxString::Format(_("Error%s pos: %d"), e.GetMsg().c_str(), (int)e.GetPos());
		wxMessageBox(errMsg);
	}
	catch (...)
	{
		wxMessageBox(_("Uups some erorr"));
	}

}


// edit events
void AppFrame::OnEdit (wxCommandEvent &event) 
{
    if (m_edit) m_edit->GetEventHandler()->ProcessEvent (event);
}


void AppFrame::On3DView(wxCommandEvent &event) {
	if (m_view) m_view->GetEventHandler()->ProcessEvent(event);
}


void AppFrame::On3DViewUpdate(wxUpdateUIEvent& event) {
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
	wxMenu *menuNewFiles = new wxMenu;
	menuNewFiles->Append(wxID_NEW, _("&GCode File .."));
	menuNewFiles->Append(ID_NEWGCMC, _("G&CMC File .."));
	menuFile->Append(myID_HIGHLIGHTLANG, _("&New"), menuNewFiles);

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

	wxMenu *menuLastFiles = new wxMenu;
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
	{
		const FileNamesList &files = config->GetFiles();
		int n = 0;
		std::for_each( files.begin(), files.end(), 
			[menuLastFiles,&n](const wxString &p) {
			if (n < 10) { menuLastFiles->Append(wxID_FILE + n, p); n++; } });
	}
	menuFile->Append(myID_HIGHLIGHTLANG, _("&Last Files"), menuLastFiles);

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
    menuEdit->Append (myID_FINDNEXT, _("Find &next\tF3"));
    menuEdit->Append (myID_REPLACE, _("&Replace\tCtrl+H"));
    menuEdit->Append (myID_REPLACENEXT, _("Replace &again\tShift+F4"));
    menuEdit->AppendSeparator();
    menuEdit->Append (wxID_SELECTALL, _("&Select all\tCtrl+A"));
    menuEdit->Append (myID_SELECTLINE, _("Select &line\tCtrl+L"));
	menuEdit->AppendSeparator();
	menuEdit->Append(myID_INDENTINC, _("&Indent increase\tTab"));
	menuEdit->Append(myID_INDENTRED, _("I&ndent reduce\tShift+Tab"));
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
	menuGCode->Append(ID_GCODE_KILLGCMCPROCESS, _("&Kill Gcmc process"));
	
	menuGCode->Append(ID_MACROSES, _("Run Macros"));
	menuGCode->Append(ID_MATHCALC, _("Calculator"));
	menuGCode->Append(ID_MATHEXPRESSION, _("Calc by Expression"));

	// 3dView menu
	wxMenu *menu3D = new wxMenu;
	menu3D->Append(myID_SETVIEWFIRST + 6, _("&Isometric"));
	menu3D->Append(myID_SETVIEWFIRST,	  _("&Top"));
	menu3D->Append(myID_SETVIEWFIRST+1,   _("&Bottom"));
	menu3D->Append(myID_SETVIEWFIRST+2,   _("&Left"));
	menu3D->Append(myID_SETVIEWFIRST+3,   _("&Right"));
	menu3D->Append(myID_SETVIEWFIRST+4,   _("&Front"));
	menu3D->Append(myID_SETVIEWFIRST+5,   _("&Back"));
	menuView->AppendSeparator();
	menu3D->Append(myID_SEMULATE_START, _("&Start Simulate"));
	menu3D->Append(myID_SEMULATE_PAUSE,_("Sto&p Simulate"));
	menu3D->Append(myID_SEMULATE_STOP, _("Pause"));
		 
     // Help menu
    wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_DOWNLOADUPDATE, _("&About ..\tCtrl+D"));
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
	toolBar->AddSeparator();
	toolBar->AddTool(myID_SEMULATE_START, wxEmptyString, wxBitmap(simulate_xpm), _("simulate"));
	toolBar->AddTool(myID_SEMULATE_PAUSE, wxEmptyString, wxBitmap(pause_xpm), _("pause"));
	toolBar->AddTool(myID_SEMULATE_STOP, wxEmptyString, wxBitmap(stop_xpm), _("stop"));
	
//	toolBar->Realize();
	return toolBar;
}

void AppFrame::FileOpen (wxString fname)
{
    wxFileName w(fname); 
	w.Normalize(); 
	fname = w.GetFullPath();

	try
	{
		std::uintmax_t fsize = std::filesystem::file_size(fname.wc_str());
		if (fsize >= MAX_EDITOR_FILE_SIZE)
		{
			wxMessageBox(wxString::Format(_("File %s is very lage for the editor"), fname));
		}
		else
		{
			m_edit->LoadFile(fname);
			m_edit->SelectNone();
			FileChanged();
			ConfigData *config;
			if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
				config->AddFileNameToSaveList(fname);
		}
	}
	catch (...)
	{
		wxMessageBox(wxString::Format(_("Can not open file %s!"), fname ));
	}
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
	if(pexec) delete pexec;
	if(plogger) delete plogger;
	if(ppret) delete ppret;
}


wxThread::ExitCode IntGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.c_str()))
		{
			plogger->log(LOG_ERROR, _("Can not open file: %s"), fname.c_str() );
			return NULL;
		}
		ppret->execute_file();
	}
	plogger->log(LOG_INFORMATIONSUM, _("Feed Lenght: %f"), pexec->get_feed_len());
	plogger->log(LOG_INFORMATIONSUM, _("Traverce Lenght: %f"), pexec->get_traverce_len());
	plogger->log(LOG_INFORMATIONSUM, _("X Min: %f X Max %f"), pexec->getBox().Min.x, pexec->getBox().Max.x);
	plogger->log(LOG_INFORMATIONSUM, _("Y Min: %f Y Max %f"), pexec->getBox().Min.y, pexec->getBox().Max.y);
	plogger->log(LOG_INFORMATIONSUM, _("Z Min: %f Z Max %f"), pexec->getBox().Min.z, pexec->getBox().Max.z);

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
	if (pexec) delete pexec;
	if (plogger) delete plogger;
	if (ppret) delete ppret;
}


wxThread::ExitCode SimulateGCodeThread::Entry()
{
	if (ppret)
	{
		if (!ppret->open_nc_file(fname.c_str()))
		{
			plogger->log(LOG_ERROR, _("Can not open file: %s"), fname.c_str());
			return NULL;
		}
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
	logwnd->Append(MSLInfo, _("Checking completed"));
}

void AppFrame::OnThreadUpdate(wxThreadEvent &ev)
{
	// convert from ILogerr Error Code to LogWindow error 
	MsgStatusLevel lvl = (MsgStatusLevel)ev.GetInt();
	int linen = static_cast<int>(ev.GetExtraLong());
	logwnd->Append(lvl, ev.GetString(), linen, true );
}

void AppFrame::OnSimulateUpdate(wxThreadEvent &ev)
{
	logwnd->Append(MSLInfo, ev.GetString());
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
	logwnd->Clear();
	if (m_edit->GetFileType() == FILETYPE_NC)
	{
		checkThread = new IntGCodeThread(this, fname);
		if (checkThread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete checkThread;
			checkThread = NULL;
		}
	}
	else if (m_edit->GetFileType() == FILETYPE_GCMC)
	{
		DoConvertGcmc(ConvertGcmcNothing);
	}
}

void  AppFrame::OnSimulate(wxCommandEvent &event)
{
	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;
	logwnd->Clear();

	if (m_edit->GetFileType() == FILETYPE_NC)
	{
		DoSimulate( fname.c_str() );
	}
	else if (m_edit->GetFileType() == FILETYPE_GCMC)
	{
		DoConvertGcmc( ConvertGcmcRunSimilate );
	}
}


bool AppFrame::CheckFileExist(const wchar_t *fname)
{
	if ( StandartPaths::Get()->CheckFileExist(fname) )
		return true;

	wxString inf = wxString::Format("File %s not found.", fname );
	logwnd->Append(MSLError, inf);
	return false;

}

// Source format:
// FILENAME:LINE:CHAR: ERRORTYPE: MSG\n
// ERRORTYPE = { "error", "internal error", "fatal","warning"  }
//or just
// MSG \n

void AppFrame::AppendGcmcError(wxString &src)
{
	bool formated = false;
	size_t colon1 = wxString::npos, colon2 = wxString::npos, colon3 = wxString::npos, colon4 = wxString::npos;
	if ((colon1 = src.find(':', 0)) != wxString::npos)
	{
		if ((colon2 = src.find(':', colon1 + 1)) != wxString::npos)
		{
			if ((colon3 = src.find(':', colon2 + 1)) != wxString::npos)
			{
				if ((colon4 = src.find(':', colon3 + 1)) != wxString::npos)
				{
					formated = true;
				}
			}
		}
	}
	if (!formated)
	{
		logwnd->Append(MSLError, src);
	}
	else
	{
		std::wstring output;
		std::wstring tmp;
		std::filesystem::path path = src.SubString(0, colon1).wc_str();
		if (path.has_filename())
		{
			output = L"File: ";
			output += path.filename();
			output += L" ";
		}
		tmp = src.SubString(colon1 + 1, colon2).wc_str();
		int linen = _wtoi(tmp.c_str());
		tmp = src.SubString(colon3 + 2, colon4).wc_str(); // Erro type
		MsgStatusLevel lvl = MSLError;
		if (tmp.compare(L"warning") == 0)
			lvl = MSLWarning;

		output += src.Mid(colon4 + 1).wc_str(); // get message
		logwnd->Append(lvl, output.c_str(),linen);
	}

}


int AppFrame::RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do)
{

	logwnd->Clear();
	// cheks files
	if (!CheckFileExist(src_fname))
		return 1;
	
	wxExecuteEnv env;
	
	env.cwd = StandartPaths::Get()->GetDirFromFName(src_fname).c_str();
	// get file name without path
	std::filesystem::path src_fname_no_path = std::filesystem::path(src_fname).filename();
	std::filesystem::path dst_fname_no_path;

	if (StandartPaths::Get()->GetDirFromFName(dst_fname).compare(env.cwd) == 0)
		dst_fname_no_path = std::filesystem::path(dst_fname).filename();
	else
		dst_fname_no_path = dst_fname;


	wxString arg = StandartPaths::Get()->GetExecutablePath( L"gcmc_vc.exe" ).c_str();

	if (!CheckFileExist(arg))
		return 1;

	arg += " -o ";
	arg += dst_fname_no_path.c_str();
	arg += " ";
	if (args)
		arg += args;
	arg += " ";
	arg += src_fname_no_path.c_str();

	wxArrayString output;
	wxArrayString errors;

	
#if 0 
	logwnd->Append(MSLInfo, L"Start converting...");
	logwnd->Append(MSLInfo, arg.c_str());
	int code = wxExecute(arg, output, errors, wxEXEC_SYNC | wxEXEC_HIDE_CONSOLE, &env);
	for (size_t i = 0; i < errors.Count(); ++i)
	{
		AppendGcmcError(errors[i]);
	}

	wxString inf = wxString::Format("Process terminated with exit code %d", code);
	logwnd->Append(code == 0 ? MSLInfo : MSLError, inf);
	
	return code;
#endif

	if (gcmcProcess)
	{
		logwnd->Append(MSLInfo, _("gcmc_vc.exe already running"));
		return 1;
	}
	logwnd->Append(MSLInfo, _("Start converting..."));
	logwnd->Append(MSLInfo, arg.c_str());

	if (m_timer.IsRunning())
		m_timer.Stop();

	gcmc_running_in_sec = 0;
	m_timer.Start(1000);


	gcmcProcess = new GcmcProcess(this, dst_fname, what_to_do);
	int code = wxExecute(arg, wxEXEC_ASYNC| wxEXEC_HIDE_CONSOLE | wxEXEC_NODISABLE, gcmcProcess, &env);
	return code;

}




void AppFrame::GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do)
{

	if (gcmcProcess)
	{
		gcmc_running_in_sec = 0;
		m_timer.Stop();
		wxString inf = wxString::Format(_("Process terminated with exit code %d"), status);
		logwnd->Append(status == 0 ? MSLInfo : MSLError, inf);
		if (status == 0)
		{
			if (what_to_do == ConvertGcmcOpenFile)
				FileOpen(dst_fname);
			else if (what_to_do == ConvertGcmcPasteFile)
				m_edit->PasteFile(dst_fname) ;
			else if (what_to_do == ConvertGcmcRunSimilate)
				DoSimulate(dst_fname);
		}
		delete gcmcProcess;
		gcmcProcess = NULL;
	}
}

int AppFrame::DoConvertGcmc(DoAfterConvertGcmc what_to_do)
{
	wxString src_fname = m_edit->GetFilename();
	if (src_fname.IsEmpty())
		return 1;
	wxString dst_fname = src_fname.BeforeLast('.');
	if (dst_fname.IsEmpty())
		dst_fname = src_fname;
	dst_fname += wxString(".nc");

	return RunGcmc(src_fname, dst_fname, 0, what_to_do);
}


void AppFrame::OnConvertGcmc(wxCommandEvent &event)
{
	if (!DoFileSave(false, false))
		return;

	DoConvertGcmc(ConvertGcmcOpenFile);
	
}


void AppFrame::OnUpdateConvertGcmc(wxUpdateUIEvent& event)
{
	//event.Enable(m_edit->GetFileType() == FILETYPE_GCMC);
	event.Enable(true);
}

void AppFrame::OnKillGcmcProcess(wxCommandEvent &event)
{
	if (gcmcProcess)
		wxKill(gcmcProcess->GetPid(), wxSIGKILL, NULL, wxKILL_CHILDREN);
}

void AppFrame::OnUpdateKillGcmcProcess(wxUpdateUIEvent& event)
{
	event.Enable(gcmcProcess ? true : false);
}


void AppFrame::DoSimulate(const wchar_t *fname)
{

	if (simulateThread == NULL)
	{
		simulateThread = new SimulateGCodeThread(this, fname);
		if (simulateThread->Run() != wxTHREAD_NO_ERROR)
		{
			logwnd->Append(MSLError, _("Can't create the thread to run simulate"));
			delete simulateThread;
			simulateThread = NULL;

		}
	}
}


