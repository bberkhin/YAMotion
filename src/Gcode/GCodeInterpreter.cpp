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
	env(penv), executor(ix), logger(log), gfile(0)
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
	runner = RunnerData();
	state = InterError();
//	std::string file_name.;     don't change name
	submap.clear();
	while( !substack.empty() ) substack.pop();
	cursubr_.clear();
	fpos = -1;
}



//====================================================================================================
// open the file
bool GCodeInterpreter::open_nc_file(const wchar_t *name)
{
	if ( file_name.empty() && name == NULL )
		RET_F_SETSTATE( ERROR_FILEREAD, "File name not specified" );
	
	//empty or new name
	if (name != NULL && file_name != std::wstring(name) )
	{
		file_name = name;
		close_nc_file();
	}

	if (gfile != NULL)
		return true;
	gfile = _wfopen(name,L"r");
	IF_F_RET_F_SETSTATE((gfile != NULL), ERROR_FILEREAD, "Can not open file %s", name); 
	init();
	return true;
}

void GCodeInterpreter::close_nc_file()
{
	if (gfile)
		fclose(gfile);
	gfile = NULL;
}

void GCodeInterpreter::execute_file()
{
	SubratinInfo mainsub;
	mainsub.name = "_main_";
	mainsub.callfrom = mainsub.startpos = 0;
	mainsub.type = O_;
	mainsub.nline = 1;
	
	substack.push(mainsub);
	cursubr_ = mainsub.name;
	int nline = 1;
	execute_file_int(0, &GCodeInterpreter::execute_frame, nline );


	// next time will reopen and seek to begin and call init
	if ( state.code == PRAGRAMM_ENDCLEAR)
	{ 
		close_nc_file(); 
	}
	
	if (state.code != PRAGRAMM_END && state.code != PRAGRAMM_ENDCLEAR )
	{
		logger->log(LOG_WARNING, "No end of programm command ");
		executor->set_end_programm();
	}
	if (substack.size() != 1)
	{
		logger->log(LOG_WARNING, "The programm end being in subrotinue" );
	}

	// clear stack
	while (!substack.empty()) substack.pop();

	
}

bool GCodeInterpreter::execute_file_int( long pos, ExecFunction fun, int &lineNumber )
{
	char line[MAX_GCODE_LINELEN];
	size_t length;
	IF_F_RET_F(open_nc_file());
	IF_F_RET_F_SETSTATE((fseek(gfile, pos, SEEK_SET) == 0), ERROR_FILEREAD, "Can not seek to start of file");

	for (; true ; ++lineNumber)
	{
		if (fgets(line, MAX_GCODE_LINELEN, gfile) == NULL)
			break;
		length = strlen(line);
		if (length == (MAX_GCODE_LINELEN - 1))    // line is too long. need to finish reading the line to recover
		{
			for (; fgetc(gfile) != '\n' && !feof(gfile););
			logger->log(LOG_WARNING, " Line %d is too long.", lineNumber);
		}
		
		fpos = ftell(gfile); 
		cpy_close_and_downcase( line, line, lineNumber);
	
		if (executor)		
			executor->set_current_line(lineNumber);

		state.clear();
		
		state = ((*this.*fun))( line );

		if (state.code == PRAGRAMM_END || state.code == PRAGRAMM_ENDCLEAR || state.code == SUBROTINE_END )
			break;

		else if (state.code )
			logger->log(LOG_ERROR, "Error line %d %s\n", lineNumber, state.description.c_str());

	}

	return true;
}

/*
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


	*/

InterError GCodeInterpreter::is_subrotin_start(const char *str)
{
	CmdParser parser(env);                              //парсер команд

	if (!parser.parse(str))
		return parser.get_state();

	if (!parser.getSubName().empty() )
	{
		InterError out;
		if (parser.getSubName() == cursubr_)
			out.code = SUBROTINE_END; // to out from internal circle
		return out;
	}
	return InterError();
}

bool GCodeInterpreter::find_subrotinue(const char *subname, SubratinInfo *psub )
{
	auto iter = submap.find(subname);
	if (iter != submap.end())
	{
		*psub = iter->second;
		psub->callfrom = fpos;
	}
	else
	{
		//find in file
		psub->name = subname;
		psub->callfrom = fpos;
		int nline = 1;
		std::string savesbn = cursubr_;
		
		cursubr_ = subname;
		if (!execute_file_int(0, &GCodeInterpreter::is_subrotin_start, nline))
		{
			cursubr_ = savesbn;
			return false;
		}

		cursubr_ = savesbn;
		if (state.code != SUBROTINE_END)
		{
			RET_F_SETSTATE(SUBROUTINE_ERROR, "Can not find subroutinue: %s", subname);
		}

		psub->nline = nline+1; //+1 becouse sekeep o100 string
		psub->startpos = ftell(gfile);
		submap.insert( std::pair<std::string, SubratinInfo>(psub->name,*psub) );
	}
	return true;
}

bool GCodeInterpreter::execute_subrotinue( const  CmdParser parser )
{
	std::string sname;

	double dblval;
	int ival;

	IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_P, &dblval), PARAMETER_ERROR, "There is no 'P' parameter for m98");
	IF_F_RET_F(parser.real_to_int(&dblval, &ival));
	sname = std::to_string(ival);
	
	SubratinInfo newsub;
	IF_F_RET_F(find_subrotinue(sname.c_str(), &newsub));
	substack.push(newsub);
	
	

	int times = 1;
	parser.getIParam(PARAM_L, &times);

	for (int i = 0; i < times; ++i)
	{
		reset_motion_mode();
		cursubr_ = sname; //restore current sub
		int nline = substack.top().nline;
		execute_file_int(substack.top().startpos, &GCodeInterpreter::execute_frame, nline );
		reset_motion_mode();
		if (state.code == SUBROTINE_END)
			state.clear(); // clear END_SUBROTINUE STATE 
		else if (state.code == PRAGRAMM_END || state.code == PRAGRAMM_ENDCLEAR)
			break;
	}
	
	// rewind file to the position just after the call
	long pos = substack.top().callfrom;
	IF_F_RET_F_SETSTATE((fseek(gfile, pos, SEEK_SET) == 0), ERROR_FILEREAD, "Can not seek to right position %ld of file", pos);

	substack.pop();
	if (!substack.empty())
		cursubr_ = substack.top().name;

	return true;
	
}



InterError GCodeInterpreter::execute_frame(const char *str)
{
	CmdParser parser(env);                              //парсер команд
	bool executablecall = (cursubr_ == substack.top().name);

	if (!parser.parse(str))
		return parser.get_state();
	
	if (!parser.neead_execute())
		return InterError();

	if ( parser.contain_m(98) && executablecall) // call sub
	{
		execute_subrotinue( parser );
		return get_state();
	}
	else if ( !parser.getSubName().empty() ) // start sub desc
	{
		cursubr_ = parser.getSubName();
		return get_state();
	}
	else if ( parser.contain_m(99) ) // end sub
	{
		// variant 1 you now execute the subrotine 
		if ( executablecall )
		{
			// stop internal loop
			state.code = SUBROTINE_END;
			return get_state();
		}
		// variant 2 you just go throw code not execute 
		cursubr_ = substack.top().name; // restore execute name
		return get_state();
	}
	//stopping commands(m0, m1, m2, m30, or m60).
	else if ( run_stop(parser) ) // END of programm
	{	
		return get_state();
	}

	// check that we are in the same subrotinue as in the stack
	if (cursubr_ != substack.top().name )
		return get_state();


	//====================================================================================================
	//Actions are executed in the following order:
	//1. run dwell
	//2. a feed mode setting (g93, g94, g95)
	//3. a feed rate (f) setting if in units_per_minute feed mode.
	//4. a spindle speed (s) setting.
	//5. a tool selection (t).
	// Set Plane
	//6. "m" commands as described in convert_m (includes tool change).
	//7. any g_codes (except g93, g94, g95) as described in convert_g.
	

	if (!run_dwell(parser))
		return get_state();
	if (!run_input_mode(parser))
		return get_state();
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

	return InterError();
}


bool GCodeInterpreter::run_feed_mode( CmdParser &parser )
{
	//G93, G94, G95
	//G93  is Inverse Time Mode.In inverse time feed rate mode, an F word means the move should be completed in[one divided by the F number] minutes.
	//G94 - is Units per Minute Mode.
	//G95 - is Units per Revolution Mode 
	if (parser.contain_g(G_93))
	{
		//G96 D2500 S250
		RET_F_SETSTATE( NO_VALUE, "G93 Inverse Time Mode not supported");
		parser.remove_g(G_93);
	}
	else if (parser.contain_g(G_94))
	{
		// ok do nothing
		parser.remove_g(G_94);
	}
	else if (parser.contain_g(G_95))
	{
		RET_F_SETSTATE(NO_VALUE, "G95 - is Units per Revolution Mode not supported");
		parser.remove_g(G_95);
	}
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


bool GCodeInterpreter::run_dwell(CmdParser &parser)
{
	if (parser.contain_g(G_4))
	{
		//G96 D2500 S250
		double millseconds, sec;
		if (parser.getRParam(PARAM_P, &millseconds))
			; 
		else if (parser.getRParam(PARAM_X, &sec))
		{
			millseconds = sec * 1000;
		}
		else if (parser.getRParam(PARAM_S, &sec))
		{
			millseconds = sec * 1000;
		}
		else if (parser.getRParam(PARAM_U, &sec))
		{
			millseconds = sec * 1000;
		}
		if (parser.params_count() != 1 )
			RET_F_SETSTATE(WRONG_VALUE, "very many parameters for dwell G4 ");

		executor->set_dwell(static_cast<long>(millseconds));
		reset_motion_mode();
		parser.remove_g(G_4);
		parser.remove_params();
	}
	return true;

}


bool GCodeInterpreter::run_spindle_mode( CmdParser &parser)
{
	if ( parser.contain_g(G_96) )
	{
		//G96 D2500 S250
		double diam, speed;
		IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_D, &diam), NO_VALUE, "Parametr 'D' must be defined for G96 (CSS mode)");
		IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_S, &speed), NO_VALUE, "Parametr 'S' must be defined for G96 (CSS mode)");
		executor->set_css_spindlemode(diam, speed);		
		parser.remove_g(G_96);
		parser.remove_param(PARAM_D);
		parser.remove_param(PARAM_S);
	}
	else if (parser.contain_g(G_97))
	{
		executor->set_regular_spindlemode();
		parser.remove_g(G_97);
	}
	return true;
}

bool GCodeInterpreter::run_input_mode( CmdParser &parser )
{
	if (parser.contain_g(G_10))
	{
		//G10 L2 P2 X2 Y0 Z0(Set G55 offset to 2, 0, 0)

		//now we can work only with L2  - setting coordinate sistem
		int l;
		double p;
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_L, &l), NO_VALUE, "Parametr 'L' must be defined for G10 ");
		IF_F_RET_F_SETSTATE((l==2), WRONG_VALUE,"we can work only with L2 for G10 ");
		IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_P, &p), NO_VALUE, "Parametr 'p' must be defined for G10 ");
		int ip = static_cast<int>(p);
		IF_F_RET_F_SETSTATE((ip >= 1 && ip <= 5), WRONG_VALUE, "Parametr 'p' out of range ");
		Coords newpos;
		setcoordinates(newpos, parser);
		env->SetG54G58(ip - 1, newpos, parser.contain_g(G_91)); 
		parser.clear();
	}
	return true;
}

bool GCodeInterpreter::run_tool_crc(const CmdParser &parser)
{
//G_40:	runner.tool_crc = TCRC_NONE;	//Tool radius compensation off
//G_41:	runner.tool_crc = TCRC_LEFT;	//Turn on cutter radius compensation left
//G_42:	runner.tool_crc = TL_RIGHT;	    //Turn on cutter radius compensation right
	
	if (parser.contain_g(G_40))
	{
		runner.tool_crc_type = CutterCompType_NONE;
		runner.tool_crc = 0;
		return true;
	}
	else if (parser.contain_g(G_41))
	{
		runner.tool_crc_type = CutterCompType_LEFT;	//Turn on cutter radius compensation left
	}
	else if (parser.contain_g(G_42))
	{
		runner.tool_crc_type = CutterCompType_RIGHT;	    //Turn on cutter radius compensation right
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "GCodeInterpreter::run_tool_crc can notbe called here");

	double d = 0;
	IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_D, &d), NO_VALUE, "Parametr 'D' must be defined for G41 ");
	IF_F_RET_F_SETSTATE((d != 0), WRONG_VALUE, "Parametr 'D' must be non zero. Use G40 to cancel cutter radius compensation");
	runner.tool_crc = d;
	return true;

}
	


bool GCodeInterpreter::run_tool_height_offset(const CmdParser &parser)
{
	//G_43:  Tool height offset compensation negative
	//G_44:  Tool height offset compensation positive
	//G_49:  Tool height offset compensation off
	int h = 0;
	if (parser.contain_g(G_49))
	{
		runner.tools_offset_height = 0;
	}
	else if (parser.contain_g(G_43))
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G44 ");
		if  ( h > 0 )
			runner.tools_offset_height = -h;
		else
			runner.tools_offset_height = h;
	}
	else if (parser.contain_g(G_44))
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G43 ");
		runner.tools_offset_height = h;
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "GCodeInterpreter::run_tool_height_offset can notbe called here");

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

void GCodeInterpreter::reset_motion_mode()
{
	runner.motionMode = MotionMode_NONE;
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
		switch (num)
		{
		// Movement
			case G_0:   newMove = MotionMode_FAST;   break;
			case G_1:   newMove = MotionMode_LINEAR; break;
			case G_2:   newMove = MotionMode_CW_ARC; break;
			case G_3:   newMove = MotionMode_CCW_ARC; break;
		// Src Plane
			case G_17: runner.plane = Plane_XY; break;
			case G_18: runner.plane = Plane_XZ; break;
			case G_19: runner.plane = Plane_YZ; break;
		// Units
			case G_20: runner.units = UnitSystem_INCHES; break;
			case G_21: runner.units = UnitSystem_MM; break;
		// Porbe G_38 for linuxcnc  
			case G_31: newMove = MotionMode_PROBE; break;
		// 	G32 is a thread cutting.
			case G_32: 
				reset_motion_mode();  
				RET_F_SETSTATE(INVALID_STATEMENT, "G32 threading mode doas not supporeted yet");
				break;
		 // Cutter radius compensation (CRC),
			case G_40:	//Tool radius compensation off
			case G_41:	//Turn on cutter radius compensation left
			case G_42:  //Turn on cutter radius compensation right
				IF_F_RET_F( run_tool_crc(parser));
				break;
		// Tool height offset compensation
			case G_43:  //Tool height offset compensation negative
			case G_44:  //Tool height offset compensation positive
			case G_49:  //Tool height offset compensation off
				IF_F_RET_F(run_tool_height_offset(parser));
				break;
		// Coordinate systems
			case G_53:  g53 = true;  break;  //move to position in Global coordinate system
			case G_52:  g52 = true; break; // offset of current coordinats system 
			case G_54:  case G_55: case G_56: case G_57: case G_58:
				runner.origin = env->GetG54G58(*iter - 54);
				break;
		//G61, G64, G60 G - Code: Exact Stop & Anti - Backlash
			case G_61: runner.accuracy = AccuracyExactStop;
			case G_64: runner.accuracy = AccuracyNormal;
				break;
		//  Drilling Cycle
			case G_80: runner.cycle = CannedCycle_RESET; reset_motion_mode();  break;
			case G_81: runner.cycle = CannedCycle_SINGLE_DRILL; break;
			case G_82: runner.cycle = CannedCycle_DRILL_AND_PAUSE; break;
			case G_83: runner.cycle = CannedCycle_DEEP_DRILL; break;
				break;
		//  Boring Cycle
			case G_85:
			case G_86:
			case G_87:
			case G_88:
			case G_89:
				 break;
						 
			case G_90: runner.incremental = false; break;
			case G_91: runner.incremental = true; break;
		
		//Coordinate System Offset  //TODO
			case G_92: 
			case G_92_1:   
			case G_92_2:
			case G_92_3:	
				g52 = true; 
				break;  

			case G_98: runner.cycleLevel = CannedLevel_HIGH; break; //Отмена G99
			case G_99: runner.cycleLevel = CannedLevel_LOW; break; // Return to R level in canned cycle
			

		default:
			RET_F_SETSTATE(INVALID_STATEMENT, "Unknown code: G%d", (num)/10 );
		}
	}

	if (g52)
	{
		setcoordinates( runner.origin, parser);
		reset_motion_mode();
		if (parser.contain_cmd( ModalGroup_MOVE ) )
			RET_F_SETSTATE(INVALID_STATEMENT, "G52 and movement command can not be in one frame" );
	}
	


	// check if need not move just return
	if (newMove != MotionMode_NONE)
	{

		Coords newPos;
		if (g53) // do movement in Global Coordinates
		{
			newPos = runner.position;
			setcoordinates(newPos, parser);
		}
		else
		{
			newPos = get_new_coordinate(currentLocal, parser);
		}

		switch (newMove)
		{
			case MotionMode_FAST:    move_to(newPos, true); break;
			case MotionMode_LINEAR:  move_to(newPos, false);   break;
			case MotionMode_CW_ARC:  arc_to(newPos, true); break;
			case MotionMode_CCW_ARC: arc_to(newPos, false); break;
			case MotionMode_PROBE:   probe_to(newPos);   break;
			case MotionMode_NONE:    break; // ta avoid compiler warning
		}
		if (state.code)
			return false;
		
		if (newMove == MotionMode_PROBE)
			reset_motion_mode();
		else
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
	if (runner.units == UnitSystem_INCHES)
	{
		newpos = to_mm(newpos);
	}

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

//M30 = Program end, Rewind to first block and STOP execution.
//M02 = Program end, STOP execution with no Rewind.Hitting "START" again will continue with block after M02

bool GCodeInterpreter::run_stop(const CmdParser &parser)
{
	//           M02	Конец программы	M02;
	if ( parser.contain_m(2) )
	{
		executor->set_end_programm();
		state.code = PRAGRAMM_END;
		return true;
	}
	else if (parser.contain_m(30))
	{
		executor->set_end_programm();
		state.code = PRAGRAMM_ENDCLEAR;
		return true;
	}
	return false;
}


void  GCodeInterpreter::probe_to(const Coords &position)
{
	if (executor)
		executor->process_probe(position);
	
	//executor->straight_traverce(position);
	//runner.position = position; //???
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
coord GCodeInterpreter::to_mm(coord value) const
{
	if (runner.units == UnitSystem_INCHES)
		value *= MM_PER_INCHES;
	return value;
}

//====================================================================================================
Coords GCodeInterpreter::to_mm(Coords value) const
{
	for (int i = 0; i < MAX_AXES; ++i)
		value.r[i] = to_mm(value.r[i]);
	return value;
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
	if (comment)
		logger->log(LOG_WARNING, "Line %d  unclosed comment found", lineNumber);

	line[n] = 0;

	if (src[m] != '\0' && src[m] == '\n')//need skip long string
	{
		for (; src[m] != '\0' && src[m] != '\n'; m++);
	}

	if (src[m] == '\n')
		return src + m + 1; // next symvol
	else
		return NULL;

}
