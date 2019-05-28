#pragma once
#include "macroses.h"

class MacrosParamDlg :	public wxDialog
{
public:
	MacrosParamDlg(MacrosDesc *pm, wxWindow *parent, bool new_window = true);
	~MacrosParamDlg(); 
	virtual int ShowModal();
	bool IsInNewWindow() { return m_new_window; }
private:
	MacrosDesc *mdesc;
	bool m_new_window;
};

