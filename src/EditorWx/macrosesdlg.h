#pragma once
#include <wx/listbox.h>
#include "macroses.h"

class MacrosesDlg : public wxDialog
{
public:
	MacrosesDlg(Macroses *pm, wxWindow *parent);
	~MacrosesDlg();
	int GetSelected() { return selection; }

	void OnLboxSelect(wxCommandEvent& event);
	void OnLboxDClick(wxCommandEvent& event);
	void UpdateInfo(int sel);
private:
	Macroses *msc;
	int selection;
	wxListBox *m_list;
	wxStaticText *m_text;
	wxStaticBitmap *m_bitmapCtrl;
	wxDECLARE_EVENT_TABLE();
};

