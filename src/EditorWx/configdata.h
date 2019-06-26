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
	void WriteFindAndReplase(wxFindReplaceData *find_data);
	void ReadFindAndReplase(wxFindReplaceData *find_data);
	void AddFileNameToSaveList(const wxFileName &fname);
	void ReadFileNames();
	void WriteFileNames();
	const FileNamesList &GetFiles() { return files; }
	bool IsFirstTimeRun();
	int GetLanguage(int deflang);
	void SetLanguage(int lang);
private:
	FileNamesList files;	
};

