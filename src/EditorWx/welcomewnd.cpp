#include "wx/wx.h"
#include "wx/html/htmlproc.h"
#include "wx/html/m_templ.h"

#include "appdefs.h"
#include "welcomewnd.h"
#include "standartpaths.h"
#include "configdata.h"
#include "app.h"



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



WelcomeWnd::WelcomeWnd(wxWindow *parent) : wxHtmlWindow()
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

WelcomeWnd::~WelcomeWnd()
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

void WelcomeWnd::SetHomePage()
{
	wxString path_name = StandartPaths::Get()->GetResourcesPath(L"welcome.htm").c_str();
	LoadFile(path_name);
	UpdateFooter();
	
}


void WelcomeWnd::ShowWelcome(bool bShow)
{
	pWelcomeFrame->Show(bShow);
}



wxBEGIN_EVENT_TABLE(WelcomeWnd, wxHtmlWindow)
//EVT_ERASE_BACKGROUND(WelcomeWnd::OnEraseBgEvent)
EVT_HTML_LINK_CLICKED(wxID_ANY, WelcomeWnd::OnHtmlLinkClicked)
EVT_SIZE(WelcomeWnd::OnSize)
wxEND_EVENT_TABLE()

//EVT_HTML_LINK_CLICKED(wxID_ANY, MyFrame::OnHtmlLinkClicked)


void WelcomeWnd::RunCommand(const wxString &url, int baseCmd)
{
	long n = 0;
	if (url.After(':').ToLong(&n))
	{
		wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU, baseCmd + n);
		ev->SetClientData(this);
		wxQueueEvent(pWelcomeFrame->GetParent(), ev);
	}
}
void WelcomeWnd::OnHtmlLinkClicked(wxHtmlLinkEvent &event)
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

void WelcomeWnd::UpdateFooter()
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

void WelcomeWnd::OnSize(wxSizeEvent& event)
{
	wxHtmlWindow::OnSize(event);
	UpdateFooter();
	event.Skip();
}




