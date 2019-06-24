#include "wx/wx.h"
#include "editorpanel.h"
#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "wx/splitter.h"
#include "flatbuttom.h"
#include "FlatScrollBar.h"
#include "defsext.h"
#include "View3D.h"
#include "edit.h"    
#include "logwindow.h"
#include "configdata.h"
#include "app.h"          //for upadte title :(
#include "appframe.h"     //for upadte title :(

#define MAX_BTN_PRIORITY 1101
enum
{
	ID_TO3DBUTTON = 100,
	ID_TOGCODEBUTTON,
	ID_CHECKBUTTON,
	ID_CLOSEOUTPUT,
	ID_CLOSE3DVIEW,
	ID_BTN_TOP,
	ID_BTN_ISOMETRIC,
	ID_BTN_BOTTOM,
	ID_BTN_LEFT,
	ID_BTN_RIGHT,
	ID_BTN_FRONT,
	ID_BTN_BACK,
	ID_BTN_OTHER
};

enum
{
	ID_CTRL_MINX = 150,
	ID_CTRL_MINY,
	ID_CTRL_MINZ,
	ID_CTRL_MAXX,
	ID_CTRL_MAXY,
	ID_CTRL_MAXZ,
	ID_CTRL_PATH,
	ID_CTRL_TRAVERCE
};


wxBEGIN_EVENT_TABLE(EditorPanel, wxPanel)
EVT_BUTTON(ID_TO3DBUTTON, EditorPanel::OnTo3DButton)
EVT_BUTTON(ID_TOGCODEBUTTON, EditorPanel::OnToGcodeButton)
EVT_BUTTON(ID_CHECKBUTTON, EditorPanel::OnCheckButton)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(EditorPanel, wxPanel);

EditorPanel::EditorPanel(wxWindow *parent, FilePage *fp, int filetype, const wxString &filename, bool isnew) :
	m_fp(fp), wxPanel(parent)
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
	
		FlatButton *p3dViewBt = new FlatButton(this, ID_TO3DBUTTON, _("3D view"), true);
		wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
		//padd->SetWindowStyle(wxBORDER_NONE);
		p3dViewBt->SetBitmap(bmp);
		totalpane->Add(p3dViewBt, 0, wxRIGHT);
		totalpane->AddSpacer(10);

		FlatButton *pCheckBt = new FlatButton(this, ID_CHECKBUTTON, _("Check"), true);
		wxBitmap bmp1 = wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_OTHER, FromDIP(wxSize(16, 16)));
		pCheckBt->SetBitmap(bmp1);

		totalpane->Add(pCheckBt, 0,  wxRIGHT);
		totalpane->AddSpacer(10);
		if (ftype == FILETYPE_GCMC)
		{
			FlatButton *pConvertBt = new FlatButton(this, ID_TOGCODEBUTTON, _("Convert"), true);
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
	if(m_fp)
		m_fp->Draw3D();
	
}

void EditorPanel::OnToGcodeButton(wxCommandEvent& WXUNUSED(ev))
{	
	if (m_fp)
		m_fp->ConvertGcmc();
}
void EditorPanel::OnCheckButton(wxCommandEvent& WXUNUSED(ev))
{
	if (m_fp)
	{
		m_fp->Check();
	}
				
}

#define EVT_BUTTON_RANGE(id1, id2, func) wx__DECLARE_EVT2(wxEVT_BUTTON, id1, id2,wxCommandEventHandler(func))


wxBEGIN_EVENT_TABLE(View3DPanel, View3DPanelBase)
	EVT_BUTTON(ID_CLOSE3DVIEW, View3DPanel::OnClose)
	EVT_BUTTON_RANGE(ID_BTN_TOP, ID_BTN_BACK, View3DPanel::OnStandartView)
	EVT_MENU_RANGE(ID_BTN_TOP, ID_BTN_BACK,  View3DPanel::OnStandartView)
	EVT_BUTTON(ID_BTN_OTHER, View3DPanel::OnMenuView)

wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(View3DPanel, wxSashWindow);

View3DPanel::View3DPanel(wxWindow *parent, FilePage *fp) :	
	m_fp(fp), View3DPanelBase(parent, 100, wxDefaultPosition,wxDefaultSize,wxCLIP_CHILDREN|wxNO_BORDER )//| wxSW_BORDER)wxCLIP_CHILDREN | 
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
	
// move all content left for sizer
	wxBoxSizer *super_totalpane = new wxBoxSizer(wxHORIZONTAL);
	super_totalpane->AddSpacer(10);
	super_totalpane->Add(totalpane, wxEXPAND, wxEXPAND);;

	UpdateThemeColor();
	SetSizerAndFit(super_totalpane);
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


class PriorityData : public wxObject
{
public:
	PriorityData(int pr) : m_priority(pr), wxObject() { }
	int GetPriority() {return m_priority; }
private:
	int m_priority;

};
class PriorityBoxSizer : public wxBoxSizer
{
public:
	PriorityBoxSizer() : wxBoxSizer(wxHORIZONTAL) { }
	void AddButton(wxWindow *win, int priorirty, bool right = false)
	{
		Add(win, 0, wxALIGN_CENTRE_VERTICAL | (right ? wxRight : wxLEFT), 0, new PriorityData(priorirty) );
	}
	void AddButtonSpacer(int size, int priorirty)
	{
		Add(size, size, 0,0,0, new PriorityData(priorirty));
	}

	protected:
		void RecalcSizes();

};

void PriorityBoxSizer::RecalcSizes()
{
	if (m_children.empty())
		return;
	const wxCoord totalMajorSize = GetSizeInMajorDir(m_size);

	// declare loop variables used below:
	wxSizerItemList::const_reverse_iterator i;  // iterator in m_children list

	// First, inform item about the available size in minor direction as this
	// can change their size in the major direction. Also compute the number of
	// visible items and sum of their min sizes in major direction.

	int minMajorSize = 0;
	for (i = m_children.rbegin(); i != m_children.rend(); ++i)
	{		
		wxSizerItem * const item = *i;
		item->Show(true);
		minMajorSize += GetSizeInMajorDir(item->GetMinSizeWithBorder());
	}
	
	if (totalMajorSize < minMajorSize)
	{
		std::multimap<int, wxSizerItem *> prioroty_map;
		for (i = m_children.rbegin(); i != m_children.rend(); ++i)
		{
			wxSizerItem * const item = *i;
			PriorityData *p = dynamic_cast<PriorityData *>(item->GetUserData());
			if (p)
				prioroty_map.insert(std::make_pair(p->GetPriority(), item));
		}
		int cur_priority = -1;
		for (auto it  = prioroty_map.begin(); it != prioroty_map.end(); ++it)
		{
			if (cur_priority != -1 && cur_priority != it->first)
				break;
			wxSizerItem * const item = it->second;
			minMajorSize -= GetSizeInMajorDir(item->GetMinSizeWithBorder());
			item->Show(false);
			if (totalMajorSize > minMajorSize)
			{
				if (cur_priority == -1)
					cur_priority = it->first;				
			}
				
		}
	}
	else
	{
		//everithing in the bar remove ... button
		for (i = m_children.rbegin(); i != m_children.rend(); ++i)
		{
			wxSizerItem * const item = *i;
			PriorityData *p = dynamic_cast<PriorityData *>(item->GetUserData());
			if (p && p->GetPriority() == MAX_BTN_PRIORITY)
				item->Show(false);
		}

	}
	wxBoxSizer::RecalcSizes();
}


#define APPEND_BUTTOM(id,label,pr,sh)  pbtn = new FlatButton(this, id, label); \
								 header->AddButtonSpacer(5,pr); \
								 pbtn->Show(sh);\
								 header->AddButton(pbtn, pr)

								
wxBoxSizer *View3DPanel::CreateHeaderPanel()
{
	PriorityBoxSizer *header = new PriorityBoxSizer();
	wxStaticText *txt = new wxStaticText(this, wxID_ANY, _("3D View:"));
	header->Add(txt, 0, wxALIGN_CENTRE_VERTICAL| wxLEFT);// wxEXPAND);
	
	FlatButton *pbtn;
	APPEND_BUTTOM(ID_BTN_TOP, _("TOP"),9,true);
	APPEND_BUTTOM(ID_BTN_ISOMETRIC, _("ISOMETRIC"),8, true);
	APPEND_BUTTOM(ID_BTN_FRONT, _("FRONT"),5, false);
	APPEND_BUTTOM(ID_BTN_LEFT, _("LEFT"),4, false);
	APPEND_BUTTOM(ID_BTN_BOTTOM, _("BOTTOM"),3, false);
	APPEND_BUTTOM(ID_BTN_RIGHT, _("RIGHT"),2, false);
	APPEND_BUTTOM(ID_BTN_BACK, _("BACK"),1, false);
	APPEND_BUTTOM(ID_BTN_OTHER, _("..."), MAX_BTN_PRIORITY, true);

	//pbtn = new FlatButton(this, ID_BTN_OTHER, _("..."));//| wxBORDER_NONE); 
	//header->AddSpacer(5);
	//header->Add(pbtn, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT);

	header->AddStretchSpacer();

	FlatButton *pClose = new FlatButton(this, ID_CLOSE3DVIEW, _("Close"));//| wxBORDER_NONE); 
	wxBitmap bmp2 = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	pClose->SetBitmap(bmp2);
	header->Add(pClose, 0, wxRIGHT);
	header->AddSpacer(10);
	return header;
}

wxSizer *View3DPanel::CreateFooterPanel()
{
	wxFlexGridSizer  *gd = new wxFlexGridSizer(4,wxSize(10,5));// 2, 0, 0);
	gd->Add(new wxStaticText(this, wxID_ANY, _("X Min: ")),	0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MINX, _("     ")), 0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("X Max: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MAXX, _("     ")), 0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("Y Min: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MINY, _("     ")), 0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("Y Max: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MAXY, _("     ")), 0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("Z Min: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MINZ, _("     ")), 0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, wxID_ANY, _("Z Max: ")), 0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_MAXZ, _("     ")), 0, wxALIGN_LEFT); 
	
	gd->Add(new wxStaticText(this, wxID_ANY, _("Traverce: ")),0, wxALIGN_LEFT); 
	gd->Add(new wxStaticText(this, ID_CTRL_TRAVERCE, _("       ")),	0, wxALIGN_LEFT); // lenght val
	gd->Add(new wxStaticText(this, wxID_ANY, _("Path: ")),	0, wxALIGN_LEFT);
	gd->Add(new wxStaticText(this, ID_CTRL_PATH, _("       ")),0, wxALIGN_LEFT); // path val
	return gd;
}

void View3DPanel::SetValue(int id, const double &val)
{

	wxStaticText *ptxt = dynamic_cast<wxStaticText *>(FindWindowById(id,this));
	if (ptxt)
	{
		wxString txt = wxString::Format("%g mm.", val);
		ptxt->SetLabelText(txt);
	}
}

void View3DPanel::UpdateStatistics(const ConvertGCMCInfo &dt)
{
	SetValue(ID_CTRL_MINX, dt.box.Min.x);
	SetValue(ID_CTRL_MINY, dt.box.Min.y);
	SetValue(ID_CTRL_MINZ, dt.box.Min.z);
	SetValue(ID_CTRL_MAXX, dt.box.Max.x);
	SetValue(ID_CTRL_MAXY, dt.box.Max.y);
	SetValue(ID_CTRL_MAXZ, dt.box.Max.z);
	SetValue(ID_CTRL_PATH, dt.feed_len);
	SetValue(ID_CTRL_TRAVERCE, dt.traverce_len);
	
	Layout();
}

void View3DPanel::OnStandartView(wxCommandEvent& ev)
{
	if (!m_pview)
		return;

	switch (ev.GetId())
	{
		case ID_BTN_TOP: m_pview->DoSetView(View::TOP); break;
		case ID_BTN_ISOMETRIC: m_pview->DoSetView(View::ISOMETR); break;
		case ID_BTN_FRONT: m_pview->DoSetView(View::FRONT); break;
		case ID_BTN_LEFT: m_pview->DoSetView(View::LEFT); break;
		case ID_BTN_BOTTOM: m_pview->DoSetView(View::BOTTOM); break;		
		case ID_BTN_RIGHT: m_pview->DoSetView(View::RIGHT); break;		
		case ID_BTN_BACK: m_pview->DoSetView(View::BACK); break;
	};
}

#define APPEND_VIEW_MENU(id)  winBt = dynamic_cast<FlatButton *>(FindWindowById(id, this)); \
							  if ( winBt && !winBt->IsShown() )\
								  menu.Append(id,  winBt->GetLabel() )

void View3DPanel::OnMenuView( wxCommandEvent& WXUNUSED(ev))
{
	wxPoint pt(0, 0);
	wxWindow *winBt = FindWindowById(ID_BTN_OTHER, this);
	if (winBt)
	{
		wxRect btnRc = winBt->GetClientRect();
		pt = winBt->GetPosition() + btnRc.GetBottomLeft();
	}
	
	
	wxMenu menu;
	APPEND_VIEW_MENU(ID_BTN_TOP);
	APPEND_VIEW_MENU(ID_BTN_ISOMETRIC);
	APPEND_VIEW_MENU(ID_BTN_FRONT);
	APPEND_VIEW_MENU(ID_BTN_LEFT);
	APPEND_VIEW_MENU(ID_BTN_BOTTOM);
	APPEND_VIEW_MENU(ID_BTN_RIGHT);
	APPEND_VIEW_MENU(ID_BTN_BACK);
	if (menu.GetMenuItemCount() > 0 )
		PopupMenu(&menu, pt);// ScreenToClient(event.GetPosition()));
}

void View3DPanel::OnClose(wxCommandEvent& WXUNUSED(ev))
{
	if (m_fp)
	{
		m_fp->Hide3D();
	}
}



wxBEGIN_EVENT_TABLE(LogPane, wxPanel)
EVT_BUTTON(ID_CLOSEOUTPUT, LogPane::OnClose)
wxEND_EVENT_TABLE()

LogPane::LogPane(wxWindow *parent, FilePage *fb)
	: m_fb(fb), wxPanel(parent,-1,wxDefaultPosition,wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER | wxCAPTION)
{

	wxBoxSizer *header = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *txt = new wxStaticText(this, wxID_ANY, _("Output"));
	
	header->Add(10,0);
	header->Add(txt, 1, wxALIGN_CENTRE_VERTICAL);
	
	FlatButton *padd = new FlatButton(this, ID_CLOSEOUTPUT, _("Close"));//| wxBORDER_NONE); 
	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_OTHER, FromDIP(wxSize(16, 16)));
	padd->SetBitmap(bmp);
	header->Add(padd, 0, wxRIGHT);



	m_plog = new LogWindow(this, m_fb, wxID_ANY);
	m_plog->SetWindowStyle(m_plog->GetWindowStyle() | wxNO_BORDER);
	FlatScrollBar *barv = new FlatScrollBar(this, m_plog, wxID_ANY);
	FlatScrollBar *barh = 0;
	//if (common_prefs.visibleHSB)
		//barh = new FlatScrollBar(this, m_pedit, wxID_ANY, FlatScrollBar::typeHorisontal);

	m_plog->SetVScrollBar(barv);

	wxFlexGridSizer  *gd = new wxFlexGridSizer(2);// 2, 0, 0);
	gd->AddGrowableCol(0);
	gd->AddGrowableRow(0);
	gd->Add(m_plog, wxEXPAND, wxEXPAND);
	gd->Add(barv, 0, wxEXPAND);
	if (barh)
		gd->Add(barh, 0, wxEXPAND);

		
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(header, 0, wxEXPAND);
	totalpane->Add(gd, wxEXPAND, wxEXPAND); //wxEXPAND
	
	SetSizerAndFit(totalpane);
	UpdateThemeColor();
}

void LogPane::UpdateThemeColor()
{
	
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW);
	wxColor fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);
	wxColor bgColorFr = clrs->Get(ColourScheme::FRAME);
	
	
	SetBackgroundColour(bgColorFr);
	SetForegroundColour(fgColor);

	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColorFr);
		child->SetForegroundColour(fgColor);
		node = node->GetNext();
	}

	m_plog->SetBackgroundColour(bgColor);
	m_plog->SetForegroundColour(fgColor);


}

void LogPane::OnClose(wxCommandEvent& WXUNUSED(ev))
{
	m_fb->HideLog();
}


wxBEGIN_EVENT_TABLE(FilePage, wxPanel)
EVT_SIZE(FilePage::OnSize)
EVT_SASH_DRAGGED_RANGE(100, 101, FilePage::OnSashDrag)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(FilePage, wxPanel);


FilePage::FilePage(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	m_logwn(0), wxPanel(parent)
{

	m_view3dsize = -1;
	m_view3d = 0;
	m_worker = new Worker(this);
	

		
		
	m_splitter = new wxSplitterWindow( this,-1, wxDefaultPosition,wxDefaultSize, wxSP_LIVE_UPDATE);
	

	m_splitter->SetSize(GetClientSize());
	m_splitter->SetSashGravity(1.0);
	m_editor = new EditorPanel(m_splitter,this, filetype, filename, isnew);		
	m_logwn = new LogPane(m_splitter,this );
	
	
	
	m_logwn->Show(false);
	m_splitter->Initialize(m_editor);
	m_splitter->SetMinimumPaneSize(40);

	//wxGridSizer *totalpane;
	int ftype = m_editor->GetEdit()->GetFileType();
	if ((ftype == FILETYPE_NC) || (ftype == FILETYPE_GCMC))
	{

		//		wxSplitterWindow *splitMain = new wxSplitterWindow(this, -1, wxDefaultPosition, wxDefaultSize, 0);
	//	splitMain->SetSize(GetClientSize());
		//splitMain->SetSashGravity(1.0);
		//m_splitter->Reparent(splitMain);
		//m_view3d = new View3DPanel(splitMain);
		//splitMain->SplitVertically(m_splitter, m_view3d);

		//totalpane = new wxGridSizer(2);
		//totalpane->Add(m_splitter, 0, wxEXPAND);
		
		m_view3d = new View3DPanel(this, this);
		m_view3d->SetSashVisible(wxSASH_LEFT, true);
		//m_view3d->SetAutoLayout(true);
		
		//totalpane->Add(m_view3d, 1, wxEXPAND);
	}
	else
	{
		//totalpane = new wxGridSizer(1);
		//totalpane->Add(m_splitter, 0, wxEXPAND);
	}

	UpdateThemeColor();
	//SetSizerAndFit(totalpane);
	DoLayout();
}


void FilePage::OnSize(wxSizeEvent& event)
{
	DoLayout();
}

void FilePage::DoLayout(const wxSize &szin)
{
	wxSize sz = szin;
	if (sz == wxDefaultSize)
	{
		sz = GetSize();
		if (m_view3d && m_view3d->IsShown())
		{
			if (m_view3dsize == -1 && sz.x > 25)
				m_view3dsize = sz.x / 3;
			else
				m_view3dsize = m_view3d->GetSize().x;
			sz.x -= m_view3dsize;
		}
	}

	m_splitter->SetSize(0, 0, sz.x, sz.y);
	if (m_view3d && m_view3d->IsShown())
	{
		m_view3d->SetSize(sz.x, 0, GetSize().x - sz.x, sz.y);
		m_view3d->Layout();
		m_view3d->Refresh();
	}

}

void FilePage::OnSashDrag(wxSashEvent& event)
{
	if (event.GetDragStatus() == wxSASH_STATUS_OUT_OF_RANGE)
		return;

	wxRect rcDrag = event.GetDragRect();
	wxSize szClient(GetSize().x - rcDrag.width, GetSize().GetY());
	DoLayout(szClient);
}

FilePage::~FilePage()
{
	delete m_worker;

}

void FilePage::Draw3D()
{
	if (m_worker->IsRunning())
		return;

	if (!DoFileSave(false, false))
		return;
	// we don't show log here it will be shown automatically if error occure
	m_worker->Draw3D();
	Show3D();
}


void FilePage::Check()
{
	if (m_worker->IsRunning())
		return;

	if (!DoFileSave(false, false))
		return;

	ShowLog();
	m_worker->Check();
}

void FilePage::ConvertGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args)
{
	if (m_worker->IsRunning())
		return;
	ShowLog();
	m_worker->RunGcmc(src_fname, dst_fname, args, ConvertGcmcPasteFile);
}

void FilePage::ConvertGcmc()
{
	if (m_worker->IsRunning())
		return;

	if (!DoFileSave(false, false))
		return;

	ShowLog();
	m_worker->DoConvertGcmc(ConvertGcmcOpenFile);
}


wxString FilePage::GetSavedFileName()
{
	if (!DoFileSave(false, false))
		return wxString();

	Edit *pedit = GetEdit();
	return  pedit ? pedit->GetFileName() : wxString();
}




void FilePage::UpdateThemeColor()
{
}

void FilePage::ShowLog( )
{
	if (m_splitter->IsSplit())
		return;
		
	m_editor->Show(true);
	m_logwn->Show(true);
	m_splitter->SplitHorizontally(m_editor, m_logwn,-250);
}

void FilePage::HideLog()
{
	if (m_splitter->IsSplit())
		m_splitter->Unsplit();
}

void FilePage::UpdateStatistics(const ConvertGCMCInfo &dt)
{
	if (m_view3d)
		m_view3d->UpdateStatistics(dt);
}



void FilePage::Show3D()
{
	if ( m_view3d )
		m_view3d->Show(true);
	DoLayout();
}



void FilePage::Hide3D()
{
	if ( m_view3d )
		m_view3d->Show(false);
	DoLayout();
}

bool FilePage::DoFileSave(bool askToSave, bool bSaveAs)
{

	Edit *pedit = GetEdit();
	if (!pedit)
		return true;

	m_worker->StopAll();

	if (!pedit->Modified() && !bSaveAs)
		return true;

	// Ask need to save
	if (askToSave)
	{
		int rez = wxMessageBox(_("Text is not saved, save before closing?"), _("Save file"),
			wxYES_NO | wxCANCEL | wxICON_QUESTION);
		if (rez == wxCANCEL)
			return false;
		else if (rez == wxNO)
			return true;
	}
	// Need save
	if (bSaveAs || pedit->IsNew())
	{
		wxString filename = pedit->GetFileName();
		wxString wildCard;
		if (pedit->GetFileType() == FILETYPE_GCMC)
			wildCard = _("GCMC Files (*.gcmc)|*.gcmc");
		else
			wildCard = _("GCode Files (*.ngc;*.nc)|*.ngc;*.nc");

		wxFileDialog dlg(this, _("Save file As"), wxEmptyString, filename, wildCard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() != wxID_OK)
			return false;
		filename = dlg.GetPath();
		pedit->SaveFile(filename);
		ConfigData *config;
		if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) != NULL)
			config->AddFileNameToSaveList(filename);
	}
	else //  fname exist && not save as  - just save
	{
		pedit->SaveFile();
		if (pedit->Modified())
		{
			wxMessageBox(_("Text could not be saved!"), _("Close abort"),
				wxOK | wxICON_EXCLAMATION);
			return false;
		}
	}
	
	wxGetApp().GetFrame()->UpdateTitle(this);

	return true;
}
