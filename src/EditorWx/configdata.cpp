#include "configdata.h"
#include "appdefs.h"
//#include "view3d.h" // for VSTYLE_XXXXXXXXXX

#include <wx/fdrepdlg.h>

#define DEFAULT_THEME_ID "BLACK"

ConfigData::ConfigData() : wxFileConfig(APP_NAME)
{
	m_viewstyle = 0x001;
	m_find_data = new wxFindReplaceData();
	m_themeid = DEFAULT_THEME_ID;
	DoLoadOptions();
}


ConfigData::~ConfigData()
{
	DoSaveOptions();
	delete m_find_data;
}

void ConfigData::DoSaveOptions()
{
	WriteFindAndReplase(m_find_data);
	WriteFileNames();
	// Save view 3d
	wxString strOldPath = GetPath();
	SetPath(L"/GLView");
	Write(L"3DStyle", m_viewstyle);
	SetPath(strOldPath);	
}

void ConfigData::DoLoadOptions()
{
	SetPath("/YAMOTION");
	m_themeid = Read("Theme", DEFAULT_THEME_ID);

	ReadFindAndReplase(m_find_data);
	ReadFileNames();
	// load view 3d
	wxString strOldPath = GetPath();
	SetPath(L"/GLView");
	Read(L"3DStyle", &m_viewstyle, m_viewstyle);
	SetPath(strOldPath);
}

bool ConfigData::IsFirstTimeRun()
{
	SetPath("/YAMOTION");
	return !HasEntry("Language");
}
int ConfigData::GetLanguage(int deflang)
{
	SetPath("/YAMOTION");
	return static_cast<int>(ReadLong("Language", deflang ));
}

void ConfigData::SetLanguage(int lang)
{
	SetPath("/YAMOTION");
	Write("Language", lang);
}

void ConfigData::SetTheme(const wxString &theme)
{
	SetPath("/YAMOTION");
	if (theme.empty())
		m_themeid = DEFAULT_THEME_ID;
	else
		m_themeid = theme;

	Write("Theme", m_themeid);
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


void ConfigData::AddFileNameToSaveList(const wxFileName &fname)
{
	RemoveFileNameFromSaveList(fname);
	files.push_front(fname);
}
void ConfigData::RemoveFileNameFromSaveList(const wxFileName &fname)
{
	auto it = std::find(files.begin(), files.end(), fname);
	if (it != files.end())
		files.erase(it);
}


void ConfigData::WriteFileNames()
{
	wxString strOldPath = GetPath();
	SetPath("/YAMOTION/Files");
	int n = 1;
	for (auto it = files.begin(); it != files.end() && n <= 9; ++it, n++)
	{
		Write(wxString::Format("File%d",n), it->GetFullPath() );
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

void ConfigData::GetFindAndReplase(wxFindReplaceData *find_data)
{
	*find_data = *m_find_data;
}
void ConfigData::SetFindAndReplase(wxFindReplaceData *find_data)
{
	 *m_find_data = *find_data;
}


