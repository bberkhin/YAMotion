#pragma once
#include <string>
#include <vector>
#include <map>
#include "rapidxml.hpp"

typedef std::vector<std::pair<std::string, std::wstring>> VariantsList;
struct ArgumentDesc
{
	std::string ref;
	std::wstring name;
	std::wstring desc;
	std::string defval;
	std::string type;
	std::string val;
	VariantsList vars;
};

typedef std::vector<ArgumentDesc> ArgumentMap;
struct MacrosDesc
{
	std::wstring name;
	std::wstring desc;
	std::wstring gcmcfile;
	std::wstring imgfile;
	std::wstring funct;
	std::wstring inc_file;
	ArgumentMap args;
	
};

typedef rapidxml::xml_node<char> xml_nodew;
typedef rapidxml::xml_attribute<char> xml_attribute;

class Macroses
{
public:
	Macroses();
	~Macroses();
	int Count() { return m_mcrs.size(); }
	MacrosDesc &Get(int index) { return m_mcrs[index];  }
	std::wstring BuildGCMCCode(int indx, std::wstring &include_file);
	std::wstring BuildCommandLine(int indx);
	void Init();
private:
	void parse_file(const wchar_t *path);
	void read_raw_data(const wchar_t *path, std::vector<char> &data);
	void read_arguments(xml_nodew *node, MacrosDesc &mdesc);
private:
	std::vector<MacrosDesc> m_mcrs;
};

