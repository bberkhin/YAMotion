#include "wx/wx.h"
#include <wx/textctrl.h>
#include <wx/statline.h>
#include "RotateDlg.h"
#include "flatstaticline.h"

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

#define Y_MARGIN 10
#define X_MARGIN	4
#define MARGIN_COLUMN	10

#define ADD_GRIPPER(margin1,margin2) clientarea->AddSpacer(margin1);\
					pGripper = new FlatStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL); \
					clientarea->Add(pGripper, 0, wxGROW | wxLEFT | wxRIGHT, 0);\
					clientarea->AddSpacer(margin2);

#define ADD_STATICTEXT_TO_GRID(text, pmax) pt = new wxStaticText(this, wxID_ANY, text); \
									if ( pmax ) { *pmax = std::max(*pmax, pt->GetSize().x); } \
									gd->Add(pt, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);

#define ADD_EDITTEXT_TO_GRID(id,text) pedit = new wxTextCtrl(this,id, text); \
									gd->Add(pedit, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL);

RotateDlg::RotateDlg(DoMathRotate *dm, wxWindow *parent, bool hasselection)
	: m_domath(dm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
{
	// sets the application title
	SetTitle(_("Rotate"));

	wxBoxSizer *clientarea = new wxBoxSizer(wxVERTICAL);
	FlatStaticLine *pGripper;
	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
	// Add Parameters
	wxStaticText *pt;
	wxTextCtrl *pedit;
	wxBoxSizer *inputpane;
	int max_width = 0;
	int *pmax_width = &max_width;

	
	// create 2 column flex grid sizer with growable 2nd column
	wxFlexGridSizer *gd = new wxFlexGridSizer(6, wxSize(10, 5));
	//sizer->AddGrowableCol(0);
	ADD_STATICTEXT_TO_GRID(_("Angle (degree): "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_ANGLE, DoubleToString(m_domath->GetAngle()));
	ADD_STATICTEXT_TO_GRID(_("Plane: "), pmax_width);
	int select = 0, i = 0;
	wxChoice *plist = new wxChoice(this, ID_PLANE_CHOISE);
	plist->Append(L"XY");
	plist->Append(L"YZ");
	plist->Append(L"XZ");
	plist->SetSelection(m_domath->GetPlane() - 1);
	gd->Add(plist, 0, wxEXPAND);
	gd->AddSpacer(1); 
	gd->AddSpacer(1);

	ADD_STATICTEXT_TO_GRID(_("Center X: "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_CENTER_X, DoubleToString(m_domath->GetCenter().x));
	ADD_STATICTEXT_TO_GRID(_("Center Y: "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_CENTER_Y, DoubleToString(m_domath->GetCenter().y));
	ADD_STATICTEXT_TO_GRID(_("Center Z: "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_CENTER_Z, DoubleToString(m_domath->GetCenter().z));


	inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);
	inputpane->Add(gd, 0, wxEXPAND);
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, wxEXPAND, wxEXPAND);

	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
	// Add min max
	gd = new wxFlexGridSizer(4, wxSize(10, 0));
	double minv, maxv;
	m_domath->GetMinMax(&minv, &maxv);
	pmax_width = 0;
	ADD_STATICTEXT_TO_GRID(_("Min value: "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_MINVALUE, DoubleToString(minv));
	ADD_STATICTEXT_TO_GRID(_("Max value: "), pmax_width);
	ADD_EDITTEXT_TO_GRID(ID_MAXVALUE, DoubleToString(maxv));
	
	inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);
	inputpane->Add(gd, 0, wxEXPAND);
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, 0, wxEXPAND);
	
	ADD_GRIPPER(Y_MARGIN, Y_MARGIN);
	
	inputpane = new wxBoxSizer(wxHORIZONTAL);
	inputpane->AddSpacer(X_MARGIN);
	wxCheckBox *pinnefile = new wxCheckBox(this, ID_INNEWFILE, _("Create new file"));
	pinnefile->SetValue(m_domath->InNewFile());
	inputpane->Add(pinnefile);
	inputpane->AddSpacer(X_MARGIN * 2);
	wxCheckBox *pinsel = new wxCheckBox(this, ID_INSELECTED, _("In selected"));
	pinsel->SetValue(hasselection ? dm->InSelected() : false);
	pinsel->Enable(hasselection);
	inputpane->Add(pinsel);
	inputpane->AddSpacer(X_MARGIN);
	clientarea->Add(inputpane, 0, wxEXPAND);

	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(clientarea, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
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