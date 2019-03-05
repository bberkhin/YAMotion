#pragma once
#include  <string>
#include  <map>
#include "cmdparser.h"

class CodeDescription
{
public:
	CodeDescription();
	~CodeDescription();
	std::wstring get_description(const char *src);
private:
	std::wstring get_g_description(int gc );
	std::wstring get_m_description(int mc );
	bool cpy_close_and_downcase(char *line, const char *src, std::wstring &error);
private:
	std::map<int, std::wstring> commands;
	Interpreter::CmdParser parser;

};

