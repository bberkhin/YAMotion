#include <wx/wx.h>


class editor_cnc : public wxApp
{
public:
	bool OnInit();
};


bool editor_cnc::OnInit()
{
	wxFrame * m_frame = new wxFrame(NULL, -1, "hi there");
	m_frame->Show(true);
	return true;
}

IMPLEMENT_APP(editor_cnc);

