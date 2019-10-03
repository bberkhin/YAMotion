#include "wx/wx.h"
#include <wx/textctrl.h>
#include <wx/statline.h>
#include "RotateDlg.h"

wxString DoubleToString(const double &val);

enum
{
	ID_ANGLE = wxID_HIGHEST,
	ID_CENTER_X,
	ID_CENTER_Y,
	ID_CENTER_Z,
	ID_PLANE_CHOISE,
	ID_MAXVALUE,
	ID_MINVALUE,
	ID_INSELECTED,
	ID_INNEWFILE
};

using namespace Interpreter;

#define MARGIN_VERT 10
#define MARGIN_HOR	4
#define MARGIN_COLUMN	10

RotateDlg::RotateDlg(DoMathRotate *dm, wxWindow *parent, bool hasselection)
	: m_domath(dm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("Rotate"));

	// create 2 column flex grid sizer with growable 2nd column
	wxFlexGridSizer *sizer = new wxFlexGridSizer(2, MARGIN_VERT, MARGIN_HOR);
	sizer->AddGrowableCol(0);
	sizer->Add(new wxStaticText(this, wxID_ANY, _("Angle (degree):")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	wxTextCtrl *pedit = new wxTextCtrl(this, ID_ANGLE, DoubleToString(m_domath->GetAngle()));
	sizer->Add(pedit, 0, wxEXPAND);

	sizer->Add(new wxStaticText(this, wxID_ANY, _("Center X:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	pedit = new wxTextCtrl(this, ID_CENTER_X, DoubleToString(m_domath->GetCenter().x));
	sizer->Add(pedit, 0, wxEXPAND);
	sizer->Add(new wxStaticText(this, wxID_ANY, _("Center Y:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	pedit = new wxTextCtrl(this, ID_CENTER_Y, DoubleToString(m_domath->GetCenter().y));
	sizer->Add(pedit, 0, wxEXPAND);
	sizer->Add(new wxStaticText(this, wxID_ANY, _("Center Z:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	pedit = new wxTextCtrl(this, ID_CENTER_Z, DoubleToString(m_domath->GetCenter().z));
	sizer->Add(pedit, 0, wxEXPAND);

	sizer->Add(new wxStaticText(this, wxID_ANY, _("Plane:")), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	int select = 0, i = 0;
	wxChoice *plist = new wxChoice(this, ID_PLANE_CHOISE);
	plist->Append(L"XY");
	plist->Append(L"YZ");
	plist->Append(L"XZ");
	plist->SetSelection(m_domath->GetPlane() - 1);
	sizer->Add(plist, 0, wxEXPAND);

	
	wxBoxSizer *inputpane = new wxBoxSizer(wxVERTICAL);
	
	double minv, maxv;
	m_domath->GetMinMax(&minv, &maxv);
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Min value:")));
	inputpane->Add(new wxTextCtrl(this, ID_MINVALUE, DoubleToString(minv)));
	inputpane->Add(new wxStaticText(this, wxID_ANY, _("Max value:")));
	inputpane->Add(new wxTextCtrl(this, ID_MAXVALUE, DoubleToString(maxv)));

	inputpane->Add(10, 10);
	inputpane->Add(new wxStaticLine(this), wxSizerFlags().Expand());
	wxCheckBox *pinsel = new wxCheckBox(this, ID_INSELECTED, _("In selected"));
	pinsel->SetValue(hasselection ? dm->InSelected() : false);
	pinsel->Enable(hasselection);
	inputpane->Add(pinsel);

	wxBoxSizer *clientarea = new wxBoxSizer(wxHORIZONTAL);

	clientarea->Add(sizer,0, wxEXPAND);
	clientarea->AddSpacer(MARGIN_COLUMN);
	clientarea->Add(inputpane);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(clientarea, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->AddSpacer(10);
	
	wxCheckBox *pinnefile = new wxCheckBox(this, ID_INNEWFILE, _("Create new file"));
	pinnefile->SetValue( dm->InNewFile() );
	totalpane->Add(pinnefile, 0, wxEXPAND,10 );

	totalpane->AddSpacer(10);
	totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);

	SetSizerAndFit(totalpane);
}


RotateDlg::~RotateDlg()
{
}


bool RotateDlg::GetEditDouble(int id, double *val)
{
	wxWindow *pwnd = FindWindow(id);
	if (pwnd)
	{
		wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(pwnd);
		if (pedit)
		{
			wxString label = pedit->GetValue();
			if (label.ToDouble(val))
				return true;
		}
	}
	return false;

}

int RotateDlg::ShowModal()
{
	double val, minv, maxv;
	int ret = wxDialog::ShowModal();


	if (ret == wxID_OK)
	{
		Interpreter::Coords center = m_domath->GetCenter();
		if (GetEditDouble(ID_ANGLE, &val))
			m_domath->SetAngle(val);

		if (GetEditDouble(ID_CENTER_X, &val))
			center.x = val;
		if (GetEditDouble(ID_CENTER_Y, &val))
			center.y = val;
		if (GetEditDouble(ID_CENTER_Z, &val))
			center.z = val;
		
		m_domath->SetCenter(center);
				
		wxChoice *plist = dynamic_cast<wxChoice *>(FindWindow(ID_PLANE_CHOISE));
		if (plist)
		{
			int n = plist->GetSelection();
			m_domath->SetPlane(Plane(n+1));
		}

		if (GetEditDouble(ID_MINVALUE, &minv) && GetEditDouble(ID_MAXVALUE, &maxv))
			m_domath->SetMinMax(minv, maxv);

		wxCheckBox *pinsel = dynamic_cast<wxCheckBox *>(FindWindow(ID_INSELECTED));
		if (pinsel && pinsel->IsEnabled())
			m_domath->SetSelected(pinsel->GetValue());
		else
			m_domath->SetSelected(false);

		wxCheckBox *pnewfile = dynamic_cast<wxCheckBox *>(FindWindow(ID_INNEWFILE));
		if (pnewfile)
			m_domath->SetInNewFile(pnewfile->GetValue());

		m_domath->SaveConfig();
	}
	return ret;
}