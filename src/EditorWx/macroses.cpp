#include "wx/wx.h"
#include "macroses.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <string>
#include <string.h>


namespace fs = std::filesystem;
using namespace rapidxml;

static bool toWstring(const char *s, std::wstring & out)
{
	int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
	out.resize(n-1);
	if (MultiByteToWideChar(CP_UTF8, 0, s, -1, &(out.front()), n) != n)
		return false;
	return true;
}

static bool toMBstring(const wchar_t *s, std::string & out)
{
	int n = WideCharToMultiByte(CP_OEMCP, 0, s, -1, 0, 0, 0, 0);
	out.resize(n-1);
	if (WideCharToMultiByte(CP_OEMCP, 0, s, -1, &(out.front()), n, 0, 0) != n)
		return false;
	return true;
}

Macroses::Macroses()
{
}


Macroses::~Macroses()
{
}


void Macroses::parse_dir(const wchar_t *dirpath, bool fast)
{

	mcrs.clear();
	std::string errmsg;
	try
	{

		for (const auto & entry : fs::directory_iterator(dirpath))
		{
			if (!entry.is_regular_file())
				continue;

			std::wstring wstrcrs = entry.path().filename().c_str();
			std::wstring wstr;
			wstr.resize(wstrcrs.size(), 0);
			std::transform(wstrcrs.begin(), wstrcrs.end(), wstr.begin(), ::towlower);
			size_t n = wstr.find_last_of(L'.');

			if ((n == std::wstring::npos) || (wstr.compare(n + 1, 3, L"xml") != 0))
				continue;

			parse_file(entry.path().c_str(), fast);
		}
		return;
	}
	catch (std::exception &e)
	{
		errmsg = e.what();
	}
	catch (...)
	{
		errmsg = "Uncknown exeption parsing file";
	}
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




void Macroses::parse_file(const wchar_t *path, bool fast)
{

	std::vector<char> data;
	read_raw_data(path, data);
	if (data.size() == 0)
		throw std::exception("Empty macros file");
	rapidxml::xml_document<char> doc;
	doc.parse<0>(&data.front());
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
				else if (strcmp(cn->name(), "desc") == 0)
				{
					toWstring(cn->value(), mdesc.desc);
				}
				else if (strcmp(cn->name(), "gcmc") == 0)
				{
					toWstring(cn->value(), mdesc.gcmcfile);
				}
				
				else if (strcmp(cn->name(), "arguments") == 0)
				{
					read_arguments(cn, mdesc);
				}
			}
			mcrs.push_back(mdesc);
		}
	}

}



void Macroses::read_arguments(xml_nodew *node, MacrosDesc &mdesc)
{
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
					;//to do 
				else if (strcmp(pattr->name(), "ref") == 0)
					atr.ref = pattr->value();//to do 
			}
			for (xml_nodew *cna = cn->first_node(); cna != 0; cna = cna->next_sibling())
			{
				if (strcmp(cna->name(), "name") == 0)
				{
					toWstring(cna->value(), atr.name);
				}
				else if (strcmp(cna->name(), "desc") == 0)
				{
					toWstring(cna->value(), atr.desc);
				}
			}
			mdesc.args.push_back(atr);
		}
	}
		
}

std::wstring Macroses::build_commad_line(int indx)
{
	std::wstring arg;
	std::wstring tmp;
	MacrosDesc &mdesc = get(indx);
	//std::pair<std::string, ArgumntDesc> itt;
	//itt.first
	arg = L" --define=\"";
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