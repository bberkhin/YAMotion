#include "cmdparser.h"
#include "ienvironment.h"

#include <math.h>

#ifndef M_PIl
#define M_PIl 3.1415926535897932384626433832795
#endif



namespace Interpreter
{
	


bool CmdParser::read_parameter(double *pdbl, bool check_exists)    //!< test for existence, not value
{
	int index;
	IF_F_RET_F_SETSTATE((line[position] == '#'), INTERNAL_ERROR, "read_parameter can not called here");
	position++;

	// named parameters look like '<letter...>' or '<_.....>'
	if (line[position] == '<')
	{
		RET_F_SETSTATE(NOTSUPPORTEDYET, "Named paramtr does not support yet");
	}
	else
	{
		IF_F_RET_F(read_int_value( &index));
		if (check_exists)
		{
			*pdbl = index >= 1 && index < RS274NGC_MAX_PARAMETERS;
			return true;
		}
		IF_F_RET_F_SETSTATE(((index >= 1) && (index < RS274NGC_MAX_PARAMETERS)), PARAMETER_ERROR, "Parameter number is out of range");
		//IF_F_RET_F_SETSTATE(((index < 5420) || (index <= 5428) && (true)), PARAMETER_ERROR, "Cannot read current position with cutter radius compensation on");
		
		*pdbl = env->GetVariable(index);
	}
	return true;
}

bool CmdParser::read_operation_unary( int *operation ) 
{
	char c;
	c = line[position];
	position++;
	switch (c) 
	{
	case 'a':
		if ((line[position] == 'b') && (line[position + 1] == 's')) {
			*operation = ABS;
			position += 2;
		}
		else if (strncmp((line + position), "cos", 3) == 0) {
			*operation = ACOS;
			position += 3;
		}
		else if (strncmp((line + position), "sin", 3) == 0) {
			*operation = ASIN;
			position += 3;
		}
		else if (strncmp((line + position), "tan", 3) == 0) {
			*operation = ATAN;
			position += 3;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'a'");
		break;
	case 'c':
		if ((line[position] == 'o') && (line[position + 1] == 's')) {
			*operation = COS;
			position += 2;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'c'");
		break;
	case 'e':
		if ((line[position] == 'x') && (line[position + 1] == 'p')) {
			*operation = EXP;
			position += 2;
		}
		else if ((line[position] == 'x')
			&& (line[position + 1] == 'i')
			&& (line[position + 2] == 's')
			&& (line[position + 3] == 't')
			&& (line[position + 4] == 's')
			) {
			position += 5;
			*operation = EXISTS;
		}
		else {
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'e'");
		}
		break;
	case 'f':
		if ((line[position] == 'i') && (line[position + 1] == 'x')) {
			*operation = FIX;
			position += 2;
		}
		else if ((line[position] == 'u') && (line[position + 1] == 'p')) {
			*operation = FUP;
			position += 2;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'f'");
		break;
	case 'l':
		if (line[position] == 'n') {
			*operation = LN;
			position++;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'l'");
		break;
	case 'r':
		if (strncmp((line + position), "ound", 4) == 0) {
			*operation = ROUND;
			position += 4;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 'r'");
		break;
	case 's':
		if ((line[position] == 'i') && (line[position + 1] == 'n')) {
			*operation = SIN;
			position += 2;
		}
		else if (strncmp((line + position), "qrt", 3) == 0) {
			*operation = SQRT;
			position += 3;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 's'");
		break;
	case 't':
		if ((line[position] == 'a') && (line[position + 1] == 'n')) {
			*operation = TAN;
			position += 2;
		}
		else
			RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word starting with 't'");
		break;
	default:
		RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown word where unary operation could be");
	}
	return true;
}

bool CmdParser::read_bracketed_parameter( double *double_ptr, bool check_exists)
{
	IF_F_RET_F_SETSTATE((line[position] == '['), INTERNAL_ERROR, "read_bracketed_parameter can not called here");
	position++;
	IF_F_RET_F_SETSTATE((line[position] == '#'), EXPRESSION_ERROR, "Expected # reading bracketed parameter");
	IF_F_RET_F(read_parameter( double_ptr, check_exists));
	IF_F_RET_F_SETSTATE((line[position] == ']'), EXPRESSION_ERROR, "Expected ] reading bracketed parameter");
	position++;
	return true;
}

bool CmdParser::execute_unary(double *double_ptr, int operation) 
{
	switch (operation) 
	{
	case ABS:
		if (*double_ptr < 0.0)
			*double_ptr = (-1.0 * *double_ptr);
		break;
	case ACOS:
		IF_F_RET_F_SETSTATE(((*double_ptr >= -1.0) && (*double_ptr <= 1.0)), EXPRESSION_ERROR, "ACOS arcument is out of range");
		*double_ptr = acos(*double_ptr);
		*double_ptr = ((*double_ptr * 180.0) / M_PIl);
		break;
	case ASIN:
		IF_F_RET_F_SETSTATE(((*double_ptr >= -1.0) && (*double_ptr <= 1.0)), EXPRESSION_ERROR, "ASIN arcument is out of range");
		*double_ptr = asin(*double_ptr);
		*double_ptr = ((*double_ptr * 180.0) / M_PIl);
		break;
	case COS:
		*double_ptr = cos((*double_ptr * M_PIl) / 180.0);
		break;
	case EXISTS:
		// do nothing here
		// result for the EXISTS function is set by Interp:read_unary()
		break;
	case EXP:
		*double_ptr = exp(*double_ptr);
		break;
	case FIX:
		*double_ptr = floor(*double_ptr);
		break;
	case FUP:
		*double_ptr = ceil(*double_ptr);
		break;
	case LN:
		IF_F_RET_F_SETSTATE((*double_ptr <= 0.0), EXPRESSION_ERROR, "Zero or negative argument to LN");
		*double_ptr = log(*double_ptr);
		break;
	case ROUND:
		*double_ptr = (double)
			((int)(*double_ptr + ((*double_ptr < 0.0) ? -0.5 : 0.5)));
		break;
	case SIN:
		*double_ptr = sin((*double_ptr * M_PIl) / 180.0);
		break;
	case SQRT:
		IF_F_RET_F_SETSTATE((*double_ptr >= 0.0), EXPRESSION_ERROR, "Zero or negative argument to LN");
		*double_ptr = sqrt(*double_ptr);
		break;
	case TAN:
		*double_ptr = tan((*double_ptr * M_PIl) / 180.0);
		break;
	default:
		RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown operation");
	}
	return true;
}

bool CmdParser::read_atan(double *pdbl)
{
	double argument2;
	IF_F_RET_F_SETSTATE((line[position] == '/'), EXPRESSION_ERROR, "Missing slash after first atan argument");
	position++;
	IF_F_RET_F_SETSTATE((line[position] == '['), EXPRESSION_ERROR, "Missing left bracket after slash with atan");
  	IF_F_RET_F(read_real_expression( &argument2));
	*pdbl = atan2(*pdbl, argument2);  /* value in radians */
	*pdbl = ((*pdbl * 180.0) / M_PIl);   /* convert to degrees */
	return true;
}



bool CmdParser::read_unary(double *pdbl)
{
	int operation;
	IF_F_RET_F(read_operation_unary(&operation));
	IF_F_RET_F_SETSTATE((line[position] == '['), EXPRESSION_ERROR, "Basket '[' missing after unary");

	if (operation == EXISTS)
	{
		IF_F_RET_F(read_bracketed_parameter(pdbl, true));
	}

	IF_F_RET_F(read_real_expression(pdbl));

	if (operation == ATAN)
		IF_F_RET_F(read_atan(pdbl));
	else
		IF_F_RET_F(execute_unary(pdbl, operation));
	return true;
}


bool CmdParser::read_operation(int *operation)
{
	char c;
	c = line[position];
	position++;
	switch (c) 
	{
	case '+':	*operation = PLUS;	break;
	case '-':	*operation = MINUS;	break;
	case '/':	*operation = DIVIDED_BY; break;
	case '*':	
		if (line[position] == '*') 
		{
			*operation = POWER;
			position++;
		}
		else
			*operation = TIMES;
		break;
	case ']':
		*operation = RIGHT_BRACKET;
		break;
	case 'a':
		if ((line[position] == 'n') && (line[position + 1] == 'd')) {
			*operation = AND2;
			position += 2;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'a'");
		break;
	case 'm':
		if ((line[position] == 'o') && (line[position + 1] == 'd')) {
			*operation = MODULO;
			position += 2;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'm'");
		break;
	case 'o':
		if (line[position] == 'r') {
			*operation = NON_EXCLUSIVE_OR;
			position++;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'o'");
		break;
	case 'x':
		if ((line[position] == 'o') && (line[position + 1] == 'r')) {
			*operation = EXCLUSIVE_OR;
			position += 2;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'x'");
		break;

		/* relational operators */
	case 'e':
		if (line[position] == 'q')
		{
			*operation = EQ;
			position++;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'e'");
		break;
	case 'n':
		if (line[position] == 'e')
		{
			*operation = NE;
			position++;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'n'");
		break;
	case 'g':
		if (line[position] == 'e')
		{
			*operation = GE;
			position++;
		}
		else if (line[position] == 't')
		{
			*operation = GT;
			position++;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'g'");
		break;
	case 'l':
		if (line[position] == 'e')
		{
			*operation = LE;
			position++;
		}
		else if (line[position] == 't')
		{
			*operation = LT;
			position++;
		}
		else
			RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unknown operator starting with 'l'");
		break;

	case 0:
		RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unclosed expression");
	default:
		RET_F_SETSTATE(UNKNOWN_OPERATOR, "Unclosed operator");
	}
	return true;

}

bool CmdParser::execute_binary(double *left, int operation, double *right)
{
	if (operation < AND2)
		IF_F_RET_F(execute_binary1(left, operation, right));
	else
		IF_F_RET_F(execute_binary2(left, operation, right));
	return true;
}

/****************************************************************************/


bool CmdParser::execute_binary1(double *left, int operation, double *right) 
{
	switch (operation) 
	{
	case DIVIDED_BY:
		IF_F_RET_F_SETSTATE((*right != 0.0), EXPRESSION_ERROR, "Attempt to devide by zero");
		*left = (*left / *right);
		break;
	case MODULO:                 /* always calculates a positive answer */
		*left = fmod(*left, *right);
		if (*left < 0.0) {
			*left = (*left + fabs(*right));
		}
		break;
	case POWER:
		if((*left < 0.0) && (floor(*right) != *right))
			RET_F_SETSTATE(EXPRESSION_ERROR, "Attempt to raize negative to non integer power");
		*left = pow(*left, *right);
		break;
	case TIMES:
		*left = (*left * *right);
		break;
	default:
		RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown operator");
	}
	return true;
}


bool CmdParser::execute_binary2(double *left, int operation,  double *right) 
{
	double diff;
	switch (operation) {
	case AND2:
		*left = ((*left == 0.0) || (*right == 0.0)) ? 0.0 : 1.0;
		break;
	case EXCLUSIVE_OR:
		*left = (((*left == 0.0) && (*right != 0.0))
			|| ((*left != 0.0) && (*right == 0.0))) ? 1.0 : 0.0;
		break;
	case MINUS:
		*left = (*left - *right);
		break;
	case NON_EXCLUSIVE_OR:
		*left = ((*left != 0.0) || (*right != 0.0)) ? 1.0 : 0.0;
		break;
	case PLUS:
		*left = (*left + *right);
		break;

	case LT:
		*left = (*left < *right) ? 1.0 : 0.0;
		break;
	case EQ:
		diff = *left - *right;
		diff = (diff < 0) ? -diff : diff;
		*left = (diff < TOLERANCE_EQUAL) ? 1.0 : 0.0;
		break;
	case NE:
		diff = *left - *right;
		diff = (diff < 0) ? -diff : diff;
		*left = (diff >= TOLERANCE_EQUAL) ? 1.0 : 0.0;
		break;
	case LE:
		*left = (*left <= *right) ? 1.0 : 0.0;
		break;
	case GE:
		*left = (*left >= *right) ? 1.0 : 0.0;
		break;
	case GT:
		*left = (*left > *right) ? 1.0 : 0.0;
		break;

	default:
		RET_F_SETSTATE(EXPRESSION_ERROR, "Unknown operator");
	}
	return true;
}

int CmdParser::precedence(int an_operator)
{
	switch (an_operator)
	{
		case RIGHT_BRACKET:
			return 1;

		case AND2:
		case EXCLUSIVE_OR:
		case NON_EXCLUSIVE_OR:
			return 2;

		case LT:
		case EQ:
		case NE:
		case LE:
		case GE:
		case GT:
			return 3;

		case MINUS:
		case PLUS:
			return 4;

		case NO_OPERATION:
		case DIVIDED_BY:
		case MODULO:
		case TIMES:
			return 5;

		case POWER:
			return 6;
	}
	// should never happen
	return 0;
}

#define MAX_STACK 7

bool CmdParser::read_real_expression(double *pdbl)
{
	double values[MAX_STACK];
	int operators[MAX_STACK];
	int stack_index;

	if (line[position] != '[')
		RET_F_SETSTATE(INTERNAL_ERROR, "read_real_expression can not been called hear");

	position++;
	IF_F_RET_F(read_real_value(values));
	IF_F_RET_F(read_operation(operators));
	stack_index = 1;
	for (; operators[0] != RIGHT_BRACKET;) {
		IF_F_RET_F(read_real_value(values + stack_index));
		IF_F_RET_F(read_operation(operators + stack_index));
		if (precedence(operators[stack_index]) >
			precedence(operators[stack_index - 1]))
			stack_index++;
		else {                      /* precedence of latest operator is <= previous precedence */

			for (; precedence(operators[stack_index]) <=
				precedence(operators[stack_index - 1]);) {
				IF_F_RET_F(execute_binary((values + stack_index - 1),
					operators[stack_index - 1],
					(values + stack_index)));
				operators[stack_index - 1] = operators[stack_index];
				if ((stack_index > 1) &&
					(precedence(operators[stack_index - 1]) <=
						precedence(operators[stack_index - 2])))
					stack_index--;
				else
					break;
			}
		}
	}
	*pdbl = values[0];
	return true;
}


};