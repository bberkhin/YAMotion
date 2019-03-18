#include "configdata.h"
#include "appdefs.h"
#include <wx/fdrepdlg.h>


ConfigData::ConfigData() : wxFileConfig(APP_NAME)
{
}


ConfigData::~ConfigData()
{
}

void ConfigData::WriteFindAndReplase(wxFindReplaceData *find_data)
{
	wxString strOldPath = GetPath();
	SetPath("/YAMOTION/Find");	
	Write("Find", find_data->GetFindString());
	Write("Replace", find_data->GetReplaceString());
	Write("Flag", find_data->GetFlags());	
	SetPath(strOldPath);
}

void ConfigData::ReadFindAndReplase(wxFindReplaceData *find_data)
{
	wxString strOldPath = GetPath();
	SetPath("/YAMOTION/Find");
	find_data->SetFindString( Read("Find", wxEmptyString ));
	find_data->SetReplaceString( Read("Replace", wxEmptyString));
	int flag;
	if( Read("Flag",&flag ) )
		find_data->SetFlags(flag);
	SetPath(strOldPath);
}


void ConfigData::AddFileNameToSaveList(const wxString &fname)
{
	auto it = std::find(files.begin(), files.end(), fname);
	if (it != files.end())
		files.erase(it);
	files.push_front(fname);
}


void ConfigData::WriteFileNames()
{
	wxString strOldPath = GetPath();
	SetPath("/YAMOTION/Files");
	int n = 1;
	for (auto it = files.begin(); it != files.end() && n <= 9; ++it, n++)
	{
		Write(wxString::Format("File%d",n), *it );
	}
	SetPath(strOldPath);
}

void ConfigData::ReadFileNames()
{
	wxString strOldPath = GetPath();
	SetPath("/YAMOTION/Files");
	files.clear();
	wxString strKey;
	wxString strfname;
	long dummy;
	// first enum all entries
	bool bCont = GetFirstEntry(strKey, dummy);
	while (bCont)
	{
		if (Read(strKey, &strfname) )
		{
			files.push_back(strfname);
			bCont = GetNextEntry(strKey, dummy);
		}
	}
	SetPath(strOldPath);
}

