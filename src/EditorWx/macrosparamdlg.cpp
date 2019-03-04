#include "wx/wx.h"
#include <wx/textctrl.h>
#include "standartpaths.h"
#include "macrosparamdlg.h"




MacrosParamDlg::MacrosParamDlg(MacrosDesc *pm, wxWindow *parent)
	: mdesc(pm), wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxDEFAULT_DIALOG_STYLE)//| wxRESIZE_BORDER) 
	{

		// sets the application title
		SetTitle(_("Macros Parameter"));
		
		
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

			wxTextCtrl *pedit = new wxTextCtrl(this, id_input , it->defval);
			id_input++;
			sizer->Add(pedit, 0, 0);
			//textinfos->Add(0, 6);
		}
		textinfos->Add(sizer, 1, wxALL | wxEXPAND, 10);
		textinfos->Add(Info);	
		inputpane->Add(textinfos);

		// add picture
		if (!mdesc->imgfile.empty())
		{
			wxString imageFile = StandartPaths::Get()->GetMacrosPath(mdesc->imgfile.c_str()).c_str();
			wxImage image;
			if (image.LoadFile(imageFile))
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

int MacrosParamDlg::ShowModal()
{
	int ret = wxDialog::ShowModal();
	if (ret == wxID_OK)
	{

		int id_input = wxID_HIGHEST;
		for (size_t i = 0; i < mdesc->args.size(); ++i)
		{
			
			wxWindow *pwnd = FindWindow(wxID_HIGHEST + i);
			if (pwnd)
			{
				wxTextCtrl *pedit = dynamic_cast<wxTextCtrl *>(pwnd);
				if (pedit)
				{
					wxString label = pedit->GetValue();
					mdesc->args[i].val = label;
				}
			}
		}
	}
	return ret;

}
