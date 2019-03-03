#pragma once
#include "macroses.h"

class MacrosParamDlg :	public wxDialog
{
public:
	MacrosParamDlg(MacrosDesc *pm, wxWindow *parent);
	~MacrosParamDlg(); 
	virtual int ShowModal();
private:
	MacrosDesc *mdesc;
};

