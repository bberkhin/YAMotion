#include "wx/wx.h"
#include <string.h>
#include <stdint.h>
#include "codedescription.h"
#include "standartpaths.h"



using namespace Interpreter;

#pragma warning(disable : 4996)

CodeDescription::CodeDescription()
{
	//read description file
	std::filesystem::path name = StandartPaths::Get()->GetResourcesPath(L"code_defs.ini");
	FILE *file = _wfopen(name.c_str(), L"r,ccs=UTF-8");
	if (file == NULL)
		return;

	double d = 0;
	int index = 0;
	wchar_t *c = 0;
	wchar_t line[512];
	int n;
	while (true)
	{
		if( fgetws(line, 512, file) == NULL )
			break;
		line[511] = 0;
		n = wcsnlen(line,512);
		// remove '\n' && '\r'
		if (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
		{
			n--;
			line[n] = 0; 			
			if (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
			{
				line[n - 1] = 0; 
			}
		}

		c = wcschr(line, L'=');
		if (c == NULL)
			continue;
		*c = 0;
		switch (line[0])
		{
		case L'G':
		case L'g':
			d = _wtof(line + 1);
			index = static_cast<int>(d * 10);
			commands[index] = c + 1;
			break;
		case L'M':
		case L'm':
			index = _wtoi(line + 1);
			commands[1000+index] = c + 1;
			break;
		}
	}
	fclose(file);	
}


CodeDescription::~CodeDescription()
{
}

bool CodeDescription::cpy_close_and_downcase(char *line, const char *src, std::wstring &error)  
{
	int m;
	int n;
	bool comment, semicomment;
	char item;
	comment = semicomment = false;
	for (n = 0, m = 0; src[m] != '\0' && src[m] != '\n'; m++)
	{
		item = src[m];
		if (n >= MAX_GCODE_LINELEN - 1)
		{
			error = L"Error: line is very long";
			return false;
		}

		if ((item == ';' || (item == '/' && src[m + 1] == '/')) && !comment)
			semicomment = 1;

		if (semicomment)
		{
			line[n++] = item; // pass literally
			continue;
		}
		else if (comment)
		{
			line[n++] = item;
			if (item == ')')
			{
				comment = 0;
			}
			else if (item == '(')
			{
				error = L"Error: '(' inside comment";
				return false;
			}
		}
		else if ((item == ' ') || (item == '\t') || (item == '\r')) /* don't copy blank or tab or CR */
		{
			;
		}
		else if ((64 < item) && (item < 91))   /* downcase upper case letters */
		{
			line[n++] = (32 + item);
		}
		else if ((item == '(') && !semicomment) {   /* (comment is starting */
			comment = 1;
			line[n++] = item;
		}
		else {
			line[n++] = item;         /* copy anything else */
		}
	}
	if (comment)
	{
		error = L"Error: unclosed comment";
		return false;
	}

	line[n] = 0;

	if (src[m] != '\0' && src[m] == '\n')//need skip long string
	{
		for (; src[m] != '\0' && src[m] != '\n'; m++);
	}

	return true;

}


std::wstring CodeDescription::get_description(const char *src)
{
	
	std::wstring out;
	char line[MAX_GCODE_LINELEN];

	if (!cpy_close_and_downcase(line, src, out))
		return out;
	
	if (!parser.parse(line))
	{
		wxString s( parser.get_state().description.c_str());
		out = s.wc_str();
		return out;
	}


	if (!parser.neead_execute())
	{
		out = L"The string contains nothing to execute";
		return out;
	}


	int gc;
	for (int i = 0; i < ModalGroup_Size; ++i)
	{
		if ((gc = parser.getGCode( (GModalGroup)i )) != -1)
		{
			out += get_g_description(gc);
			out += L"\n";
		}
	}

	const m_container &mcodes = parser.getMCodes();

	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
	{
		out += get_m_description(*iter);
		out += L" ";
	}
	return out;

}



std::wstring CodeDescription::get_g_description(int gc)
{
	std::wstring  out = L"G";
	out += std::to_wstring(gc);
	out += L": ";
	
	auto iter = commands.find(gc);
	if (iter != commands.end())
		out += iter->second;
	else if( !parser.acsept_gcode(gc) )
		out += L"Unknown G Cod";
	return out;
}

std::wstring CodeDescription::get_m_description(int mc )
{
	std::wstring  out;
	auto iter = commands.find(1000+mc);
	if (iter != commands.end())
		out = iter->second;
	return out;

}