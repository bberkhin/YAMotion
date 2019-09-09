#pragma once
#include <wx/config.h>
#include "wx/fileconf.h"
#include <list>

class wxFindReplaceData;
typedef std::list<wxFileName> FileNamesList;


class ConfigData :	public wxFileConfig
{
public:
	ConfigData();
	~ConfigData();
	void AddFileNameToSaveList(const wxFileName &fname);
	void RemoveFileNameFromSaveList(const wxFileName &fname);
	const FileNamesList &GetFiles() { return files; }
	bool IsFirstTimeRun();
	int GetLanguage(int deflang);
	void SetLanguage(int lang);
	int GetViewStyle() { return m_viewstyle; };
	void SetViewStyle(int style) { m_viewstyle = style; };
	void GetFindAndReplase(wxFindReplaceData *find_data);
	void SetFindAndReplase(wxFindReplaceData *find_data);
private:
	void WriteFindAndReplase(wxFindReplaceData *find_data);
	void ReadFindAndReplase(wxFindReplaceData *find_data);
	void DoLoadOptions();
	void DoSaveOptions();
	void ReadFileNames();
	void WriteFileNames();

private:
	FileNamesList files;
	int m_viewstyle;
	wxFindReplaceData *m_find_data;
};

