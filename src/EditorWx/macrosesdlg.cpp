//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1

#include "wx/wx.h"
#include "macrosesdlg.h"
#include "standartpaths.h"

MacrosesDlg::MacrosesDlg(Macroses *pm,wxWindow *parent)
	: msc(pm), selection(-1), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		 wxDEFAULT_DIALOG_STYLE )//| wxRESIZE_BORDER) 
{

	// sets the application title
	SetTitle(_("Macroses List"));
	wxString text;

	
	wxArrayString arrays;
	for (int i = 0; i < msc->Count(); i++)
	{
		arrays.Add(msc->Get(i).name);
	}

	m_list = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		arrays, wxNO_BORDER);

	wxStaticBoxSizer *textinfos = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _("Select the macros:")), wxHORIZONTAL);
	
	textinfos->Add(m_list, wxEXPAND, wxEXPAND); //wxEXPAND


	wxBoxSizer *rightColumn = new wxBoxSizer(wxVERTICAL);
	
	rightColumn->AddSpacer(10);
	m_text = new wxStaticText(this, wxID_ANY, L"Just to define place for this we need vore space ");
	rightColumn->Add(m_text, 0, wxEXPAND);
	rightColumn->AddSpacer(5);

	
	wxBitmap bmp;
	m_bitmapCtrl  = new wxStaticBitmap(this, wxID_ANY, bmp, wxDefaultPosition, wxSize(512,512) );
	rightColumn->Add(m_bitmapCtrl);
	rightColumn->AddSpacer(5);
	wxBoxSizer *infoPane = new wxBoxSizer(wxHORIZONTAL);
	infoPane->Add(textinfos, wxEXPAND, wxEXPAND);
	infoPane->Add(rightColumn);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(infoPane, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);
	
	if (arrays.Count())
	{
		m_list->SetSelection(0);
		UpdateInfo(0);
	}
	
	SetSizerAndFit(totalpane);
	if (ShowModal() == wxID_OK)
		selection = m_list->GetSelection();
	else
		selection = -1;

}

MacrosesDlg::~MacrosesDlg()
{
}

wxBEGIN_EVENT_TABLE(MacrosesDlg, wxDialog)

EVT_LISTBOX(wxID_ANY, MacrosesDlg::OnLboxSelect)
EVT_LISTBOX_DCLICK(wxID_ANY, MacrosesDlg::OnLboxDClick)

wxEND_EVENT_TABLE()



void MacrosesDlg::OnLboxSelect(wxCommandEvent& event)
{
	selection = m_list->GetSelection();
	UpdateInfo(selection);
	
}
void MacrosesDlg::UpdateInfo(int sel)
{
	MacrosDesc &mdesc = msc->Get(sel);
	m_text->SetLabel(mdesc.desc.c_str());
	wxBitmap bmp;
	if (!mdesc.imgfile.empty())
	{
		// check in lang directory
		std::filesystem::path imagepath = StandartPaths::Get()->GetMacrosPath(mdesc.imgfile.c_str(), true);
		if (!std::filesystem::exists(imagepath))
			imagepath = StandartPaths::Get()->GetMacrosPath(mdesc.imgfile.c_str(), false);
		wxImage image;
		if (image.LoadFile(imagepath.c_str()))
		{
			bmp = image;
		}
	}
	m_bitmapCtrl->SetBitmap(bmp);
}

void MacrosesDlg::OnLboxDClick(wxCommandEvent& event)
{
	selection = m_list->GetSelection();
	EndModal(wxID_OK);
}