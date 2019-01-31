#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

#include "GCodeInterpreter.h"


using namespace Interpreter;

#pragma warning(disable:4996)

//====================================================================================================
GCodeInterpreter::GCodeInterpreter(IEnvironment *penv, IExecutor *ix, ILogger *log) :
	env(penv), executor(ix), logger(log)
{
	init();
}

//====================================================================================================
GCodeInterpreter::~GCodeInterpreter(void)
{
}

//====================================================================================================
void GCodeInterpreter::init()
{

}



//====================================================================================================
//читает строки в список
bool GCodeInterpreter::read_file(const char *name)
{
	std::ifstream file(name); //открываем файл

	inputFile.clear();
	while (file) //пока он не закончился
	{
		std::string str;
		std::getline(file, str); //читаем строку
		inputFile.push_back(str); //добавляем в конец списка
	}

	return true;
}

void GCodeInterpreter::execute_file(const char *data)
{

	char line[256];
	const char *p = data;
	int  i = 0;
	int lineNumber = 1;
	do
	{
		//_sleep(200);
		const char *pEnd = strchr(p, '\n');
		if (pEnd != NULL)
			i = pEnd - p + 1;
		else
			i = -1;

		if (i >= 256)
		{
			logger->log(LOG_WARNING, "Line %d is very long\n", lineNumber);
		}
		else if (i >= 0)
		{
			strncpy(line, p, i);
			line[i] = 0;
			execute_line(line, ++lineNumber);
			p = pEnd+1;
		}
	} while (i >= 0);
}

//====================================================================================================
//читает строки в список
void GCodeInterpreter::execute_file(IExecutor *ix)
{
	RunnerData  runnerDump;
	runnerDump = runner;

	if (executor)
		executor = ix;
	if (!executor)
	{
		logger->log(LOG_ERROR,"Executor not defined");
		return;
	}

	int lineNumber = 0;
	for (auto iter = inputFile.begin(); iter != inputFile.end(); ++iter)
	{
		execute_line(iter->c_str(), ++lineNumber);
	};
	// restore ???
	runner = runnerDump;
}

//====================================================================================================
//читает строки в список
void GCodeInterpreter::execute_line(const char *line, int lineNumber)
{
	if (executor)
		executor->set_current_line(lineNumber);
	auto result = execute_frame(line);
	if (result.code)
		logger->log(LOG_ERROR, "Error line %d %s\n", lineNumber, result.description.c_str());
}

//====================================================================================================
//Actions are executed in the following order:
//1. any comment.
//2. a feed mode setting (g93, g94, g95)
//3. a feed rate (f) setting if in units_per_minute feed mode.
//4. a spindle speed (s) setting.
//5. a tool selection (t).
// Set Plane
//6. "m" commands as described in convert_m (includes tool change).
//7. any g_codes (except g93, g94, g95) as described in convert_g.
//8. stopping commands (m0, m1, m2, m30, or m60).


InterError GCodeInterpreter::execute_frame(const char *str)
{
	CmdParser parser;                              //парсер команд

	if (!parser.parse_codes(str))
		return parser.get_state();

	if (!parser.check_modal_group()) //проверяем что в одной строке нет команд одной группы
		return parser.get_state();
// выполняем команды в нужной последовательности 
	if (!run_feed_mode(parser))
		return get_state();
	if (!run_feed_rate(parser))
		return get_state();
	if (!run_spindle_mode(parser))
		return get_state();
	if (!run_speed(parser))
		return get_state();
	if (!run_tool_cmd(parser))
		return get_state();
	if (!run_mcode(parser))
		return get_state();
	if (!run_gcode(parser))
		return get_state();
	if (!run_stop(parser))
		return get_state();

	return InterError();
}


bool GCodeInterpreter::run_feed_mode(const CmdParser &parser)
{
	if (parser.contain_cmd(ModalGroup_FEEDMODE))
	{
		error_ = InterError(InterError::Code::INVALID_STATEMENT, "FEEDMODE not suppoted");
		return false;
	}
	else
		return true;
}

bool GCodeInterpreter::run_feed_rate(const  CmdParser &parser)
{
	double feed;
	if (parser.getRValue('F', &feed))
	{
		if (feed <= 0. || feed > MAX_FEED_RATE)
		{
			error_ = InterError(InterError::Code::WRONG_VALUE, "feed value is incorrect ");
			return false;
		}
		runner.feed = feed;
		if (executor)
			executor->set_feed_rate(feed);
	}
	return true;
}


bool GCodeInterpreter::run_spindle_mode(const  CmdParser &parser)
{
	if (parser.contain_cmd(ModalGroup_SPINDLEMODE))
	{
		error_ = InterError(InterError::Code::INVALID_STATEMENT, "SPINDLE mode not suppoted");
		return false;
	}
	return true;
}


bool GCodeInterpreter::run_speed(const CmdParser &parser)
{
	int speed;
	if (parser.getIValue('S', &speed))
	{
		if (speed <= 0. || speed > MAX_SPINDELSPEED)
		{
			error_ = InterError(InterError::Code::WRONG_VALUE, "spindle speed  is incorrect ");
			return false;
		}
		runner.spindlespeed = speed;
		if (executor)
			executor->set_spindle_speed(speed);
	}
	return true;
}

// M06
bool GCodeInterpreter::run_tool_cmd(const CmdParser &parser)
{
	if (parser.contain_cmd(ModalGroup_TOOL_CHANGE))
	{
		int tool = 0;
		if (parser.getIValue('T', &tool))
		{
			if (tool > 0. || tool <= 15)
			{
				if (runner.toolid != tool)
				{
					runner.toolid = tool;
					if (executor)
						executor->set_tool_change(tool);
				}
				return true;
			}
			else
				error_ = InterError(InterError::Code::WRONG_VALUE, "invalid tool number");
		}
		else
			error_ = InterError(InterError::Code::WRONG_VALUE, " tool number is not spesified");
		return false;
	}
	return true;
}



// run all other mcode
//            M01	Приостановить работу станка до нажатия кнопки «старт», если включен режим подтверждения останова	G0 X0 Y0 Z100 M1;
//            M02	Конец программы	M02;
//            M03	Начать вращение шпинделя по часовой стрелке	M3 S2000;
//            M04	Начать вращение шпинделя против часовой стрелки	M4 S2000;
//            M05	Остановить вращение шпинделя	M5;
//            M06	Сменить инструмент	M6 T15;
//            M07	Включить дополнительное охлаждение	M3 S2000 M7;
//            M08	Включить основное охлаждение	M3 S2000 M8;
//            M09	Выключить охлаждение	G0 X0 Y0 Z100 M5 M9;
//            M30	Конец информации	M30;
//            M98	Вызов подпрограммы	M98 P101;
//            M99	Конец подпрограммы, возврат к основной программе

bool GCodeInterpreter::run_mcode(const  CmdParser &parser)
{
	for (auto iter = parser.codes.begin(); iter != parser.codes.end(); ++iter)
	{
		int intValue = int(iter->value);
		if (iter->letter != 'M')
			continue;
		switch (intValue)
		{
		case 2:
		case 6:
			return true;
		case 98:
		case 99:
			error_ = InterError(InterError::Code::WRONG_VALUE, "subroutines don't not support yet");
			return false;
		}
		executor->run_mcode(intValue);
	}
	return true;
}


void GCodeInterpreter::setopionalcoordinate(Coords &newpos, optdouble *pvalss)
{
	for (int i = 0; i < MAX_AXES; ++i)
	{
		if (pvalss[i])
			newpos.r[i] = to_mm(pvalss[i].value());
	}
}


bool GCodeInterpreter::run_gcode(const CmdParser &parser)
{

	Coords newpos;
	optdouble i, j, k, r;
	optdouble valcc[MAX_AXES];
	MotionMode newMove = MotionMode_NONE;
	// current coordinate is in the local system
	Coords  currentLocal = runner.position;
	to_local(currentLocal);

	bool  g52 = false, g53 = false;

	for (auto iter = parser.codes.begin(); iter != parser.codes.end(); ++iter)
	{

		switch (iter->letter)
		{
		case 'A': valcc[3] = iter->value; break;
		case 'B': valcc[4] = iter->value; break;
		case 'C': valcc[5] = iter->value; break;
		case 'X': valcc[0] = iter->value; break;
		case 'Y': valcc[1] = iter->value; break;
		case 'Z': valcc[2] = iter->value; break;

		case 'I': i = iter->value; break;
		case 'J': j = iter->value; break;
		case 'K':k = iter->value; break;
		case 'R': r = iter->value; break;
			// как-то очень криво - нужно как-то метить необработанные команды и на них ругаться
		case 'P':
		case 'Q':
		case 'D':
		case 'L':
			error_ = InterError(InterError::INVALID_STATEMENT, std::string("unknown code: ") + std::to_string(iter->letter));
			return false;
		default:
			break;
		}
		if (iter->letter != 'G')
			continue;

		int intValue = static_cast<int>(iter->value);
		switch (intValue)
		{
		case 0:   newMove = MotionMode_FAST;          break;
		case 1:   newMove = MotionMode_LINEAR;      break;
		case 2:   newMove = MotionMode_CW_ARC;    break;
		case 3:   newMove = MotionMode_CCW_ARC;  break;
		case 17: runner.plane = Plane_XY; break;
		case 18: runner.plane = Plane_XZ; break;
		case 19: runner.plane = Plane_YZ; break;
		case 20: runner.units = UnitSystem_INCHES; break;
		case 21: runner.units = UnitSystem_MM; break;
		case 53:  g53 = true;  break;  //move to position in Global coordinate system
		case 52:  g52 = true; break; // offset of current coordinats system do offset latter
		case 54:  case 55: case 56: case 57: case 58:
			runner.origin = env->GetG54G58(intValue - 54);
			break;

		case 80: runner.cycle = CannedCycle_RESET; break;
		case 81: runner.cycle = CannedCycle_SINGLE_DRILL; break;
		case 82: runner.cycle = CannedCycle_DRILL_AND_PAUSE; break;
		case 83: runner.cycle = CannedCycle_DEEP_DRILL; break;

		case 90: runner.incremental = false; break;
		case 91: runner.incremental = true; break;

			//case 98: runner.cycleLevel = CannedLevel_HIGH; break;
			//case 99: runner.cycleLevel = CannedLevel_LOW; break;

		default:
			error_ = InterError(InterError::INVALID_STATEMENT,
				std::string("unknown code: G") + std::to_string(intValue));
			return false;
		}
	}
	if (g52)
	{
		setopionalcoordinate(runner.origin, valcc);
		if (newMove != MotionMode_NONE)
		{

			error_ = InterError(InterError::INVALID_STATEMENT,
				std::string("G52 and movement command can not be in one frame"));
			return false;
		}
	}
	if (g53)
	{
		error_ = InterError(InterError::INVALID_STATEMENT,
			std::string("G53 does not suppered yet, sorry"));
		return false;
	}

	// check if need not move just return
	if (newMove != MotionMode_NONE)
	{

		Coords newPos = get_new_coordinate(currentLocal, valcc);

		switch (newMove)
		{
		case MotionMode_FAST: move_to(newPos, true); break;
		case MotionMode_LINEAR: move_to(newPos, false);   break;
		case MotionMode_CW_ARC:   arc_to(newPos, true); break;
		case MotionMode_CCW_ARC: arc_to(newPos, false); break;
		case MotionMode_NONE:  break; // ta avoid compiler warning
		}
		if (error_.code)
			return false;
		runner.motionMode = newMove;
	}

	return true;
}

//====================================================================================================
//чтение новых координат с учётом модальных кодов
Coords GCodeInterpreter::get_new_coordinate(Coords &oldLocal, optdouble *pvalss)
{
	Coords  newpos;
	if (runner.incremental)
	{
		newpos = runner.position;
		for (int i = 0; i < MAX_AXES; ++i)
		{
			if (pvalss[i])
				newpos.r[i] += to_mm(pvalss[i].value());
		}
	}
	else
	{
		newpos = oldLocal;
		setopionalcoordinate(newpos, pvalss);
		to_global(newpos);
	}
	return newpos;
}

//====================================================================================================
//сдвиг в глобальные координаты
void GCodeInterpreter::to_global(Coords &coords)
{
	for (int i = 0; i < MAX_AXES; ++i)
		coords.r[i] += runner.origin.r[i];
}

//====================================================================================================
//получение локальных координат из глобальных
void GCodeInterpreter::to_local(Coords &coords)
{
	for (int i = 0; i < MAX_AXES; ++i)
		coords.r[i] -= runner.origin.r[i];
}

bool GCodeInterpreter::run_stop(const CmdParser &parser)
{
	//           M02	Конец программы	M02;
	if (parser.contain_cmd('M', 2))
	{
		executor->set_end_programm();
	}
	return true;
}



//====================================================================================================
void  GCodeInterpreter::move_to(const Coords &position, bool fast)
{

	if (executor)
	{
		if (fast)
		{
			executor->straight_traverce(position);
		}
		else
			executor->straight_feed(position);
	}
	runner.position = position;

}

void  GCodeInterpreter::arc_to(const Coords &position, bool cw)
{

	if (executor)
	{
		executor->arc_feed(position, cw);
	}
	runner.position = position;
}


//====================================================================================================
//перевод в мм
coord GCodeInterpreter::to_mm(coord value)
{
	if (runner.units == UnitSystem_INCHES)
		value *= MM_PER_INCHES;
	return value;
}

//====================================================================================================
Coords GCodeInterpreter::to_mm(Coords value)
{
	for (int i = 0; i < MAX_AXES; ++i)
		value.r[i] = to_mm(value.r[i]);
	return value;
}


InterError CmdParser::get_state() const
{
	return state;
}

//====================================================================================================
//читает данные из строки в массив
bool  CmdParser::parse_codes(const char *frame)
{
	codes.clear();
	state = InterError();
	int position = 0;

	GKey key;
	while (parse_code(frame, position, key))
	{
		codes.push_back(key);
	}

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

	if (letter == '%')
		return false;

	if (letter >= 'a' && letter <= 'z')
		letter += 'A' - 'a';

	if (letter < 'A' || letter > 'Z')
	{
		state = InterError(InterError::WRONG_LETTER, std::string("wrong letter: ") + letter);
		return false;
	}

	key.position = position;
	position++;

	double value;
	find_significal_symbol(frame, position);
	if (!parse_value(frame, position, value))
	{
		state = InterError(InterError::WRONG_VALUE, std::string("cant parse value"));
		return false;
	};
	key.letter = letter;
	key.value = value;
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
			while (frame[position] != ')' && frame[position] != 0) position++;
			if (frame[position] == ')') position++;
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
	Flags flagModal;
	for (auto iter = codes.begin(); iter != codes.end(); ++iter)
	{
		ModalGroup group = get_modal_group(*iter);
		if (group > 0)
		{
			if (flagModal.get(group))   //встретили два оператора из одной группы
			{
				state = InterError(InterError::DOUBLE_DEFINITION,
					std::string("conflict modal group for ") + std::to_string(iter->letter) + std::to_string(iter->value));
				return false;
			}
			flagModal.set(group, true);
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
