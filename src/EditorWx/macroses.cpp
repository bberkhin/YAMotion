#include "wx/wx.h"
#include "macroses.h"
#include "standartpaths.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <string>
#include <map>
#include <string.h>


namespace fs = std::filesystem;
using namespace rapidxml;

static bool toWstring(const char *s, std::wstring & out)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	out.resize(n-1);
	if (n <= 1) // empty string
	{
		out.clear();
		return true;
	}
	if (MultiByteToWideChar(CP_UTF8, 0, s, -1, &(out.front()), n) != n)
		return false;
	return true;
}

static bool toMBstring(const wchar_t *s, std::string & out)
{
	int n = WideCharToMultiByte(CP_OEMCP, 0, s, -1, 0, 0, 0, 0);
	out.resize(n-1);
	if (n <= 1) // empty string
	{
		out.clear();
		return true;
	}
	if (WideCharToMultiByte(CP_OEMCP, 0, s, -1, &(out.front()), n, 0, 0) != n)
		return false;
	return true;
}

Macroses::Macroses()
{
	Init();
}


Macroses::~Macroses()
{
}

static void scan_xml_files(const std::filesystem::path &dirpath, std::map<std::wstring, std::filesystem::path> &namesList)
{
	std::filesystem::path ext(L".xml");
	for (const auto & entry : fs::directory_iterator(dirpath))
	{
		if (!entry.is_regular_file())
			continue;
		std::filesystem::path path = entry.path();
		if (path.extension() == ext)
		{
			namesList[path.filename()] = path;
		}
	}
}

void Macroses::Init()
{
	std::map<std::wstring, std::filesystem::path> namesList;
	std::string errmsg;
	m_mcrs.clear();
	try
	{
		std::filesystem::path dirpath = StandartPaths::Get()->GetMacrosPath();
		scan_xml_files(dirpath, namesList);
		/*
		std::filesystem::path dirpathLan = StandartPaths::Get()->GetMacrosPath(0, true);
		if ((dirpathLan != dirpath) && std::filesystem::exists(dirpathLan) )
		{
			scan_xml_files(dirpathLan, namesList); // rewrite def xml by language specific xml
		}
		*/
		// read macroses from files
		for (const auto & entry : namesList )
		{
			parse_file(entry.second.c_str());
		}
	}
	catch (std::exception &e)
	{
		errmsg = e.what();
	}
	catch (...)
	{
		errmsg = "Uncknown exeption parsing file";
	}
	if( !errmsg.empty() )
		wxMessageBox(errmsg.c_str(), _("Close abort"), wxOK | wxICON_EXCLAMATION);

}



void Macroses::read_raw_data(const wchar_t *path, std::vector<char> &data)
{

	FILE *file = _wfopen(path, L"r");
	if (file == NULL)
	{
		std::string errmsg("Can not open file: ");
		std::string path1;
		toMBstring(path, path1);
		errmsg += path1;
		throw std::exception(errmsg.c_str());
	}
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Load data and add terminating 0
	data.resize(size + 1);
	fread(&data.front(), 1, size, file);
	data[size] = 0;
	fclose(file);
}




void Macroses::parse_file(const wchar_t *path)
{

	std::vector<char> data;
	read_raw_data(path, data);
	if (data.size() == 0)
		throw std::exception("Empty macros file");
	rapidxml::xml_document<char> doc;
	doc.parse<0>(&data.front());
	
	std::string catalog;
	toMBstring(StandartPaths::Get()->GetLanguageCatalog().c_str(), catalog);
	std::string nameid("name");
	std::string descid("desc");
	if (!catalog.empty())
	{
		catalog = "_"+ catalog;
		nameid += catalog;
		descid += catalog;
	}


	xml_nodew *root = doc.first_node("macroses");
	for (xml_nodew *node = root->first_node(); node != 0; node = node->next_sibling())
	{
		if (strcmp(node->name(), "macros") == 0)
		{

			MacrosDesc mdesc;
			for (xml_nodew *cn = node->first_node(); cn != 0; cn = cn->next_sibling())
			{
				if (strcmp(cn->name(), "name") == 0)
				{
					toWstring(cn->value(), mdesc.name);
				}
				else if(!catalog.empty() && (strcmp(cn->name(), nameid.c_str() ) == 0) )
				{
					toWstring(cn->value(), mdesc.name);
				}
				else if (strcmp(cn->name(), "desc") == 0)
				{
					toWstring(cn->value(), mdesc.desc);
				}
				else if (!catalog.empty() && (strcmp(cn->name(), descid.c_str()) == 0))
				{
					toWstring(cn->value(), mdesc.desc);
				}
				else if (strcmp(cn->name(), "gcmc") == 0)
				{
					toWstring(cn->value(), mdesc.gcmcfile);
				}
				else if (strcmp(cn->name(), "image") == 0)
				{
					toWstring(cn->value(), mdesc.imgfile);
				}		
				else if (strcmp(cn->name(), "arguments") == 0)
				{
					read_arguments(cn, mdesc, catalog);
				}
				else if(strcmp(cn->name(), "include") == 0)
				{
					toWstring(cn->value(), mdesc.inc_file);
				}
				else if (strcmp(cn->name(), "function") == 0)
				{
					toWstring(cn->value(), mdesc.funct);
				}
			}
			m_mcrs.push_back(mdesc);
		}
	}

}



void Macroses::read_arguments(xml_nodew *node, MacrosDesc &mdesc, const std::string &catalog)
{
	std::string nameid("name");
	std::string descid("desc");
	if (!catalog.empty())
	{
		nameid += catalog;
		descid += catalog;
	}

	for (xml_nodew *cn = node->first_node(); cn != 0; cn = cn->next_sibling())
	{
		if (strcmp(cn->name(), "argument") == 0)
		{
			// read attributes
			ArgumentDesc atr;
			std::string ref;
			for (rapidxml::xml_attribute<char> *pattr = cn->first_attribute(); pattr != 0; pattr = pattr->next_attribute())
			{
				if (strcmp(pattr->name(), "defvalue") == 0)
					atr.defval = pattr->value();
				else if (strcmp(pattr->name(), "type") == 0)
					atr.type = pattr->value();
				else if (strcmp(pattr->name(), "ref") == 0)
					atr.ref = pattr->value();//to do 
			}
			for (xml_nodew *cna = cn->first_node(); cna != 0; cna = cna->next_sibling())
			{
				if (strcmp(cna->name(), "name") == 0)
				{
					toWstring(cna->value(), atr.name);
				}
				else if (!catalog.empty() && (strcmp(cna->name(), nameid.c_str()) == 0))
				{
					toWstring(cna->value(), atr.name);
				}
				else if (strcmp(cna->name(), "desc") == 0)
				{
					toWstring(cna->value(), atr.desc);
				}
				else if (!catalog.empty() && (strcmp(cna->name(), descid.c_str()) == 0))
				{
					toWstring(cna->value(), atr.desc);
				}
				else if (strcmp(cna->name(), "list") == 0)
				{
					std::string val;
					std::wstring name;
					for (rapidxml::xml_attribute<char> *pattr = cna->first_attribute(); pattr != 0; pattr = pattr->next_attribute())
					{
						if (strcmp(pattr->name(), "value") == 0)
							val = pattr->value();
						else if (strcmp(pattr->name(), "name") == 0)
							toWstring(pattr->value(), name);
						else if( !catalog.empty() && (strcmp(pattr->name(), nameid.c_str()) == 0) )
							toWstring(pattr->value(), name);
					}
					atr.vars.push_back(std::make_pair(val,name));
				}

				
			}
			mdesc.args.push_back(atr);
		}
	}
		
}

std::wstring Macroses::BuildGCMCCode(int indx, std::wstring &include_file, bool &needGcmcFileBody)
{
	std::wstring arg;
	std::wstring tmp;
	MacrosDesc &mdesc = Get(indx);
	
	include_file = mdesc.inc_file;
	for (auto it = mdesc.args.begin(); it != mdesc.args.end(); ++it)
	{
		toWstring(it->ref.c_str(), tmp);
		arg += tmp;
		arg += L"=";
		if (it->val.empty())
			toWstring(it->defval.c_str(), tmp);
		else
			toWstring(it->val.c_str(), tmp);
		arg += tmp;
		arg += L"; //";  // add comment
		if ( it->desc.empty() )
			arg += it->name; 
		else
			arg += it->desc;
		arg += L"\n";
	}
	arg += L"\n";
	if (!mdesc.funct.empty())
	{
		arg += mdesc.funct;
		arg += L";\n";
		needGcmcFileBody = false;
	}
	else
	{
		needGcmcFileBody = true;
	}
	return arg;
}

std::wstring Macroses::BuildCommandLine(int indx)
{
	std::wstring arg;
	std::wstring tmp;
	MacrosDesc &mdesc = Get(indx);
	//std::pair<std::string, ArgumntDesc> itt;
	//itt.first
	arg += L" --define=\"";
	for (auto it = mdesc.args.begin(); it != mdesc.args.end(); ++it)
	{
		toWstring(it->ref.c_str(),tmp);
		arg += tmp;
		arg += L"=";
		if ( it->val.empty() )
			toWstring(it->defval.c_str(), tmp);
		else
			toWstring(it->val.c_str(), tmp);
		arg += tmp;
		arg += L";";
	}
	arg += L"\"";
	return arg;
}