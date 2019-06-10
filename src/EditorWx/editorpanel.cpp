#include "wx/wx.h"
#include "editorpanel.h"
#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "flatbuttom.h"
#include "FlatScrollBar.h"
#include "defsext.h"

#define ID_TO3DBUTTON 100
#define ID_TOGCODEBUTTON 101
#define ID_CHECKBUTTON 102

wxBEGIN_EVENT_TABLE(EditorPanel, wxPanel)
EVT_BUTTON(ID_TO3DBUTTON, EditorPanel::OnTo3DButton)
EVT_BUTTON(ID_TOGCODEBUTTON, EditorPanel::OnToGcodeButton)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(EditorPanel, wxPanel);

EditorPanel::EditorPanel(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	wxPanel(parent)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	const CommonInfo &common_prefs = Preferences::Get()->Common();

    m_pedit = new Edit(this, wxID_ANY);

	if (isnew)
		m_pedit->NewFile(filetype, filename);
	else
		m_pedit->LoadFile(filename);

	FlatScrollBar *barv = new FlatScrollBar(this, m_pedit, wxID_ANY);
	FlatScrollBar *barh = 0;
	if (common_prefs.visibleHSB)
		barh = new FlatScrollBar(this, m_pedit, wxID_ANY, FlatScrollBar::typeHorisontal);

	m_pedit->SetVScrollBar(barv);
	m_pedit->SetHScrollBar(barh);

	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->Add(pHeader, 0, wxEXPAND);


	wxFlexGridSizer  *gd = new wxFlexGridSizer(2);// 2, 0, 0);
	gd->AddGrowableCol(0);
	gd->AddGrowableRow(0);
	gd->Add(m_pedit, wxEXPAND,  wxEXPAND );
	gd->Add(barv, 0, wxEXPAND);
	if ( barh )
		gd->Add(barh, 0, wxEXPAND);

	totalpane->Add(gd, wxEXPAND, wxEXPAND);

	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}

wxBoxSizer *EditorPanel::CreateHeaderPanel()
{
	//wxPanel *pHeader = new wxPanel(this);
	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);
	
	wxString label;
	int ftype = m_pedit->GetFileType();
	switch (ftype)
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


	if ((ftype == FILETYPE_NC) || (ftype == FILETYPE_GCMC) )
	{
	
		FlatButton *p3dViewBt = new FlatButton(this, ID_TO3DBUTTON, _("3D view"), ID_GCODE_SIMULATE);// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT );

		p3dViewBt->SetCustomColor(ColourScheme::CONTROL, ColourScheme::WINDOW);
		p3dViewBt->SetCustomColor(ColourScheme::CONTROL_HOVER, ColourScheme::FRAME);
		p3dViewBt->SetCustomColor(ColourScheme::CONTROL_PRESSED, ColourScheme::FRAME);

		wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
		//padd->SetWindowStyle(wxBORDER_NONE);
		p3dViewBt->SetBitmap(bmp);
		totalpane->Add(p3dViewBt, 0, wxRIGHT);
		totalpane->AddSpacer(10);

		FlatButton *pCheckBt = new FlatButton(this, ID_CHECKBUTTON, _("Check"), ID_GCODE_CHECK);// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT); //wxBORDER_NONE
		wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
		pCheckBt->SetBitmap(bmp1);
		pCheckBt->SetCustomColor(ColourScheme::CONTROL, ColourScheme::WINDOW);
		pCheckBt->SetCustomColor(ColourScheme::CONTROL_HOVER, ColourScheme::FRAME);
		pCheckBt->SetCustomColor(ColourScheme::CONTROL_PRESSED, ColourScheme::FRAME);	

		totalpane->Add(pCheckBt, 0,  wxRIGHT);
		totalpane->AddSpacer(10);
		if (ftype == FILETYPE_GCMC)
		{
			FlatButton *pConvertBt = new FlatButton(this, ID_CHECKBUTTON, _("Convert"), ID_GCODE_CONVERTGCMC);// , wxDefaultPosition, wxDefaultSize, wxBU_LEFT); //wxBORDER_NONE
			wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_HELP_BOOK, wxART_OTHER, FromDIP(wxSize(16, 16)));
			pConvertBt->SetBitmap(bmp1);
			pConvertBt->SetCustomColor(ColourScheme::CONTROL, ColourScheme::WINDOW);
			pConvertBt->SetCustomColor(ColourScheme::CONTROL_HOVER, ColourScheme::FRAME);
			pConvertBt->SetCustomColor(ColourScheme::CONTROL_PRESSED, ColourScheme::FRAME);

			totalpane->Add(pConvertBt, 0, wxRIGHT);
			totalpane->AddSpacer(10);
		}
	}

	return totalpane;
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

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);
		child->SetForegroundColour(fgColor);
		node = node->GetNext();
	}
}

void EditorPanel::OnTo3DButton(wxCommandEvent &ev)
{
}

void EditorPanel::OnToGcodeButton(wxCommandEvent& WXUNUSED(ev))
{
}
