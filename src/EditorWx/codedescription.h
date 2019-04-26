#pragma once
#include  <string>
#include  <map>
#include "cmdparser.h"

class CodeDescription
{
public:
	CodeDescription();
	~CodeDescription();
	std::wstring get_description(const char *src, const char *word);
private:
	std::wstring get_g_description(int gc );
	std::wstring get_m_description(int mc );
	std::wstring get_p_description(int cmd);
	bool cpy_close_and_downcase(char *line, const char *src, std::wstring &error);
	std::wstring format(const std::wstring &src);
	std::wstring variable_precision(double val);
private:
	std::map<int, std::wstring> commands;
	Interpreter::CmdParser parser;

};

