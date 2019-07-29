#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include "wx/event.h"
#include "wx/artprov.h"


//! application headers
#include "appframe.h"       // Prefs
#include "app.h"
#include "appdefs.h"      
#include "defsext.h"     
#include "prefs.h"
#include "editorpanel.h"
#include "edit.h"
#include "View3D.h"

#include "about.h"
#include "propertiesdlg.h"
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


using namespace Interpreter;


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
			{

				const wxString &fname = filenames[n];
				// first check that it is a file
				if (!std::filesystem::is_regular_file(filenames[n].wc_str()))
				{
					int ret = wxMessageBox(wxString::Format(_("File %s is not a regular file of the file system\nWould you like to add it to folders pane?"), fname),
						wxMessageBoxCaptionStr, wxYES_NO | wxCANCEL | wxICON_QUESTION);
					if (ret == wxYES)
					{
						m_pOwner->AddPath(fname);
					}
					else if (ret == wxCANCEL)
						return false;
				}
				else
					m_pOwner->FileOpen(fname);
			}
		}
		return true;
	}

private:
	AppFrame *m_pOwner;
};


//----------------------------------------------------------------------------
// AppFrame
//----------------------------------------------------------------------------

const int wxAuiBaseTabCtrlId = 5380;


// -- wxAuiNotebook class implementation --

#define EVT_AUI_ANY(event, func) \
    wx__DECLARE_EVT2(event, wxID_ANY, wxID_ANY, wxAuiNotebookEventHandler(func))


wxBEGIN_EVENT_TABLE (AppFrame, wxFrame)
    // common
    EVT_CLOSE (                      AppFrame::OnClose)
	    // file
	EVT_MENU(ID_NEWNC,				 AppFrame::OnFileNew)
	EVT_MENU(ID_NEWGCMC,			 AppFrame::OnFileNew)
    EVT_MENU (ID_OPENFILE,             AppFrame::OnFileOpen)
    EVT_MENU (wxID_SAVE,             AppFrame::OnFileSave)
    EVT_MENU (wxID_SAVEAS,           AppFrame::OnFileSaveAs)
    EVT_MENU (wxID_CLOSE,            AppFrame::OnFileClose)
	EVT_MENU_RANGE(wxID_FILE, wxID_FILE9, AppFrame::OnOpenLastFile)	
	EVT_MENU_RANGE(ID_MACROSFIRST, ID_MACROSLAST, AppFrame::OnMacros)
	EVT_MENU (ID_MACROSES,			 AppFrame::OnMacroses)
	EVT_MENU(ID_MATHCALC,			 AppFrame::OnMathCalc)
	EVT_MENU(ID_MATHEXPRESSION, AppFrame::OnMathExpression)
	EVT_UPDATE_UI(ID_MATHCALC, AppFrame::OnUpdateNCIsOpen)
	EVT_UPDATE_UI(ID_MATHEXPRESSION, AppFrame::OnUpdateNCIsOpen)

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
	EVT_MENU(ID_SHOWWELCOME, AppFrame::OnShowWelcome)
	EVT_MENU(ID_SHOWDIRPANE, AppFrame::OnShowDirPane)
	EVT_UPDATE_UI(ID_SHOWDIRPANE, AppFrame::OnUpdateUIShowDirPane)
	

    // help
    EVT_MENU(wxID_ABOUT,            AppFrame::OnAbout)	
	EVT_MENU(ID_WRITEFEEDBACK, AppFrame::OnWriteFeedback)
	EVT_MENU(ID_HELPGCMC, AppFrame::OnHelp)
	EVT_MENU(ID_HELPGCMC, AppFrame::OnHelp)
	EVT_MENU(ID_HELPNC, AppFrame::OnHelp)
	EVT_MENU(ID_WHATNEWS, AppFrame::OnHelp)



  //  EVT_CONTEXT_MENU(                AppFrame::OnContextMenu)
//GCode
	
	EVT_MENU_RANGE(ID_3D_FIRST, ID_3D_LAST, AppFrame::On3DView)
	EVT_UPDATE_UI_RANGE(ID_3D_FIRST, ID_3D_LAST, AppFrame::On3DViewUpdate)

	EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, AppFrame::OnNotebookPageClose)
	EVT_COMMAND(wxID_ANY, FILE_MODIFYED_EVENT, AppFrame::OnFileModified)
	EVT_COMMAND(wxID_ANY, FILE_OPEN_EVENT, AppFrame::OnFileOpenEvent)
	EVT_COMMAND(wxID_ANY, FILE_RENAME_EVENT, AppFrame::OnFileRenamed)
	EVT_COMMAND(wxID_ANY, FILE_REMOVE_EVENT, AppFrame::OnFileRemoveEvent)
	EVT_COMMAND(wxID_ANY, FILE_NEW_EVENT, AppFrame::OnFileNewEvent)
	
	EVT_AUI_ANY(wxEVT_AUINOTEBOOK_TAB_RIGHT_UP,	AppFrame::OnTabRightUp)
	
wxEND_EVENT_TABLE ()



AppFrame::AppFrame (const wxString &title)
        : wxFrame ((wxFrame *)NULL, wxID_ANY, title, wxDefaultPosition, wxSize(840,650),
                    wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
	// tell wxAuiManager to manage this frame
	m_mgr.SetManagedWindow(this);
	m_mgr.SetArtProvider( Preferences::Get()->GetArtProvider(true) );

	wxArtProvider::Push(new ExArtProvider());

	m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
	m_notebook_theme = 0;
	m_dirtree = 0;
	m_watcher = 0;
	m_macroses = new Macroses();

    SetIcon(wxICON(sample));
    SetTitle (APP_NAME);
    //SetBackgroundColour ("GREEN");
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config != NULL)
		config->ReadFileNames();

    // create menu
	wxMenuBar *m_menuBar = CreateMenu();
	SetMenuBar(m_menuBar);

	
	m_notebook = CreateNotebook();

	m_mgr.AddPane(m_notebook, wxAuiPaneInfo().Name("notebook_content").
		CenterPane().PaneBorder(false));

	
	m_dirtree = new DirPane(this);
	m_mgr.AddPane(m_dirtree, wxAuiPaneInfo().
		Name("Folders").Caption("Folders").
		Left().Layer(1).Position(1).
		CloseButton(false).MaximizeButton(false).CaptionVisible(false));
	
	
	

	
	bool visibleDir = true;
	if (config != NULL)
		visibleDir = config->Read(L"DirVisible", visibleDir);
	
	wxAuiPaneInfo& pinfo = m_mgr.GetPane(m_dirtree);
	pinfo.Show(visibleDir);


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
	
	if (m_macroses)
		delete m_macroses;
}

void AppFrame::OnTabRightUp(wxAuiNotebookEvent& evt)
{
	wxMenu menu(wxEmptyString);
	/*
	if (IsModified())
	{
		wxFileName fn(m_filename);
		wxString menuTxt = wxString::Format(_("Save %s"), fn.GetFullName());
		menu.Append(wxID_SAVE, menuTxt);
		menu.AppendSeparator();
	}
	wxString incl_file = GetGcmcIncludeFileName();
	if (!incl_file.empty())
	{
		menu.Append(ID_INCLUDE_FILE_OPEN, wxString::Format(_("Open file: \"%s\""), incl_file));
		menu.AppendSeparator();
	}
	*/
	menu.Append(wxID_UNDO, _("Undo form wxAuiNotebook"));
	menu.AppendSeparator();
	menu.Append(wxID_CUT, _("Cut"));
	menu.Append(wxID_COPY, _("Copy"));
	menu.Append(wxID_PASTE, _("Paste"));
	menu.AppendSeparator();
	menu.Append(wxID_SELECTALL, "Select All");

	PopupMenu(&menu, ScreenToClient(wxPoint(0,0)));
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
	void OnContextMenu(wxContextMenuEvent& event);	
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(StubNotebook, wxAuiNotebook)
//	EVT_RIGHT_UP(StubNotebook::OnRightUp)
	//EVT_CONTEXT_MENU(StubNotebook::OnContextMenu)
wxEND_EVENT_TABLE()

//TODO
void StubNotebook::OnContextMenu(wxContextMenuEvent& event)
{
	wxMenu menu(wxEmptyString);
	/*
	if (IsModified())
	{
		wxFileName fn(m_filename);
		wxString menuTxt = wxString::Format(_("Save %s"), fn.GetFullName());
		menu.Append(wxID_SAVE, menuTxt);
		menu.AppendSeparator();
	}
	wxString incl_file = GetGcmcIncludeFileName();
	if (!incl_file.empty())
	{
		menu.Append(ID_INCLUDE_FILE_OPEN, wxString::Format(_("Open file: \"%s\""), incl_file));
		menu.AppendSeparator();
	}
	*/
	menu.Append(wxID_UNDO, _("Undo form wxAuiNotebook"));
	menu.AppendSeparator();
	menu.Append(wxID_CUT, _("Cut"));
	menu.Append(wxID_COPY, _("Copy"));
	menu.Append(wxID_PASTE, _("Paste"));
	menu.AppendSeparator();
	menu.Append(wxID_SELECTALL, "Select All");

	PopupMenu(&menu, ScreenToClient(event.GetPosition()));
	event.Skip();
}

wxAuiNotebook* AppFrame::CreateNotebook()
{
	// create the notebook off-window to avoid flicker
	wxSize client_size = GetClientSize();

	//wxAuiNotebook* ctrl = new wxAuiNotebook();
	StubNotebook* ctrl = new StubNotebook();
	ctrl->SetAuiArtProvider();
	ctrl->Create(this, wxID_ANY,
		wxPoint(client_size.x, client_size.y),
		FromDIP(wxSize(330, 200)),
		m_notebook_style);
	ctrl->SetArtProvider(Preferences::Get()->GetTabArtProvider());
	ctrl->SetBackgroundColour(Preferences::Get()->GetStdColor(ColourScheme::WINDOW));
	return ctrl;
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

void AppFrame::OnFileModified(wxCommandEvent &)
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

	FilePage *pedit = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
	if (!pedit)
		return;
	pedit->GetEdit()->SetFileName( pstring_data->GetData() );
	UpdateTitle(nPage);	
}


void AppFrame::OnNotebookPageClose(wxAuiNotebookEvent& evt)
{
	wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
	wxWindow *page = ctrl->GetPage(evt.GetSelection());
	if (page->IsKindOf(CLASSINFO(FilePage)))
	{
		FilePage *fp = dynamic_cast<FilePage *>(page);
		if ( !fp->DoFileSave(true,false) )
			evt.Veto();
	}
}


// common event handlers

void AppFrame::OnClose (wxCloseEvent &event)
{

// save all modified files
	if (!DoSaveAllFiles() )
	{
		event.Veto();
		return;
	}
	
	wxAuiPaneInfo& pinfo = m_mgr.GetPane(m_dirtree);
	bool visibleDir  = pinfo.IsShown();

	wxString strPerspective = m_mgr.SavePerspective();
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config != NULL)
	{
		config->WriteFileNames();
		config->Write(L"DirVisible", visibleDir);
	}
	
    Destroy();
}


void AppFrame::OnDownloadUpdate(wxCommandEvent &WXUNUSED(event)) 
{
	wxMessageBox("Download update");
}

void AppFrame::OnWriteFeedback( wxCommandEvent &WXUNUSED(event) )
{
	wxString sendTo = APP_MAIL;
	sendTo += L"?subject=";
	sendTo += wxString::Format(L"%s%%20%s", wxString(APP_NAME), wxString(APP_VERSION));	
	ShellExecute(NULL, L"open", sendTo.c_str(), L"", L"", 0);
	

}

void AppFrame::OnHelp(wxCommandEvent &event)
{
	wxString topic;
	switch(event.GetId())
	{
		case ID_HELPGCMC: topic = L"gcodehelp\\gcode.htm"; break;
		case ID_HELPNC: topic = L"gcmchelp\\gcmc.htm"; break;
		case ID_WHATNEWS: topic = "whatnews.htm"; break;
		default: topic = "unknown cmd"; break;
	}

	std::filesystem::path name_topic = StandartPaths::Get()->GetResourcesPath( topic.wc_str() );	
	wxLaunchDefaultApplication(name_topic.c_str());	
}

void AppFrame::OnAbout (wxCommandEvent &WXUNUSED(event)) {
    AppAbout dlg(this);
}

void AppFrame::OnShowWelcome(wxCommandEvent &WXUNUSED(event))
{
	ShowWelcome();
}

void AppFrame::OnUpdateUIShowDirPane(wxUpdateUIEvent& event)
{
	if ( m_dirtree)
		event.SetText(m_dirtree->IsShown() ? _("Hide Folders Pane") : _("Show Folders Pane") );
}

void AppFrame::ShowHideDirPane(bool allwaysshow)
{
	if (!m_dirtree->IsShown())
	{
		wxAuiPaneInfo& pinfo = m_mgr.GetPane(m_dirtree);
		pinfo.Show();
		m_mgr.Update();
	}
	else if(!allwaysshow)
	{
		wxAuiPaneInfo& pinfo = m_mgr.GetPane(m_dirtree);
		pinfo.Hide();
		m_mgr.Update();
	}

}

void AppFrame::OnShowDirPane(wxCommandEvent &WXUNUSED(event))
{
	ShowHideDirPane();
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
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(FilePage)))
		{
			FilePage *pEdit = dynamic_cast<FilePage *>(m_notebook->GetPage(i));
			if (pEdit == 0 || !pEdit->IsModified())
				continue;

			m_notebook->SetSelection(i);
			if (  !pEdit->DoFileSave(true, false) )
			{
				return false;
			}
		}
	}
	return true;
}

bool AppFrame::FindPageByFileName(const wxString &new_file_name, size_t *nPage)
{
	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(FilePage)))
		{
			FilePage *pEdit = dynamic_cast<FilePage *>(m_notebook->GetPage(i));
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

FilePage *AppFrame::DoNewFile(int file_type, const wxString &defpath, bool closeWelcome, const wxString &contextFile)
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
	
	FilePage * pedit = new FilePage(m_notebook, file_type, defPath.GetFullPath(),true );
	//Edit *pedit = new Edit(m_notebook, wxID_ANY);
	m_notebook->AddPage(pedit, new_file_name , true);
	//pedit->NewFile(file_type, defPath.GetFullPath());

	if ( !contextFile.empty() )
		pedit->GetEdit()->PasteFile(contextFile.wc_str());
		
	UpdateTitle();

	m_notebook->Thaw();

	if (closeWelcome)
		HideWelcome();

	return pedit;
}

// file event handlers
void AppFrame::OnFileOpen (wxCommandEvent &event ) 
{
  
	wxString fname;
    wxFileDialog dlg (this, _("Open file"), wxEmptyString, wxEmptyString, 
		_("GCMC and NC files (*.gcmc;*.nc;*.ngc)|*.gcmc;*.nc;*.ngc|GCMC files (*.gcmc)|*.gcmc|NC files (*.nc;*.ngc)|*.nc;*.ngc|Any file(*.*) |*"),
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
			FileOpen( it->GetFullPath() );
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
	wxWindow *wnd = m_notebook->GetCurrentPage();
	FilePage *panel = dynamic_cast<FilePage *>(wnd);
	if (panel)
		panel->DoFileSave( false, false );
    //UpdateTitle();
}

void AppFrame::OnFileSaveAs(wxCommandEvent &WXUNUSED(event))
{
	wxWindow *wnd = m_notebook->GetCurrentPage();
	FilePage *panel = dynamic_cast<FilePage *>(wnd);
	if (panel)
		panel->DoFileSave(false, true);
	//UpdateTitle();
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
	
	MacrosesDlg dlg(m_macroses, this);
	DoRunMacros( dlg.GetSelected() );
}

void AppFrame::OnMacros(wxCommandEvent &event)
{
	DoRunMacros(event.GetId() - ID_MACROSFIRST);
}

void AppFrame::DoRunMacros(int indx)
{

	if (indx < 0 || indx >= m_macroses->Count())
		return;

	MacrosDesc &desc = m_macroses->Get(indx);
	MacrosParamDlg dlgparam(&desc, this);
	if (dlgparam.ShowModal() != wxID_OK)
		return;

	wxString  args = m_macroses->BuildCommandLine(indx);
	std::wstring src_fname = StandartPaths::Get()->GetMacrosPath(desc.gcmcfile.c_str());
	std::wstring dst_fname = StandartPaths::Get()->GetTemporaryPath(L"tmp.nc");

	FilePage *panel = 0;
	if (!dlgparam.IsInNewWindow())
	{
		wxWindow *wnd = m_notebook->GetCurrentPage();
		panel = dynamic_cast<FilePage *>(wnd);		
	}
	else
	{
		panel = DoNewFile(FILETYPE_NC, wxEmptyString, true);
	}

	if (!panel)
		return;

	panel->ConvertGcmc(src_fname.c_str(), dst_fname.c_str(), args.c_str());
	
}


void AppFrame::DoMathCalc( DoMathBase &mth )
{
	Edit *pedit = 0;
	wxWindow *wnd = m_notebook->GetCurrentPage();
	FilePage *panel = dynamic_cast<FilePage *>(wnd);
	if (panel)
		pedit = panel->GetEdit();

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

	Edit *pedit = 0;
	FilePage *panel = dynamic_cast<FilePage *>(m_notebook->GetCurrentPage());
	if (panel)
		pedit = panel->GetEdit();
	else
		return;
	
	DoMathSimple mth;
	MathSimpleDlg dlg(&mth, this, pedit->HasSelection() );
	if (dlg.ShowModal() != wxID_OK)
		return;
	DoMathCalc(mth);
}


void AppFrame::OnUpdateNCIsOpen(wxUpdateUIEvent& event)
{

	FilePage *panel = dynamic_cast<FilePage *>(m_notebook->GetCurrentPage());
	bool enable = false;
	if (panel)
	{
		Edit *pedit = panel->GetEdit();
		if (pedit && pedit->GetFileType() == FILETYPE_NC)
			enable = true;
	}
	event.Enable( enable );
}


void AppFrame::OnUpdateAnyFileIsOpen(wxUpdateUIEvent& event)
{
	FilePage *panel = dynamic_cast<FilePage *>(m_notebook->GetCurrentPage());
	bool enable = panel != 0;
	event.Enable(enable);
}

// properties event handlers
void AppFrame::OnMathExpression(wxCommandEvent &WXUNUSED(event))
{


	Edit *pedit = 0;
	FilePage *panel = dynamic_cast<FilePage *>(m_notebook->GetCurrentPage());
	if (panel)
		pedit = panel->GetEdit();
	else
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
	Edit *pedit = 0;
	FilePage *panel = dynamic_cast<FilePage *>(m_notebook->GetCurrentPage());
	if (panel)
		pedit = panel->GetEdit();

    if (pedit) 
		pedit->GetEventHandler()->ProcessEvent (event);
}


void AppFrame::On3DView(wxCommandEvent &event)
{
	View3D *view = 0;
	wxWindow *wnd = m_notebook->GetCurrentPage();
	FilePage *panel = dynamic_cast<FilePage *>(wnd);
	if (panel)
		view = panel->Get3D();

	if (view)
		view->GetEventHandler()->ProcessEvent(event);
}


void AppFrame::On3DViewUpdate(wxUpdateUIEvent& event)
{
	View3D *view = 0;
	wxWindow *wnd = m_notebook->GetCurrentPage();
	FilePage *panel = dynamic_cast<FilePage *>(wnd);
	if (panel)
		view = panel->Get3D();


	if (view)
		view->GetEventHandler()->ProcessEvent(event);
	else
		event.Enable(false);
}

void AppFrame::OnDirTree(wxCommandEvent &event)
{
	if (m_dirtree) 
		m_dirtree->GetEventHandler()->ProcessEvent(event);
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
	wxMenuItem *mi = menuFile->Append(ID_OPENFILE, _("Open ..\tCtrl+O")); 
	mi->SetBitmaps(wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_MENU)); 


	wxMenu *menuLastFiles = new wxMenu;
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
	{
		const FileNamesList &files = config->GetFiles();
		int n = 0;
		std::for_each( files.begin(), files.end(), 
			[menuLastFiles,&n](const wxFileName &p) {
			if (n < 10) { menuLastFiles->Append(wxID_FILE + n, p.GetFullPath() ); n++; } });
	}
	menuFile->Append(ID_OPENRECENT, _("Open recent"), menuLastFiles);
	menuFile->AppendSeparator();
	//New
	menuFile->Append(ID_NEWNC, _("New GCODE"));
	menuFile->Append(ID_NEWGCMC, _("New GCMC"));
	menuFile->AppendSeparator();
	menuFile->Append(ID_SHOWDIRPANE, _("Show Folders Pane"));
	menuFile->Append(ID_SHOWWELCOME, _("Welcome window"));
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
  	
	// Macrosos
	wxMenu *insertMenu = new wxMenu;
	CreateMacrosesMenu(insertMenu);
	
/*
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

	// GCode menu
	wxMenu *menuGCode = new wxMenu;
	menuGCode->Append(ID_GCODE_CHECK, _("&Check"));
	menuGCode->Append(ID_GCODE_SIMULATE, _("&Simulate"));
	
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
*/	
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
	m_menuBar->Append(insertMenu, _("&Insert"));
  //  m_menuBar->Append (menuView, _("&View"));
//	m_menuBar->Append(menuGCode, _("&GCode"));
//	m_menuBar->Append(menu3D, _("&3DView"));
	m_menuBar->Append(menuPref, _("Preferences"));
    m_menuBar->Append (menuHelp, _("&Help"));    
	return m_menuBar;

}

void AppFrame::CreateMacrosesMenu(wxMenu *menuInsert)
{
	int nmsc = m_macroses->Count();
	for (int i = 0; i < nmsc && i < NUM_MENU_MACROS; ++i)
	{
		MacrosDesc &md = m_macroses->Get(i);
		menuInsert->Append(ID_MACROSFIRST + i, md.name.c_str());
	}
	menuInsert->AppendSeparator();
	menuInsert->Append(ID_MACROSES, _("All Macroses..."));
}

void AppFrame::AddPath(const wxString &path)
{
	if (m_dirtree)
	{
		ShowHideDirPane(true);		
		m_dirtree->AddPath(path);
	}
}

void AppFrame::FileOpen (const wxString &fn)
{
    wxFileName w(fn); 
	w.Normalize(); 
	wxString fname = w.GetFullPath();
	
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
			
			FilePage *pedit = new FilePage(m_notebook, FILETYPE_UNKNOW, fname, false );
			//pedit->LoadFile(fname);
			m_notebook->AddPage(pedit, w.GetFullName(), true);
			UpdateTitle();
			ConfigData *config;
			if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
				config->AddFileNameToSaveList(w);

		}
	}
	catch (...)
	{
		wxMessageBox(wxString::Format(_("Can not open file %s!"), fname ), _("Error opening file") );
	}
	m_notebook->Thaw();
}


void AppFrame::UpdateTitle(FilePage *page)
{
	size_t n = m_notebook->GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(FilePage)))
		{
			if (page == dynamic_cast<FilePage *>(m_notebook->GetPage(i)))
			{
				UpdateTitle(i);
				return;
			}
		}
	}
}



void AppFrame::UpdateTitle(size_t nPage )
{
	if (nPage == wxNOT_FOUND)
		nPage = m_notebook->GetSelection();
	if (nPage == wxNOT_FOUND)
		return;

	FilePage *pedit = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
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
	// Add macros catalog
	fn = wxFileName::DirName(StandartPaths::Get()->GetMacrosPath().c_str());
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
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(FilePage)))
		{
			FilePage *pEdit = dynamic_cast<FilePage *>(m_notebook->GetPage(i));
			pEdit->GetEdit()->UpdatePreferences();	
			if ( m_notebook->GetSelection() == i )
				pEdit->Refresh(false);
		}
	}
	return;
}
void AppFrame::UpdateMacroses()
{	
	m_macroses->Init();
	// TODO update MenuBar
	wxMenuBar *m_menuBar = GetMenuBar();
	int n = m_menuBar->FindMenu(_("Insert"));
	if (n == wxNOT_FOUND)
		return;
	wxMenu *insertMenu = m_menuBar->GetMenu(n);
	while (insertMenu->GetMenuItemCount() )
	{
		insertMenu->Delete(insertMenu->FindItemByPosition(0));
	}
	CreateMacrosesMenu(insertMenu);
}


void AppFrame::OnFileSystemEvent(wxFileSystemWatcherEvent& event)
{
	
	wxFileName prefpath = wxFileName::DirName(StandartPaths::Get()->GetPreferencesPath().c_str());
	wxFileName macrospath = wxFileName::DirName(StandartPaths::Get()->GetMacrosPath().c_str());
	wxString s = event.GetPath().GetPath();
	if (s == prefpath.GetPath())
	{
		UpdatePreferences();
	}
	else if (s == macrospath.GetPath())
	{
		UpdateMacroses();
	}

	if (m_dirtree) 
		m_dirtree->GetEventHandler()->ProcessEvent(event);
}
