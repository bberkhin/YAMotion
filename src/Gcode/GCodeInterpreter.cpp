#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include "GCodeInterpreter.h"
#include "cmdparser.h"


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

	char line[MAX_GCODE_LINELEN];
	const char *p ;
	const char *pEnd = data;
	int lineNumber = 1;
	do
	{
		p = pEnd;
		pEnd = cpy_close_and_downcase(line, p, lineNumber);
		if (line[0] != 0 )
		{
			execute_line(line, lineNumber);
		}
		++lineNumber;	
	} while (pEnd);
}

const char *GCodeInterpreter::cpy_close_and_downcase(char *line, const char *src, int lineNumber)       //!< string: one line of NC code
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
			logger->log(LOG_WARNING, "Line %d is very long\n", lineNumber);
			break;
		}

		if ((item == ';' || (item == '/' && src[m+1] == '/')  ) && !comment)
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
				logger->log(LOG_WARNING, "Line %d  '(' inside comment", lineNumber);
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
	if ( comment )
		logger->log(LOG_WARNING, "Line %d  unclosed comment found", lineNumber);
	
	line[n] = 0;

	if (src[m] != '\0' && src[m] == '\n')//need skip long string
	{
		for (;  src[m] != '\0' && src[m] != '\n'; m++);
	}
	
	if (src[m] == '\n')
		return src + m + 1; // next symvol
	else
		return NULL;

}

//====================================================================================================
//читает строки в список
void GCodeInterpreter::execute_file()
{
	RunnerData  runnerDump;
	runnerDump = runner;
	
	if (!executor)
	{
		logger->log(LOG_ERROR,"Executor not defined");
		return;
	}

	int lineNumber = 0;
	char line[MAX_GCODE_LINELEN];
	for (auto iter = inputFile.begin(); iter != inputFile.end(); ++iter)
	{
		cpy_close_and_downcase(line, iter->c_str(), lineNumber);
		execute_line(line, ++lineNumber);
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
	
	state.clear();
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
	CmdParser parser(env);                              //парсер команд

	if (!parser.parse(str))
		return parser.get_state();
	
	if (!parser.neead_execute())
		return InterError();

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


bool GCodeInterpreter::run_feed_mode( const CmdParser &parser )
{
	if (parser.contain_cmd(ModalGroup_FEEDMODE))
		RET_F_SETSTATE(NOTSUPPORTEDYET, "FEEDMODE not suppoted");
	else
		return true;
}

bool GCodeInterpreter::run_feed_rate(const  CmdParser &parser)
{
	double feed;
	if (parser.getRParam(PARAM_F, &feed))
	{
		if (feed <= 0. || feed > MAX_FEED_RATE)
			RET_F_SETSTATE(WRONG_VALUE, "feed value is incorrect ");
		runner.feed = feed;
		if (executor)
			executor->set_feed_rate(feed);
	}
	return true;
}


bool GCodeInterpreter::run_spindle_mode(const  CmdParser &parser)
{
	if (parser.contain_cmd(ModalGroup_SPINDLEMODE))
		RET_F_SETSTATE(NOTSUPPORTEDYET, "SPINDLE mode not suppoted");
	return true;
}


bool GCodeInterpreter::run_speed(const CmdParser &parser)
{
	double speed;
	if (parser.getRParam(PARAM_S, &speed))
	{
		if (speed <= 0. || speed > MAX_SPINDELSPEED)
			RET_F_SETSTATE(WRONG_VALUE, "spindle speed  is incorrect ");
		runner.spindlespeed = speed;
		if (executor)
			executor->set_spindle_speed(speed);
	}
	return true;
}

// M06
bool GCodeInterpreter::run_tool_cmd(const CmdParser &parser)
{
	if (parser.contain_m(6))
	{
		int tool = 0;
		if (parser.getIParam(PARAM_T, &tool))
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
				RET_F_SETSTATE(WRONG_VALUE, "invalid tool number");
		}
		else
			RET_F_SETSTATE(WRONG_VALUE, "tool number is not spesified");
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
	const m_container &mcodes = parser.getMCodes();
	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
	{
		switch (*iter)
		{
		case 2:
		case 6:
			return true;
		case 98:
		case 99:
			RET_F_SETSTATE(WRONG_VALUE, "subroutines don't not support yet");			
		}
		executor->run_mcode(*iter);
	}
	return true;
}


bool GCodeInterpreter::run_gcode(const CmdParser &parser)
{

	Coords newpos;
	MotionMode newMove = runner.motionMode;

	// current coordinate is in the local system
	Coords  currentLocal = runner.position;
	to_local(currentLocal);

	const g_container &gcodes = parser.getGCodes();

	bool  g52 = false, g53 = false;


	for (auto iter = gcodes.begin(); iter != gcodes.end(); ++iter)
	{
		int num = *iter;
		switch (*iter)
		{
			case G_0:   newMove = MotionMode_FAST;   break;
			case G_1:   newMove = MotionMode_LINEAR; break;
			case G_2:   newMove = MotionMode_CW_ARC; break;
			case G_3:   newMove = MotionMode_CCW_ARC; break;
			case G_17: runner.plane = Plane_XY; break;
			case G_18: runner.plane = Plane_XZ; break;
			case G_19: runner.plane = Plane_YZ; break;
			case G_20: runner.units = UnitSystem_INCHES; break;
			case G_21: runner.units = UnitSystem_MM; break;
			//case G_40://	Cutter Diameter Compensation
			case G_53:  g53 = true;  break;  //move to position in Global coordinate system
			case G_52:  g52 = true; break; // offset of current coordinats system 
			case G_54:  case 55: case 56: case 57: case 58:
				runner.origin = env->GetG54G58(*iter - 54);
				break;

			case G_80: runner.cycle = CannedCycle_RESET; newMove = MotionMode_NONE;  break;
			case G_81: runner.cycle = CannedCycle_SINGLE_DRILL; break;
			case G_82: runner.cycle = CannedCycle_DRILL_AND_PAUSE; break;
			case G_83: runner.cycle = CannedCycle_DEEP_DRILL; break;

			case G_90: runner.incremental = false; break;
			case G_91: runner.incremental = true; break;
			//case 98: runner.cycleLevel = CannedLevel_HIGH; break;
			//case 99: runner.cycleLevel = CannedLevel_LOW; break;

		default:
			RET_F_SETSTATE(INVALID_STATEMENT, "Unknown code: G%d", (*iter)/10 );
		}
	}

	if (g52)
	{
		setcoordinates( runner.origin, parser);
		if (newMove != MotionMode_NONE)
			RET_F_SETSTATE(INVALID_STATEMENT, "G52 and movement command can not be in one frame" );
	}
	if (g53)
		RET_F_SETSTATE(INVALID_STATEMENT, "G53 does not suppered yet");


	// check if need not move just return
	if (newMove != MotionMode_NONE)
	{

		Coords newPos = get_new_coordinate(currentLocal, parser );

		switch (newMove)
		{
			case MotionMode_FAST: move_to(newPos, true); break;
			case MotionMode_LINEAR: move_to(newPos, false);   break;
			case MotionMode_CW_ARC:   arc_to(newPos, true); break;
			case MotionMode_CCW_ARC: arc_to(newPos, false); break;
			case MotionMode_NONE:  break; // ta avoid compiler warning
		}
		if (state.code)
			return false;
		runner.motionMode = newMove;
	}

	return true;
}

//====================================================================================================
//чтение новых координат с учётом модальных кодов

void GCodeInterpreter::setcoordinates(Coords &newpos, const CmdParser &parser) const
{
	parser.getRParam(PARAM_X, &(newpos.x));
	parser.getRParam(PARAM_Y, &(newpos.y));
	parser.getRParam(PARAM_Z, &(newpos.z));
	parser.getRParam(PARAM_A, &(newpos.a));
	parser.getRParam(PARAM_B, &(newpos.b));
	parser.getRParam(PARAM_C, &(newpos.c));	
}


Coords GCodeInterpreter::get_new_coordinate(Coords &oldLocal, const CmdParser &parser)
{
	Coords  newpos;
	if (runner.incremental)
	{
		newpos = runner.position;
		double v;
		if (parser.getRParam(PARAM_X, &v)) newpos.x += to_mm(v);
		if (parser.getRParam(PARAM_Y, &v)) newpos.y += to_mm(v);
		if (parser.getRParam(PARAM_Z, &v)) newpos.z += to_mm(v);
		if (parser.getRParam(PARAM_A, &v)) newpos.a += to_mm(v);
		if (parser.getRParam(PARAM_B, &v)) newpos.b += to_mm(v);
		if (parser.getRParam(PARAM_C, &v)) newpos.c += to_mm(v);
	}
	else
	{
		newpos = oldLocal;
		setcoordinates(newpos, parser);
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
	if ( parser.contain_m(2) )
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

