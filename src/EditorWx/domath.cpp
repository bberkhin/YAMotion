#include "domath.h"
#include <iostream>
#include <sstream>
#include <stdio.h>


using namespace Interpreter;
#pragma warning(disable:4996)


DoMath::DoMath()
{
}


DoMath::~DoMath()
{
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
	switch (operation)
	{
	case MOT_PLUS: return operand + val;
	case MOT_MINUS:  return val - operand;
	case MOT_DIVIDE: return operand == 0.0 ? val : (val/operand);
	case MOT_MULTIPLY: return val *operand;
	}
	return val;
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
	
	outpos = static_cast<int>(outpos + st.length() );
	strcat(strout, st.c_str());
}