#include "GCodeInterpreter.h"


//====================================================================================================
//читает данные из строки в массив
bool  CmdParser::parse(const char *frame)
{
	// Clear data
	init();
	
	IF_F_RET_F( parse_codes(frame) );

	//GKey key;
	//while (parse_code(frame, position, key))
	//{
	//	codes.push_back(key);
	//}

	IF_F_RET_F(check_modal_group()); //проверяем что в одной строке нет команд одной группы
	return true;
}




// Clear data
bool  CmdParser::init(const char *frame)
{
	// Clear data
	codes.clear();
	state = InterError();
	return true;
}



bool  CmdParser::parse_codes(const char *line )
{
	int counter;
	//int m9899 = 0, mcounter;  // for checking m98/m99 as o-words
	int length;

	length = strlen(line);
	counter = 0;

	if (line[counter] == '/')     /* skip the slash character if first */
		counter++;

	if (line[counter] == 'N') 
	{
		IF_F_RET_F(read_n_number(line, &counter));
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

	for (; counter < length;) 
	{
		IF_F_RET_F( parse_code( line, &counter) );
	}
	return true;
}


bool CmdParser::read_n_number(char *line, int *counter )
{
	int value;
	*counter = (*counter + 1);
	if (!read_integer_unsigned(line, counter, &value))
	{
		state = InterError(InterError::WRONG_VALUE, std::string("wrong N value ") );
		return false;
	}

	n_number = value;

	// accept & ignore fractional line numbers
	if (line[*counter] == '.') {
		*counter = (*counter + 1);
		if (!read_integer_unsigned(line, counter, &value))
		{
			state = InterError(InterError::WRONG_VALUE, std::string("wrong N value "));
			return false;
		}
	}
	return true;
}


bool CmdParser::read_integer_unsigned(char *line, int *counter,	int *integer_ptr)
{
	int n;
	char c;

	for (n = *counter;; n++) {
		c = line[n];
		if ((c < 48) || (c > 57))
			break;
	}
	if (n == *counter || (sscanf(line + *counter, "%d", integer_ptr) == 0) )
	{
		state = InterError(InterError::WRONG_VALUE, std::string("wrong integer value "));
		return false;
	}

	*counter = n;
	return true;
}


bool CmdParser::contain_cmd(char letter, int ival) const
{
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		if (iter->letter == letter && ival == static_cast<int>(iter->value))
			return true;
	}
	return false;
}

bool CmdParser::contain_cmd(ModalGroup group) const
{
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		if (group == get_modal_group(*iter))
			return true;
	}
	return false;
}


bool CmdParser::getRValue(char ch, double *pr) const
{
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		if (iter->letter == ch)
		{
			*pr = iter->value;
			return true;
		}
	}
	return false;
}

bool CmdParser::getIValue(char ch, int *pi) const
{
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		if (iter->letter == ch)
		{
			*pi = static_cast<int>(iter->value);
			return true;
		}
	}
	return false;
}


//====================================================================================================
//читает следующий код
bool CmdParser::parse_code(const char *frame, int &position, GKey &key)
{

	find_significal_symbol(frame, position); 
	
	if (frame[position] == 0)
		return false;

	char letter = frame[position];

	if (letter == '%') //don't know what should i do
		return true ;

	// set to upper case
	if (letter >= 'a' && letter <= 'z')
		letter += 'A' - 'a';

	switch (letter)
	{
	//specific
		case '%';	break;
		case '#':	read_set_param(position); break;
		case '$':	read_dollars(position); break;
		case ';':	read_semicolon(position); break;
		case '@':	read_atsign(position); break;

	// Coordinates
		case 'A':	read_real_val(RPARAM_A, position); break;
		case 'B':	read_real_val(RPARAM_B, position); break;
		case 'C':	read_real_val(RPARAM_C, position); break;
		case 'X':	read_real_val(RPARAM_X, position); break;
		case 'Y':	read_real_val(RPARAM_Y, position); break;
		case 'Z':	read_real_val(RPARAM_Z, position); break;
	// parameters
		case 'D'	read_real_val(RPARAM_D, position); break;
		case 'E'	read_real_val(RPARAM_E, position); break;
		case 'F'	read_real_val(RPARAM_F, position); break;
		case 'G'	read_g( position ); break;
		case 'H'	read_int_val(IPARAM_H, position); break;
		case 'F'	read_real_val(RPARAM_F, position); break;
		case 'I'	read_real_val(RPARAM_I, position); break;
		case 'J'	read_real_val(RPARAM_J, position); break;
		case 'K'	read_real_val(RPARAM_K, position); break;
		case 'L'	read_int_val(IPARAM_L, position); break;
		case 'M'	read_m(position); break;
		case 'P'	read_real_val(RPARAM_P, position); break;
		case 'Q'	read_real_val(RPARAM_Q, position); break;
		case 'R'	read_real_val(RPARAM_R, position); break;
		case 'S'	read_real_val(RPARAM_S, position); break;
		case 'T'	read_int_val(IPARAM_T, position);  break;
		case 'U'	read_real_val(RPARAM_U, position); break;
		case 'V'	read_real_val(RPARAM_V, position); break;
		case 'W'	read_real_val(RPARAM_W, position); break;

		default:
			state = InterError(InterError::WRONG_LETTER, std::string("wrong letter: ") + letter);
			return false;

	}; // reads z or ASCII 0x7A
	return true;
}

//====================================================================================================
//доходит до следующего кода
void CmdParser::find_significal_symbol(const char *frame, int &position) const
{
	while (frame[position] != 0)
	{
		//skip spaces
		while (frame[position] == ' ' || frame[position] == '\t')
			position++;
		//skip comments
		if (frame[position] == '(')
		{
			int start = position + 1;
			while (frame[position] != ')' && frame[position] != 0)	position++;
			if (frame[position] == ')') position++;
			if(position > start )
				comment = std.string(frame + start, position - start - 1 ) ;
		}
		else if (frame[position] == '/' && frame[position + 1] == '/')
		{
			comment = std.string( frame + position + 2 );
			// skeep till end 
			while (frame[position] != 0)	position++;
		}
		else
			break;
	}
}

//====================================================================================================
//читает число
bool CmdParser::parse_value(const char *string, int &position, double &dst) const
{
	const char *cursor = string + position;

	double value = 0;
	int sign = 1;       // +-
	int numDigits = 0;  //сколько цифр прочитано
	int maxDigits = 20; //сколько всего можно
	double denominator = 1;//на сколько поделить прочитанное

	if (*cursor == '-')
		sign = -1;
	else if (*cursor == '+')
		sign = 1;
	else if (*cursor >= '0' && *cursor <= '9')
	{
		value = *cursor - '0';
		numDigits++;
	}
	else if (*cursor != '.')
		return false;

	if (*cursor != '.')
		++cursor;

	while (*cursor >= '0' && *cursor <= '9' && ++numDigits <= maxDigits)
		value = value * 10 + (*(cursor++) - '0');

	if (numDigits > maxDigits)
	{
		position = static_cast<int>(cursor - string);
		return false;
	}

	if (*cursor == '.')
	{
		++cursor;
		while (*cursor >= '0' && *cursor <= '9' && ++numDigits <= maxDigits)
		{
			value = value * 10 + (*(cursor++) - '0');
			denominator *= 10;
		}

		if (numDigits > maxDigits)
		{
			position = static_cast<int>(cursor - string);
			return false;
		}

		value /= denominator;
	}

	dst = value * sign;
	position = static_cast<int>(cursor - string);
	return true;
}


bool CmdParser::check_modal_group() const
{
	unsigned int flag = 0;;
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		ModalGroup group = get_modal_group(*iter);
		if (group > 0)
		{
			if ((flag & (1 << group)) != 0)   //встретили два оператора из одной группы
			{
				state = InterError(InterError::DOUBLE_DEFINITION,
					std::string("conflict modal group for ") + std::to_string(iter->letter) + std::string(" ") + std::to_string(iter->value));
				return false;
			}
			flag |= (1 << group);
		}
	}
	return true;
}

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
