#include "GCodeInterpreter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>

using namespace Interpreter;

#pragma warning(disable:4996)

CmdParser::CmdParser()
{
}

//====================================================================================================
//читает данные из строки в массив
bool  CmdParser::parse(const char *frame)
{
	// Clear data
	IF_F_RET_F(init());
	IF_F_RET_F(parse_codes(frame) );
	IF_F_RET_F(check_modal_group()); //проверяем что в одной строке нет команд одной группы
	return true;
}




// Clear data
bool  CmdParser::init()
{
	// Clear data
	for (int i = 0; i < PARAM_MAX; ++i)
		params[i].reset();

	n_number = -1;
	comment.clear();
	line = 0;
	position = 0;
	state = InterError();
	return true;
}



bool  CmdParser::parse_codes(const char *frame )
{
	line = frame;
	position = 0;

	//int m9899 = 0, mcounter;  // for checking m98/m99 as o-words
	int length;

	length = strlen(line);

	if (line[position] == '/')     /* skip the slash character if first */
		position++;

	if (line[position] == 'N')
	{
		IF_F_RET_F(read_n_number());
	}

	//// Pre-check for M code, used in following logic
	//if (!(line[counter] == 'M' &&
	//	read_integer_value(line, &(m_counter = counter + 1), &m_number,
	//		parameters) == INTERP_OK))
	//	m_number = -1;

	//if (line[counter] == 'o' || m_number == 98 ||
	//	(m_number == 99 && _setup.call_level > 0))

	//	/* Handle 'o', 'm98' and 'm99' sub return (but not 'm99' endless
	//	   program) explicitly here. Default is to read letters via pointer
	//	   calls to related reader functions. 'o' control lines have their
	//	   own commands and command handlers. */
	//{
	//	CHP(read_o(line, &counter, block, parameters));

	//	// if skipping, the conditionals are not evaluated and are therefore unconsumed
	//	// so we can't check the rest of the line.  but don't worry, we'll get it later
	//	if (_setup.skipping_o) return INTERP_OK;

	//	// after if [...], etc., nothing is allowed except comments
	//	for (; counter < length;) {
	//		if (line[counter] == ';') read_semicolon(line, &counter, block, parameters);
	//		else if (line[counter] == '(') read_comment(line, &counter, block, parameters);
	//		else ERS("Unexpected character after O-word");
	//	}
	//	return INTERP_OK;
	//}

	// non O-lines

	//while (parse_code(frame, position, key))
	//{
	//	codes.push_back(key);
	//}

	for (; position < length;)
	{
		IF_F_RET_F( parse_code() );
	}
	return true;
}


bool CmdParser::read_n_number()
{
	int value;
	position++;
	IF_F_RET_F_SETSTATE( read_integer(&value), InterError::WRONG_VALUE, "wrong N value ");

	n_number = value;

	if (line[position] == '.')
	{
		position++;
		IF_F_RET_F_SETSTATE(read_integer(&value), InterError::WRONG_VALUE, "wrong N value ");
	}
	return true;
}



//bool CmdParser::contain_cmd(char letter, int ival) const
//{
//	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
//	{
//		if (iter->letter == letter && ival == static_cast<int>(iter->value))
//			return true;
//	}
//	return false;
//}
//
//bool CmdParser::contain_cmd(ModalGroup group) const
//{
//	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
//	{
//		if (group == get_modal_group(*iter))
//			return true;
//	}
//	return false;
//}



//====================================================================================================
//читает следующий код
bool CmdParser::parse_code()
{

	find_significal_symbol(); 
	
	if (line[position] == 0)
		return false;

	char letter = line[position];

	if (letter == '%') //don't know what should i do
		return true ;

	// set to upper case
	if (letter >= 'a' && letter <= 'z')
		letter += 'A' - 'a';

	switch (letter)
	{
	//specific
		case '%':	break;
		case '#':	read_set_param(); break;
		case '$':	read_dollars(); break;
		case ';':	read_semicolon(); break;
		case '@':	read_atsign(); break;
	//codes
		case 'G':   read_g(); break;
		case 'M':   read_m(); break;
	// Coordinates
		case 'A':	read_real_param(PARAM_A); break;
		case 'B':	read_real_param(PARAM_B); break;
		case 'C':	read_real_param(PARAM_C); break;
		case 'X':	read_real_param(PARAM_X); break;
		case 'Y':	read_real_param(PARAM_Y); break;
		case 'Z':	read_real_param(PARAM_Z); break;
	// parameters
		case 'D':   read_real_param(PARAM_D); break;
		case 'E':   read_real_param(PARAM_E); break;
		case 'F':   read_real_param(PARAM_F); break;		
		case 'I':   read_real_param(PARAM_I); break;
		case 'J':   read_real_param(PARAM_J); break;
		case 'K':   read_real_param(PARAM_K); break;		
		case 'P':   read_real_param(PARAM_P); break;
		case 'Q':   read_real_param(PARAM_Q); break;
		case 'R':   read_real_param(PARAM_R); break;
		case 'S':   read_real_param(PARAM_S); break;
		case 'T':   read_int_param(PARAM_T);  break;
		case 'U':   read_real_param(PARAM_U); break;
		case 'V':   read_real_param(PARAM_V); break;
		case 'W':   read_real_param(PARAM_W); break;
		case 'H':   read_int_param(PARAM_H); break;
		case 'L':   read_int_param(PARAM_L); break;

		default:
			RET_F_SETSTATE(InterError::WRONG_LETTER, "wrong letter: %c", letter);

	}; // reads z or ASCII 0x7A
	return true;
}

//====================================================================================================
//доходит до следующего кода
void CmdParser::find_significal_symbol() 
{
	while (line[position] != 0)
	{
		//skip spaces
		while (line[position] == ' ' || line[position] == '\t')
			position++;
		//skip comments
		if (line[position] == '(')
		{
			int start = position + 1;
			while (line[position] != ')' && line[position] != 0)	position++;
			if (line[position] == ')') position++;
			if(position > start )
				comment = std::string(line + start, position - start - 1 ) ;
		}
		else if (line[position] == '/' && line[position + 1] == '/')
		{
			comment = std::string( line + position + 2 );
			// skeep till end 
			while (line[position] != 0)	position++;
		}
		else
			break;
	}
}

////====================================================================================================
////читает число
//bool CmdParser::parse_value(const char *string, int &position, double &dst) const
//{
//	const char *cursor = string + position;
//
//	double value = 0;
//	int sign = 1;       // +-
//	int numDigits = 0;  //сколько цифр прочитано
//	int maxDigits = 20; //сколько всего можно
//	double denominator = 1;//на сколько поделить прочитанное
//
//	if (*cursor == '-')
//		sign = -1;
//	else if (*cursor == '+')
//		sign = 1;
//	else if (*cursor >= '0' && *cursor <= '9')
//	{
//		value = *cursor - '0';
//		numDigits++;
//	}
//	else if (*cursor != '.')
//		return false;
//
//	if (*cursor != '.')
//		++cursor;
//
//	while (*cursor >= '0' && *cursor <= '9' && ++numDigits <= maxDigits)
//		value = value * 10 + (*(cursor++) - '0');
//
//	if (numDigits > maxDigits)
//	{
//		position = static_cast<int>(cursor - string);
//		return false;
//	}
//
//	if (*cursor == '.')
//	{
//		++cursor;
//		while (*cursor >= '0' && *cursor <= '9' && ++numDigits <= maxDigits)
//		{
//			value = value * 10 + (*(cursor++) - '0');
//			denominator *= 10;
//		}
//
//		if (numDigits > maxDigits)
//		{
//			position = static_cast<int>(cursor - string);
//			return false;
//		}
//
//		value /= denominator;
//	}
//
//	dst = value * sign;
//	position = static_cast<int>(cursor - string);
//	return true;
//}
//
//
//bool CmdParser::check_modal_group() const
//{
//	unsigned int flag = 0;;
//	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
//	{
//		ModalGroup group = get_modal_group(*iter);
//		if (group > 0)
//		{
//			if ((flag & (1 << group)) != 0)   //встретили два оператора из одной группы
//			{
//				state = InterError(InterError::DOUBLE_DEFINITION,
//					std::string("conflict modal group for ") + std::to_string(iter->letter) + std::string(" ") + std::to_string(iter->value));
//				return false;
//			}
//			flag |= (1 << group);
//		}
//	}
//	return true;
//}

//====================================================================================================
//возвращает модальную группу команды

ModalGroup CmdParser::get_modal_group(const GKey &key) const
{
	int num = static_cast<int>(key.value);
	if (key.letter == 'G')
	{
		switch (num)
		{
		case 0: case 1: case 2: case 3:
		case 80: case 81: case 82: case 83: case 84: case 85: case 86: case 87: case 88: case 89:
			return ModalGroup_MOVE;

		case 90: case 91:
			return ModalGroup_INCREMENTAL;

		case 20: case 21:
			return ModalGroup_UNITS;

		case 54: case 55: case 56: case 57: case 58:
			return ModalGroup_COORD_SYSTEM;

		case 43: case 44: case 49:
			return ModalGroup_TOOL_LENGTH_CORRECTION;

		case 40: case 41: case 42:
			return ModalGroup_TOOL_RADIUS_CORRECTION;

		case 98: case 99:
			return ModalGroup_CYCLE_RETURN;

		case 17: case 18: case 19:
			return ModalGroup_ACTIVE_PLANE;

		default:
			return ModalGroup_NONE;
		}
	}
	else if (key.letter == 'M')
	{
		switch (num)
		{
		case 0: case 1: case 2: case 30: case 60:
			return ModalGroup_STOP;

		case 6:
			return ModalGroup_TOOL_CHANGE;

		case 3: case 4: case 5:
			return ModalGroup_TURN_TOOL;

		case 7: case 8: case 9:
			return ModalGroup_GREASER;

		default:
			return ModalGroup_NONE;
		}
	}
	else
		return ModalGroup_NONE;
}

InterError CmdParser::get_state() const
{
	return state;
}


bool CmdParser::getRParam(IndexParam param, double *pd) const
{
	if (params[param])
	{
		(*pd) = params[param].value().dval;
		return true;
	}
	else
		return false;
}

bool CmdParser::getIParam(IndexParam param, int *pi) const
{
	if (params[param])
	{
		(*pi) = params[param].value().ival;
		return true;
	}
	else
		return false;
}

bool CmdParser::read_real_param(IndexParam param)
{
	ParamType value;
	if (params[param])
		RET_F_SETSTATE(InterError::MUITYPLIE_PARAM, "Multiply parameter %c is defened", line[position]);

	position++;
	IF_F_RET_F(read_real_value(&(value.dval)));
	params[param] = value;
	return true;
}


bool CmdParser::read_int_param(IndexParam param)
{
	ParamType value;
	if (params[param])
		RET_F_SETSTATE(InterError::MUITYPLIE_PARAM, "Multiply parameter %c is defened", line[position]);

	position++;
	IF_F_RET_F(read_int_value(&(value.ival)));
	params[param] = value;
	return true;
}

bool CmdParser::read_int_value( int *pint )
{
	return read_integer(pint);
}


bool CmdParser::read_real_value( double *pdbl )
{

	return read_real(pdbl);
}

bool CmdParser::read_integer( int *pint )
{
	int n;
	char c;

	for (n = position;; n++) {
		c = line[n];
		if ((c < 48) || (c > 57))
			break;
	}
	if (n == position || (sscanf(line + position, "%d", pint) == 0))
	{
		state = InterError(InterError::WRONG_VALUE, std::string("wrong integer value "));
		return false;
	}

	position = n;
	return true;
}


bool CmdParser::read_real( double *pdbl )
{
	const char *start = line + position;
	size_t after;
	
	after = strspn(start, "+-");
	after = strspn(start + after, "0123456789.") + after;

	//size_t len = after - start;
	std::string st(start,  after);
	std::stringstream s( st );
	double val;
	if ( !(s >> val) ) 
		RET_F_SETSTATE(InterError::WRONG_VALUE,"bad number format (conversion failed) parsing '%s'", st.c_str());

	if ( s.get() != std::char_traits<char>::eof() ) 
		RET_F_SETSTATE(InterError::WRONG_VALUE,"bad number format (trailing characters) parsing '%s'", st.c_str());

	*pdbl = val;
	position = start + after - line;
	return true;
}


void CmdParser::make_error_state(InterError::Code cod, const char *fmt, ...)
{
	static char buf_error[512];
	va_list ap;
	
	va_start(ap, fmt);

	vsnprintf(buf_error, 512, fmt, ap);

	va_end(ap);
	state = InterError(cod, std::string(buf_error));
}