#include "wx/wx.h"
#include "wx/html/htmlproc.h"
#include "wx/html/m_templ.h"
//#include <wx/statline.h>
#include "flatstaticline.h"

#include "appdefs.h"
#include "welcomewnd.h"
#include "standartpaths.h"
#include "configdata.h"
#include "app.h"
#include "prefs.h"
#include "defsext.h"
#include "flatbuttom.h"

#define WELCOME_MARGIN 10
#define MARGIN_TOP 20
#define MARGIN_BOTTOM 8
#define MARGIN_LEFT_RIGHT 20

class FooterCell : public wxHtmlContainerCell
{
	
public:
	FooterCell(wxHtmlContainerCell *parent, int height);
	virtual ~FooterCell() { }
	//virtual ~wxHtmlListCell();
	virtual void Layout(int w) wxOVERRIDE;
	virtual void Draw(wxDC& WXUNUSED(dc),
		int WXUNUSED(x), int WXUNUSED(y),
		int WXUNUSED(view_y1), int WXUNUSED(view_y2),
		wxHtmlRenderingInfo& WXUNUSED(info));
	void CalcHeight(int height) { m_calcHeight = height;  }
private:
	int m_calcHeight;
	wxDECLARE_NO_COPY_CLASS(FooterCell);
	
};


FooterCell::FooterCell(wxHtmlContainerCell *p, int height ) : wxHtmlContainerCell(p)
{
	m_calcHeight = 0;
}

void FooterCell::Layout(int w)  
{
	int h = GetParent()->GetHeight();
	wxHtmlContainerCell::Layout(w);	
	m_Height = m_calcHeight; //windowH - h;
	SetPos(0, 0);
	if (m_Cells)
	{
		for (wxHtmlCell *cell = m_Cells; cell; cell = cell->GetNext())
			cell->SetPos(cell->GetPosX(), m_Height - cell->GetHeight());
	}
}

void FooterCell::Draw(wxDC &dc, int x, int y,int view_y1, int view_y2, wxHtmlRenderingInfo &info) 
{
#if 1 // useful for debugging
	dc.SetPen(*wxBLACK_PEN);
	dc.DrawRectangle(x + m_PosX, y + m_PosY, m_Width /* VZ: +1? */, m_Height);
#endif

	wxHtmlContainerCell::Draw(dc, x, y, view_y1, view_y2, info);
}




TAG_HANDLER_BEGIN(FOOTER, "FOOTER")
TAG_HANDLER_PROC(tag)
{
	int ah;

	tag.ScanParam("Height", "%i", &ah);
	wxHtmlContainerCell *c;
	m_WParser->CloseContainer();
	c = m_WParser->OpenContainer();
	m_WParser->SetContainer(new FooterCell(c,ah));
	ParseInner(tag);
	m_WParser->CloseContainer();
	m_WParser->OpenContainer();
	
	return false;
}

TAG_HANDLER_END(MYBIND)



TAGS_MODULE_BEGIN(Footer)

TAGS_MODULE_ADD(FOOTER)

TAGS_MODULE_END(Footer)




class WelcomProcessor : public wxHtmlProcessor
{
public:
	virtual wxString Process(const wxString& s) const wxOVERRIDE
	{
		wxString r(s);
		// set version info
		r.Replace("<verinfo>", APP_VERSION);
		wxString updateString;
		if (wxGetApp().GetUptadeInfo(updateString))
		{
			r.Replace("<updateinfo>", updateString);
			r.Replace("<download>", _("<a href = \"cmd:6005\">Download update</a>"));
		}

		ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
		if (config)
		{
			const FileNamesList &files = config->GetFiles();
			if (!files.empty())
			{
				wxString table(_("<table>")); //<tr><td>File Name</td><td>Date</td></tr>
				int n = 0;
				std::for_each(files.begin(), files.end(),
					[&table, &n](const wxFileName &p) {
					//table += wxString::Format("<tr><td><a href=\"gcode:%d\">%s</a></td><td>%s</td></tr>", n, p, _("Today")); n++; });
					table += wxString::Format("<tr><td><a href=\"gcode:%d\">%s</a></td></tr>", n, p.GetFullName()); n++; });

				table += ("</table>");
				r.Replace("<lastfiles>", table);
			}
		}
		return r;
	}
};



WelcomeWndHtml::WelcomeWndHtml(wxWindow *parent) : wxHtmlWindow()
{
	// tempoary create own frame
	long style = GetWindowStyle();
	SetWindowStyle(style | wxBORDER_NONE );
	pWelcomeFrame = new wxFrame(parent, wxID_ANY, _("Welcome Wnd"));
	Create(pWelcomeFrame);
	SetRelatedFrame(pWelcomeFrame, _("Welcome Wnd1"));
	pWelcomeFrame->Layout();

	WelcomProcessor *processor = new WelcomProcessor;
	processor->Enable(true);
	ReadCustomization(wxConfig::Get());
	AddProcessor(processor);
	SetHomePage();
}

WelcomeWndHtml::~WelcomeWndHtml()
{
}

FooterCell *FindFooter(wxHtmlContainerCell *Cell)
{

	FooterCell *fc = dynamic_cast<FooterCell *>(Cell);
	if (fc)
		return fc;

	if (!Cell)
		return 0;

	for (wxHtmlCell *cell = Cell->GetFirstChild() ; cell; cell = cell->GetNext())
	{
		wxHtmlContainerCell *c = dynamic_cast<wxHtmlContainerCell *>(cell);
		if (!c)
			continue;
		fc = FindFooter(c);
		if (fc)
			return fc;
	}
	return 0;
}

void WelcomeWndHtml::SetHomePage()
{
	wxString path_name = StandartPaths::Get()->GetResourcesPath(L"welcome.htm").c_str();
	LoadFile(path_name);
	UpdateFooter();
	
}


void WelcomeWndHtml::ShowWelcome(bool bShow)
{
	pWelcomeFrame->Show(bShow);
}



wxBEGIN_EVENT_TABLE(WelcomeWndHtml, wxHtmlWindow)
//EVT_ERASE_BACKGROUND(WelcomeWnd::OnEraseBgEvent)
EVT_HTML_LINK_CLICKED(wxID_ANY, WelcomeWndHtml::OnHtmlLinkClicked)
EVT_SIZE(WelcomeWndHtml::OnSize)
wxEND_EVENT_TABLE()

//EVT_HTML_LINK_CLICKED(wxID_ANY, MyFrame::OnHtmlLinkClicked)


void WelcomeWndHtml::RunCommand(const wxString &url, int baseCmd)
{
	long n = 0;
	if (url.After(':').ToLong(&n))
	{
		wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, baseCmd + n);
		ev->SetClientData(this);
		wxQueueEvent(pWelcomeFrame->GetParent(), ev);
	}
}
void WelcomeWndHtml::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
{
	// skipping this event the default behaviour (load the clicked URL)
	// will happen...

	const wxString &url = event.GetLinkInfo().GetHref();
	//wxMessageBox(url);
	wxString cmdType = url.BeforeFirst(':');
	if (cmdType == "gcode")
	{
		RunCommand(url,wxID_FILE);
		SetHomePage(); // need to reload last file table	
	}
	else if (cmdType == "cmd")
	{
		RunCommand(url,0);
	}
	else
		event.Skip();
}

void WelcomeWndHtml::UpdateFooter()
{
	FooterCell *fc = FindFooter(m_Cell);
	if (!fc)
		return;
	wxHtmlContainerCell *Cell = fc->GetParent();
	int h = 0;
	for (wxHtmlCell *cell = Cell->GetFirstChild(); cell; cell = cell->GetNext())
	{
		if (fc == cell)
			continue;
		int hc = cell->GetHeight();
		if (hc > h) h = hc;
	}
	wxSize cs = GetSize();
	fc->CalcHeight(cs.y - h);
	m_Cell->Layout(cs.x);
}

void WelcomeWndHtml::OnSize(wxSizeEvent& event)
{
	wxHtmlWindow::OnSize(event);
	UpdateFooter();
	event.Skip();
}





wxIMPLEMENT_ABSTRACT_CLASS(WelcomeWnd, wxPanel);

wxBEGIN_EVENT_TABLE(WelcomeWnd, wxPanel)
//EVT_BUTTON(ID_TO3DBUTTON, EditorPanel::OnTo3DButton)
EVT_SIZE(WelcomeWnd::OnSize)
wxEND_EVENT_TABLE()



WelcomeWnd::WelcomeWnd(wxWindow *parent) : wxPanel(parent)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	const CommonInfo &common_prefs = Preferences::Get()->Common();

	
	m_fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);
	m_fghColor = clrs->Get(ColourScheme::WINDOW_TEXT_HOVER);
	m_bgColor = clrs->Get(ColourScheme::WINDOW);
	m_bghColor = clrs->Get(ColourScheme::WINDOW_HOVER); //wxColor(0x4d4d4d); 


	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	//Top Margin
	totalpane->AddSpacer(MARGIN_TOP);	
	// Header
	wxStaticText *ptxt = new wxStaticText(this, wxID_ANY, APP_NAME );
	ptxt->SetForegroundColour(m_fgColor);
	ptxt->SetFont(wxFontInfo(28).Bold());
	wxBoxSizer *phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(ptxt, 0, wxEXPAND);
	totalpane->Add(phor, 0, wxEXPAND);
	totalpane->AddSpacer(MARGIN_TOP);

	wxBoxSizer *panemain = new wxBoxSizer(wxHORIZONTAL);
	panemain->Add(CreateCommand(), 0, wxLEFT);
	panemain->AddSpacer(WELCOME_MARGIN);
	FlatStaticLine *pGripper = new FlatStaticLine(this,wxID_ANY,wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	
	panemain->Add(CreateRecentFilesList(), 0, wxEXPAND, wxBORDER);
	panemain->AddSpacer(WELCOME_MARGIN);
	pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	panemain->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 5);
	panemain->AddSpacer(WELCOME_MARGIN);
	panemain->Add(CreateDoc(), 0, wxRIGHT);


	phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(panemain, wxEXPAND, wxEXPAND);
	totalpane->Add(phor, wxEXPAND, wxEXPAND);
	
	phor = new wxBoxSizer(wxHORIZONTAL);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	phor->Add(CreateFooter(), wxEXPAND, wxEXPAND);
	phor->AddSpacer(MARGIN_LEFT_RIGHT);
	totalpane->Add(phor, 0, wxEXPAND);
	totalpane->AddSpacer(MARGIN_BOTTOM);
	
	UpdateThemeColor();
	SetSizerAndFit(totalpane);
}


void WelcomeWnd::OnSize(wxSizeEvent& event)
{
	Layout();
	Refresh(); 
}

void WelcomeWnd::UpdateThemeColor()
{

	SetBackgroundColour(m_bgColor);
	SetForegroundColour(m_fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(m_bgColor);
		//child->SetForegroundColour(m_fgColor);
		node = node->GetNext();
	}
	
}

void WelcomeWnd::AddColumnHeader(wxBoxSizer *pane, const wxString &text)
{
	wxStaticText *ph = new wxStaticText(this, wxID_ANY, text);
	ph->SetFont(wxFontInfo(10).Bold()); 
	ph->SetForegroundColour(m_fgColor);
	pane->Add(ph, 0, 0); 
	pane->AddSpacer(WELCOME_MARGIN );
}

void WelcomeWnd::AddCommand(wxBoxSizer *pane, const wxString &text, int cmd, bool footer)
{
	//wxStaticText *ph = new wxStaticText(this, cmd, text);	
	FlatButton *ph = new FlatButton(this, cmd, text, footer ? (FB_BITMAP_LEFT | FB_LABEL_LEFT) : (FB_BITMAP_RIGHT | FB_LABEL_LEFT));
	ph->SetForegroundColour(m_fgColor);
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	wxColor fgColor = m_fgColor;
	wxColor fghColor = m_fghColor;
	if (footer)
	{
		ColourScheme *clrs = Preferences::Get()->GetColorScheme();
		fgColor = clrs->Get(ColourScheme::CONTROL_TEXT);
		fghColor = clrs->Get(ColourScheme::CONTROL_TEXT_HOVER);
	}
	ph->SetColour(FlatButton::ForegroundColour, fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, fghColor);

	wxArtID idArt;
	switch (cmd)
	{
		case ID_OPENFILE:		idArt = wxART_FILE_OPEN; break;
		case ID_NEWNC:
		case ID_NEWGCMC:		idArt = wxART_NEW; break;
		case ID_GLOBALPREFS:	idArt = ART_PREFERENCES; break;
		case ID_DOWNLOADUPDATE:	idArt = ART_UPDATE; break;
	}

	wxBitmap bmp = wxArtProvider::GetBitmap(idArt, wxART_MENU);
	wxBitmap bmphover = wxArtProvider::GetBitmap(idArt, ART_MENUHOVER);

	if (footer)
	{
		ph->SetBitmap(bmp, bmphover, 3);
		pane->Add(ph, 0, wxALIGN_CENTER_VERTICAL);//wxALIGN_BOTTOM);
	}
	else
	{
		ph->SetBitmap(bmp, bmphover, 30);
		pane->Add(ph, 0, wxEXPAND);
	}
}

void WelcomeWnd::AddRecentFile(wxBoxSizer *pane, const wxFileName &p, int n)
{	
	int cmd = wxID_FILE + n;
	FlatButton *ph = new FlatButton(this,100+n, p.GetFullName(), FB_BITMAP_LEFT);
	ph->SetForegroundColour(m_fgColor);
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_NEW, wxART_LIST);
	ph->SetBitmap(bmp, 10 );
	ph->SetToolTip(p.GetFullPath() );
	pane->Add(ph, 0, wxEXPAND);
}

wxBoxSizer *WelcomeWnd::CreateCommand()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Files"));
	AddCommand(pane, _("Open"), ID_OPENFILE);
	pane->AddSpacer(WELCOME_MARGIN/2);
	AddCommand(pane, _("New GCODE"), ID_NEWNC );
	AddCommand(pane, _("New GCMC"), ID_NEWGCMC);
	return pane;
}


void WelcomeWnd::AddHelpLink(wxBoxSizer *pane, const wxString &text, int cmd )
{
	//wxStaticText *ph = new wxStaticText(this, cmd, text);
	FlatButton *ph = new FlatButton(this, cmd, text, FB_LABEL_LEFT);
	ph->SetForegroundColour(m_fgColor);
	ph->SetCommand(cmd);
	ph->SetFont(wxFontInfo(10));
	ph->SetColour(FlatButton::BackgroundColour, m_bgColor);	
	ph->SetColour(FlatButton::HoverBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::PressBackgroundColour, m_bghColor);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fghColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fghColor);

	ph->UpdateSize();
	pane->Add(ph, 0, wxEXPAND);

}


wxBoxSizer *WelcomeWnd::CreateDoc()
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Help"));
	AddHelpLink(pane, _("Use GCMC to write easy"), ID_HELPGCMC);
	AddHelpLink(pane, _("Use GCode directly"), ID_HELPNC);
	AddHelpLink(pane, _("Whats News"), ID_WHATNEWS);
	return pane;
}

wxBoxSizer *WelcomeWnd::CreateRecentFilesList( )
{
	wxBoxSizer *pane = new wxBoxSizer(wxVERTICAL);
	AddColumnHeader(pane, _("Recent Files"));
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	if (config)
	{
		const FileNamesList &files = config->GetFiles();
		if (!files.empty())
		{
			int n = 0;
			WelcomeWnd *parent = this;
			std::for_each(files.begin(), files.end(),
				[&pane, &n, parent](const wxFileName &p) {
				parent->AddRecentFile(pane, p, n++);
				});
		}
	}
	return pane;
}


wxBoxSizer *WelcomeWnd::CreateFooter()
{

	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

	wxBoxSizer *pane = new wxBoxSizer(wxHORIZONTAL);
	pane->AddSpacer(WELCOME_MARGIN);
	wxString ver = APP_VERSION;
	ver += L" ";
	ver += APP_COPYRIGTH;

	wxBoxSizer *paneCmd = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *pTxt = new wxStaticText(this, wxID_ANY, ver);
	pTxt->SetFont(wxFontInfo(10));
	pTxt->SetForegroundColour(clrs->Get(ColourScheme::WINDOW_TEXT_DISABLE) );
	
	//pane->Add(pTxt , 0, wxALIGN_BOTTOM);
	paneCmd->Add(pTxt, 0, wxALIGN_CENTER_VERTICAL);
	paneCmd->AddSpacer(WELCOME_MARGIN);
	
	//AddCommand(pane, _("Preference"), ID_GLOBALPREFS, true);
	AddCommand(paneCmd, _("Preference"), ID_GLOBALPREFS, true);

	//pane->Add(new wxStaticText(this, wxID_ANY, ), 0, wxALIGN_BOTTOM);
	paneCmd->AddSpacer(WELCOME_MARGIN);
	//AddCommand(pane, _("Check for Update"), ID_DOWNLOADUPDATE, true);
	AddCommand(paneCmd, _("Check for Update"), ID_DOWNLOADUPDATE, true);
	pane->Add( paneCmd, 0, wxALIGN_BOTTOM);
	pane->AddStretchSpacer();
	wxBoxSizer *pane1 = new wxBoxSizer(wxVERTICAL);

	pTxt = new wxStaticText(this, wxID_ANY, _("Help us become better."));
	pTxt->SetForegroundColour(m_fgColor);
	pTxt->SetFont(wxFontInfo(10).Bold());
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);
	
	pTxt = new wxStaticText(this, wxID_ANY, _(" Tell us what you liked or what you lack in our application"));
	pTxt->SetFont(wxFontInfo(10));
	pTxt->SetForegroundColour(m_fgColor);
	pane1->Add(pTxt, 0, wxALIGN_CENTER_HORIZONTAL);

	FlatButton *ph = new FlatButton(this, wxID_ANY, _("WRITE TO US"), FB_LABEL_CENTER);
	ph->SetForegroundColour(m_fgColor);
	ph->SetCommand(ID_WRITEFEEDBACK);
	ph->SetFont(wxFontInfo(11).Bold() );
	ph->SetMargins(-1, 8);

	

	wxBitmap bmp = wxArtProvider::GetBitmap(ART_MAIL, wxART_OTHER);
	ph->SetBitmap(bmp, 2);
	
	wxColor clrbg = clrs->Get(ColourScheme::BUTTON_FEEDBACK);// ("#cc8830");
	wxColor clrbghv = clrs->Get(ColourScheme::BUTTON_FEEDBACK_HOVER);//("#bb6600");

	ph->SetColour(FlatButton::BackgroundColour, clrbg);
	ph->SetColour(FlatButton::HoverBackgroundColour, clrbghv);
	ph->SetColour(FlatButton::PressBackgroundColour, clrbghv);
	ph->SetColour(FlatButton::ForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::HoverForegroundColour, m_fgColor);
	ph->SetColour(FlatButton::PressForegroundColour, m_fgColor);

	pane1->Add(ph, 0, wxEXPAND );
	pane->Add(pane1, 0, wxRIGHT | wxALIGN_BOTTOM);
	return pane;
}

WelcomeWnd::~WelcomeWnd()
{

}

void WelcomeWnd::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
{

}

