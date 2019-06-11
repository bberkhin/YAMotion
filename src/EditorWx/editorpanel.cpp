#include "wx/wx.h"
#include "editorpanel.h"
#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "flatbuttom.h"
#include "FlatScrollBar.h"
#include "defsext.h"
#include "View3D.h"

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
	
		FlatButton *p3dViewBt = new FlatButton(this, ID_TO3DBUTTON, _("3D view"), ID_GCODE_SIMULATE, true);
		wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
		//padd->SetWindowStyle(wxBORDER_NONE);
		p3dViewBt->SetBitmap(bmp);
		totalpane->Add(p3dViewBt, 0, wxRIGHT);
		totalpane->AddSpacer(10);

		FlatButton *pCheckBt = new FlatButton(this, ID_CHECKBUTTON, _("Check"), ID_GCODE_CHECK, true);
		wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
		pCheckBt->SetBitmap(bmp1);

		totalpane->Add(pCheckBt, 0,  wxRIGHT);
		totalpane->AddSpacer(10);
		if (ftype == FILETYPE_GCMC)
		{
			FlatButton *pConvertBt = new FlatButton(this, ID_CHECKBUTTON, _("Convert"), ID_GCODE_CONVERTGCMC, true);
			wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_HELP_BOOK, wxART_OTHER, FromDIP(wxSize(16, 16)));
			pConvertBt->SetBitmap(bmp1);
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



wxBEGIN_EVENT_TABLE(View3DPanel, wxPanel)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(View3DPanel, wxPanel);

View3DPanel::View3DPanel(wxWindow *parent) :
	wxPanel(parent)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	const CommonInfo &common_prefs = Preferences::Get()->Common();

	m_pview = new View3D(this, wxID_ANY);
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->Add(pHeader, 0, wxEXPAND);
	totalpane->Add(m_pview, wxEXPAND, wxEXPAND);

	wxSizer *pFooter = CreateFooterPanel();
	totalpane->AddSpacer( FromDIP(10) );
	totalpane->Add(pFooter, 0, wxEXPAND);
	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}


View3DPanel::~View3DPanel()
{
}

void View3DPanel::UpdateThemeColor()
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


wxBoxSizer *View3DPanel::CreateHeaderPanel()
{
	//wxPanel *pHeader = new wxPanel(this);
	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *txt = new wxStaticText(this, wxID_ANY, _("3D View"));
	totalpane->Add(txt, 1, wxALIGN_CENTRE_VERTICAL);// wxEXPAND);

	FlatButton *p3dViewBt = new FlatButton(this, ID_TO3DBUTTON, _("Start"), ID_GCODE_SIMULATE, true);

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	//padd->SetWindowStyle(wxBORDER_NONE);
	p3dViewBt->SetBitmap(bmp);
	totalpane->Add(p3dViewBt, 0, wxRIGHT);
	totalpane->AddSpacer(10);

	FlatButton *pCheckBt = new FlatButton(this, ID_CHECKBUTTON, _("Stop"), ID_GCODE_CHECK, true);
	wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
	pCheckBt->SetBitmap(bmp1);
	
	totalpane->Add(pCheckBt, 0, wxRIGHT);
	totalpane->AddSpacer(10);
	return totalpane;
}

wxSizer *View3DPanel::CreateFooterPanel()
{
	// about info
	wxFlexGridSizer  *gd = new wxFlexGridSizer(4,wxSize(10,5));// 2, 0, 0);
	//gd->AddGrowableCol(0);
	//gd->AddGrowableCol(1);
	//gd->AddGrowableCol(2);
	//gd->AddGrowableCol(3);

	
	gd->Add(new wxStaticText(this, wxID_ANY, _("Width: ")),	0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, wxID_ANY, _("456mm ")), 0, wxALIGN_LEFT); // width val
	gd->Add(new wxStaticText(this, wxID_ANY, _("Height: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, wxID_ANY, _("116mm ")), 0, wxALIGN_LEFT); // height val
	gd->Add(new wxStaticText(this, wxID_ANY, _("Lenght: ")),0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("04040406mm ")),	0, wxALIGN_LEFT); // lenght val
	gd->Add(new wxStaticText(this, wxID_ANY, _("Path: ")),	0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, wxID_ANY, _("550406mm ")),0, wxALIGN_LEFT); // path val
	
	
	return gd;
}


wxBEGIN_EVENT_TABLE(FilePage, wxPanel)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(FilePage, wxPanel);


FilePage::FilePage(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	wxPanel(parent)
{
	

	m_editor = new EditorPanel(this, filetype, filename, isnew);

	wxGridSizer *totalpane;
	int ftype = m_editor->GetEdit()->GetFileType();
	if ((ftype == FILETYPE_NC) || (ftype == FILETYPE_GCMC))
	{
		totalpane = new wxGridSizer(2);
		totalpane->Add(m_editor, 0, wxEXPAND);
		m_view3d = new View3DPanel(this);
		totalpane->Add(m_view3d, 1, wxEXPAND);
	}
	else
	{
		totalpane = new wxGridSizer(1);
		totalpane->Add(m_editor, wxEXPAND, wxEXPAND);
	}

	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}

FilePage::~FilePage()
{

}

void FilePage::UpdateThemeColor()
{
}
