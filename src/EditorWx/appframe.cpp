#include "wx/wx.h" // filename support
#include "wx/filename.h" // filename support
#include "app.h"
#include "appframe.h"       // Prefs


#include "wx/event.h"
#include "wx/artprov.h"
#include "appdefs.h"      
#include "defsext.h"     
#include "prefs.h"
#include "editorpanel.h"
#include "edit.h"
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

/**/
//! application headers



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
    EVT_MENU (ID_CLOSEACTIVETAB,            AppFrame::OnFileClose)
	EVT_MENU_RANGE(wxID_FILE, wxID_FILE9, AppFrame::OnOpenLastFile)
	EVT_MENU_RANGE(ID_MACROSFIRST, ID_MACROSLAST, AppFrame::OnMacros)
	EVT_MENU (ID_MACROSES,			 AppFrame::OnMacroses)
	EVT_MENU(ID_MATHCALC,			 AppFrame::OnMathCalc)
	EVT_MENU(ID_MATHEXPRESSION, AppFrame::OnMathExpression)
	EVT_UPDATE_UI(ID_MATHCALC, AppFrame::OnUpdateNCIsOpen)
	EVT_UPDATE_UI(ID_MATHEXPRESSION, AppFrame::OnUpdateNCIsOpen)
	EVT_MENU(ID_CLOSEALL, AppFrame::OnFileCloseAll)
	EVT_MENU(ID_CLOSEALLBUTTHIS, AppFrame::OnFileCloseAllButThis)
	EVT_MENU(ID_ADDFIILEDIRTOPANE, AppFrame::OnAddFilePathToDirPane)

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
	//EVT_MENU(ID_USERPREFS, AppFrame::OnUserPreferences)
	EVT_MENU_RANGE(ID_CHANGETHEME1, ID_CHANGETHEMELAST, AppFrame::OnChangeTheme)
	EVT_UPDATE_UI_RANGE(ID_CHANGETHEME1, ID_CHANGETHEMELAST, AppFrame::OnUpdateChangeTheme)
	
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

	//wxIcon ic = wxICON(app_icon);// wxICON(IDI_ICON1);
    SetIcon(wxICON(app_icon));
	//SetIcon();

    SetTitle (APP_NAME);
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
	
	
	bool visibleDir = m_dirtree->Load();
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
	m_notebook->SetSelection(evt.GetSelection());
	wxMenu menu(wxEmptyString);
	int nPage = m_notebook->GetSelection();
	FilePage *pFile = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
	if ( pFile && pFile->IsModified() )
	{
		wxFileName fn(pFile->GetEdit()->GetFileName());
		wxString menuTxt = wxString::Format(_("Save %s"), fn.GetFullName()); 	// Save
		menu.Append(wxID_SAVE, menuTxt);
	}

	menu.Append(ID_CLOSEACTIVETAB, _("Close")); 	//Close
	menu.Append(ID_CLOSEALL, _("Close All")); 	//Close All but this
	wxMenuItem *item = menu.Append(ID_CLOSEALLBUTTHIS, _("Close All but this")); 	//Close All but this
	item->Enable(m_notebook->GetPageCount() > 1);

	if (pFile)
	{
		menu.Append(ID_ADDFIILEDIRTOPANE, _("Add file path to Pane")); 	//Close All but this
	}

	menu.AppendSeparator();
	menu.Append(ID_NEWNC, _("New GCODE"));
	menu.Append(ID_NEWGCMC, _("New GCMC"));
	menu.Append(ID_OPENFILE, _("Open file..."));

	
	PopupMenu(&menu, ScreenToClient( wxGetMousePosition()));
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
	void UpdatePreferences();
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(StubNotebook, wxAuiNotebook)
wxEND_EVENT_TABLE()

void StubNotebook::UpdatePreferences()
{
	SetBackgroundColour(Preferences::Get()->GetStdColor(ColourScheme::WINDOW));
	GetArtProvider()->UpdateColoursFromSystem();
	m_mgr.GetArtProvider()->UpdateColoursFromSystem();

	wxAuiTabCtrl* tabCtrl = GetActiveTabCtrl();
	tabCtrl->GetArtProvider()->UpdateColoursFromSystem();

	size_t n = GetPageCount();
	for (size_t i = 0; i < n; ++i)
	{
		if (GetPage(i)->IsKindOf(CLASSINFO(FilePage)))
		{
			FilePage *fp = dynamic_cast<FilePage *>(GetPage(i));
			fp->UpdatePreferences();
			if (GetSelection() == i)
				fp->Refresh(false);
		}
	}
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
	ctrl->UpdatePreferences();
	return ctrl;
}


WelcomeWnd *AppFrame::FindWelcomePage(size_t *welcome_page)
{
	size_t n = m_notebook->GetPageCount();
	WelcomeWnd *welcome = 0;
	if ( welcome_page )
		*welcome_page = wxNOT_FOUND;
	for (size_t i = 0; i < n; ++i)
	{
		if (m_notebook->GetPage(i)->IsKindOf(CLASSINFO(WelcomeWnd)))
		{
			welcome = dynamic_cast<WelcomeWnd *>(m_notebook->GetPage(i));
			if (welcome_page)
				*welcome_page = i;
			break;
		}

	}
	return welcome;
}

void AppFrame::ShowWelcome()
{
	m_notebook->Freeze();
	// check is welcome window exist
	size_t welcome_page = wxNOT_FOUND;
	FindWelcomePage(&welcome_page);
	if (welcome_page == wxNOT_FOUND)
	{
		m_notebook->InsertPage(0, new WelcomeWnd(m_notebook), _("Welcome") , true);
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
	FindWelcomePage(&welcome_page);
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
	
	wxString strPerspective = m_mgr.SavePerspective();
	m_dirtree->Save();
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
	wxString wildCard = Preferences::Get()->CreateWildCard();
	//wildCard = _("Any file(*.*)|*.*|GCMC and NC files (*.gcmc;*.nc;*.ngc)|*.gcmc;*.nc;*.ngc|GCMC files (*.gcmc)|*.gcmc|NC files (*.nc;*.ngc)|*.nc;*.ngc");

    wxFileDialog dlg (this, _("Open file"), wxEmptyString, wxEmptyString, wildCard,
		wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
	
//		_("GCMC and NC files (*.gcmc;*.nc;*.ngc)|*.gcmc;*.nc;*.ngc|GCMC files (*.gcmc)|*.gcmc|NC files (*.nc;*.ngc)|*.nc;*.ngc|Any file(*.*) |*")

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
		
		//paths.Add(StandartPaths::Get()->GetRootPath().c_str());
		//paths.Add(StandartPaths::Get()->GetMacrosPath().c_str());
		paths.Add(StandartPaths::Get()->GetLibraryPath().c_str());

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
	
	if ( FileOpen( fname.GetFullPath() ) )
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
	wxASSERT(config);
	int n = event.GetId() - wxID_FILE;
	const FileNamesList &files = config->GetFiles();
	if (n >= 0 && n < static_cast<int>(files.size()) )
	{
		auto it = files.begin();
		for (int i = 0; i < n; i++, it++) ;
		if (!FileOpen(it->GetFullPath()))
		{
			// Ask to remove from 
			if (wxMessageBox(wxString::Format(_("Would you like to remove file %s from history list?"), it->GetFullName()), _("Error opening file"),
				wxYES | wxNO | wxCENTRE) == wxYES)
			{
				config->RemoveFileNameFromSaveList(it->GetFullPath() );
				UpdateLastFilesList();
			}
		}
		else if (event.GetClientData() != NULL)
			HideWelcome();
	}
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


bool AppFrame::DoClosePage(int nPage)
{
	wxCHECK_MSG((nPage >= 0 && nPage < int(m_notebook->GetPageCount())), false,  "Invalid page index");
	FilePage *pEdit = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
	if (pEdit != 0 && !pEdit->DoFileSave(true, false))
		return false;
	m_notebook->DeletePage(nPage);
	return true;
}


void AppFrame::OnFileClose(wxCommandEvent &event)
{
	DoClosePage(m_notebook->GetSelection());	
	m_mgr.Update();
}



void AppFrame::OnFileCloseAll(wxCommandEvent &event)
{
	m_notebook->Freeze();
	while (m_notebook->GetPageCount())
	{
		if (!DoClosePage(0))
			return;
	}
	m_notebook->Thaw();
	m_mgr.Update();
}
void AppFrame::OnFileCloseAllButThis(wxCommandEvent &event)
{
	m_notebook->Freeze();
	int nPage = m_notebook->GetSelection();
	wxWindow *wnd = m_notebook->GetPage(nPage);
	//class all befor
	for (int i = 0; i < nPage; i++)
	{
		if ( !DoClosePage(0) )
			return;
	}
	// close all after
	while ((nPage=m_notebook->GetPageCount()-1) > 0)
	{
		if (!DoClosePage(nPage))
			return;
	}
	m_notebook->Thaw();
	m_mgr.Update();
}

void AppFrame::OnAddFilePathToDirPane(wxCommandEvent &event)
{
	int nPage = m_notebook->GetSelection();
	FilePage *pEdit = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
	if (pEdit == 0)
		return;	

	wxFileName fn( pEdit->GetEdit()->GetFileName() );
	wxString path = fn.GetPath(wxPATH_GET_VOLUME, wxPATH_NATIVE);
	AddPath(path);
}

// properties event handlers
void AppFrame::OnProperties(wxCommandEvent &WXUNUSED(event))
{
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);

	int oldlang = config->GetLanguage(-1);
	int lng = wxGetSingleChoiceIndex
	(
		_("Select language:"),
		_("Languages"),
		g_lang_count,
		g_langNames
	);

	int newlang = lng == -1 ? wxLANGUAGE_DEFAULT : g_langIds[lng];
	if (oldlang != newlang)
	{
		config->SetLanguage(newlang);
		if (DoSaveAllFiles())
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

	FilePage *panel = dynamic_cast<FilePage *>( m_notebook->GetCurrentPage() );
	int ftype = FILETYPE_UNKNOW;
	if ( panel )
		ftype = panel->GetEdit()->GetFileType();


	MacrosDesc &desc = m_macroses->Get(indx);
	MacrosParamDlg dlgparam(&desc, this, ftype );
	if (dlgparam.ShowModal() != wxID_OK)
		return;

	
	if ( dlgparam.IsInNewWindow() )
	{
		panel = DoNewFile(dlgparam.IsInGCMC() ? FILETYPE_GCMC : FILETYPE_NC, wxEmptyString, true);
	}

	if (!panel)
		return;


	std::wstring src_fname = StandartPaths::Get()->GetMacrosPath(desc.gcmcfile.c_str());

	if (dlgparam.IsInGCMC())
	{
		std::wstring include_file;
		bool needGcmcFileBody;
		wxString  args = m_macroses->BuildGCMCCode(indx, include_file, needGcmcFileBody);
		panel->GetEdit()->PasteGCMCText(args, include_file);
		if (needGcmcFileBody)
			panel->GetEdit()->PasteFile(src_fname.c_str(), true);
	}
	else
	{

		wxString  args = m_macroses->BuildCommandLine(indx);
		std::wstring dst_fname = StandartPaths::Get()->GetTemporaryPath(L"tmp.nc");
		panel->ConvertGcmc(src_fname.c_str(), dst_fname.c_str(), args.c_str(), dlgparam.IsInNewWindow() );
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
	
	std::shared_ptr<DoMathBase> mth( new DoMathSimple() );
	MathSimpleDlg dlg(dynamic_cast<DoMathSimple *>(mth.get()), this, pedit->HasSelection() );
	if (dlg.ShowModal() != wxID_OK)
		return;
	panel->DoMathCalc(mth);
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
		
		std::shared_ptr<DoMathBase> mth(new DoMathExpression());
		MathExpressionDlg dlg(dynamic_cast<DoMathExpression *>(mth.get()), this, pedit->HasSelection());
		if (dlg.ShowModal() != wxID_OK)
			return;
		panel->DoMathCalc(mth);
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

void AppFrame::OnChangeTheme(wxCommandEvent &event)
{
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);

	size_t n = event.GetId() - ID_CHANGETHEME1;
	const ThemeInfos &themes = Preferences::Get()->GetThemes();
	wxASSERT(n >= 0 && n < themes.size());
	config->SetTheme(themes[n].id );
	UpdatePreferences();
}

void AppFrame::OnUpdateChangeTheme(wxUpdateUIEvent& event)
{
	size_t n = event.GetId() - ID_CHANGETHEME1;
	const ThemeInfos &themes = Preferences::Get()->GetThemes();
	wxASSERT(n >= 0 && n < themes.size() );
	const ThemeInfo &ti = themes[n];

		//add two theme
	ConfigData * config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);
	
	if (config->GetTheme() == ti.id )
		event.Check(true);
	else
		event.Check(false);
}

void AppFrame::AddThemesToMenu()
{
	//clesr all 
	while (true)
	{
		auto nodeLast = m_menuThemes->GetMenuItems().GetLast();
		if (nodeLast)
		{
			wxMenuItem * const lastMenuItem = nodeLast->GetData();
			m_menuThemes->Destroy(lastMenuItem);
		}
		else
			break;
	}
	//add two theme
	const ThemeInfos &themes = Preferences::Get()->GetThemes();

	int n = 0;
	for (auto it = themes.begin(); it != themes.end(); ++it, ++n)
	{
		if (n >= 10)
			break;
		m_menuThemes->Append(ID_CHANGETHEME1 + n, it->name, wxEmptyString, wxITEM_CHECK);
	}
}


void AppFrame::AddFileToHisotyList(const wxFileName &filename)
{
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);

	config->AddFileNameToSaveList(filename);
	UpdateLastFilesList();
}

void AppFrame::UpdateLastFilesList()
{
	AddLastFilesToMenu();
	WelcomeWnd *welcome = FindWelcomePage();
	if (welcome)
		welcome->AddLastFilesToMenu();
}



void AppFrame::AddLastFilesToMenu()
{
	
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT( config );
	size_t n;
	wxMenu *menuFiles = m_menuLastFiles;
	const FileNamesList &files = config->GetFiles();
	size_t files_count = files.size();
	size_t menuitem_count = menuFiles->GetMenuItemCount();
	if (menuitem_count > files_count) // remove not needed  menuitem
	{
		n = menuitem_count - files_count;
		for (size_t i = 0; i < n; i++)
		{
			auto nodeLast = menuFiles->GetMenuItems().GetLast();
			if (nodeLast)
			{
				wxMenuItem * const lastMenuItem = nodeLast->GetData();
				menuFiles->Destroy(lastMenuItem);
				menuitem_count--;
			}
		}
	}
	
	// set new label
	n = 0;
	for (auto it = files.begin(); it != files.end(); ++it,++n)
	{
		if (n >= 10) 
			break;
		if (n < menuitem_count)
			menuFiles->SetLabel(wxID_FILE + n, it->GetFullPath());
		else
			menuFiles->Append(wxID_FILE + n, it->GetFullPath());
	}
	
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
	m_menuLastFiles = new wxMenu;
	AddLastFilesToMenu();


	menuFile->Append(ID_OPENRECENT, _("Open recent"), m_menuLastFiles);
	menuFile->AppendSeparator();
	//New
	mi = menuFile->Append(ID_NEWNC, _("New GCODE\tCtrl+N"));
	mi->SetBitmaps(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU));
	mi = menuFile->Append(ID_NEWGCMC, _("New GCMC\tCtrl+Shift+N"));
	mi->SetBitmaps(wxArtProvider::GetBitmap(wxART_NEW, wxART_MENU));
	menuFile->AppendSeparator();
	menuFile->Append(ID_SHOWDIRPANE, _("Show Folders Pane\tCtrl+P"));
	menuFile->Append(ID_SHOWWELCOME, _("Welcome window\tCtrl+W"));
	menuFile->AppendSeparator();
	//Save	
	mi = menuFile->Append(wxID_SAVE, _("Save\tCtrl+S"));
	mi->SetBitmaps(wxArtProvider::GetBitmap(ART_SAVE, wxART_MENU));
	mi = menuFile->Append(wxID_SAVEAS, _("Save  as ..\tCtrl+Shift+S"));
	mi->SetBitmaps(wxArtProvider::GetBitmap(ART_SAVE, wxART_MENU));
	mi = menuFile->Append(ID_CLOSEACTIVETAB, _("Close"));
	menuFile->AppendSeparator();
	
	menuFile->AppendSeparator();

    menuFile->Append (wxID_EXIT, _("&Quit\tCtrl+Q"));
	
	// Edit menu
	   	
	// change case submenu
	wxMenu *menuChangeCase = new wxMenu;
	menuChangeCase->Append(ID_CHANGEUPPER, _("&Upper case\tCtrl+Shift+U"));
	menuChangeCase->Append(ID_CHANGELOWER, _("&Lower case\tCtrl+U"));

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
	menuEdit->Append(ID_INDENTINC, _("&Indent increase\tTab"));
	menuEdit->Append(ID_INDENTRED, _("I&ndent reduce\tShift+Tab"));
	menuEdit->AppendSeparator();
	menuEdit->Append(ID_CHANGECASE, _("Change &case to .."), menuChangeCase);

	
	wxMenu *menuTools = new wxMenu;
	mi = menuTools->Append(ID_MATHCALC, _("Transform..."));
	mi->SetBitmaps(wxArtProvider::GetBitmap(ART_CONVERT, wxART_MENU));
	menuTools->AppendSeparator();


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
*/
	// Pregerences menu
	wxMenu *menuPref = new wxMenu;
	mi = menuPref->Append(ID_GLOBALPREFS, _("Default Preferences"));
	mi->SetBitmaps(wxArtProvider::GetBitmap(ART_PREFERENCES, wxART_MENU));
	//menuPref->Append(ID_USERPREFS, _("User Preferences"));
	m_menuThemes = new wxMenu;
	AddThemesToMenu();
	menuPref->Append(ID_CHANGETHEME, _("Themes"), m_menuThemes);
	menuPref->Append(ID_PROPERTIES, _("Language ..."));

     // Help menu
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_DOWNLOADUPDATE, _("&Download ..."));
	menuHelp->Append (wxID_ABOUT, _("&About..."));
	// construct menu
	m_menuBar->Append(menuFile, _("&File"));
	m_menuBar->Append(menuEdit, _("&Edit"));
	m_menuBar->Append(menuTools, _("&Tools"));
	m_menuBar->Append(insertMenu, _("&Insert"));
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

bool AppFrame::FileOpen (const wxString &fn,bool reloadifopen)
{
    wxFileName w(fn); 
	w.Normalize(); 
	wxString fname = w.GetFullPath();
	
	// first try  to find the file in the opened tabs
	size_t nPage = 0; 
	bool bOk = true;
	if (FindPageByFileName(fname, &nPage) )
	{
		m_notebook->SetSelection(nPage);
		if (reloadifopen)
		{
			FilePage *fp = dynamic_cast<FilePage *>(m_notebook->GetPage(nPage));
			if (fp && fp->GetEdit() )
				fp->GetEdit()->ReLoadFile();
		}
		return bOk;
	}
	
	m_notebook->Freeze();
	try
	{
		std::uintmax_t fsize = std::filesystem::file_size(fname.wc_str());
		if (fsize >= MAX_EDITOR_FILE_SIZE)
		{
			wxMessageBox(wxString::Format(_("File %s is very lage for the editor"), fname));
			bOk = false;
		}
		else
		{
			FilePage *pedit = new FilePage(m_notebook, FILETYPE_UNKNOW, fname, false );
			//pedit->LoadFile(fname);
			m_notebook->AddPage(pedit, w.GetFullName(), true);
			UpdateTitle();
			AddFileToHisotyList(w);		
		}
	}
	catch (...)
	{
		wxMessageBox(wxString::Format(_("Can not open file %s!"), fname ), _("Error opening file") );
		bOk = false;
	}
	m_notebook->Thaw();
	return bOk;
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
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);
	Preferences::Get()->UpdateAll( config->GetTheme() );
	dynamic_cast<StubNotebook *>(m_notebook)->UpdatePreferences();
	if ( m_dirtree )
		m_dirtree->UpdatePreferences();
	
	WelcomeWnd *welcome = FindWelcomePage();
	if (welcome)
		welcome->UpdateThemeColor();
	
	m_mgr.GetArtProvider()->UpdateColoursFromSystem();

	AddThemesToMenu();
	Refresh();
	Layout();
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
