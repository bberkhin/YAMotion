#include "wx/wx.h"
#include "editorpanel.h"
#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "flatbuttom.h"

wxBEGIN_EVENT_TABLE(EditorPanel, wxPanel)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(EditorPanel, wxPanel);

EditorPanel::EditorPanel(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	wxPanel(parent)
{
	long style = GetWindowStyle();
	SetWindowStyle(style | wxBORDER_NONE);

	m_pedit = new Edit(this, wxID_ANY);
	if (isnew)
		m_pedit->NewFile(filetype, filename);
	else
		m_pedit->LoadFile(filename);


	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->Add(pHeader, 0, wxEXPAND);
	totalpane->Add(m_pedit, wxEXPAND, wxEXPAND); //wxEXPAND
	
	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}

wxBoxSizer *EditorPanel::CreateHeaderPanel()
{
	//wxPanel *pHeader = new wxPanel(this);
	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);
	
	wxString label;
	switch (m_pedit->GetFileType())
	{
	case FILETYPE_NC:	label = _("GCODE"); break;
	case FILETYPE_GCMC:	label = _("GCMC"); break;
	case FILETYPE_JSON: label = _("JSON"); break;
	}
	if ( !label.empty() )
	{
		wxStaticText *txt = new wxStaticText(this, wxID_ANY, label);
		totalpane->Add(txt, 1, wxALIGN_CENTRE_VERTICAL);// wxEXPAND);
	}

	FlatButtom *padd = new FlatButtom(this, 100, _("3D VIEW"));// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT); //wxBORDER_NONE
	//wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	//padd->SetBitmap(bmp, wxRIGHT);
	totalpane->Add(padd, 0, wxRIGHT);

	FlatButtom *padd1 = new FlatButtom(this, 101, _("CHECK"));// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT); //wxBORDER_NONE
	//wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
	//padd1->SetBitmap(bmp1, wxRIGHT);
	totalpane->Add(padd1, 0,  wxRIGHT);
	return totalpane;
}


EditorPanel::~EditorPanel()
{
}



void EditorPanel::UpdateThemeColor()
{

	wxColor bgColor = Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_BACKGROUND_COLOUR);
	wxColor fgColor = Preferences::Get()->GetArtProvider()->GetColor(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR);

	SetBackgroundColour(bgColor);
	SetForegroundColour(fgColor);
	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);
		child->SetForegroundColour(fgColor);
		node = node->GetNext();
	}
}
