//#include "wx/wx.h"
#include "domath.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

#pragma warning(disable:4996)
#include "configdata.h"


using namespace Interpreter;


DoMath::DoMath()
{
	minvalue = -1000000.0;
	maxvalue = 1000000.0;
	LoadConfig();	
}


DoMath::~DoMath()
{
}


void DoMath::LoadConfig()
{
	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) == NULL)	
		return;
	params.clear();

	wxString strKey;
	wxString strval;
	long dummy;
	long val;
	wxString strOldPath = config->GetPath();
	config->SetPath("/DoMath");

	minvalue = config->ReadDouble("MinValue", minvalue);
	maxvalue = config->ReadDouble("MaxValue", maxvalue);
	operation = static_cast<MathOperationType>(config->Read("Operation", static_cast<long>(operation)));
	operand = config->ReadDouble("Operand", operand);	
	
	config->SetPath("/DoMath/Params");
	bool bCont = config->GetFirstEntry(strKey, dummy);
	while (bCont)
	{
		if (config->Read(strKey, &strval))
		{			
			strval.ToLong(&val);
			params.push_back( static_cast<IndexParam>(val));
			bCont = config->GetNextEntry(strKey, dummy);
		}
	}
	config->SetPath(strOldPath);
}

void DoMath::SaveConfig()
{
	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) == NULL)
		return;

	wxString strOldPath = config->GetPath();
	config->SetPath("/DoMath");

	config->Write("MinValue", minvalue);
	config->Write("MaxValue", maxvalue);
	config->Write("Operation", static_cast<long>(operation) );
	config->Write("Operand", operand);
	config->SetPath("/DoMath/Params");

	int n = 1;
	std::for_each(params.begin(), params.end(), [config, &n](IndexParam &p)
	{ config->Write(wxString::Format("Param%d",n), static_cast<int>(p));  ++n; });

	config->SetPath(strOldPath);
}


void DoMath::AddParam(Interpreter::IndexParam param)
{
	params.push_back(param);
}

bool DoMath::Process(const char *strin, char *strout)
{

	const char *line = strin;
	int position = 0;
	int outpos = 0;
	int length = static_cast<int>(strlen(line));
	bool comment = false;
	bool didit = false;
	double valnew, val;
	bool isint;

	
	*strout = 0;
	for (; position < length;)
	{
		if (line[position] == '/' && line[position + 1] == '/')
		{
			strcpy(strout + outpos, line + position);
			break;
		}
		if (line[position] == '(')
		{
			comment = true;
			strout[outpos] = line[position];
			position++; outpos++;
		}
		else if ( comment )
		{			
			strout[outpos] = line[position];
			position++; outpos++;
			if ( line[position] == ')' )
				comment = false;
		}
		else
		{

		//skip spaces
			while (line[position] == ' ' || line[position] == '\t' || line[position] == '\r')
			{
				strout[outpos] = line[position];
				position++; outpos++;
			}
			// check letter
			if ( (position == 0 || !isalpha(line[position-1])) && position + 1 < length && !isalpha(line[position + 1]) && is_param_letter(line[position], &isint) )
			{
				strout[outpos] = line[position];
				position++; outpos++;
				if (read_real(line, position, &val))
				{
					valnew = do_math(val);
					write_result(strout, outpos, valnew, isint);
					didit = true;
				}
			}
			else //just copy
			{
				strout[outpos] = line[position]; 
				position++; outpos++;
			}
		}		
	}
	strout[outpos] = 0;
	return didit;

}


bool DoMath::read_real(const char *line, int &position, double *pdbl)
{
	const char *start = line + position;
	size_t after;

	after = strspn(start, "+-");
	after = strspn(start + after, "0123456789.") + after;

	//size_t len = after - start;
	std::string st(start, after);
	std::stringstream s(st);
	double val;
	if (!(s >> val))
		return false;

	if (s.get() != std::char_traits<char>::eof())
		return false;

	*pdbl = val;
	position = static_cast<int>(start + after - line);
	return true;
}

bool DoMath::is_param_letter(char c, bool *isint)
{
	if ((64 < c) && (c < 91))   /* downcase upper case letters */
		c += 32;
	IndexParam index = PARAM_MAX;
	*isint = false;
	switch (c)
	{
		case 'a':	index = PARAM_A; break;
		case 'b':	index = PARAM_B; break;
		case 'c':	index = PARAM_C; break;
		case 'x':	index = PARAM_X; break;
		case 'y':	index = PARAM_Y; break;
		case 'z':	index = PARAM_Z; break;
		case '@':	index = PARAM_AT; break;
		case 'd':   index = PARAM_D; break;
		case 'e':   index = PARAM_E; break;
		case 'f':   index = PARAM_F; break;
		case 'i':   index = PARAM_I; break;
		case 'j':   index = PARAM_J; break;
		case 'k':   index = PARAM_K; break;
		case 'p':   index = PARAM_P; break;
		case 'q':   index = PARAM_Q; break;
		case 'r':   index = PARAM_R; break;
		case 's':   index = PARAM_S; break;
		case 'u':   index = PARAM_U; break;
		case 'v':   index = PARAM_V; break;
		case 'w':   index = PARAM_W; break;
		case 't':   index = PARAM_T; *isint = true; break;
		case 'h':   index = PARAM_H; *isint = true; break;
		case 'l':   index = PARAM_L; *isint = true; break;
		case 'n':   index = PARAM_N; *isint = true; break;
		default:
			return false;
	}
	return ( std::find(params.begin(), params.end(), index) != params.end() );
}


double DoMath::do_math(double val)
{
	double result;
	switch (operation)
	{
		case MOT_PLUS:      result = operand + val; break;
		case MOT_MINUS:     result = val - operand; break;
		case MOT_DIVIDE:	result = operand == 0.0 ? val : (val/operand); break;
		case MOT_MULTIPLY:  result = val *operand; break;
	}
	result = std::max(result, minvalue);
	result = std::min(result, maxvalue);
	return result;
}

void DoMath::write_result(char *strout, int &outpos, double val, bool isint)
{
	//size_t len = after - start;
	std::string st;
	std::stringstream s(st);
	if (isint)
	{
		if (!(s << static_cast<int>(val)))
			return;
	}
	else
	{
		if (!(s << val))
			return;
	}
	strcpy(strout + outpos, s.str().c_str());
	outpos = static_cast<int>(outpos + s.str().length() );	
}