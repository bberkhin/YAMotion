#pragma once

//#include "appframe.h"
#include "wx/aui/aui.h"


enum DoAfterConvertGcmc
{
	ConvertGcmcNothing,
	ConvertGcmcOpenFile,
	ConvertGcmcPasteFile,
	ConvertGcmcRunSimilate
};

class Edit;
class wxSimpleHtmlListBox;
class wxToolBar;
class IntGCodeThread;
class SimulateGCodeThread;
class ViewGCode;
class LogWindow;
class MyGcmcProcess;
class DoMathBase;


//----------------------------------------------------------------------------
//! frame of the application APP_VENDOR-APP_NAME.
class AppFrame : public wxFrame {

	friend class IntGCodeThread;
	friend class SimulateGCodeThread;
	friend class GcmcProcess;

public:
	//! constructor
	AppFrame(const wxString &title);

	//! destructor
	~AppFrame();

	//! event handlers
	//! common	
	void OnTimer(wxTimerEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnAbout(wxCommandEvent &event);	
	void OnShowWelcome(wxCommandEvent &event);
	void OnDownloadUpdate(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnTimerEvent(wxTimerEvent &event);
	//! file
	void OnFileNew(wxCommandEvent &event);
	void OnFileOpen(wxCommandEvent &event);
	void OnFileOpenEvent(wxCommandEvent &event);
	void OnFileSave(wxCommandEvent &event);
	void OnFileSaveAs(wxCommandEvent &event);
	void OnFileClose(wxCommandEvent &event);
	void OnOpenLastFile(wxCommandEvent &event);
	//! dialogs
	void OnProperties(wxCommandEvent &event);
	void OnMacroses(wxCommandEvent &event);
	void OnMathCalc(wxCommandEvent &event);
	void OnMathExpression(wxCommandEvent &event);
	//! edit events
	void OnEdit(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent& evt);
	//! 3DViewevents
	void On3DView(wxCommandEvent &event);
	void On3DViewUpdate(wxUpdateUIEvent& event);
	//Gcode
	void OnCheck(wxCommandEvent &event);
	void OnSimulate(wxCommandEvent &event);
	void OnConvertGcmc(wxCommandEvent &event);
	void OnUpdateCheck(wxUpdateUIEvent& event);
	void OnUpdateSimulate(wxUpdateUIEvent& event);
	void OnUpdateConvertGcmc(wxUpdateUIEvent& event);
	void OnKillGcmcProcess(wxCommandEvent &event);
	void OnUpdateKillGcmcProcess(wxUpdateUIEvent& event);


	void OnThreadUpdate(wxThreadEvent&);
	void OnThreadCompletion(wxThreadEvent&);
	void OnSimulateUpdate(wxThreadEvent&);
	void OnSimulateCompletion(wxThreadEvent&);

	void OnNotebookPageClose(wxAuiNotebookEvent& evt);
	void OnFileChanged(wxCommandEvent& event);


	LogWindow *getLogWnd() { return m_logwnd; }
	wxString GetText();
	void UpdateTitle();
private:
	bool CheckNewName(const wxString &new_file_name);
	wxString GetSavedFileName();
	bool DoSaveAllFiles();
	bool DoFileSave(bool askToSave, bool bSaveAs, Edit *pedit = NULL);
	void FileChanged();
	void DoSimulate(const wchar_t *fname);
	int DoConvertGcmc(DoAfterConvertGcmc what_to_do);
	int RunGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, DoAfterConvertGcmc what_to_do);
	bool CheckFileExist(const wchar_t *fname);
	void AppendGcmcError(wxString &src);
	void GcmcProcessTerminated(int status, const wchar_t *dst_fname, DoAfterConvertGcmc what_to_do);
	void DoMathCalc(DoMathBase &mth);
	void ShowWelcome();
	void HideWelcome();
	wxAuiNotebook* CreateNotebook();
	wxAuiToolBar *CreateToolBar();
	ViewGCode* CreateGLView();
	Edit *GetActiveFile();
private:
	// edit object
	LogWindow *m_logwnd;
	ViewGCode *m_view;
	wxTimer m_timer;

	IntGCodeThread *checkThread;
	SimulateGCodeThread *simulateThread;
	wxCriticalSection critsect;
	GcmcProcess *gcmcProcess;
	unsigned int m_gcmc_running_in_sec;

	void FileOpen(wxString fname);
	

	//! creates the application menu bar
	wxMenuBar *CreateMenu();

	// print preview position and size
	wxRect DeterminePrintSize();
	//AUI
	wxAuiManager m_mgr;
	wxAuiNotebook *m_notebook;
	long m_notebook_style;
	long m_notebook_theme;


	wxDECLARE_EVENT_TABLE();
};

