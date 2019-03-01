#pragma once
#include <wx/listbox.h>

class MacrosesDlg :	public wxDialog
{
public:
	MacrosesDlg(wxWindow *parent);
	~MacrosesDlg();
	void InitList(wxListBox *list);
private:
	bool GetMacrosNames(const wchar_t *path, wxArrayString &arr);
};

