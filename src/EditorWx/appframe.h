#pragma once

#include "appframe.h"

class Edit;
class wxSimpleHtmlListBox;
class wxToolBar;
class IntGCodeThread;
class SimulateGCodeThread;
class ViewGCode;

// declare a new type of event, to be used by our MyThread class:
//wxDECLARE_EVENT(wxEVT_COMMAND_GCODETHREAD_COMPLETED, wxThreadEvent);
//wxDECLARE_EVENT(wxEVT_COMMAND_GCODETHREAD_UPDATE, wxThreadEvent);

//----------------------------------------------------------------------------
//! frame of the application APP_VENDOR-APP_NAME.
class AppFrame : public wxFrame {

	friend class IntGCodeThread;
	friend class SimulateGCodeThread;

public:
	//! constructor
	AppFrame(const wxString &title);

	//! destructor
	~AppFrame();

	//! event handlers
	//! common
	void OnClose(wxCloseEvent &event);
	void OnAbout(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnTimerEvent(wxTimerEvent &event);
	//! file
	void OnFileNew(wxCommandEvent &event);
	void OnFileNewFrame(wxCommandEvent &event);
	void OnFileOpen(wxCommandEvent &event);
	void OnFileOpenFrame(wxCommandEvent &event);
	void OnFileSave(wxCommandEvent &event);
	void OnFileSaveAs(wxCommandEvent &event);
	void OnFileClose(wxCommandEvent &event);
	//! properties
	void OnProperties(wxCommandEvent &event);
	//! edit events
	void OnEdit(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent& evt);
	//! 3DViewevents
	void On3DView(wxCommandEvent &event);
	//Gcode
	void OnCheck(wxCommandEvent &event);
	void OnSimulate(wxCommandEvent &event);
	void OnUpdateCheck(wxUpdateUIEvent& event);
	void OnUpdateSimulate(wxUpdateUIEvent& event);

	void OnThreadUpdate(wxThreadEvent&);
	void OnThreadCompletion(wxThreadEvent&);
	void OnSimulateUpdate(wxThreadEvent&);
	void OnSimulateCompletion(wxThreadEvent&);


	wxSimpleHtmlListBox *getLogWnd() { return m_hlbox; }
	wxString GetText();
private:
	wxString GetSavedFileName();
	bool DoFileSave(bool askToSave, bool bSaveAs);
private:
	// edit object
	Edit *m_edit;
	wxSimpleHtmlListBox *m_hlbox;
	ViewGCode *m_view;

	IntGCodeThread *checkThread;
	SimulateGCodeThread *simulateThread;
	wxCriticalSection critsect;

	void FileOpen(wxString fname);
	void UpdateTitle();

	//! creates the application menu bar
	wxMenuBar *m_menuBar;
	void CreateMenu();
	wxToolBar *CreateToolBar();

	// print preview position and size
	wxRect DeterminePrintSize();

	wxDECLARE_EVENT_TABLE();
};

