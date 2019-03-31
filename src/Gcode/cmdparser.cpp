#include "cmdparser.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include "ienvironment.h"
#include "gcodeerrors.h"


namespace Interpreter
{

#pragma warning(disable:4996)

CmdParser::CmdParser(IEnvironment *env_) : env(env_)
{
}

//====================================================================================================
//читает данные из строки в массив
bool  CmdParser::parse(const char *frame)
{
	// Clear data
	clear();
	IF_F_RET_F(parse_codes(frame) );
	IF_F_RET_F(check_modal_group()); //проверяем что в одной строке нет команд одной группы
	return true;
}




// Clear data
void CmdParser::clear()
{
	// Clear data
	remove_params();
	n_number = -1;
	comment.clear();
	mcodes.clear();
	memset(g_mode, -1, sizeof(int)*ModalGroup_Size);
	line = 0;
	position = 0;
	o_name.clear();
	o_type = O_none;
	state = InterError();
}


bool CmdParser::neead_execute()  const
{
// absolutly empty just comments
	if (!mcodes.empty() || !o_name.empty())
		return true;
	// check params
	for (int i = 0; i < PARAM_MAX; ++i)
	{
		if (params[i])
			return true;
	}
	
	for (int i = 0; i < ModalGroup_Size; i++)
	{
		if (g_mode[i] != -1)
			return true;
	}

	return false;
}



bool  CmdParser::parse_codes(const char *frame )
{
	line = frame;
	position = 0;

	//int m9899 = 0, mcounter;  // for checking m98/m99 as o-words
	int length;

	length = static_cast<int>(strlen(line));

	if (line[position] == '/')     /* skip the slash character if first */
		position++;

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
	IF_F_RET_F_SETSTATE( read_integer(&value), WRONG_VALUE, YA_WRONG_N);

	n_number = value;

	if (line[position] == '.')
	{
		position++;
		IF_F_RET_F_SETSTATE(read_integer(&value), WRONG_VALUE, YA_WRONG_N);
	}
	return true;
}





//====================================================================================================
//читает следующий код
bool CmdParser::parse_code()
{

	find_significal_symbol(); 
	
	if (line[position] == 0 || line[position] == '\n'  )
	{
		position++;
		return true;
	}


	char letter = line[position];

	if (letter == '%') //don't know what should i do, so just skeep
	{
		position++;
		return true;
	}
		
		
	switch (letter)
	{
	//specific
//		case '%':	break; // do nothing
		case '#':	read_set_param(); break;
		case '$':	read_dollars(); break;
		case ';':	read_semicolon(); break;
	//codes
		case 'g':   read_g(); break;
		case 'm':   read_m(); break;
		case 'n':   read_n_number(); break;
	// subrotinue
		case 'o':   read_subrotinue(); break;
	// Coordinates
		case 'a':	read_real_param(PARAM_A); break;
		case 'b':	read_real_param(PARAM_B); break;
		case 'c':	read_real_param(PARAM_C); break;
		case 'x':	read_real_param(PARAM_X); break;
		case 'y':	read_real_param(PARAM_Y); break;
		case 'z':	read_real_param(PARAM_Z); break;
	// parameters
		case '@':	read_real_param(PARAM_AT); break;
		case 'd':   read_real_param(PARAM_D); break;
		case 'e':   read_real_param(PARAM_E); break;
		case 'f':   read_real_param(PARAM_F); break;		
		case 'i':   read_real_param(PARAM_I); break;
		case 'j':   read_real_param(PARAM_J); break;
		case 'k':   read_real_param(PARAM_K); break;		
		case 'p':   read_real_param(PARAM_P); break;
		case 'q':   read_real_param(PARAM_Q); break;
		case 'r':   read_real_param(PARAM_R); break;
		case 's':   read_real_param(PARAM_S); break;
		case 't':   read_int_param(PARAM_T);  break;
		case 'u':   read_real_param(PARAM_U); break;
		case 'v':   read_real_param(PARAM_V); break;
		case 'w':   read_real_param(PARAM_W); break;
		case 'h':   read_int_param(PARAM_H); break;
		case 'l':   read_int_param(PARAM_L); break;

		default:
			position++;
			RET_F_SETSTATE(WRONG_LETTER, YA_WRONG_LETTER, letter);

	}; // reads z or ASCII 0x7A
	if (state.code)
		return false;
	return true;
}

//====================================================================================================
//доходит до следующего кода
void CmdParser::find_significal_symbol() 
{
	while (line[position] != 0)
	{
		//skip spaces
		while (line[position] == ' ' || line[position] == '\t' || line[position] == '\r')
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
		else if (line[position] == '/' || line[position] == ';')
		{
			position++;
			read_comment_eol();			
		}
		else
			break;
	}
}

//bool CmdParser::contain_cmd(MModalGroup group) const
//{
//	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
//	{
//		if (group == get_mmodal_group(*iter))
//			return true;
//	}
//	return false;
//}

bool CmdParser::contain_m(int val) const
{
	if (std::find(mcodes.begin(), mcodes.end(), val) != mcodes.end())
		return true;
	return false;
}

//bool CmdParser::contain_g(int val)  const
//{
//	if (std::find(gcodes.begin(), gcodes.end(), val) != gcodes.end())
//		return true;
//	return false;
//}


bool CmdParser::check_modal_group() const
{
	unsigned int flag = 0;
	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
	{
		MModalGroup group = get_mmodal_group(*iter);
		if (group > 0)
		{
			if ((flag & (1 << group)) != 0)   //встретили два оператора из одной группы
				RET_F_SETSTATE(DOUBLE_DEFINITION, YA_CONFLICT_MMODAL_GROUP, *iter);
			flag |= (1 << group);
		}
	}
	return true;
}

//====================================================================================================
//возвращает модальную группу команды

MModalGroup CmdParser::get_mmodal_group(int num) const
{
	switch (num)
	{
	case 0: case 1: case 2: case 30: case 60:
		return ModalGroup_STOP;

	case 3: case 4: case 5:
		return ModalGroup_TURN_TOOL;

	case 7: case 8: case 9:
		return ModalGroup_GREASER;

	default:
		return ModalGroup_NONE;
	}
}


InterError CmdParser::get_state() const
{
	return state;
}


//void CmdParser::remove_g(int n)
//{
//	auto iter = std::find( gcodes.begin(), gcodes.end(), n);
//	if (iter != gcodes.end())
//		gcodes.erase(iter);
//}

void CmdParser::remove_param(IndexParam param)
{
	params[param].reset();
}

void CmdParser::remove_params()
{
	std::for_each(std::begin(params), std::end(params), // lambda
		[](optparam &p) { p.reset(); });
}


int CmdParser::params_count()
{
	int n = 0;
	/*
	for (int i = 0; i < PARAM_MAX; ++i)
	{
		if (params[i]) n++;
	}
	*/
	std::for_each(std::begin(params), std::end(params), // lambda
		[&n](optparam &p) { if (p) ++n;} );
	return n;
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
		if (param < PARAM_MAX_R_PARAM)
		{
			double dv = params[param].value().dval;
			real_to_int(&dv, pi);
		}
		else
			(*pi) = params[param].value().ival;
		return true;
	}
	else
		return false;
}

bool CmdParser::hasParam(IndexParam param) const
{
	return params[param].has_value();
}

bool CmdParser::read_set_param()
{
	int index;
	double value;

	IF_F_RET_F_SETSTATE((line[position] == '#'), INTERNAL_ERROR,YA_CAN_NOT_CALLED_HERE);
	position++;

	// named parameters look like '<letter...>' or '<_letter.....>'
	if (line[position] == '<')
	{
		position++;
		RET_F_SETSTATE(NOTSUPPORTEDYET, YA_NAMED_PARAMETER_NOT_SUPPORTED);
	}
	else
	{
		IF_F_RET_F(read_int_value(&index));
		IF_F_RET_F_SETSTATE(((index >= 1) && (index < RS274NGC_MAX_PARAMETERS)), PARAMETER_ERROR, YA_PARAMETER_NUMBER_OUT_OF_RANGE);
		
		IF_F_RET_F_SETSTATE((!isreadonly_param(index)), PARAMETER_ERROR, YA_PARAMETER_NUMBER_READONLY);
			
		IF_F_RET_F_SETSTATE((line[position] == '='),PARAMETER_ERROR, YA_EQUAL_SIGN_MISSING_IN_PARAMETER_SETTING);
		position++;
		IF_F_RET_F( read_real_value(&value) );
		if ( env )
			env->SetVariable(index, value);
		else
			RET_F_SETSTATE(INTERNAL_ERROR, "IEnvironment == 0");

	}
	return true;
}


bool CmdParser::read_dollars()
{
	position++;
	RET_F_SETSTATE(NOTSUPPORTEDYET, YA_MUILTISPINDLE_NOT_SUPPORTED);
}

bool CmdParser::read_semicolon()
{
	position++;
	IF_F_RET_F(read_comment_eol());
	return true;
}

bool CmdParser::read_comment_eol()
{
	comment = std::string(line + position + 2);
	// skeep till end 
	while (line[position] != 0)	position++;
	return true;
}


bool CmdParser::read_subrotinue()
{
	int oNumber;
	char oNameBuf[MAX_GCODE_LINELEN];
	//position is on '0'
	position++;
	if (line[position] == '<')
	{
		RET_F_SETSTATE(PARAMETER_ERROR, YA_SUBNAME_NOT_SUPPORTED);
		//read_name(oNameBuf);
	}
	else
	{
		IF_F_RET_F(read_int_value( &oNumber ));
		sprintf(oNameBuf, "%d", oNumber);
	}
	// We stash the text the offset part of setup

#define CMP(txt) (strncmp(line+position, txt, strlen(txt)) == 0 && (position += strlen(txt)))
	  // characterize the type of o-word

	if (CMP("sub"))
		o_type = O_sub;
	else if (CMP("endsub"))
		o_type = O_endsub;
	else if (CMP("call"))
		o_type = O_call;
	else if (CMP("do"))
		o_type = O_do;
	else if (CMP("while"))
		o_type = O_while;
	else if (CMP("repeat"))
		o_type = O_repeat;
	else if (CMP("if"))
		o_type = O_if;
	else if (CMP("elseif"))
		o_type = O_elseif;
	else if (CMP("else"))
		o_type = O_else;
	else if (CMP("endif"))
		o_type = O_endif;
	else if (CMP("break"))
		o_type = O_break;
	else if (CMP("continue"))
		o_type = O_continue;
	else if (CMP("endwhile"))
		o_type = O_endwhile;
	else if (CMP("endrepeat"))
		o_type = O_endrepeat;
	else if (CMP("return"))
		o_type = O_return;	
	else
		o_type = O_;

	// we now have it characterized
	// now create the text of the oword

	switch (o_type)
	{
			// the global cases first
		case O_sub:
		case O_:
		case O_endsub:
		case O_call:
		case O_return:
			o_name = oNameBuf;
			break;
	}
	return true;
}


bool CmdParser::read_m()
{
	int ival;
	//position is on 'M'
	position++;
	IF_F_RET_F(read_int_value(&ival) );
	if (ival < 0)
		RET_F_SETSTATE(WRONG_VALUE, YA_NEGATIVE_M_CODE_USED);

	if (ival > 199 )
		RET_F_SETSTATE(WRONG_VALUE, YA_M_CODE_GREATER_THAN_199, ival);

	mcodes.push_back(ival);
	return true;
}

bool CmdParser::read_g()
{
	double value_read;
	int value;

	//position is on 'M'
	position++;
	IF_F_RET_F( read_real_value(&value_read) );
	value_read = (10.0 * value_read);
	value = (int)floor(value_read);

	if ((value_read - value) > 0.999)
		value = (int)ceil(value_read);
	else if ((value_read - value) > 0.001)
		RET_F_SETSTATE(WRONG_VALUE, YA_G_CODE_OUT_OF_RANGE);

	if( value > 999 )
		RET_F_SETSTATE(WRONG_VALUE, YA_G_CODE_OUT_OF_RANGE);

	if (value < 0)
		RET_F_SETSTATE(WRONG_VALUE, YA_NEGATIVE_G_CODE_USED);

	IF_F_RET_F_SETSTATE(acsept_gcode(value), WRONG_VALUE, YA_UNKNOWN_G_CODE_USED, static_cast<int>(value/10));

	GModalGroup grp = get_gmodal_group( value );
	IF_T_RET_F_SETSTATE( hasGCode(grp) , DOUBLE_DEFINITION, YA_TWO_G_CODES_USED_FROM_SAME_MODAL_GROUP, static_cast<int>(value / 10) );
	g_mode[grp] = value;
	return false;
}


bool CmdParser::read_real_param(IndexParam param)
{
	ParamType value;
	if (params[param])
		RET_F_SETSTATE(MUITYPLIE_PARAM, YA_MULTIPLE_WORDS_ON_ONE_LINE, line[position]);

	position++;
	IF_F_RET_F(read_real_value(&(value.dval)));
	params[param] = value;
	return true;
}


bool CmdParser::read_int_param(IndexParam param)
{
	ParamType value;
	if (params[param])
		RET_F_SETSTATE(MUITYPLIE_PARAM, YA_MULTIPLE_WORDS_ON_ONE_LINE, line[position]);

	position++;
	IF_F_RET_F(read_int_value(&(value.ival)));
	params[param] = value;
	return true;
}

bool CmdParser::read_int_value( int *pint )
{
	double dblval;

	IF_F_RET_F(read_real_value( &dblval));
	IF_F_RET_F(real_to_int(&dblval,pint));
	return true;
}



bool CmdParser::real_to_int(double *pdbl, int *pint) const
{
	*pint = static_cast<int>(floor(*pdbl));
	if ((*pdbl - *pint) > 0.9999)
		*pint = static_cast<int>(ceil(*pdbl));
	else if ((*pdbl - *pint) > 0.0001)
		RET_F_SETSTATE(WRONG_VALUE, YA_NON_INTEGER_VALUE_FOR_INTEGER);
	return true;
}

bool CmdParser::read_real_value( double *pdbl )
{
	char c, c1;
	c = line[position];
	if (c == 0)
		RET_F_SETSTATE(NO_VALUE, YA_NO_CHARACTERS_FOUND_IN_READING_REAL_VALUE);
	c1 = line[position + 1];

	if (c == '[')
		IF_F_RET_F(read_real_expression(pdbl));
	else if (c == '#')
	{
		IF_F_RET_F(read_parameter(pdbl, false));
	}
	else if (c == '+' && c1 && !isdigit(c1) && c1 != '.')
	{
		position++;
		IF_F_RET_F(read_real_value(pdbl));
	}
	else if (c == '-' && c1 && !isdigit(c1) && c1 != '.')
	{
		position++;
		IF_F_RET_F(read_real_value(pdbl));
		*pdbl = -*pdbl;
	}
	else if ((c >= 'a') && (c <= 'z'))
		IF_F_RET_F(read_unary(pdbl));
	else
		IF_F_RET_F(read_real(pdbl));

	if(std::isnan( *pdbl) )
		RET_F_SETSTATE(NO_VALUE, YA_CALC_RESULT_NOT_NUMBER);

	if ( std::isinf(*pdbl) )
		RET_F_SETSTATE(NO_VALUE, YA_CALC_RESULT_INFINITY);

	return true;
}



bool CmdParser::read_integer( int *pint )
{
	int n;
	char c;

	for (n = position;; n++) 
	{
		c = line[n];
		if ((c < 48) || (c > 57))
			break;
	}
	if (n == position || (sscanf(line + position, "%d", pint) == 0))
		RET_F_SETSTATE(WRONG_VALUE, YA_BAD_FORMAT_INTEGER);

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
		RET_F_SETSTATE(WRONG_VALUE, YA_BAD_NUMBER_FORMAT1, st.c_str());

	if ( s.get() != std::char_traits<char>::eof() ) 
		RET_F_SETSTATE(WRONG_VALUE, YA_BAD_NUMBER_FORMAT1, st.c_str());

	*pdbl = val;
	position = static_cast<int>(start + after - line);
	return true;
}

InterError InterError::CreateErrorCode(ErrorCode cod, const char *fmt, ...)
{
	static char buf_error[512];
	va_list ap;

	va_start(ap, fmt);

	vsnprintf(buf_error, 512, fmt, ap);

	va_end(ap);
	return InterError(cod, std::string(buf_error));
}


GModalGroup CmdParser::get_gmodal_group(int num) const
{
	switch (num)
	{
		//G0, G1, G2, G3, G38.2, G80, G81 to G89, G33, G33.1, G76
	case G_0: case G_1: case G_2: case G_3: case G_5: case G_38_2: case G_33: case G_33_1: case G_76:
	case G_80: case G_81: case G_82: case G_83: case G_84: case G_85: case G_86: case G_87: case G_88: case G_89:
	//case G_6:
		return ModalGroup_MOVE;
	case G_17: case G_18: case G_19:
		return ModalGroup_ACTIVE_PLANE;
	case G_90: case G_91:
		return ModalGroup_DISTANCE;
	case G_90_1: case G_91_1:
		return ModalGroup_DISTANCE;
	case G_93: case G_94: case G_95:
		return ModalGroup_FEEDMODE;
	case G_20: case G_21:
		return ModalGroup_UNITS;
	case G_40: case G_41: case G_42: case G_42_1:
	//case G41_1:
		return ModalGroup_CUTTER_COMP;
	case G_43: case G_44: case G_49: 
	//case G43_1: case G43_2:
		return ModalGroup_TOOL_LENGTH_CORRECTION;
	case G_98: case G_99:
		return ModalGroup_CYCLE_RETURN;
		//g54, g55, g56, g57, g58, g59, g59.1, g59.2, g59.3
	case G_54: case G_55: case G_56: case G_57: case G_58: case G_59: case G_59_1: 
	//case G59_2: case G59_3:
		return ModalGroup_COORD_SYSTEM;
	case G_61: case G_61_1: case G_64:
		return ModalGroup_CONTROL;
	case G_96: case G_97:
		return ModalGroup_SPINDLEMODE;  //G96 G97 spindle
	case G_7: case G_8:
		return ModalGroup_LATHE_DIAMETER; //G7 or G8
	default: ////g4, g10, g28, g30, g53, g92 g92.1, g92.2, g92.3 - misc
		return ModalGroup_MODAL_0;
	}
}

bool CmdParser::acsept_gcode(int num) const
{
	switch (num)
	{
	case G_0:
	case G_1:
	case G_2:
	case G_3:
	case G_4:
	case G_5:
	case G_5_1:
	case G_5_2:
	case G_5_3:
	case G_7:
	case G_8:
	case G_10:
	case G_17:
	case G_17_1:
	case G_18:
	case G_18_1:
	case G_19:
	case G_19_1:
	case G_20:
	case G_21:
	case G_28:
	case G_28_1:
	case G_30:
	case G_30_1:
	case G_31:
	case G_32:
	case G_33:
	case G_33_1:
	case G_38_2:
	case G_38_3:
	case G_38_4:
	case G_38_5:
	case G_40:
	case G_41:
	case G_41_1:
	case G_42:
	case G_42_1:
	case G_43:
	case G_43_1:
	case G_43_2:
	case G_49:
	case G_50:
	case G_51:
	case G_52:
	case G_53:
	case G_54:
	case G_55:
	case G_56:
	case G_57:
	case G_58:
	case G_59:
	case G_59_1:
	case G_59_2:
	case G_59_3:
	case G_61:
	case G_61_1:
	case G_64:
	case G_73:
	case G_74:
	case G_76:
	case G_80:
	case G_81:
	case G_82:
	case G_83:
	case G_84:
	case G_85:
	case G_86:
	case G_87:
	case G_88:
	case G_89:
	case G_90:
	case G_90_1:
	case G_91:
	case G_91_1:
	case G_92:
	case G_92_1:
	case G_92_2:
	case G_92_3:
	case G_93:
	case G_94:
	case G_95:
	case G_96:
	case G_97:
	case G_98:
	case G_99:
		return true;
	default:
		return false;
	}
}

bool CmdParser::isreadonly_param(int num) const
{
	switch (num)
	{
		case 5400: // tool toolno
		case 5401: // tool x offset
		case 5402: // tool y offset
		case 5403: // tool z offset
		case 5404: // tool a offset
		case 5405: // tool b offset
		case 5406: // tool c offset
		case 5407: // tool u offset
		case 5408: // tool v offset
		case 5409: // tool w offset
		case 5410: // tool diameter
		case 5411: // tool frontangle
		case 5412: // tool backangle
		case 5413: // tool orientation
		case 5420:	case 5421:	case 5422:	case 5423:	case 5424:	case 5425:	case 5426:	case 5427:	case 5428: // current X Y ... W
			return true;
	}
	return false;
}

};


