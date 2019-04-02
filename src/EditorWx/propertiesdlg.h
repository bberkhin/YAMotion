#pragma once

//----------------------------------------------------------------------------
//! PropertiesDlg


class PropertiesDlg : public wxDialog
{

public:
	//! constructor
	PropertiesDlg(wxWindow *parent);
	void InitLangList();
	int ShowModal();
	bool NeedRestart() { return need_restart; }
private:
	wxListBox *langlist;
	bool need_restart;
};