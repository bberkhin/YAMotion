//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING 1

#include "wx/wx.h"
#include "macrosesdlg.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <string>
#include <string.h>
#include "rapidxml.hpp"

namespace fs = std::filesystem;
using namespace rapidxml;


MacrosesDlg::MacrosesDlg(wxWindow *parent)
	: wxDialog(parent, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		 wxDEFAULT_DIALOG_STYLE )//| wxRESIZE_BORDER) 
{

	// sets the application title
	SetTitle(_("Macroses List"));
	wxString text;

	
	wxListBox *list = new wxListBox(this, wxID_ANY);

	wxStaticBoxSizer *textinfos = new wxStaticBoxSizer(
		new wxStaticBox(this, wxID_ANY, _("Select from the list:")),
		wxVERTICAL);
	
	textinfos->Add(list, 0, wxEXPAND);
	textinfos->Add(0, 6);

	

	// buttons
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* bt;
	bt = new wxButton(this, wxID_OK, "Ok");
	buttonSizer->Add(bt, 0, wxALL, 2);
	bt = new wxButton(this, wxID_CANCEL, "Cancel");
	buttonSizer->Add(bt, 0, wxALL, 2);
	
	// total pane
	wxBoxSizer *totalpane = new wxBoxSizer(wxVERTICAL);
	totalpane->Add(textinfos, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	totalpane->Add(0, 10);
	totalpane->Add(buttonSizer, 0, wxALL | wxALIGN_RIGHT, 2);
	
	InitList(list);
	
	SetSizerAndFit(totalpane);
	ShowModal();

}

MacrosesDlg::~MacrosesDlg()
{
}

void MacrosesDlg::InitList(wxListBox *list)
{
	wxArrayString arrays;
	//arrays.Add(_("Item 1"));
	//arrays.Add(_("Item 2"));
	//arrays.Add(_("штука 3"));
	//arrays.Add(_("Item 4"));
	int pos = 0;
	std::wstring path = L"E:/Projects/YAMotion/src/example/";
	for (const auto & entry : fs::directory_iterator(path))
	{
		if (!entry.is_regular_file())
			continue;
		
		std::wstring wstrcrs = entry.path().filename().c_str();
		std::wstring wstr;
		wstr.resize( wstrcrs.size(), 0);
		std::transform(wstrcrs.begin(), wstrcrs.end(), wstr.begin(), ::towlower);
		size_t n = wstr.find_last_of(L'.');
		if ( (n == std::wstring::npos) || (wstr.compare(n+1,3, L"xml") != 0) )
			continue;
		if ( GetMacrosNames( entry.path().c_str(), arrays) )
		{
			list->InsertItems(arrays, pos);
			pos += arrays.Count();
		}
		arrays.Clear();
	}


	if (pos)
	{
		list->SetSelection(0);
	}
}



bool toWstring(const char *s, std::wstring & out)
{
	int n =  MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	out.resize(n);
	if ( MultiByteToWideChar(CP_UTF8, 0, s, -1, &(out.front()), n) != n)
		return false;
	return true;
}



bool MacrosesDlg::GetMacrosNames(const wchar_t *path, wxArrayString &arrays)
{

	typedef rapidxml::xml_node<char> xml_nodew;
	// Open stream
	FILE *file = _wfopen(path, L"r");
	if (file == NULL)
		return false;
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Load data and add terminating 0
	std::vector<char> data;
	data.resize(size + 1);
	fread(&data.front(), 1, size, file);
	data[size] = 0;
	fclose(file);

	std::wstring out;


	try
	{
		rapidxml::xml_document<char> doc;
		doc.parse<0>(&data.front());		
		xml_nodew *root = doc.first_node("macroses");
		for(xml_nodew *node = root->first_node(); node !=0 ; node = node->next_sibling() )
		{
			if (strcmp(node->name(), "macros") == 0)
			{
				for (xml_nodew *cn = node->first_node(); cn != 0; cn = cn->next_sibling())
				{
					if (strcmp(cn->name(), "name") == 0)
					{
						if (!toWstring(cn->value(), out))
						{
							out = path;
						}
						arrays.Add(out);
						break;
					}
				}
			}
		}
	}
	catch (...)
	{
		return false;
	}
	return true;
}
	



