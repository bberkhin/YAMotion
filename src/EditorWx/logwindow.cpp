#include "wx/wx.h"
#include "logwindow.h"
#include "defsext.h"


wxBEGIN_EVENT_TABLE(LogWindow, wxSimpleHtmlListBox)

EVT_LISTBOX(wxID_ANY, LogWindow::OnLboxSelect)
EVT_LISTBOX_DCLICK(wxID_ANY, LogWindow::OnLboxDClick)
EVT_KEY_DOWN(LogWindow::OnKeyDown)

wxEND_EVENT_TABLE()

LogWindow::LogWindow(wxWindow *parent, wxEvtHandler *_handler, wxWindowID id )
	: handler(_handler) , wxSimpleHtmlListBox(parent, id, wxDefaultPosition, wxDefaultSize,
		0, NULL, 0)
{
	SetClientDataType(wxClientData_Object);
}


LogWindow::~LogWindow()
{
}

void LogWindow::Append(MsgStatusLevel lvl, const wchar_t *str, int linen, bool update )
{
	wxString label = L"<font color=";
	switch (lvl)
	{
		case MSLError: label += L"#880000> Error! "; break;
		case MSLFileStatus: label += L"#008888>"; break;
		case MSLInfo: label += L"#008800>"; break;
		case MSLUndefened: label += L"#000000>"; break;
		case MSLWarning: label += L"#000088>Warning! "; break;	
	}
	if (linen > 0)
	{
		label += ::wxString::Format("Line %d: ", linen);
	}
	label += str;
	label += L"</font>";
	IntClientData *data = new IntClientData(linen);
	wxSimpleHtmlListBox::Append(label,data);
	if (update)
		Update();
}



void LogWindow::OnLboxSelect(wxCommandEvent& event)
{
	//wxSimpleHtmlListBox::Append(L"OnLboxSelect");
}

void LogWindow::OnLboxDClick(wxCommandEvent& event)
{
	DoSinchronize();
}

void LogWindow::DoSinchronize()
{
	//Move to indows line
	int n = GetSelection();
	if (n < 0 || n >= (int)GetCount())
		return;
	IntClientData *data = dynamic_cast<IntClientData *>(GetClientObject(n));
	if (data == NULL || data->GetData() <= 0 )
		return;

	IntClientData *dataCmd = data;// new IntClientData(data->GetData());
	wxCommandEvent *ev = new wxCommandEvent(wxEVT_MENU,myID_SELECTLINE);
	ev->SetClientObject(dataCmd);
	wxQueueEvent(handler, ev);
}

void LogWindow::Clear()
{
	wxItemContainer::Clear();
	SetClientDataType(wxClientData_Object);
}


void LogWindow::OnKeyDown(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_RETURN )
		DoSinchronize();	
	event.Skip();
}