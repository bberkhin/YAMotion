#include "wx/wx.h"
#include "propertiesdlg.h"
#include "app.h"
#include "configdata.h"

//----------------------------------------------------------------------------
// PropertiesDlg
//----------------------------------------------------------------------------


PropertiesDlg::PropertiesDlg(wxWindow *parent)
	: need_restart(false), wxDialog(parent, wxID_ANY, ("Properties"))
{

	//Select Lang
	langlist = new wxListBox(this, wxID_ANY);
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);

	totalpane->Add(new wxStaticBox(this, wxID_ANY, _("Select language:")) );

	totalpane->Add(langlist, 0, 0); //wxEXPAND
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);
	InitLangList();

	SetSizerAndFit(totalpane);

	ShowModal();
}

void PropertiesDlg::InitLangList()
{
	int n = g_lang_count;
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	int lan = config ? config->GetLanguage(-1) : -1;
	int select = 0;
	for (int i = 0; i < n; i++)
	{
		langlist->Append(g_langNames[i], (void *)(&(g_langIds[i])));
		if (g_langIds[i] == lan)
			select = i;
	}

	langlist->SetSelection(select);
}


int PropertiesDlg::ShowModal()
{	
	int ret = wxDialog::ShowModal();
	if (ret != wxID_OK)
		return ret;

	
	int select = langlist->GetSelection();
	if (select >= 0)
	{
		ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
		int lan = config ? config->GetLanguage(-1) : -1;
		wxLanguage *pl = static_cast<wxLanguage *>(langlist->GetClientData(select));
		if (*pl != lan)
		{
			need_restart = true;
			config->SetLanguage(*pl);
		}
			
	}
	if (need_restart &&  wxMessageBox(_("The changes you did, will applay after restarting the program. Would you like to restart?"),
		_("Properties changed"), wxOK | wxCANCEL | wxICON_QUESTION, this) == wxCANCEL)
		need_restart = false;

	return ret;
}