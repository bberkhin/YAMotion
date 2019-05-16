#pragma once
#include  <string>
#include  <map>
#include "cmdparser.h"
#include "prefs.h"

class ICodeDescription
{
public:
	virtual ~ICodeDescription() { }
	virtual std::wstring get_description(const char *src, const char *word) = 0;
	virtual int file_type() = 0;
};

class GCodeDescription : public ICodeDescription
{
public:
	GCodeDescription();
	~GCodeDescription();
	std::wstring get_description(const char *src, const char *word);
	virtual int file_type() { return FILETYPE_NC; }
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

class GcmcCodeDescription : public ICodeDescription
{
public:
	GcmcCodeDescription();
	~GcmcCodeDescription();
	std::wstring get_description(const char *src, const char *word);
	virtual int file_type() { return FILETYPE_GCMC; }
private:
	std::map<std::wstring, std::wstring> commands;
};
