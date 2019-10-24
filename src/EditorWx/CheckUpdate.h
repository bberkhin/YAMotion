#pragma once
class CheckUpdateDlg  : public wxDialog
{
public:
	CheckUpdateDlg(wxWindow *parent);
	~CheckUpdateDlg();
private:
	wxDECLARE_EVENT_TABLE();
};

bool DoCheckUpdate(wxString &desc, wxString &verName, int *err);

