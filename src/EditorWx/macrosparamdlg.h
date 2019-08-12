#pragma once
#include "macroses.h"

class MacrosParamDlg :	public wxDialog
{
public:
	MacrosParamDlg(MacrosDesc *pm, wxWindow *parent, int curfiletype );
	~MacrosParamDlg(); 
	bool IsInNewWindow() { return m_new_window; }
	bool IsInGCMC() { return m_as_gcmc; }
private:
	void OnOk(wxCommandEvent& event);
	bool GetAndValidateInput();
	void UpdateThemeColor();
private:
	MacrosDesc *mdesc;
	static bool m_new_window;
	static bool m_as_gcmc;
	int m_curfiletype;
	wxDECLARE_EVENT_TABLE();
};

