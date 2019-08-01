#include "wx/wx.h"
#include <wx/textctrl.h>
#include "standartpaths.h"
#include "macrosparamdlg.h"
#include "prefs.h"

#define ID_IN_NEW_WINDOW wxID_HIGHEST+100
#define ID_AS_GCMC_CODE  wxID_HIGHEST+101



wxBEGIN_EVENT_TABLE(MacrosParamDlg, wxDialog)
	EVT_BUTTON(wxID_OK, MacrosParamDlg::OnOk)
wxEND_EVENT_TABLE()

bool MacrosParamDlg::m_new_window = true;
bool MacrosParamDlg::m_as_gcmc = false;

MacrosParamDlg::MacrosParamDlg(MacrosDesc *pm, wxWindow *parent, int curfiletype )
	: mdesc(pm), m_curfiletype(curfiletype), 
	wxDialog(parent, wxID_ANY, wxEmptyString,wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
	{

		// sets the application title
		SetTitle(mdesc->name.c_str());
					
		wxBoxSizer *inputpane = new wxBoxSizer(wxHORIZONTAL);
		
		wxStaticBoxSizer *textinfos = new wxStaticBoxSizer(
			new wxStaticBox(this, wxID_ANY, _("Fill parameters:")),
			wxVERTICAL);

		wxStaticText *Info = new wxStaticText(this, wxID_ANY, pm->desc );
		// create 2 column flex grid sizer with growable 2nd column
		wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 10, 20);
		sizer->AddGrowableCol(0);
		int id_input = wxID_HIGHEST;
		for(auto it = mdesc->args.begin(); it != mdesc->args.end(); ++it )
		{ 
			wxStaticText *prompt = new wxStaticText(this, wxID_ANY, it->name);
			sizer->Add(prompt, 0, 0);
		//	textinfos->Add(0, 6);	
			if (it->type == "list" )
			{
				int select = 0, i = 0;
				wxComboBox *plist = new wxComboBox(this, id_input);
				for (auto itl = it->vars.begin(); itl != it->vars.end(); ++itl, ++i)
				{
					plist->Append(itl->second, (void *)itl->first.c_str() );
					if (it->defval == itl->first)
						select = i;
				}
				plist->SetSelection(select);
				sizer->Add(plist, 0, 0);
			}
			else
			{
				wxTextCtrl *pedit = new wxTextCtrl(this, id_input, it->defval);
				sizer->Add(pedit, 0, 0);
			}
			id_input++;
			//textinfos->Add(0, 6);
		}
		textinfos->Add(sizer, 1, wxALL | wxEXPAND, 10);


		wxCheckBox *pcheck_newwnd = new wxCheckBox(this, ID_IN_NEW_WINDOW, _("Create new window"));

		if (curfiletype == FILETYPE_UNKNOW)
		{
			m_new_window = true;
			pcheck_newwnd->Enable(false);
		}
		pcheck_newwnd->SetValue(m_new_window );
		textinfos->Add(pcheck_newwnd);

		wxCheckBox *pcheck_as_gcmc = new wxCheckBox(this, ID_AS_GCMC_CODE, _("Insert as GCMC"));
		pcheck_as_gcmc->SetValue(m_as_gcmc);
		textinfos->Add(pcheck_as_gcmc);
			   
		textinfos->Add(Info);	
		inputpane->Add(textinfos);

		// add picture
		if (!mdesc->imgfile.empty())
		{
			// check in lang directory
			std::filesystem::path imagepath = StandartPaths::Get()->GetMacrosPath(mdesc->imgfile.c_str(), true);
			if (!std::filesystem::exists(imagepath) )
				imagepath = StandartPaths::Get()->GetMacrosPath(mdesc->imgfile.c_str(), false);
			wxImage image;
			if (image.LoadFile(imagepath.c_str()) )
			{
				wxBitmap bmp(image);
				wxStaticBitmap *pbmpctrl = new wxStaticBitmap(this, wxID_ANY, bmp);
				inputpane->Add(pbmpctrl);
			}
		}
		

		// total pane
		wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
		totalpane->Add(inputpane, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		totalpane->Add(0, 10);
		totalpane->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, 2);

		
		SetSizerAndFit(totalpane);
}


MacrosParamDlg::~MacrosParamDlg()
{
}

bool MacrosParamDlg::GetAndValidateInput()
{
	int id_input = wxID_HIGHEST;
	for (size_t i = 0; i < mdesc->args.size(); ++i)
	{

		wxWindow *pwnd = FindWindow(wxID_HIGHEST + i);
		if (pwnd)
		{
			if (mdesc->args[i].type == "list")
			{
				wxComboBox *plist = dynamic_cast<wxComboBox *>(pwnd);
				int select = plist->GetSelection();
				if (select >= 0)
				{
					mdesc->args[i].val = mdesc->args[i].vars[select].first;
				}
				else
					mdesc->args[i].val = mdesc->args[i].defval;
			}
			else
			{
				wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(pwnd);
				if (pedit)
				{
					wxString label = pedit->GetValue();
					if (mdesc->args[i].type == "scalar")
					{
						label.Replace(",", ".");
						mdesc->args[i].val = label;
					}
					else
						mdesc->args[i].val = label;
				}
				// Save def value
			}
			mdesc->args[i].defval = mdesc->args[i].val;
		}
	}

	wxCheckBox *pcheck_newwnd = dynamic_cast<wxCheckBox *>(FindWindow(ID_IN_NEW_WINDOW));
	m_new_window = pcheck_newwnd->GetValue();
	wxCheckBox *pcheck_as_gcmc = dynamic_cast<wxCheckBox *>(FindWindow(ID_AS_GCMC_CODE));
	m_as_gcmc = pcheck_as_gcmc->GetValue();

	if (m_as_gcmc && !m_new_window && (m_curfiletype == FILETYPE_NC))
	{
		wxMessageBox(_("Can not insert GCMC code to GCODE file!"),wxMessageBoxCaptionStr, wxOK | wxICON_INFORMATION);
		return false;
	}
	else if (!m_as_gcmc && !m_new_window && (m_curfiletype == FILETYPE_GCMC))
	{
		wxMessageBox(_("Can not insert GCODE to GCMC file!"), wxMessageBoxCaptionStr, wxOK | wxICON_INFORMATION);
		return false;
	}
	return true;
}


void MacrosParamDlg::OnOk(wxCommandEvent& WXUNUSED(event))
{
	if ( GetAndValidateInput() )
		EndModal(wxID_OK);
}

