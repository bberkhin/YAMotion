#pragma once

//#include "appframe.h"
#include "wx/aui/aui.h"
#include "wx/fswatcher.h"


class DoMathBase;
class DirPane;
class DropFileOpen;
class Macroses;
class FilePage;
//----------------------------------------------------------------------------
//! frame of the application APP_VENDOR-APP_NAME.
class AppFrame : public wxFrame 
{

	friend class GcmcProcess;
	friend class DropFileOpen;

public:
	//! constructor
	AppFrame(const wxString &title);

	//! destructor
	~AppFrame();

	//! event handlers
	//! common	
	void OnClose(wxCloseEvent &event);
	void OnAbout(wxCommandEvent &event);	
	void OnShowWelcome(wxCommandEvent &event);
	void OnDownloadUpdate(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnWriteFeedback(wxCommandEvent &event);
	void OnHelp(wxCommandEvent &event);
	//! file
	void OnFileNew(wxCommandEvent &event);
	void OnFileOpen(wxCommandEvent &event);
	void OnFileOpenEvent(wxCommandEvent &event);
	void OnFileRemoveEvent(wxCommandEvent &event);
	void OnFileNewEvent(wxCommandEvent &event);
	void OnFileSave(wxCommandEvent &event);
	void OnFileSaveAs(wxCommandEvent &event);
	void OnFileClose(wxCommandEvent &event);
	void OnOpenLastFile(wxCommandEvent &event);
	//properties
	void OnProperties(wxCommandEvent &event);
	void OnDefaultPreferences(wxCommandEvent &event);
	void OnUserPreferences(wxCommandEvent &event);
	//! dialogs
	void OnMacroses(wxCommandEvent &event);
	void OnMacros(wxCommandEvent &event);
	
	void OnMathCalc(wxCommandEvent &event);
	void OnMathExpression(wxCommandEvent &event);
	//! edit events
	void OnEdit(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent& evt);
	//! 3DViewevents
	void On3DView(wxCommandEvent &event);
	void On3DViewUpdate(wxUpdateUIEvent& event);
	//! dirtree events
	void OnDirTree(wxCommandEvent &event);
	
	void OnNotebookPageClose(wxAuiNotebookEvent& evt);
	void OnFileModified(wxCommandEvent& event);
	void OnFileRenamed(wxCommandEvent &evt);

	void OnFileSystemEvent(wxFileSystemWatcherEvent& event);
	void CreateWatcher();

	void UpdateTitle(FilePage *page);
	void UpdateTitle(size_t npage = wxNOT_FOUND);
	FilePage *DoNewFile(int file_type, const wxString &defpath, bool closeWelcome, const wxString &contextFile = wxEmptyString);
	void FileOpen(const wxString &fn);

private:
	bool FindPageByFileName(const wxString &new_file_name, size_t *nPage = NULL);
	bool DoSaveAllFiles();
	void DoMathCalc(DoMathBase &mth);
	void ShowWelcome();
	void HideWelcome();
	wxAuiNotebook* CreateNotebook();
	void CreateMacrosesMenu(wxMenu *menuInsert);
	void UpdatePreferences();
	void UpdateMacroses();
	wxMenuBar *CreateMenu();
	wxRect DeterminePrintSize();
	void DoRunMacros(int idx);
	
private:
	// edit object
	DirPane *m_dirtree;
	wxFileSystemWatcher *m_watcher;
	wxAuiManager m_mgr;
	wxAuiNotebook *m_notebook;
	long m_notebook_style;
	long m_notebook_theme;
	Macroses *m_macroses;
	
	wxDECLARE_EVENT_TABLE();
};

