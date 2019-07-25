#pragma once
#include  <string>
#include  <map>
#include "cmdparser.h"
#include "prefs.h"


class ICodeDescription
{
public:
	virtual ~ICodeDescription() { }
	virtual bool get_description(const char *src, const char *word);
	virtual int file_type() = 0;
	virtual bool IsEmpty() { return m_results.empty(); }
	virtual bool GetFirst(wxString &cmd, wxString &desc);
	virtual bool GetNext(wxString &cmd, wxString &desc);
	virtual wxColor GetKeyColor(const wxString &cmd);
protected:
	typedef std::vector < std::pair<wxString, wxString>> ResultsList;
	ResultsList m_results;
	ResultsList::iterator m_it;
};

class GCodeDescription : public ICodeDescription
{
public:
	GCodeDescription();
	~GCodeDescription();
	virtual bool get_description(const char *src, const char *word);
	virtual int file_type() { return FILETYPE_NC; }
	virtual wxColor GetKeyColor(const wxString &cmd);
private:
	
	void do_get_description(int cm, wchar_t letter = 0, int k = 1);
	void get_p_description(int cmd);
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
	virtual bool get_description(const char *src, const char *word);
	virtual int file_type() { return FILETYPE_GCMC; }
	virtual wxColor GetKeyColor(const wxString &cmd);
private:
	std::map<std::wstring, std::wstring> commands;
};
