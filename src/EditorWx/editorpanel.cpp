#include "wx/wx.h"
#include "editorpanel.h"

#include "wx/artprov.h"
#include "prefs.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/dockart.h"
#include "wx/splitter.h"
#include <wx/popupwin.h>
#include <wx/animate.h>
#include <wx/mstream.h>

#include "flatstaticline.h"

#include "flatbuttom.h"
#include "FlatScrollBar.h"
#include "FlatSlider.h"
#include "defsext.h"
#include "View3D.h"
#include "edit.h"    
#include "logwindow.h"
#include "configdata.h"
#include "app.h"          //for upadte title :(
#include "appframe.h"     //for upadte title :(

#define MAX_BTN_PRIORITY 1101
#define SPEED_WND_WIDTH 150
#define MARGIN_LEFT  12
#define MARGIN_RIGHT 12
#define MIN_EDITOR_X 50
#define MIN_EDITOR_Y 50
#define MIN_3DVIEW_X 20
#define MIN_LOGWND_Y 40

enum
{
	ID_STATICTEXTFG = 100,
	ID_STATICTEXTDISABLE,
	ID_TO3DBUTTON,
	ID_TOGCODEBUTTON,
	ID_CHECKBUTTON,
	ID_CLOSEOUTPUT,
	ID_STOPPROCESS,
	ID_CLOSE3DVIEW,
	ID_SAVEBUTTON,
	ID_BTN_TOP,
	ID_BTN_ISOMETRIC,
	ID_BTN_BOTTOM,
	ID_BTN_LEFT,
	ID_BTN_RIGHT,
	ID_BTN_FRONT,
	ID_BTN_BACK,
	ID_BTN_OTHER,
	ID_BTN_PAUSE,
	ID_BTN_SIMULATE,
	ID_BTN_STOP,
	ID_BTN_SHOWAXIS,
	ID_BTN_SHOWGRID,
	ID_BTN_SHOWBOX,
	ID_BTN_SHOWFAST,
	ID_SETSIMULATIONSPEED,
	ID_LOGWINDOW,
	ID_3DVIEWWINDOW
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
	ID_CTRL_TRAVERCE,
	ID_SIMULATED_SLIDER,
	ID_SIMULATEDSPEED_SLIDER
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
	const CommonInfo &common_prefs = Preferences::Get()->Common();

    m_pedit = new Edit(this, wxID_ANY);
	FlatScrollBar *barv = new FlatScrollBar(this, m_pedit, wxID_ANY);
	FlatScrollBar *barh = 0;
	if (common_prefs.visibleHSB)
		barh = new FlatScrollBar(this, m_pedit, wxID_ANY, FlatScrollBar::typeHorisontal);

	m_pedit->SetVScrollBar(barv);
	m_pedit->SetHScrollBar(barh);


	if (isnew)
		m_pedit->NewFile(filetype, filename);
	else
		m_pedit->LoadFile(filename);
	
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->AddSpacer(5);
	totalpane->Add(pHeader, 0, wxEXPAND);
	totalpane->AddSpacer(10);
	FlatStaticLine *pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	totalpane->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, MARGIN_LEFT);
	totalpane->AddSpacer(10);


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

#define ADD_COMMAND_TO_VIEW(id, Text, artId) \
	ph = new FlatButton(this, id, Text, FB_BITMAP_RIGHT | FB_LABEL_LEFT, artId); \
	totalpane->Add(ph, 0, wxRIGHT); \
	totalpane->AddSpacer(10);



wxBoxSizer *EditorPanel::CreateHeaderPanel()
{
	wxBoxSizer *totalpane = new wxBoxSizer(wxHORIZONTAL);	
	wxString label;
	int ftype = m_pedit->GetFileType();
	
	switch (ftype)
	{
		case FILETYPE_NC:	label = _("G-Code"); break;
		case FILETYPE_GCMC:	label = _("GCMC"); break;
		case FILETYPE_JSON: label = _("JSON"); break;
	}
	if ( !label.empty() )
	{
		wxStaticText *txt = new wxStaticText(this, ID_STATICTEXTFG, label);
		totalpane->AddSpacer(MARGIN_LEFT);
		totalpane->Add(txt, 1, wxALIGN_CENTRE_VERTICAL);// wxEXPAND);
	}

	FlatButton *ph;
	//ADD_COMMAND_TO_VIEW(ID_SAVEBUTTON, _("Save"), ART_SAVE)
	//ph->SetCommand(wxID_SAVE);

	if ((ftype == FILETYPE_NC) || (ftype == FILETYPE_GCMC) )
	{
		ADD_COMMAND_TO_VIEW(ID_CHECKBUTTON, _("Check"), ART_VERIFY)
		if (ftype == FILETYPE_GCMC)
		{
			ADD_COMMAND_TO_VIEW(ID_TOGCODEBUTTON, _("Convert"), ART_CONVERT)
		}
		ADD_COMMAND_TO_VIEW(ID_TO3DBUTTON, _("3D view"), ART_DRAW3D)
	}

	return totalpane;
}



EditorPanel::~EditorPanel()
{
}

void EditorPanel::UpdatePreferences()
{
	UpdateThemeColor();
	m_pedit->UpdatePreferences();
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
		FlatButton *fbt = dynamic_cast<FlatButton *>(child);
		if (fbt)
			fbt->UpdateThemeColor();
		else
		{
			child->SetBackgroundColour(bgColor);
			child->SetForegroundColour(fgColor);
		}
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
EVT_MENU_RANGE(ID_BTN_TOP, ID_BTN_BACK, View3DPanel::OnStandartView)
EVT_BUTTON(ID_BTN_OTHER, View3DPanel::OnMenuView)
EVT_BUTTON(ID_BTN_PAUSE, View3DPanel::OnPauseSimulate)
EVT_BUTTON(ID_BTN_SIMULATE, View3DPanel::OnRunSimulate)
EVT_BUTTON(ID_BTN_STOP, View3DPanel::OnStopSimulate)
EVT_BUTTON(ID_SETSIMULATIONSPEED, View3DPanel::OnSetSimulateSpeed)
EVT_BUTTON(ID_BTN_SHOWAXIS, View3DPanel::OnTune3DView)
EVT_BUTTON(ID_BTN_SHOWGRID, View3DPanel::OnTune3DView)
EVT_BUTTON(ID_BTN_SHOWBOX, View3DPanel::OnTune3DView)
EVT_BUTTON(ID_BTN_SHOWFAST, View3DPanel::OnTune3DView)

EVT_COMMAND_SCROLL(ID_SIMULATED_SLIDER, View3DPanel::OnSimulateProgress)
EVT_COMMAND_SCROLL(ID_SIMULATEDSPEED_SLIDER, View3DPanel::OnSpeedChanged)

EVT_IDLE(View3DPanel::OnIdle)

wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(View3DPanel, View3DPanelBase);

View3DPanel::View3DPanel(wxWindow *parent, FilePage *fp) :	
	m_fp(fp), View3DPanelBase(parent, ID_3DVIEWWINDOW, wxDefaultPosition,wxDefaultSize,wxCLIP_CHILDREN|wxNO_BORDER )//| wxSW_BORDER)wxCLIP_CHILDREN | 
{
	m_pview = new View3D(this, wxID_ANY);
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pHeader = CreateHeaderPanel();
	totalpane->AddSpacer(5);
	totalpane->Add(pHeader, 0, wxEXPAND);
	totalpane->AddSpacer(10);
	FlatStaticLine *pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	totalpane->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, MARGIN_LEFT);
	totalpane->AddSpacer(10);
	totalpane->Add(m_pview, wxEXPAND, wxEXPAND);

	totalpane->AddSpacer(10);
	pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	totalpane->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, MARGIN_LEFT);
	totalpane->AddSpacer(10);

	wxSizer *pSimulate = CreateSimulationPanel();
	wxSizer *pFooter = CreateFooterPanel();
	
	totalpane->Add(pSimulate, 0, wxEXPAND);
	
	//totalpane->AddSpacer(FromDIP(15));
	totalpane->AddSpacer(10);
	//pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	//totalpane->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, MARGIN_LEFT);
	totalpane->AddSpacer(8);


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

void View3DPanel::UpdatePreferences()
{
	UpdateThemeColor();
	m_pview->UpdatePreferenses();
	InitColours();
	m_pview->Refresh();
}

void View3DPanel::UpdateThemeColor()
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW_3DVIEW);
	wxColor fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);
	wxColor fgdisableColor = clrs->Get(ColourScheme::WINDOW_TEXT_DISABLE);

	SetBackgroundColour(bgColor);
	SetForegroundColour(fgColor);
	
	wxWindowList::compatibility_iterator node = GetChildren().GetFirst();
	while (node)
	{
		wxWindow* child = node->GetData();
		child->SetBackgroundColour(bgColor);
		
		//child->SetForegroundColour(fgColor);
		if (child->GetId() == ID_STATICTEXTDISABLE )
			child->SetForegroundColour(fgdisableColor);
		else
			child->SetForegroundColour(fgColor);

		FlatButton *fbt = dynamic_cast<FlatButton *>(child);
		if (fbt)
			fbt->UpdateThemeColor();
		
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
		Add(win, 0, wxALIGN_CENTRE_VERTICAL | (right ? wxRIGHT : wxLEFT), 0, new PriorityData(priorirty) );
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
	//ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	//wxColor colorfg = clrs->Get(ColourScheme::WINDOW_TEXT);
	PriorityBoxSizer *header = new PriorityBoxSizer();
	wxStaticText *txt = new wxStaticText(this, ID_STATICTEXTFG, _("3D View:"));
	//txt->SetForegroundColour(colorfg);
	header->AddSpacer(MARGIN_LEFT);
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
	header->AddStretchSpacer();

	FlatButton *pClose = new FlatButton(this, ID_CLOSE3DVIEW, wxEmptyString, FB_TRANSPARENT, ART_CLOSE);
	header->Add(pClose, 0, wxRIGHT|wxALIGN_CENTER_VERTICAL);	
	header->AddSpacer(MARGIN_RIGHT);

	return header;
}

wxString View3DPanel::GetSpeedBtLabel()
{
	int speedK = m_fp->GetWorker()->GetSimulationSpeed();
	return wxString::Format(_("Speed: x%d"), speedK);
}

wxSizer *View3DPanel::CreateSimulationPanel()
{
	wxBoxSizer *panel = new wxBoxSizer(wxVERTICAL);
	// Create view button
	wxBoxSizer *btns = new wxBoxSizer(wxHORIZONTAL);
	FlatButton *btv1 = new FlatButton(this, ID_BTN_SHOWAXIS, _(" AXIS "), FB_LABEL_CENTER);
	wxSize btsz = btv1->GetMinSize();	
	btns->Add(btv1, 0, wxALIGN_CENTRE_VERTICAL);
	btns->AddSpacer(5);
	FlatButton *btv2 = new FlatButton(this, ID_BTN_SHOWBOX, _("BOX"), FB_LABEL_CENTER);
	wxSize sz = btv2->GetMinSize();
	if (sz.x > btsz.x) btsz.x = sz.x;
	btns->Add(btv2, 0, wxALIGN_CENTRE_VERTICAL);
	btns->AddSpacer(5);
	FlatButton *btv3 = new FlatButton(this, ID_BTN_SHOWFAST, _("G0"), FB_LABEL_CENTER);
	btns->Add(btv3, 0, wxALIGN_CENTRE_VERTICAL);
	sz = btv3->GetMinSize();
	if (sz.x > btsz.x) btsz.x = sz.x;

	btv1->SetMinSize(btsz);
	btv2->SetMinSize(btsz);
	btv3->SetMinSize(btsz);


	//panel->AddSpacer(5);
	panel->Add(btns, 0, wxALIGN_CENTRE_HORIZONTAL);



	// Create Simulation slider
	FlatSlider *pguage = new FlatSlider(this, ID_SIMULATED_SLIDER, 0, 0, 1000);
	pguage->SetMargin(MARGIN_LEFT);
	panel->AddSpacer(5);
	panel->Add(pguage, 0, wxEXPAND);

	// Create Simulation commands buttons
	btns = new wxBoxSizer(wxHORIZONTAL);
	btns->AddSpacer(MARGIN_LEFT);
	btns->AddStretchSpacer();
	FlatButton *bt = new FlatButton(this, ID_BTN_PAUSE, wxEmptyString, FB_TRANSPARENT, ART_PAUSE);
	btns->Add(bt, 0, wxALIGN_CENTRE_VERTICAL);
	bt = new FlatButton(this, ID_BTN_SIMULATE, wxEmptyString, FB_TRANSPARENT, ART_PLAY);
	btns->Add(bt, 0, wxALIGN_CENTRE_VERTICAL);
	bt = new FlatButton(this, ID_BTN_STOP, wxEmptyString, FB_TRANSPARENT, ART_STOP);
	btns->Add(bt, 0, wxALIGN_CENTRE_VERTICAL);
	btns->AddStretchSpacer();

	bt = new FlatButton(this, ID_SETSIMULATIONSPEED, GetSpeedBtLabel() );
	btns->Add(bt, 0, wxALIGN_CENTRE_VERTICAL | wxRIGHT);
	btns->Insert(0, bt->GetMinWidth(),1 );
	btns->AddSpacer(MARGIN_RIGHT);
	panel->Add(btns, 0, wxEXPAND);
	return panel;
}

#define ADD_STATISTIC_TEXT(id, text) pt = new wxStaticText(this, id, text); \
									gd->Add(pt, 0, wxALIGN_LEFT); 
									

#define ADD_STATISTIC_TEXT0(text)  ADD_STATISTIC_TEXT( ID_STATICTEXTDISABLE, text) 
#define ADD_STATISTIC_TEXT1(id)  ADD_STATISTIC_TEXT( id, L"     ")

wxSizer *View3DPanel::CreateFooterPanel()
{

	//ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	//wxColor colorfg = clrs->Get(ColourScheme::WINDOW_TEXT);
	//wxColor colorfgd = clrs->Get(ColourScheme::WINDOW_TEXT_DISABLE);
	
	wxStaticText *pt;
	wxFlexGridSizer  *gd = new wxFlexGridSizer(4,wxSize(10,5));// 2, 0, 0);	

	ADD_STATISTIC_TEXT0(_("X Min: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MINX);
	ADD_STATISTIC_TEXT0(_("X Max: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MAXX);
	ADD_STATISTIC_TEXT0(_("Y Min: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MINY);
	ADD_STATISTIC_TEXT0(_("Y Max: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MAXY);
	ADD_STATISTIC_TEXT0(_("Z Min: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MINZ);
	ADD_STATISTIC_TEXT0(_("Z Max: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_MAXZ);
	ADD_STATISTIC_TEXT0(_("Traverce: ")); 
	ADD_STATISTIC_TEXT1(ID_CTRL_TRAVERCE);
	ADD_STATISTIC_TEXT0(_("Path: "));
	ADD_STATISTIC_TEXT1(ID_CTRL_PATH);

	wxBoxSizer *pane = new wxBoxSizer(wxHORIZONTAL);
	pane->AddSpacer(MARGIN_LEFT);
	pane->Add(gd,wxEXPAND, wxEXPAND);
	pane->AddSpacer(MARGIN_RIGHT);
	return pane;
}

void View3DPanel::SetValue(int id, const double &val, bool clear)
{

	wxStaticText *ptxt = dynamic_cast<wxStaticText *>(FindWindowById(id,this));
	if (ptxt)
	{
		wxString txt = clear ? wxString(" ") : wxString::Format("%g mm.", val);
		ptxt->SetLabelText(txt);
	}
}

void View3DPanel::UpdateStatistics(const ConvertGCMCInfo &dt)
{
	bool clear = dt.num_errors != 0;
	SetValue(ID_CTRL_MINX, dt.box.Min.x, clear);
	SetValue(ID_CTRL_MINY, dt.box.Min.y, clear);
	SetValue(ID_CTRL_MINZ, dt.box.Min.z, clear);
	SetValue(ID_CTRL_MAXX, dt.box.Max.x, clear);
	SetValue(ID_CTRL_MAXY, dt.box.Max.y, clear);
	SetValue(ID_CTRL_MAXZ, dt.box.Max.z, clear);
	SetValue(ID_CTRL_PATH, dt.feed_len, clear);
	SetValue(ID_CTRL_TRAVERCE, dt.traverce_len, clear);

	FlatSlider *slider = dynamic_cast<FlatSlider *>(FindWindowById(ID_SIMULATED_SLIDER, this));
	if (slider)
	{
		int m_full_path = int(dt.feed_len + dt.traverce_len);
		if (m_full_path > 0)
		{
			slider->SetRange(0, m_full_path);
			slider->SetTickFreq(m_full_path / 10);
		}
	}

	Layout();
}

void View3DPanel::UpdateSimulationPos(int index, int dist, const TrackPointGL &pt)
{
	if (!m_pview || m_pview->IsEmpty() )
		return;
	
	
	FlatSlider *slider = dynamic_cast<FlatSlider *>(FindWindowById(ID_SIMULATED_SLIDER, this));
	if (dist < 0)
		dist = 0;
	slider->SetValue(dist);
	m_pview->setSimulationPos(index, pt);
	
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

void View3DPanel::OnPauseSimulate(wxCommandEvent& WXUNUSED(ev))
{
	m_fp->GetWorker()->SemulatePause();
}
void View3DPanel::OnRunSimulate(wxCommandEvent& WXUNUSED(ev))
{
	m_fp->GetWorker()->SemulateStart();
}
void View3DPanel::OnStopSimulate(wxCommandEvent& WXUNUSED(ev))
{
	m_fp->GetWorker()->SemulateStop();
}



class SpeedWindow : public wxPopupWindow
{
public:
	SpeedWindow(wxWindow *parent, int speedK, const wxPoint &pos);
	void OnMouseEvent(wxMouseEvent& event);
	void OnKillFocus(wxFocusEvent& event);
};


SpeedWindow::SpeedWindow(wxWindow *parent, int speedK, const wxPoint &pos)
	: wxPopupWindow(parent)
{
	SetWindowStyle(GetWindowStyle() &(~wxTAB_TRAVERSAL));
	wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
	
	int flags = wxSL_LABELS | wxSL_BOTTOM | wxSL_MIN_MAX_LABELS | wxSL_AUTOTICKS;
	
	FlatSlider *sz = new FlatSlider(this, ID_SIMULATEDSPEED_SLIDER, speedK, 1, 50, wxDefaultPosition, wxDefaultSize, flags);
	
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxColor bgColor = clrs->Get(ColourScheme::WINDOW);
	wxColor fgColor = clrs->Get(ColourScheme::WINDOW_TEXT);
	sz->SetBackgroundColour(bgColor);
	sz->SetForegroundColour(fgColor);

	sz->SetTickFreq(10);
	box->Add(sz, 0, wxEXPAND);	
	SetSizerAndFit(box);
	int h = sz->GetBestSize().y;
	SetSize(pos.x, pos.y - h - 5, SPEED_WND_WIDTH, h);
	View3DPanel *panel = dynamic_cast<View3DPanel *>(parent);
	sz->Bind(wxEVT_SCROLL_CHANGED, &View3DPanel::OnSpeedChanged, panel);
	sz->Bind(wxEVT_SCROLL_THUMBTRACK, &View3DPanel::OnSpeedChanged, panel);
	
	sz->Bind(wxEVT_KILL_FOCUS, &SpeedWindow::OnKillFocus, this);
	//sz->Bind(wxEVT_RIGHT_DOWN, &SpeedWindow::OnMouseEvent, this);
	//sz->Bind(wxEVT_LEFT_DOWN, &SpeedWindow::OnMouseEvent, this);
	//sz->Bind(wxEVT_MIDDLE_DOWN, &SpeedWindow::OnMouseEvent, this);
	Show(true);
	sz->SetFocus();
	//CaptureMouse();
}

void SpeedWindow::OnKillFocus(wxFocusEvent& event)
{
	Destroy();
}

void SpeedWindow::OnMouseEvent(wxMouseEvent& event)
{
	wxPoint pt = event.GetPosition();
	wxRect rc = GetClientRect();
	if ( rc.Contains(pt) )
		return;
	else
	{
		//ReleaseMouse();
		//Destroy();
		event.Skip();
	}
}


void View3DPanel::OnSetSimulateSpeed(wxCommandEvent& WXUNUSED(ev))
{
	wxWindow *bt = FindWindowById(ID_SETSIMULATIONSPEED, this);
	if (!bt) return;
	wxPoint pt = bt->GetScreenPosition();
	pt.x -= (SPEED_WND_WIDTH - bt->GetSize().x);
	//pt.y -= 50;
	
	int speedK = m_fp->GetWorker()->GetSimulationSpeed();
	SpeedWindow *sp = new SpeedWindow(this, speedK, pt);//, wxPOPUP_WINDOW);

}


void View3DPanel::OnSpeedChanged(wxScrollEvent& event)
{
	int position = event.GetPosition();
	int value = event.GetInt();
	m_fp->GetWorker()->SetSimulationSpeed(value);
	
	wxWindow *bt = FindWindowById(ID_SETSIMULATIONSPEED, this);
	if (bt)
	{
		bt->SetLabel(GetSpeedBtLabel());
		bt->Refresh();
	}

}

void View3DPanel::OnSimulateProgress(wxScrollEvent& event)
{
	wxEventType eventType = event.GetEventType();
	if (eventType != wxEVT_SCROLL_CHANGED && eventType != wxEVT_SCROLL_THUMBTRACK)
		return;
	
	int position = event.GetPosition();
	int value = event.GetInt();
	m_fp->GetWorker()->SetSimulationPos(value);
}

void View3DPanel::OnTune3DView(wxCommandEvent& event)
{
	unsigned int style = 0;

	switch ( event.GetId())
	{
		case ID_BTN_SHOWAXIS: style = VSTYLE_SHOWAXIS;  break;
		case ID_BTN_SHOWGRID: style = VSTYLE_SHOWGRID;  break;
		case ID_BTN_SHOWBOX : style = VSTYLE_SHOWBOX;  break;
		case ID_BTN_SHOWFAST: style = VSTYLE_SHOWFASTMOVE;  break;
	}

	m_pview->ToggleStyle(style);

	FlatButton *fb = dynamic_cast<FlatButton *>(FindWindowById(event.GetId(), this));
	if ( fb )
		fb->SetChecked((m_pview->GetStyleFlag() & style) != 0);
}


#define UPDATE_SHOW3D_BUTTON(id, Style)  fb = dynamic_cast<FlatButton *>(FindWindowById(id, this));\
		if (fb)\
			fb->SetChecked((m_pview->GetStyleFlag() & Style) != 0);

void View3DPanel::OnIdle(wxIdleEvent& event)
{
	wxWindow *win = FindWindowById(ID_BTN_SIMULATE, this);
	if (win)
		win->Enable(m_fp->GetWorker()->CanSimulateStart());

	win = FindWindowById(ID_BTN_STOP, this);
	if (win)
		win->Enable(m_fp->GetWorker()->CanSimulateStop());

	win = FindWindowById(ID_BTN_PAUSE, this);
	if (win)
		win->Enable(m_fp->GetWorker()->CanSimulatePaused());

	FlatButton *fb;
	UPDATE_SHOW3D_BUTTON(ID_BTN_SHOWAXIS, VSTYLE_SHOWAXIS);
	UPDATE_SHOW3D_BUTTON(ID_BTN_SHOWBOX, VSTYLE_SHOWBOX);
	UPDATE_SHOW3D_BUTTON(ID_BTN_SHOWFAST, VSTYLE_SHOWFASTMOVE);
}


wxIMPLEMENT_ABSTRACT_CLASS(LogPane, FlatSashWindow);

wxBEGIN_EVENT_TABLE(LogPane, FlatSashWindow)
EVT_BUTTON(ID_CLOSEOUTPUT, LogPane::OnClose)
EVT_BUTTON(ID_STOPPROCESS, LogPane::OnStop)
wxEND_EVENT_TABLE()

LogPane::LogPane(wxWindow *parent, FilePage *fb)
	: m_fb(fb), FlatSashWindow(parent, ID_LOGWINDOW, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN | wxNO_BORDER)
	//wxPanel(parent,-1,wxDefaultPosition,wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER | wxCAPTION)
{
	m_workingAnim = NULL;
	// Create header
	wxBoxSizer *header = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *txt = new wxStaticText(this, wxID_ANY, _("Output"));
	txt->SetFont(wxFontInfo(10).Bold());
	header->AddSpacer(MARGIN_LEFT);
	header->Add(txt, 0, wxALIGN_LEFT | wxALIGN_CENTRE_VERTICAL);

//crate progress contrl
	
	const void* data = NULL;
	size_t outLen = 0;
	ConfigData *config = dynamic_cast<ConfigData *>(wxConfigBase::Get());
	wxASSERT(config);
	wxString resname = wxString::Format("ID_THROBER_%s", config->GetTheme());
	if (wxLoadUserResource(&data, &outLen, resname, RT_RCDATA))
	{
		wxMemoryInputStream is(data, outLen);
		m_workingAnim = new wxAnimationCtrl(this, wxID_ANY);
		if (!m_workingAnim->Load(is))
		{
			delete m_workingAnim;
			m_workingAnim = 0;
		}
		else
		{
			header->AddStretchSpacer();
			header->Add(m_workingAnim, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
			m_workingAnim->SetUseWindowBackgroundColour(true);
			m_workingAnim->Show(false);
		}

	}
	
	header->AddStretchSpacer();
	m_stop = new FlatButton(this, ID_STOPPROCESS, _("Stop"));
	header->Add(m_stop, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL);
	m_stop->Show(false);
	header->AddSpacer(10);

	
	FlatButton *padd = new FlatButton(this, ID_CLOSEOUTPUT, wxEmptyString, FB_TRANSPARENT, ART_CLOSE);
	header->Add(padd, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL);
	header->AddSpacer(MARGIN_LEFT);

	// Create body
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

	wxBoxSizer *body = new wxBoxSizer(wxHORIZONTAL);
	body->AddSpacer(MARGIN_LEFT);
	body->Add(gd, wxEXPAND, wxEXPAND); 
		
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->AddSpacer(7);
	totalpane->Add(header, 0, wxEXPAND);


	totalpane->Add(body, wxEXPAND, wxEXPAND); //wxEXPAND
	SetSashVisible(wxSASH_TOP, true);
	SetAutoLayout(true);
	Show(false);
	SetSizerAndFit(totalpane);
	UpdateThemeColor();
}

void LogPane::UpdatePreferences()
{
	UpdateThemeColor();
	InitColours();
}

void LogPane::UpdateThemeColor()
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
	if (m_workingAnim)
	{
		m_workingAnim->SetUseWindowBackgroundColour(true);
	}
}

void LogPane::OnClose(wxCommandEvent& WXUNUSED(ev))
{
	m_fb->HideLog();
}


void LogPane::OnStop(wxCommandEvent& WXUNUSED(ev))
{
	m_fb->GetWorker()->StopAll();
}

void LogPane::StartPulse()
{
	bool needlayout = false;
	if (m_workingAnim)
	{
		wxSizerItem *item = GetSizer()->GetItem(m_workingAnim, true);
		if (item && !m_workingAnim->IsShown())
		{
			item->Show(true);
			needlayout = true;
		}
	}
	if (m_stop)
	{
		wxSizerItem *item = GetSizer()->GetItem(m_stop, true);
		if (item && !m_stop->IsShown())
		{
			item->Show(true);
			needlayout = true;
		}
	}
	if ( needlayout )
		Layout();
	
	if (m_workingAnim)
		m_workingAnim->Play();
}

void LogPane::Pulse()
{
	
}
void LogPane::StopPulse()
{
	bool needlayout = false;
	if (m_workingAnim)
	{
		wxSizerItem *item = GetSizer()->GetItem(m_workingAnim, true);
		if (item && m_workingAnim->IsShown())
		{
			item->Show(false);
			needlayout = true;
		}
	}
	if (m_stop)
	{
		wxSizerItem *item = GetSizer()->GetItem(m_stop, true);
		if (item && m_stop->IsShown())
		{
			item->Show(false);
			needlayout = true;
		}
	}

	if (m_workingAnim)
		m_workingAnim->Stop();
	
	if (needlayout)
		Layout();
}


wxBEGIN_EVENT_TABLE(FilePage, wxPanel)
EVT_SIZE(FilePage::OnSize)
EVT_SASH_DRAGGED(ID_LOGWINDOW, FilePage::OnSashDrag)
EVT_SASH_DRAGGED(ID_3DVIEWWINDOW, FilePage::OnSashDrag)
EVT_SHOW(FilePage::OnShowHideWnd)
wxEND_EVENT_TABLE()

wxIMPLEMENT_ABSTRACT_CLASS(FilePage, wxPanel);


FilePage::FilePage(wxWindow *parent, int filetype, const wxString &filename, bool isnew) :
	m_logwn(0), wxPanel(parent)
{

	m_view3dsize = -1;
	m_logwndsize = -1;
	m_view3d = 0;
	m_worker = new Worker(this);
	m_editor = new EditorPanel(this ,this, filetype, filename, isnew);		
	m_logwn = new LogPane(this,this );
	m_logwn->SetMinimumSizeY(MIN_LOGWND_Y);
	int ftype = m_editor->GetEdit()->GetFileType();
	if ((ftype == FILETYPE_NC) || (ftype == FILETYPE_GCMC))
	{
		m_view3d = new View3DPanel(this, this);
		m_view3d->SetSashVisible(wxSASH_LEFT, true);
		m_view3d->SetMinimumSizeX(MIN_3DVIEW_X);
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



void FilePage::DoLayout(const wxSize &szin, bool from3d)
{
	wxSize szEditor(wxDefaultSize);
	wxSize szLog(wxDefaultSize);
	wxSize sz3DView(wxDefaultSize);
	szEditor = GetSize();	
	if (szin == wxDefaultSize)
	{
		if (m_view3d && m_view3d->IsShown())
		{
			m_view3d->SetMaximumSizeX(szEditor.x - MIN_EDITOR_X);
			if (m_view3dsize == -1 && szEditor.x > 25)
				m_view3dsize = szEditor.x / 3;
			else
				m_view3dsize = m_view3d->GetSize().x;
			szEditor.x -= m_view3dsize;			
			sz3DView.Set(m_view3dsize, szEditor.y);
			
		}
		
		if ( m_logwn->IsShown() )
		{
			m_logwn->SetMaximumSizeY(szEditor.y - MIN_EDITOR_Y);
			if (m_logwndsize == -1)
				m_logwndsize = szEditor.y / 4;
			else
				m_logwndsize = m_logwn->GetSize().y;
			szEditor.y -= m_logwndsize;
			szLog.Set(szEditor.x, m_logwndsize);
		}
	}
	else if (from3d) // szIn is determined it is 3dView Size
	{
		wxCHECK_RET((m_view3d && m_view3d->IsShown()), "View3D should be shown");
		sz3DView = szin;
		m_view3dsize = szin.x;
		szEditor.x -= sz3DView.x;
		m_view3dsize = sz3DView.x;
		if (m_logwn->IsShown())
		{
			szEditor.y -= m_logwndsize;
			szLog.Set(szEditor.x, m_logwndsize);
		}
	}
	else // szIn is determined it is LogWnd
	{
		wxCHECK_RET((m_logwn->IsShown()), "LogWnd should be shown");
		m_logwndsize = szin.y;
		szEditor.y -= m_logwndsize;
		szEditor.x = m_editor->GetSize().x;
		szLog.x = szEditor.x;
		szLog.y = m_logwndsize;
	}

//Set Sizes
	m_editor->SetSize(0, 0, szEditor.x, szEditor.y);
	if (szLog != wxDefaultSize)
	{
		wxCHECK_RET((m_logwn->IsShown()), "LogWnd should be shown");
		m_logwn->SetSize(0, szEditor.y, szLog.x, szLog.y);
		m_logwn->Layout();
		m_logwn->Refresh();
	}
	if (sz3DView != wxDefaultSize)
	{
		wxCHECK_RET((m_view3d && m_view3d->IsShown()), "View3D should be shown");
		m_view3d->SetSize(szEditor.x, 0, sz3DView.x, sz3DView.y);
		m_view3d->Layout();
		m_view3d->Refresh();
	}
}

void FilePage::OnSashDrag(wxSashEvent& event)
{
	if (event.GetDragStatus() == wxSASH_STATUS_OUT_OF_RANGE)
		return;
// we calculate new size and mark which view should be relayout
	wxRect rcDrag = event.GetDragRect();
	wxSize szClient;
	if ( event.GetId() == ID_3DVIEWWINDOW )
		szClient = wxSize(rcDrag.width, GetSize().GetY());
	else //ID_LOGWINDOW, FilePage::OnSashDrag)
		szClient = wxSize(rcDrag.width, rcDrag.height );
	DoLayout(szClient, event.GetId() == ID_3DVIEWWINDOW );
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
	ShowLog();
	m_worker->Draw3D(false);
	Show3D();
}

bool FilePage::IsModified()
{ 
	return GetEdit()->Modified(); 
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

void FilePage::ConvertGcmc(const wchar_t *src_fname, const  wchar_t *dst_fname, const wchar_t *args, bool addprologepilog)
{
	if (m_worker->IsRunning())
		return;
	ShowLog();
	m_worker->RunGcmc(src_fname, dst_fname, args, ConvertGcmcPasteFile, addprologepilog);
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



void FilePage::UpdatePreferences()
{
	UpdateThemeColor();
	if (m_editor)
	{
		m_editor->UpdatePreferences();
	}
	if (m_view3d)
		m_view3d->UpdatePreferences();
	if (m_logwn)
		m_logwn->UpdatePreferences();
}

void FilePage::UpdateThemeColor()
{
}

void FilePage::ShowLog( )
{
	if (!m_logwn->IsShown())
	{
		m_logwn->Show(true);
		DoLayout();
	}

}

void FilePage::HideLog()
{
	if (m_logwn->IsShown())
	{
		m_logwn->Show(false);
		DoLayout();
	}
}

void FilePage::UpdateStatistics(const ConvertGCMCInfo &dt)
{
	if (m_view3d)
		m_view3d->UpdateStatistics(dt);
}


void FilePage::UpdateSimulationPos(int index, int dist, const TrackPointGL &pt)
{
	if (m_view3d)
		m_view3d->UpdateSimulationPos(index, dist, pt);

	Edit *edit = GetEdit();
	if (edit && edit->GetFileType() == FILETYPE_NC )
	{
		edit->DoSelectLine(pt.line);
	}
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
		wxFileName filename = pedit->GetFileName();
		int rez = wxMessageBox(wxString::Format(_("File %s is not saved!\nSave file before closing?"), filename.GetFullName()),
			_("Save file"),	wxYES_NO | wxCANCEL | wxICON_QUESTION);
		if (rez == wxCANCEL)
			return false;
		else if (rez == wxNO)
			return true;
	}
	// Need save
	if (bSaveAs || pedit->IsNew())
	{
		wxString filename = pedit->GetFileName();
		const LanguageInfo *plang = Preferences::Get()->FindByType(pedit->GetFileType());
		wxString wildCard;
		if ( plang )
			wildCard = plang->CreateWildCard();
		else
			wildCard = _("All Files|*.*");		
		wxFileDialog dlg(this, _("Save file As"), wxEmptyString, filename, wildCard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() != wxID_OK)
			return false;
		filename = dlg.GetPath();
		pedit->SaveFile(filename);
		wxGetApp().GetFrame()->AddFileToHisotyList(filename);
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


void FilePage::DoMathCalc(std::shared_ptr<DoMathBase> mth)
{
	ShowLog();
	m_worker->RunMath(mth);
}

void FilePage::OnShowHideWnd(wxShowEvent& event)
{
	Edit *pedit = GetEdit();
	if (pedit)
		pedit->OnShowHideWnd(event);
}
