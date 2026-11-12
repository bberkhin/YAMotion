#pragma once

#include "wx/wx.h"
#include "wx/filename.h" // filename support
#include <wx/stdpaths.h>
#include <string>
#include <filesystem>

#define MACROSES_DIR L"macroses"
#define RESOURCES_DIR L"resources"
#define PREFS_DIR L"preferences"
#define LIBRARY_DIR L"library"

template<typename  Ch> class StandartPathsTm;
typedef StandartPathsTm<wchar_t> StandartPaths;
extern StandartPaths *global_paths;

template<typename  Ch>
class StandartPathsTm
{
public:
	StandartPathsTm() 
	{
		root_path = std::filesystem::current_path();
		// check is preferences is hear
		std::filesystem::path pref = GetPreferencesPath();
		if (!std::filesystem::exists(pref))
		{
			root_path = GetExecutablePath();
			root_path.remove_filename();
			// development layout: the exe is in <repo>\src\x64\Release, the resources are in <repo>
			// so look for the preferences folder in the parents of the exe folder as well
			std::filesystem::path dir = GetExecutablePath().parent_path(); // no trailing separator
			for (int level = 0; level < 5 && !std::filesystem::exists(GetPreferencesPath()) && dir.has_parent_path() && dir != dir.parent_path(); ++level)
			{
				dir = dir.parent_path();
				std::filesystem::path candidate = dir;
				candidate.append(PREFS_DIR);
				if (std::filesystem::exists(candidate))
				{
					root_path = dir;
					break;
				}
			}
		}
	}
	~StandartPathsTm() { }
	static StandartPathsTm<Ch> *Get() { return global_paths; }
	void SetLanguageCatalog(const Ch *lang) { lang_cat = lang;  }
	std::basic_string<Ch> GetLanguageCatalog() { return lang_cat; }
	std::filesystem::path GetRootPath(const Ch *finame = 0) {	return root_path;	}
	std::filesystem::path GetLibraryPath()
	{
		std::filesystem::path  path = GetRootPath();
		path.append(LIBRARY_DIR);
		return path;
	}
	std::filesystem::path GetPreferencesPath(const Ch *finame = 0) 
	{ 
		std::filesystem::path  path = GetRootPath();
		path.append(PREFS_DIR);
		if (finame)
		{
			path.append(finame);
		}
		return path;
	}
	std::filesystem::path GetMacrosPath(const Ch *finame = 0, bool lan_sub_dir = false )
	{
		std::filesystem::path  path  = GetRootPath();
		path.append(MACROSES_DIR);
		if (lan_sub_dir && !lang_cat.empty())
			path.append(lang_cat.c_str());

		if (finame)
		{
			path.append(finame);
		}
		return path;
	}
	std::filesystem::path GetResourcesPath(const Ch *finame )
	{
		std::filesystem::path  path = GetRootPath();
		path.append(RESOURCES_DIR);
		if ( !lang_cat.empty() )
			path.append( lang_cat.c_str() );
		if ( finame )
		{
			path.append(finame);
			if( !lang_cat.empty() && !std::filesystem::exists(path) ) // file not found in lang catalog
			{
				path = GetRootPath();
				path.append(RESOURCES_DIR);
				path.append(finame);
			}
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
//typedef StandartPathsTm<wchar_t> StandartPaths;
//extern StandartPaths global_paths;
