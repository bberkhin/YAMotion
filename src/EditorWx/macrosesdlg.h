#pragma once
#include <wx/listbox.h>
#include "macroses.h"

class MacrosesDlg :	public wxDialog
{
public:
	MacrosesDlg(Macroses *pm, wxWindow *parent);
	~MacrosesDlg();
	int GetSelected() { return selection; }
	void InitList();

	void OnLboxSelect(wxCommandEvent& event);
	void OnLboxDClick(wxCommandEvent& event);

private:
	Macroses *msc;
	int selection;
	wxListBox *list;
	wxStaticText *ptext;
	
	wxDECLARE_EVENT_TABLE();
};

