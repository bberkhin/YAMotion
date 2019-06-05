#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include "wx/splitter.h"
#include "wx/event.h"
#include <wx/thread.h>
#include "wx/process.h"
#include "wx/txtstrm.h"
#include "wx/artprov.h"


//! application headers
#include "app.h"
#include "appdefs.h"       // Prefs
#include "defsext.h"     // Additional definitions
//#include "edit.h"        // Edit module
#include "editorpanel.h"
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
#include "dirtree.h"
#include "them.h"


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

class DropFileOpen : public wxFileDropTarget
{
public:
	DropFileOpen(AppFrame *pOwner) : m_pOwner(pOwner) {  }

	virtual bool OnDropFiles(wxCoord x, wxCoord y,const wxArrayString& filenames) wxOVERRIDE
	{
		size_t nFiles = filenames.GetCount();
		wxString str;
		if (m_pOwner != NULL)
		{
			for (size_t n = 0; n < nFiles; n++)
				m_pOwner->FileOpen(filenames[n]);
		}
		return true;
	}

private:
	AppFrame *m_pOwner;
};


//----------------------------------------------------------------------------
// AppFrame
//----------------------------------------------------------------------------


wxBEGIN_EVENT_TABLE (AppFrame, wxFrame)
    // common
    EVT_CLOSE (                      AppFrame::OnClose)
	EVT_TIMER( wxID_ANY, AppFrame::OnTimer)
    // file

	EVT_MENU(ID_NEWNC,				 AppFrame::OnFileNew)
	EVT_MENU(ID_NEWGCMC,			 AppFrame::OnFileNew)
    EVT_MENU (ID_OPENFILE,             AppFrame::OnFileOpen)
    EVT_MENU (wxID_SAVE,             AppFrame::OnFileSave)
    EVT_MENU (wxID_SAVEAS,           AppFrame::OnFileSaveAs)
    EVT_MENU (wxID_CLOSE,            AppFrame::OnFileClose)
	EVT_MENU_RANGE(wxID_FILE, wxID_FILE9, AppFrame::OnOpenLastFile)
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
	//EVT_MENU(ID_INDENTINC, AppFrame::OnEdit)
	// And all our edit-related menu commands.
	EVT_MENU_RANGE(ID_EDIT_FIRST, ID_EDIT_LAST, AppFrame::OnEdit)
	EVT_MENU_RANGE(ID_DIRTREE_FIRST, ID_DIRTREE_LAST, AppFrame::OnDirTree)

	// Preferences
	EVT_MENU(ID_PROPERTIES, AppFrame::OnProperties)
	EVT_MENU(ID_GLOBALPREFS, AppFrame::OnDefaultPreferences)
	EVT_MENU(ID_USERPREFS, AppFrame::OnUserPreferences)


// help
EVT_MENU(wxID_ABOUT, AppFrame::OnAbout)
EVT_MENU(ID_DOWNLOADUPDATE, AppFrame::OnDownloadUpdate)
EVT_MENU(ID_SHOWWLCOME, AppFrame::OnShowWelcome)

    // help
    EVT_MENU (wxID_ABOUT,            AppFrame::OnAbout)
	EVT_MENU(ID_DOWNLOADUPDATE,		AppFrame::OnDownloadUpdate)
	EVT_MENU(ID_SHOWWLCOME, AppFrame::OnShowWelcome)

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

	EVT_MENU_RANGE(ID_3D_FIRST, ID_3D_LAST, AppFrame::On3DView)
	EVT_UPDATE_UI_RANGE(ID_3D_FIRST, ID_3D_LAST, AppFrame::On3DViewUpdate)
	

	EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, AppFrame::OnNotebookPageClose)
	EVT_COMMAND(wxID_ANY,FILE_MODIFYED_EVENT, AppFrame::OnFileChanged)
	EVT_COMMAND(wxID_ANY,FILE_OPEN_EVENT, AppFrame::OnFileOpenEvent)
	EVT_COMMAND(wxID_ANY, FILE_RENAME_EVENT, AppFrame::OnFileRenamed)
	EVT_COMMAND(wxID_ANY, FILE_REMOVE_EVENT, AppFrame::OnFileRemoveEvent)
	EVT_COMMAND(wxID_ANY, FILE_NEW_EVENT, AppFrame::OnFileNewEvent)

// PROCESSING

	EVT_THREAD(CHECK_GCODE_UPDATE, AppFrame::OnThreadUpdate)
	EVT_THREAD(CHECK_GCODE_COMPLETE, AppFrame::OnThreadCompletion)


	EVT_THREAD(CHECK_SIMULATE_UPDATE, AppFrame::OnSimulateUpdate)
	EVT_THREAD(CHECK_SIMULATE_COMPLETE, AppFrame::OnSimulateCompletion)

	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_UPDATE, AppFrame::OnThreadUpdate)
	//EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_GCODETHREAD_COMPLETED, AppFrame::OnThreadCompletion)
	
wxEND_EVENT_TABLE ()


AppFrame::AppFrame (const wxString &title)
        : m_timer(this), wxFrame ((wxFrame *)NULL, wxID_ANY, title, wxDefaultPosition, wxSize(840,650),
                    wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
	// tell wxAuiManager to manage this frame
	m_mgr.SetManagedWindow(this);
	m_mgr.SetArtProvider( Preferences::Get()->GetArtProvider(true) );


	m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
	m_notebook_theme = 0;
	m_dirtree = 0;
	m_watcher = 0;
	m_view = 0;


    SetIcon(wxICON(sample));

	checkThread = NULL;
	simulateThread = NULL;
	gcmcProcess = NULL;
	m_gcmc_running_in_sec = 0;
	
	// initialize important variables

    // set icon and background
    SetTitle (APP_NAME);
    //SetBackgroundColour ("GREEN");


	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
		config->ReadFileNames();

    // create menu
	wxMenuBar *m_menuBar = CreateMenu();
	SetMenuBar(m_menuBar);

	
	m_notebook = CreateNotebook();

	m_mgr.AddPane(m_notebook, wxAuiPaneInfo().Name("notebook_content").
		CenterPane().PaneBorder(false));

	m_mgr.AddPane(CreateGLView(), wxAuiPaneInfo().
		Name("ViewGCode").Caption("3D View").
		Right().Layer(1).Position(1).
		CloseButton(true).MaximizeButton(true));


	
	
	m_dirtree = new DirPane(this);
	m_mgr.AddPane(m_dirtree, wxAuiPaneInfo().
		Name("Folders").Caption("Folders").
		Left().Layer(1).Position(1).
		CloseButton(false).MaximizeButton(false).CaptionVisible(false));
	

	m_logwnd = new LogWindow(this, this, wxID_ANY);
	int iconSize = m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE);
	// Make it even to use 16 pixel icons with default 17 caption height.
	iconSize &= ~1;

	m_mgr.AddPane(m_logwnd, wxAuiPaneInfo().
		Name("logwnd").Caption(_("Output")).
		Bottom().Layer(1).Position(1).
		Icon(wxArtProvider::GetBitmap(wxART_WARNING,
			wxART_OTHER,
			wxSize(iconSize, iconSize))));
	
	// add the toolbars to the manager
	
	wxAuiToolBar *toolBar = CreateToolBar();
	m_mgr.AddPane(toolBar, wxAuiPaneInfo().
		Name("tb").Caption("Standart commands").
		ToolbarPane().Top().Row(1));

	m_mgr.Update();
	
	ShowWelcome();

	SetDropTarget(new DropFileOpen(this));

#ifdef DOWX_LOGGING
		//Open a log window, don't show it though
	wxLogWindow *m_LogWin = new wxLogWindow(this, "YAMotion Gcode Editor", true, false);
	wxLog::SetActiveTarget(m_LogWin);
#endif
}

AppFrame::~AppFrame () 
{
	m_mgr.UnInit();

	if (m_watcher)
		delete m_watcher;
}

class StubNotebook : public wxAuiNotebook
{
public:
	StubNotebook() { }
	~StubNotebook() {}

	void SetAuiArtProvider()
	{
		m_mgr.SetArtProvider(Preferences::Get()->GetArtProvider(true));
	}
};



wxAuiNotebook* AppFrame::CreateNotebook()
{
	// create the notebook off-window to avoid flicker
	wxSize client_size = GetClientSize();

	StubNotebook* ctrl = new StubNotebook();
	ctrl->SetAuiArtProvider();

	ctrl->Create(this, wxID_ANY,
		wxPoint(client_size.x, client_size.y),
		FromDIP(wxSize(330, 200)),
		m_notebook_style);
	ctrl->SetArtProvider(Preferences::Get()->GetTabArtProvider());
	return ctrl;
}

Edit *AppFrame::GetActiveFile()
{
	wxWindow *wnd = m_notebook->GetCurrentPage();
	EditorPanel *panel = dynamic_cast<EditorPanel *>(wnd);
	if (panel)
		return panel->GetEdit();
	return 0;
}


ViewGCode* AppFrame::CreateGLView()
{
	m_view = new ViewGCode(this, this, wxID_ANY);
	return m_view;
}


void AppFrame::ShowWelcome()
{
	m_notebook->Freeze();
	// check is welcome window exist
	size_t welcome_page = wxNOT_FOUND;
	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		//WelcomeWnd *welcome = dynamic_cast<WelcomeWnd *>(m_notebook->GetPage(i));
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(WelcomeWnd)))
		//if (welcome)
		{
			welcome_page = i;
			break;
		}
			
	}
	if (welcome_page == wxNOT_FOUND)
	{
		m_notebook->InsertPage(0, new WelcomeWnd(this), _("Welcome"), true);
		m_notebook->SetPageToolTip(0, _("Welcome screen"));
	}
	else
	{
		m_notebook->SetSelection(welcome_page);
	}	
	m_notebook->Thaw();
}


void AppFrame::HideWelcome()
{
	m_notebook->Freeze();
	// check is welcome window exist
	size_t welcome_page = wxNOT_FOUND;
	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		//WelcomeWnd *welcome = dynamic_cast<WelcomeWnd *>(m_notebook->GetPage(i));		
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(WelcomeWnd)))
		{
			welcome_page = i;
			break;
		}

	}
	if (welcome_page != wxNOT_FOUND)
	{
		m_notebook->DeletePage(welcome_page);
	}
	m_notebook->Thaw();
}

void AppFrame::OnFileChanged(wxCommandEvent &)
{
	UpdateTitle();
}

void AppFrame::OnFileRenamed(wxCommandEvent &evn)
{
	wxString oldPath = evn.GetString();
	size_t nPage = wxNOT_FOUND;
	if (!FindPageByFileName(oldPath, &nPage))
		return;
	wxStringClientData *pstring_data = dynamic_cast<wxStringClientData *>(evn.GetClientObject());
	if (!pstring_data)
		return;

	EditorPanel *pedit = dynamic_cast<EditorPanel *>(m_notebook->GetPage(nPage));
	if (!pedit)
		return;
	pedit->GetEdit()->SetFileName( pstring_data->GetData() );
	UpdateTitle(nPage);	
}


void AppFrame::OnNotebookPageClose(wxAuiNotebookEvent& evt)
{
	wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
	if (ctrl->GetPage(evt.GetSelection())->IsKindOf(CLASSINFO(EditorPanel)))
	{
		if ( !DoFileSave(true,false) )
			evt.Veto();
	}
}


// common event handlers
void AppFrame::OnTimer(wxTimerEvent &event) 
{ 
	static bool needToAsk = true;
	if (m_gcmc_running_in_sec == 0)
		needToAsk = true;

	wxTimer &tm = event.GetTimer();
	m_gcmc_running_in_sec++;

	//SetTitle(wxString::Format(L"Process gcmc %d sec.", m_gcmc_running_in_sec));
	if (gcmcProcess && needToAsk && (m_gcmc_running_in_sec%60) == 0 )
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
		
	if ( m_view )
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
// save all modified files
	if (!DoSaveAllFiles() )
	{
		event.Veto();
		return;
	}
	

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

void AppFrame::OnShowWelcome(wxCommandEvent &WXUNUSED(event))
{
	ShowWelcome();
}

void AppFrame::OnExit (wxCommandEvent &WXUNUSED(event)) {
    Close (true);
}

bool AppFrame::DoSaveAllFiles()
{
	if (!m_notebook)
		return true;

	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(EditorPanel)))
		{
			EditorPanel *pEdit = dynamic_cast<EditorPanel *>(m_notebook->GetPage(i));
			if (pEdit && !DoFileSave(true, false, pEdit->GetEdit() ))
			{
				return false;
			}
		}
	}
	return true;
}

bool AppFrame::DoFileSave(bool askToSave, bool bSaveAs, Edit *pedit)
{
	if (pedit == NULL )
		pedit = GetActiveFile();
	
	if (!pedit) 
		return true;

	if ( !pedit->Modified() && !bSaveAs )
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
	if (bSaveAs || pedit->IsNew() )
	{
		wxString filename = pedit->GetFileName();
		wxString wildCard;
		if (pedit->GetFileType() == FILETYPE_GCMC)
			wildCard = _("GCMC Files (*.gcmc)|*.gcmc");
		else
			wildCard = _("GCode Files (*.ngc;*.nc)|*.ngc;*.nc");

		wxFileDialog dlg(this, _("Save file As"), wxEmptyString, filename, wildCard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() != wxID_OK)
			return false;
		filename = dlg.GetPath();
		pedit->SaveFile(filename);
		ConfigData *config;
		if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
			config->AddFileNameToSaveList(filename);
	}
	else //  fname exist && not save as  - just save
	{
		pedit->SaveFile();
		if (pedit->Modified())
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
	if (m_logwnd) m_logwnd->Clear();
	if (m_view) m_view->clear();
}


bool AppFrame::FindPageByFileName(const wxString &new_file_name, size_t *nPage)
{
	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(EditorPanel)))
		{
			EditorPanel *pEdit = dynamic_cast<EditorPanel *>(m_notebook->GetPage(i));
			if (pEdit->GetEdit()->GetFileName() == new_file_name)
			{
				if (nPage)
					*nPage = i;
				return true;
			}
		}
	}
	return false;

}

void AppFrame::OnFileNewEvent(wxCommandEvent &event)
{
	int file_type = (event.GetInt() == ID_NEWGCMC) ? FILETYPE_GCMC : FILETYPE_NC;
	DoNewFile(file_type, event.GetString(), false );
}

void AppFrame::OnFileNew(wxCommandEvent &event)
{
	int file_type = (event.GetId() == ID_NEWGCMC) ? FILETYPE_GCMC : FILETYPE_NC;
	DoNewFile(file_type, wxEmptyString, event.GetClientData() != NULL );
}

void AppFrame::DoNewFile(int file_type, const wxString &defpath, bool closeWelcome, const wxString &contextFile)
{
	wxFileName defPath;
	defPath.AssignDir(defpath);
	
	
	wxString new_file_name = wxString::Format(_("unnamed.%s"), (file_type == FILETYPE_GCMC) ? "gcmc" : "nc");
	defPath.SetFullName(new_file_name);
	int n = 0;
	do
	{
		if ( !FindPageByFileName(defPath.GetFullPath()) )
			break;
		new_file_name = wxString::Format(_("unnamed%d.%s"),++n, (file_type == FILETYPE_GCMC) ? "gcmc" : "nc");
		defPath.SetFullName(new_file_name);
	} while (true);

	m_notebook->Freeze();
	
	EditorPanel * pedit = new EditorPanel(m_notebook, file_type, defPath.GetFullPath(),true );
	//Edit *pedit = new Edit(m_notebook, wxID_ANY);
	m_notebook->AddPage(pedit, new_file_name , true);
	//pedit->NewFile(file_type, defPath.GetFullPath());

	if ( !contextFile.empty() )
		pedit->GetEdit()->PasteFile(contextFile.wc_str());
		
	FileChanged();
	UpdateTitle();

	m_notebook->Thaw();

	if (closeWelcome)
		HideWelcome();
}

// file event handlers
void AppFrame::OnFileOpen (wxCommandEvent &event ) 
{
  
	wxString fname;
    wxFileDialog dlg (this, _("Open file"), wxEmptyString, wxEmptyString, 
		_("GCMC and NC files (*.gcmc;*.nc;*.ngc)|*.gcmc;*.nc;*.ngc|GCMC files (*.gcmc)|*.gcmc|NC files (*.nc;*.ngc)|*.nc;*.ngc|Any file(* |*"),
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);

    if (dlg.ShowModal() != wxID_OK) return;
    fname = dlg.GetPath();
    FileOpen (fname);

	if (event.GetClientData() != NULL)
		HideWelcome();
}

void AppFrame::OnFileOpenEvent(wxCommandEvent &event)
{
	
	// we should check all possible files dir

	wxFileName fname( event.GetString() );
	if (!fname.IsAbsolute())
	{
		wxPathList paths; 
		Edit *pedit = dynamic_cast<Edit *>(event.GetEventObject());
		// try to add path from parent sender
		if (pedit)
		{
			wxFileName fn = pedit->GetFileName();
			paths.Add( fn.GetPath() );
			fn.AppendDir(L"library");
			paths.Add( fn.GetPath() );
		}
		
		paths.Add(StandartPaths::Get()->GetRootPath().c_str());
		paths.Add(StandartPaths::Get()->GetMacrosPath().c_str());

		wxString abs_fname  = paths.FindAbsoluteValidPath(fname.GetFullPath());
		if (abs_fname.empty())
		{
			wxString msg = wxString::Format(_("Can not open file %s in catalogs:\n"), fname.GetFullPath());
			//for (int i = 0; i auto p = paths.begin() p != paths.end(); ++p)
			for (auto p = paths.begin(); p != paths.end(); ++p)
			{
				msg += *p;
				msg += L"\n";
			}
			wxMessageBox(msg,_("Error opening file"));
			return;
		}
		else
			fname = abs_fname;
	}
	
	FileOpen( fname.GetFullPath() );	
	HideWelcome();
}


void AppFrame::OnFileRemoveEvent(wxCommandEvent &event)
{
	size_t nPage;
	if ( FindPageByFileName(event.GetString(), &nPage) )
	{
		m_notebook->Freeze();
		m_notebook->DeletePage(nPage);
		m_notebook->Thaw();
	}
	
}


void AppFrame::OnOpenLastFile(wxCommandEvent &event)
{
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
			if (event.GetClientData() != NULL)
				HideWelcome();
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
		if ( DoSaveAllFiles() )
			wxGetApp().Restart();
	}
}

void AppFrame::OnDefaultPreferences(wxCommandEvent &WXUNUSED(event))
{
	std::filesystem::path dirpath = StandartPaths::Get()->GetPreferencesPath(L"Default Preferences.json");	
	FileOpen(dirpath.c_str());
}

void AppFrame::OnUserPreferences(wxCommandEvent &WXUNUSED(event))
{
	std::filesystem::path dirpath = StandartPaths::Get()->GetPreferencesPath(L"User Preferences.json");
	FileOpen(dirpath.c_str());
}

void AppFrame::OnMacroses(wxCommandEvent &WXUNUSED(event))
{
	Edit *pedit = GetActiveFile();
    if (!pedit) return;
	
    //EditProperties dlg(pedit, 0);
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
	
	RunGcmc(src_fname.c_str(), dst_fname.c_str(), args.c_str(), dlgparam.IsInNewWindow() ? ConvertGcmcNewFile : ConvertGcmcPasteFile);
}


void AppFrame::DoMathCalc( DoMathBase &mth )
{

	Edit *pedit = GetActiveFile();
	if (!pedit)
		return;

	char strOut[MAX_GCODE_LINELEN];
	int line_start;
	int line_end;

	long from, to;

	if (mth.InSelected())
	{
		pedit->GetSelection(&from, &to);
		if (from == to)
		{
			wxMessageBox(_("Uups there is no any selection"));
			return;
		}
		line_start = pedit->LineFromPosition(from);
		line_end = pedit->LineFromPosition(to);
	}
	else
	{
		line_start = 0;
		line_end = pedit->GetLineCount() - 1;
	}

	for (int i = line_start; i <= line_end; i++)
	{
		wxString str = pedit->GetLine(i);
		if (mth.Process(str.c_str(), strOut))
		{
			long from = pedit->PositionFromLine(i);
			long to = from + str.length();
			pedit->Replace(from, to, strOut);
		}
	}
	if (mth.InSelected())
	{
		to = pedit->PositionFromLine(line_end + 1);
		pedit->SetSelection(from, pedit->PositionBefore(to));
	}

}

// properties event handlers
void AppFrame::OnMathCalc(wxCommandEvent &WXUNUSED(event))
{
	Edit *pedit = GetActiveFile();
	if (!pedit)
		return;

	//EditProperties dlg(pedit, 0);
	DoMathSimple mth;
	MathSimpleDlg dlg(&mth, this, pedit->HasSelection() );
	if (dlg.ShowModal() != wxID_OK)
		return;
	DoMathCalc(mth);
}

// properties event handlers
void AppFrame::OnMathExpression(wxCommandEvent &WXUNUSED(event))
{
	Edit *pedit = GetActiveFile();
	if (!pedit)
		return;
	try
	{
		DoMathExpression mth;
		MathExpressionDlg dlg(&mth, this, pedit->HasSelection());
		if (dlg.ShowModal() != wxID_OK)
			return;
		DoMathCalc(mth);
	}
	catch (mu::Parser::exception_type &e)
	{
		wxString errMsg;
		errMsg += wxString::Format(_("Error%s pos: %d"), e.GetMsg().c_str(), (int)e.GetPos());
		wxMessageBox(errMsg, _("Expression error") );
	}
	catch (...)
	{
		wxMessageBox(_("Uups some erorr"));
	}

}


// edit events
void AppFrame::OnEdit (wxCommandEvent &event) 
{
	Edit *pedit = GetActiveFile();
    if (pedit) 
		pedit->GetEventHandler()->ProcessEvent (event);
}


void AppFrame::On3DView(wxCommandEvent &event)
{
	if (m_view) m_view->GetEventHandler()->ProcessEvent(event);
}


void AppFrame::On3DViewUpdate(wxUpdateUIEvent& event) {
	if (m_view) m_view->GetEventHandler()->ProcessEvent(event);
}

void AppFrame::OnDirTree(wxCommandEvent &event)
{
	if (m_dirtree) m_dirtree->GetEventHandler()->ProcessEvent(event);
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
wxMenuBar *AppFrame::CreateMenu ()
{
    // File menu
	wxMenuBar *m_menuBar = new wxMenuBar;
    wxMenu *menuFile = new wxMenu;
	//Open
	menuFile->Append(ID_OPENFILE, _("Open ..\tCtrl+O")); 
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
	menuFile->Append(ID_OPENRECENT, _("Open recent"), menuLastFiles);
	menuFile->AppendSeparator();
	//New
	menuFile->Append(ID_NEWNC, _("New GCODE"));
	menuFile->Append(ID_NEWGCMC, _("New GCMC"));
	menuFile->Append(ID_SHOWWLCOME, _("Welcome"));
	menuFile->AppendSeparator();
	//Save	
	menuFile->Append(wxID_SAVE, _("Save\tCtrl+S"));
	menuFile->Append(wxID_SAVEAS, _("Save  as ..\tCtrl+Shift+S"));
	menuFile->Append(wxID_CLOSE, _("Close\tCtrl+W"));
	menuFile->AppendSeparator();
	
	menuFile->AppendSeparator();

    menuFile->Append (wxID_EXIT, _("&Quit\tCtrl+Q"));
	
	// Edit menu


	
	// change case submenu
	wxMenu *menuChangeCase = new wxMenu;
	menuChangeCase->Append(ID_CHANGEUPPER, _("&Upper case"));
	menuChangeCase->Append(ID_CHANGELOWER, _("&Lower case"));

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
    menuEdit->Append (ID_FINDNEXT, _("Find &next\tF3"));
    menuEdit->Append (ID_REPLACE, _("&Replace\tCtrl+H"));
    menuEdit->Append (ID_REPLACENEXT, _("Replace &again\tShift+F4"));
    menuEdit->AppendSeparator();
	menuEdit->Append(ID_MATHCALC, _("Transform..."));
	menuEdit->AppendSeparator();
	menuEdit->Append(ID_INDENTINC, _("&Indent increase\tTab"));
	menuEdit->Append(ID_INDENTRED, _("I&ndent reduce\tShift+Tab"));
	menuEdit->AppendSeparator();
	menuEdit->Append(ID_CHANGECASE, _("Change &case to .."), menuChangeCase);
  	
	// View menu
    wxMenu *menuView = new wxMenu;
    //menuView->Append (ID_HIGHLIGHTLANG, _("&Highlight language .."), menuHighlight);
    menuView->AppendSeparator();
    menuView->AppendCheckItem (ID_DISPLAYEOL, _("Show line &endings"));
    menuView->AppendCheckItem (ID_INDENTGUIDE, _("Show &indent guides"));
    menuView->AppendCheckItem (ID_LINENUMBER, _("Show line &numbers"));
    menuView->AppendCheckItem (ID_WHITESPACE, _("Show white&space"));
    menuView->AppendSeparator();
	menuView->FindChildItem(ID_LINENUMBER)->Check(true);

	// Edit menu
	wxMenu *menuGCode = new wxMenu;
	menuGCode->Append(ID_GCODE_CHECK, _("&Check"));
	menuGCode->Append(ID_GCODE_SIMULATE, _("&Simulate"));
	menuGCode->Append(ID_GCODE_CONVERTGCMC, _("&Convert Gcmc"));
	menuGCode->Append(ID_GCODE_KILLGCMCPROCESS, _("&Kill Gcmc process"));
	
	menuGCode->Append(ID_MACROSES, _("Run Macros"));
	
	menuGCode->Append(ID_MATHEXPRESSION, _("Calc by Expression"));

	// 3dView menu
	wxMenu *menu3D = new wxMenu;
	menu3D->Append(ID_SETVIEWFIRST + 6, _("&Isometric"));
	menu3D->Append(ID_SETVIEWFIRST,	  _("&Top"));
	menu3D->Append(ID_SETVIEWFIRST+1,   _("&Bottom"));
	menu3D->Append(ID_SETVIEWFIRST+2,   _("&Left"));
	menu3D->Append(ID_SETVIEWFIRST+3,   _("&Right"));
	menu3D->Append(ID_SETVIEWFIRST+4,   _("&Front"));
	menu3D->Append(ID_SETVIEWFIRST+5,   _("&Back"));
	menu3D->AppendSeparator();	
	menu3D->AppendCheckItem(ID_SHOW2DGRID, _("Show/Hide 2d grid"));
	menu3D->AppendCheckItem(ID_SHOWBOUNDS, _("Show/Hide bounds"));
	menu3D->AppendCheckItem(ID_SHOW3DGRID, _("Show/Hide 3d grid"));
	menu3D->AppendCheckItem(ID_SHOWTOOL, _("Show/Hide tool"));
	menu3D->AppendCheckItem(ID_SHOWAXIS, _("Show/Hide Axis"));
	menu3D->AppendSeparator();
	menu3D->Append(ID_SEMULATE_START, _("&Start Simulate"));
	menu3D->Append(ID_SEMULATE_PAUSE,_("Sto&p Simulate"));
	menu3D->Append(ID_SEMULATE_STOP, _("Pause"));
	
	// Pregerences menu
	wxMenu *menuPref = new wxMenu;
	menuPref->Append(ID_PROPERTIES, _("Proper&ties ..\tCtrl+I"));
	menuPref->Append(ID_GLOBALPREFS, _("Defauult Preferences"));
	menuPref->Append(ID_USERPREFS, _("User Preferences"));

     // Help menu
    wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_DOWNLOADUPDATE, _("&Download ..\tCtrl+D"));
    menuHelp->Append (wxID_ABOUT, _("&About ..\tCtrl+D"));
	
	
	

    // construct menu
    m_menuBar->Append (menuFile, _("&File"));
    m_menuBar->Append (menuEdit, _("&Edit"));
    m_menuBar->Append (menuView, _("&View"));
	m_menuBar->Append(menuGCode, _("&GCode"));
	m_menuBar->Append(menu3D, _("&3DView"));
	m_menuBar->Append(menuPref, _("Preferences"));
    m_menuBar->Append (menuHelp, _("&Help"));    
	return m_menuBar;

}


wxAuiToolBar *AppFrame::CreateToolBar()
{
	wxAuiToolBar* toolBar = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_HORIZONTAL);

	toolBar->AddTool(ID_NEWNC, wxEmptyString, wxBitmap(new_xpm), _("New"));
	toolBar->AddTool(ID_OPENFILE, wxEmptyString, wxBitmap(open_xpm), _("Open"));
	toolBar->AddTool(wxID_SAVE, wxEmptyString, wxBitmap(save_xpm), _("Save"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Cut"));
	toolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Cut"));
	toolBar->AddSeparator();
	toolBar->AddTool(ID_PROPERTIES, wxEmptyString, wxBitmap(cut_xpm), _("Macroses"));
	toolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy"));
	toolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste"));
	toolBar->AddSeparator();
	toolBar->AddTool(ID_GCODE_CHECK, wxEmptyString, wxBitmap(check_xpm), _("Check"));
	toolBar->AddTool(ID_GCODE_SIMULATE, wxEmptyString, wxBitmap(find_xpm), _("Simulate"));
	toolBar->AddTool(ID_GCODE_CONVERTGCMC, wxEmptyString, wxBitmap(new_xpm), _("Convert"));
	toolBar->AddSeparator();
	toolBar->AddTool(ID_SEMULATE_START, wxEmptyString, wxBitmap(simulate_xpm), _("simulate"));
	toolBar->AddTool(ID_SEMULATE_PAUSE, wxEmptyString, wxBitmap(pause_xpm), _("pause"));
	toolBar->AddTool(ID_SEMULATE_STOP, wxEmptyString, wxBitmap(stop_xpm), _("stop"));
	
	toolBar->Realize();
	return toolBar;
}

void AppFrame::FileOpen (wxString fname)
{
    wxFileName w(fname); 
	w.Normalize(); 
	fname = w.GetFullPath();
	// first try  to find the file in the opened tabs
	size_t nPage = 0;
	if (FindPageByFileName(fname, &nPage) )
	{
		m_notebook->SetSelection(nPage);
		return;
	}

	m_notebook->Freeze();
	try
	{
		std::uintmax_t fsize = std::filesystem::file_size(fname.wc_str());
		if (fsize >= MAX_EDITOR_FILE_SIZE)
		{
			wxMessageBox(wxString::Format(_("File %s is very lage for the editor"), fname));
		}
		else
		{						
			
			EditorPanel *pedit = new EditorPanel(m_notebook, FILETYPE_UNKNOW, fname, false );
			//pedit->LoadFile(fname);
			m_notebook->AddPage(pedit, w.GetFullName(), true);
			FileChanged();
			UpdateTitle();
			ConfigData *config;
			if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
				config->AddFileNameToSaveList(fname);

		}
	}
	catch (...)
	{
		wxMessageBox(wxString::Format(_("Can not open file %s!"), fname ), _("Error opening file") );
	}
	m_notebook->Thaw();
}


void AppFrame::UpdateTitle(size_t nPage )
{
	if (nPage == wxNOT_FOUND)
		nPage = m_notebook->GetSelection();
	if (nPage == wxNOT_FOUND)
		return;
	EditorPanel *pedit = dynamic_cast<EditorPanel *>(m_notebook->GetPage(nPage));
	if (!pedit)
		return;
	wxFileName w = pedit->GetEdit()->GetFileName();
	wxString title = w.GetFullName();
	if (pedit->GetEdit()->Modified())
		title += "*";

	m_notebook->SetPageText(nPage, title);
	m_notebook->SetPageToolTip(nPage, w.GetFullPath());
}

wxRect AppFrame::DeterminePrintSize () 
{

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
	Edit *pedit = GetActiveFile();
	if (pedit)
		return pedit->GetText();
	else
		return wxString();
}

void AppFrame::OnThreadCompletion(wxThreadEvent&)
{
	m_logwnd->Append(MSLInfo, _("Checking completed"));
}

void AppFrame::OnThreadUpdate(wxThreadEvent &ev)
{
	// convert from ILogerr Error Code to LogWindow error 
	MsgStatusLevel lvl = (MsgStatusLevel)ev.GetInt();
	int linen = static_cast<int>(ev.GetExtraLong());
	m_logwnd->Append(lvl, ev.GetString(), linen, true );
}

void AppFrame::OnSimulateUpdate(wxThreadEvent &ev)
{
	m_logwnd->Append(MSLInfo, ev.GetString());
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
	
	Edit *pedit = GetActiveFile();
	return  pedit ? pedit->GetFileName() : wxString();
}


void  AppFrame::OnCheck(wxCommandEvent &event)
{
	Edit *pedit = GetActiveFile();
	if (!pedit)
		return;

	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;	
	m_logwnd->Clear();
	if (pedit->GetFileType() == FILETYPE_NC)
	{
		checkThread = new IntGCodeThread(this, fname);
		if (checkThread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete checkThread;
			checkThread = NULL;
		}
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		DoConvertGcmc(ConvertGcmcNothing);
	}
}

void  AppFrame::OnSimulate(wxCommandEvent &event)
{
	Edit *pedit = GetActiveFile();
	if (!pedit)
		return;

	wxString fname = GetSavedFileName();
	if (fname.empty())
		return;
	m_logwnd->Clear();

	if (pedit->GetFileType() == FILETYPE_NC)
	{
		DoSimulate( fname.c_str() );
	}
	else if (pedit->GetFileType() == FILETYPE_GCMC)
	{
		DoConvertGcmc( ConvertGcmcRunSimilate );
	}
}


bool AppFrame::CheckFileExist(const wchar_t *fname)
{
	if ( StandartPaths::Get()->CheckFileExist(fname) )
		return true;

	wxString inf = wxString::Format("File %s not found.", fname );
	m_logwnd->Append(MSLError, inf);
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
		m_logwnd->Append(MSLError, src);
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
		m_logwnd->Append(lvl, output.c_str(),linen);
	}

}


int AppFrame::RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do)
{

	m_logwnd->Clear();
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
	m_logwnd->Append(MSLInfo, L"Start converting...");
	m_logwnd->Append(MSLInfo, arg.c_str());
	int code = wxExecute(arg, output, errors, wxEXEC_SYNC | wxEXEC_HIDE_CONSOLE, &env);
	for (size_t i = 0; i < errors.Count(); ++i)
	{
		AppendGcmcError(errors[i]);
	}

	wxString inf = wxString::Format("Process terminated with exit code %d", code);
	m_logwnd->Append(code == 0 ? MSLInfo : MSLError, inf);
	
	return code;
#endif

	if (gcmcProcess)
	{
		m_logwnd->Append(MSLInfo, _("gcmc_vc.exe already running"));
		return 1;
	}
	m_logwnd->Append(MSLInfo, _("Start converting..."));
	m_logwnd->Append(MSLInfo, arg.c_str());

	if (m_timer.IsRunning())
		m_timer.Stop();

	m_gcmc_running_in_sec = 0;
	m_timer.Start(1000);


	gcmcProcess = new GcmcProcess(this, dst_fname, what_to_do);
	int code = wxExecute(arg, wxEXEC_ASYNC| wxEXEC_HIDE_CONSOLE | wxEXEC_NODISABLE, gcmcProcess, &env);
	return code;

}




void AppFrame::GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do)
{

	if (gcmcProcess)
	{
		m_gcmc_running_in_sec = 0;
		m_timer.Stop();
		wxString inf = wxString::Format(_("Process terminated with exit code %d"), status);
		m_logwnd->Append(status == 0 ? MSLInfo : MSLError, inf);
		Edit *pedit;
		if (status == 0)
		{
			switch (what_to_do)
			{
				case ConvertGcmcOpenFile: 
					FileOpen(dst_fname); 
					break;
				case ConvertGcmcPasteFile:
					pedit = GetActiveFile();
					if (pedit != NULL)
						pedit->PasteFile(dst_fname);
					break;
				case ConvertGcmcNewFile:	
					DoNewFile(FILETYPE_NC, wxEmptyString, true, dst_fname); 
					break;
				case ConvertGcmcRunSimilate:	
					DoSimulate(dst_fname); 
					break;
			}
		}
		delete gcmcProcess;
		gcmcProcess = NULL;
	}
}

int AppFrame::DoConvertGcmc(DoAfterConvertGcmc what_to_do)
{
	Edit *pedit = GetActiveFile();
	if (!pedit)
		return 1;

	wxString src_fname = pedit->GetFileName();
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
	//event.Enable(pedit->GetFileType() == FILETYPE_GCMC);
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
			m_logwnd->Append(MSLError, _("Can't create the thread to run simulate"));
			delete simulateThread;
			simulateThread = NULL;

		}
	}
}





void AppFrame::CreateWatcher()
{
	if (m_watcher)
		return;

	m_watcher = new wxFileSystemWatcher();
	m_watcher->SetOwner(this);
	// Add Preferences catalog
	
	std::filesystem::path prefpath = StandartPaths::Get()->GetPreferencesPath();
	wxFileName fn = wxFileName::DirName(prefpath.c_str());
	m_watcher->AddTree(fn);

	Bind(wxEVT_FSWATCHER, &AppFrame::OnFileSystemEvent, this);
	if (m_dirtree)
		m_dirtree->SetWatcher(m_watcher);

}

void AppFrame::UpdatePreferences()
{
	Preferences::Get()->Read();

	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(EditorPanel)))
		{
			EditorPanel *pEdit = dynamic_cast<EditorPanel *>(m_notebook->GetPage(i));
			pEdit->GetEdit()->UpdatePreferences();			
		}
	}
	if (GetActiveFile())
		GetActiveFile()->Refresh(false);
	return ;
}

void AppFrame::OnFileSystemEvent(wxFileSystemWatcherEvent& event)
{
	
	wxFileName prefpath = wxFileName::DirName(StandartPaths::Get()->GetPreferencesPath().c_str());
	wxString s1 = event.GetPath().GetPath();
	wxString s2 = prefpath.GetPath();
	if ( event.GetPath().GetPath() == prefpath.GetPath() )
	{
		UpdatePreferences();
	}

	if (m_dirtree) 
		m_dirtree->GetEventHandler()->ProcessEvent(event);
}
