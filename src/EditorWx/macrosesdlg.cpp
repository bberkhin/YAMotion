//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1

#include "wx/wx.h"
#include "macrosesdlg.h"


MacrosesDlg::MacrosesDlg(Macroses *pm,wxWindow *parent)
	: msc(pm), selection(-1), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		 wxDEFAULT_DIALOG_STYLE )//| wxRESIZE_BORDER) 
{

	// sets the application title
	SetTitle(_("Macroses List"));
	wxString text;

	
	list = new wxListBox(this, wxID_ANY);

	wxStaticBoxSizer *textinfos = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _("Select from the list:")),	wxHORIZONTAL);
	
	textinfos->Add(list, 0, 0); //wxEXPAND
	textinfos->Add(0, 6);
	ptext = new wxStaticText(this, wxID_ANY, "Just to define place fo this we need vore space ");
	textinfos->Add(ptext, 0, 0);
	textinfos->Add(0, 6);

	// buttons
	//wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	/*wxButton* bt;
	wxStdDialogButtonSizer *buttonSizer = CreateStdDialogButtonSizer(wxOK | wxCANCEL);
	bt = new wxButton(this, wxID_OK, "Ok");
	buttonSizer->AddButton(bt);
	bt = new wxButton(this, wxID_CANCEL, "Cancel");
	buttonSizer->AddButton(bt);*/
	
	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(textinfos, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);
	
	InitList();
	
	SetSizerAndFit(totalpane);
	if (ShowModal() == wxID_OK)
		selection = list->GetSelection();

}

MacrosesDlg::~MacrosesDlg()
{
}

wxBEGIN_EVENT_TABLE(MacrosesDlg, wxDialog)

EVT_LISTBOX(wxID_ANY, MacrosesDlg::OnLboxSelect)
EVT_LISTBOX_DCLICK(wxID_ANY, MacrosesDlg::OnLboxDClick)

wxEND_EVENT_TABLE()

void MacrosesDlg::InitList()
{
	
	wxArrayString arrays;

	int pos = 0;
	for (int i = 0; i < msc->count(); i++)
	{
		arrays.Add(msc->get(i).name);
	}
	if ( arrays.Count() )
	{
		list->InsertItems(arrays, 0);
		list->SetSelection(0);
	}
}

void MacrosesDlg::OnLboxSelect(wxCommandEvent& event)
{
	selection = list->GetSelection();
	ptext->SetLabel( msc->get(selection).desc.c_str() );
}

void MacrosesDlg::OnLboxDClick(wxCommandEvent& event)
{
	selection = list->GetSelection();
	EndModal(wxID_OK);
}