#pragma once

#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include <wx/stdpaths.h>
#include <string>
#include <filesystem>

#define MACROSES_DIR L"macroses"
#define RESOURCES_DIR L"resources"

template<typename  Ch> class StandartPathsTm;
typedef StandartPathsTm<wchar_t> StandartPaths;
extern StandartPaths global_paths;

template<typename  Ch>
class StandartPathsTm
{
public:
	StandartPathsTm() {		root_path = std::filesystem::current_path(); }
	~StandartPathsTm() { }
	static StandartPathsTm<Ch> *Get() { return &global_paths; }
	void SetLanguageCatalog(const Ch *lang) { lang_cat = lang;  }
	std::filesystem::path GetRootPath(const Ch *finame = 0) {	return root_path;	}
	std::filesystem::path GetMacrosPath(const Ch *finame = 0)
	{
		std::filesystem::path  path  = GetRootPath();
		path.append(MACROSES_DIR);
		if (finame)
		{
			path.append(finame);
		}
		return path;
	}
	std::filesystem::path GetResourcesPath(const Ch *finame = 0)
	{
		std::filesystem::path  path = GetRootPath();
		path.append(RESOURCES_DIR);
		if ( !lang_cat.empty() )
			path.append( lang_cat.c_str() );
		if (finame)
		{
			path.append(finame);
		}
		return path;
	}
	std::filesystem::path GetExecutablePath(const Ch *finame = 0)
	{
		std::filesystem::path path  = wxStandardPaths::Get().GetExecutablePath().wc_str();
		if (finame)
		{
			path.replace_filename(finame);
		}
		return path;
	}

	std::filesystem::path GetTemporaryPath(const Ch *finame = 0)
	{
		std::filesystem::path path = std::filesystem::temp_directory_path();
		//std::filesystem::path  path = GetRootPath();
		if (finame)
		{
			path.append(finame);
		}
		return path;
	}

	bool CheckFileExist(const Ch *finame)
	{
		std::filesystem::path p(finame);
		if (std::filesystem::exists(p))
			return true;
		return false;
	}
	std::filesystem::path GetDirFromFName(const Ch *buf)
	{
		std::filesystem::path path(buf);
		path.replace_filename(L"");
		return path;
	}
private:
	std::filesystem::path root_path;
	std::basic_string<Ch> lang_cat;
};

//for win
typedef StandartPathsTm<wchar_t> StandartPaths;
extern StandartPaths global_paths;


//template<typename  Ch>
//inline static StandartPathsTm<Ch> *Get() {	return &global_paths; }