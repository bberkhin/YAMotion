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
		case L'X': commands[2001] = c + 1; break;
		case L'S': commands[2002] = c + 1; break;
		case L'F': commands[2003] = c + 1; break;
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
	bool first = true;
	for (int i = 0; i < ModalGroup_Size; ++i)
	{
		if ((gc = parser.getGCode( (GModalGroup)i )) != -1)
		{
			if (!first)
				out += L"\n";
			else 
				first = false;
			out += get_g_description(gc);
			
		}
	}
	const m_container &mcodes = parser.getMCodes();
	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
	{
		if (!first)
			out += L"\n";
		else
			first = false;
		out += get_m_description(*iter);

	}

	if (out.empty())
	{

		bool axis_flag = (parser.hasParam(PARAM_X) || parser.hasParam(PARAM_Y) ||
			parser.hasParam(PARAM_Z) || parser.hasParam(PARAM_A) ||
			parser.hasParam(PARAM_B) || parser.hasParam(PARAM_C));
		if (axis_flag)
		{
			out += get_p_description(2001);
		}
		else if (parser.hasParam(PARAM_S))
		{
			out += get_p_description(2002);
		}
		else if (parser.hasParam(PARAM_F))
		{
			out += get_p_description(2003);
		}


	}
	return out;

}

std::wstring CodeDescription::variable_precision(double val)
{
	std::wstring truncatedNum = std::to_wstring(val);

	// If the conversion ends with a 0, strip the extra parts.
	size_t p2 = truncatedNum.find_last_not_of('0');
	if (std::wstring::npos != p2)
	{
		truncatedNum = truncatedNum.substr(0, p2 + 1);
		// Make sure we're not left with just a decimal point at the end
		size_t decimalPos = truncatedNum.find_last_of('.');
		if (decimalPos == truncatedNum.length() - 1)
		{
			truncatedNum = truncatedNum.substr(0, truncatedNum.length() - 1);
		}
	}
	return truncatedNum;
}

std::wstring CodeDescription::format(const std::wstring &src)
{
	std::wstring out;
	size_t start_pos = 0;
	size_t end_pos;
	size_t npos = static_cast<size_t>(-1);
	IndexParam index;
	double val;
	int ival;
	while((end_pos = src.find_first_of('%', start_pos)) != npos )
	{
		wchar_t item = src.at(end_pos + 1);
		item = ::towupper(item);
		//if ((96 < item) && (item < 123)) item -= 32; //to UPPER
		out += src.substr(start_pos, end_pos - start_pos);
		switch (item)
		{
			case 'A':	index = PARAM_A; break;
			case 'B':	index = PARAM_B; break;
			case 'C':	index = PARAM_C; break;
			case 'X':	index = PARAM_X; break;
			case 'Y':	index = PARAM_Y; break;
			case 'Z':	index = PARAM_Z; break;
				// parameters
			case 'D':   index = PARAM_D; break;
			case 'E':   index = PARAM_E; break;
			case 'F':   index = PARAM_F; break;
			case 'I':   index = PARAM_I; break;
			case 'J':   index = PARAM_J; break;
			case 'K':   index = PARAM_K; break;
			case 'P':   index = PARAM_P; break;
			case 'Q':   index = PARAM_Q; break;
			case 'R':   index = PARAM_R; break;
			case 'S':   index = PARAM_S; break;
			case 'T':   index = PARAM_T;  break;
			case 'U':   index = PARAM_U; break;
			case 'V':   index = PARAM_V; break;
			case 'W':   index = PARAM_W; break;
			case 'H':   index = PARAM_H; break;
			case 'L':   index = PARAM_L; break;
			default:
				index = PARAM_MAX; break;
		}
		if (index < PARAM_MAX_R_PARAM)
		{
			if (parser.getRParam(index, &val))
			{
				out += variable_precision(val);
			}
			else
				out += item;
		}
		else if (index < PARAM_MAX)
		{ 
			if ( parser.getIParam(index, &ival) )
				out += std::to_wstring(ival);
			else
				out += item;
		}
		else // unknown
		{
			out += item;
		}
		
		start_pos  = end_pos + 2; //skeep  %X
	}
	out += src.substr(start_pos);
	return out;
}

std::wstring CodeDescription::get_g_description(int gc)
{
	std::wstring  out(L"G");
	out += std::to_wstring(gc/10);
	out += L": ";
	
	auto iter = commands.find(gc);
	if (iter != commands.end())
		out += format(iter->second);
	else if( !parser.acsept_gcode(gc) )
		out += L"Unknown G Cod";
	return out;
}

std::wstring CodeDescription::get_m_description(int mc )
{
	std::wstring out(L"M");
	out += std::to_wstring(mc);
	out += L": ";
	auto iter = commands.find(1000+mc);
	if (iter != commands.end())
		out += format(iter->second);
	return out;
}

std::wstring CodeDescription::get_p_description(int cmd)
{
	std::wstring out;
	auto iter = commands.find(cmd);
	if (iter != commands.end())
		out += format(iter->second);
	return out;
}
