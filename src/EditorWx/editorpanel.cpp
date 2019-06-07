#include "wx/wx.h"
#include "editorpanel.h"
#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "flatbuttom.h"
#include "FlatScrollBar.h"

#define ID_TO3DBUTTON 100
#define ID_TOGCODEBUTTON 101

wxBEGIN_EVENT_TABLE(EditorPanel, wxPanel)
EVT_BUTTON(ID_TO3DBUTTON, EditorPanel::OnTo3DButton)
EVT_BUTTON(ID_TOGCODEBUTTON, EditorPanel::OnToGcodeButton)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(EditorPanel, wxPanel);

EditorPanel::EditorPanel(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	wxPanel(parent)
{
	long style = GetWindowStyle();
	SetWindowStyle(style | wxBORDER_NONE);

	m_pedit = new Edit(this, wxID_ANY);
	//wxScrollBar *bar = CreateScrollBar();
	//m_pedit->SetVScrollBar(bar);	
	FlatScrollBar *bar = new FlatScrollBar(this, wxID_ANY);

	if (isnew)
		m_pedit->NewFile(filetype, filename);
	else
		m_pedit->LoadFile(filename);


	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->Add(pHeader, 0, wxEXPAND);


	
	wxBoxSizer *paneEdit = new wxBoxSizer(wxHORIZONTAL);
	paneEdit->Add(m_pedit, wxEXPAND, wxEXPAND); //wxEXPAND
	paneEdit->Add(bar, 0, wxEXPAND);
	totalpane->Add(paneEdit, wxEXPAND, wxEXPAND); //wxEXPAND
	//totalpane->Add(m_pedit, wxEXPAND, wxEXPAND); //wxEXPAND	


	bar->SetScrollbar(2, 10, 100,  1);
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


	
	FlatButtom *padd = new FlatButtom(this, ID_TO3DBUTTON, _("3D VIEW"),true );// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT );
	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	padd->SetWindowStyle(wxBORDER_NONE);
	padd->SetBitmap(bmp);
	totalpane->Add(padd, 0, wxRIGHT);
	totalpane->AddSpacer(10);



	FlatButtom *padd1 = new FlatButtom(this, ID_TOGCODEBUTTON, _("CHECK"), true);// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT); //wxBORDER_NONE
	wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
	padd1->SetBitmap(bmp1);
	totalpane->Add(padd1, 0,  wxRIGHT);
	totalpane->AddSpacer(10);
	return totalpane;
}


wxScrollBar *EditorPanel::CreateScrollBar()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW);

	wxScrollBar *bar = new wxScrollBar(this, wxID_ANY, wxDefaultPosition,
			wxDefaultSize, wxSB_VERTICAL);
	bar->SetBackgroundColour(bgColor);
	return bar;

}

EditorPanel::~EditorPanel()
{
}



void EditorPanel::UpdateThemeColor()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW);
	wxColor fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);

	SetBackgroundColour(bgColor);
	SetForegroundColour(fgColor);
	//m_pedit->SetBackgroundColour(bgColor);
	//m_pedit->SetForegroundColour(fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);
		child->SetForegroundColour(fgColor);
		node = node->GetNext();
	}
}

void EditorPanel::OnTo3DButton(wxCommandEvent& WXUNUSED(ev))
{}

void EditorPanel::OnToGcodeButton(wxCommandEvent& WXUNUSED(ev))
{}
