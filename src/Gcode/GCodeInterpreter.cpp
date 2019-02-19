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
		runner.tool_length_offset = 0;
	}
	else if (parser.contain_g(G_43))
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G44 ");
		if  ( h > 0 )
			runner.tool_length_offset = -h;
		else
			runner.tool_length_offset = h;
	}
	else if (parser.contain_g(G_44))
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G43 ");
		runner.tool_length_offset = h;
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
			case MotionMode_CW_ARC:  arc_to(newPos, true, parser); break;
			case MotionMode_CCW_ARC: arc_to(newPos, false, parser); break;
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
	double val;
	if (parser.getRParam(PARAM_X, &val))	newpos.x = to_mm(val);
	if (parser.getRParam(PARAM_Y, &val))	newpos.y = to_mm(val);
	if (parser.getRParam(PARAM_Z, &val))	newpos.z = to_mm(val);
	if (parser.getRParam(PARAM_A, &val))	newpos.a = to_mm(val);
	if (parser.getRParam(PARAM_B, &val))	newpos.b = to_mm(val);
	if (parser.getRParam(PARAM_C, &val))	newpos.c = to_mm(val);
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



/****************************************************************************/

/*! convert_arc

Returned Value: int
   If one of the following functions returns an error code,
   this returns that error code.
	  convert_arc_comp1
	  convert_arc_comp2
	  convert_arc2
   If any of the following errors occur, this returns the error code shown.
   Otherwise, this returns INTERP_OK.
   1. The block has neither an r value nor any i,j,k values:
	  NCE_R_I_J_K_WORDS_ALL_MISSING_FOR_ARC
   2. The block has both an r value and one or more i,j,k values:
	  NCE_MIXED_RADIUS_IJK_FORMAT_FOR_ARC
   3. In the ijk format the XY-plane is selected and
	  the block has a k value: NCE_K_WORD_GIVEN_FOR_ARC_IN_XY_PLANE
   4. In the ijk format the YZ-plane is selected and
	  the block has an i value: NCE_I_WORD_GIVEN_FOR_ARC_IN_YZ_PLANE
   5. In the ijk format the XZ-plane is selected and
	  the block has a j value: NCE_J_WORD_GIVEN_FOR_ARC_IN_XZ_PLANE
   6. In either format any of the following occurs.
	  a. The XY-plane is selected and the block has no x or y value:
		 NCE_X_AND_Y_WORDS_MISSING_FOR_ARC_IN_XY_PLANE
	  b. The YZ-plane is selected and the block has no y or z value:
		 NCE_Y_AND_Z_WORDS_MISSING_FOR_ARC_IN_YZ_PLANE
	  c. The ZX-plane is selected and the block has no z or x value:
		 NCE_X_AND_Z_WORDS_MISSING_FOR_ARC_IN_XZ_PLANE
   7. The selected plane is an unknown plane:
	  NCE_BUG_PLANE_NOT_XY_YZ__OR_XZ
   8. The feed rate mode is UNITS_PER_MINUTE and feed rate is zero:
	  NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE
   9. The feed rate mode is INVERSE_TIME and the block has no f word:
	  NCE_F_WORD_MISSING_WITH_INVERSE_TIME_ARC_MOVE

Side effects:
   This generates and executes an arc command at feed rate
   (and, possibly a second arc command). It also updates the setting
   of the position of the tool point to the end point of the move.

Called by: convert_motion.

This converts a helical or circular arc.  The function calls:
convert_arc2 (when cutter radius compensation is off) or
convert_arc_comp1 (when cutter comp is on and this is the first move) or
convert_arc_comp2 (when cutter comp is on and this is not the first move).

If the ijk format is used, at least one of the offsets in the current
plane must be given in the block; it is common but not required to
give both offsets. The offsets are always incremental [NCMS, page 21].

If cutter compensation is in use, the path's length may increase or
decrease.  Also an arc may be added, to go around a corner, before the
original arc move.  For the purpose of calculating the feed rate when in
inverse time mode, this length increase or decrease is ignored.  The
feed is still set to the original programmed arc length divided by the F
number (with the above lower bound).  The new arc (if needed) and the
new longer or shorter original arc are taken at this feed.

*/


/*
void  GCodeInterpreter::arc_to(const Coords &position, bool cw)
{

	if (executor)
	{
		executor->arc_feed(position, cw);
	}
	runner.position = position;
}
*/

bool GCodeInterpreter::arc_to(const Coords &position, bool cw, const CmdParser &parser)       //!< either G_2 (cw arc) or G_3 (ccw arc)    
{
	bool first;                    /* flag set true if this is first move after comp true */
	int ijk_flag;                 /* flag set true if any of i,j,k present in NC code  */
	double end_x;
	double end_y;
	double end_z;
	double AA_end;
	double BB_end;
	double CC_end;
	double u_end, v_end, w_end;

	//CHKS((settings->arc_not_allowed), (_("The move just after exiting cutter compensation mode must be straight, not an arc")));

	ijk_flag = parser.hasParam(PARAM_I) || parser.hasParam(PARAM_J)  || parser.hasParam(PARAM_K);

	first = runner.cutter_comp_firstmove;

	IF_T_RET_F_SETSTATE((!parser.hasParam(PARAM_R) && (!ijk_flag)), PARAMETER_ERROR, "R i j k words all missing for arc");

	IF_T_RET_F_SETSTATE((parser.hasParam(PARAM_R) && (ijk_flag)), PARAMETER_ERROR, "Mixed radius ijk format for arc");
	
	//if (settings->feed_mode == UNITS_PER_MINUTE) {
	//	CHKS((settings->feed_rate == 0.0),
	//		NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE);
	//}
	//else if (settings->feed_mode == UNITS_PER_REVOLUTION) {
	//	CHKS((settings->feed_rate == 0.0),
	//		NCE_CANNOT_MAKE_ARC_WITH_ZERO_FEED_RATE);
	//	CHKS((settings->speed[settings->active_spindle] == 0.0),
	//		_("Cannot feed with zero spindle speed in feed per rev mode"));
	//}
	//else if (settings->feed_mode == INVERSE_TIME) {
	//	CHKS((!block->f_flag),
	//		NCE_F_WORD_MISSING_WITH_INVERSE_TIME_ARC_MOVE);
	//}

	if (ijk_flag) 
	{
		if (runner.plane == Plane_XY) 
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_K), PARAMETER_ERROR, "K word given for arc in XY plane");
			if ( !parser.hasParam(PARAM_I) ) 
				RET_F_SETSTATE(PARAMETER_ERROR, "I word missing in absolute center arc");
			else if (!parser.hasParam(PARAM_J))
				RET_F_SETSTATE(PARAMETER_ERROR, "J word missing in absolute center arc");
		}
		else if (runner.plane == Plane_YZ)
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_I), PARAMETER_ERROR, "I word given for arc in YZ plane");
			if (!parser.hasParam(PARAM_J))
				RET_F_SETSTATE(PARAMETER_ERROR, "J word missing in absolute center arc");
			else if (!parser.hasParam(PARAM_K))
				RET_F_SETSTATE(PARAMETER_ERROR, "K word missing in absolute center arc");
		}
		else if(runner.plane == Plane_XZ)
		{
			IF_T_RET_F_SETSTATE(parser.hasParam(PARAM_J), PARAMETER_ERROR, "J word given for arc in XZ plane");
			if (!parser.hasParam(PARAM_I))
				RET_F_SETSTATE(PARAMETER_ERROR, "I word missing in absolute center arc");
			else if (!parser.hasParam(PARAM_K))
				RET_F_SETSTATE(PARAMETER_ERROR, "K word missing in absolute center arc");
		}
		else 
		{
			RET_F_SETSTATE(PARAMETER_ERROR, "XY, XZ or YZ plane not defined");
		}
	}
	else 	// in R format, we need some XYZ words specified because a full circle is not allowed.
	{
		// in R format, we need some XYZ words specified because a full circle is not allowed.
		if (runner.plane == Plane_XY)
		{
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_X)) && (!parser.hasParam(PARAM_Y))), ///* && (!block->radius_flag) && (!block->theta_flag)*/
				PARAMETER_ERROR, "X and Z words missing for arc in xy plane");
		}
		else if (runner.plane == Plane_YZ) {
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_Y)) && (!parser.hasParam(PARAM_Z))),
				PARAMETER_ERROR, "Y and Z words missing for arc in YZ plane");
		}
		else if (runner.plane == Plane_XZ) {
			IF_T_RET_F_SETSTATE(((!parser.hasParam(PARAM_X)) && (parser.hasParam(PARAM_Z))),
				PARAMETER_ERROR, "X and Z words missing for arc in XZ plane");  
		}
	}


	//CHP(find_ends(block, settings, &end_x, &end_y, &end_z,
	//	&AA_end, &BB_end, &CC_end,
	//	&u_end, &v_end, &w_end));

	end_x = position.x;
	end_y = position.y;
	end_z = position.z;
	AA_end = position.a;
	BB_end = position.b;
	CC_end = position.c;

	//settings->motion_mode = move;

	double i = 0,j=0,k=0;
	if( parser.getRParam(PARAM_I, &i) )  i = to_mm(i);
	if( parser.getRParam(PARAM_J, &j) )  j = to_mm(j);
	if( parser.getRParam(PARAM_K, &k) )  k = to_mm(k);
	
	if (runner.plane == Plane_XY) 
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0)) 
		{
			IF_F_RET_F(convert_arc2(cw, parser, 
					&(runner.position.x), &(runner.position.y), &(runner.position.z),
					end_x, end_y, end_z,
					AA_end, BB_end, CC_end,	
					u_end, v_end, w_end, i, j));
		}
		else if (first) 
		{
			IF_F_RET_F( convert_arc_comp1(cw, parser, end_x, end_y, end_z,
				i, j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else {
			IF_F_RET_F( convert_arc_comp2(cw, parser, end_x, end_y, end_z,
				i,j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
	}
	else if (runner.plane == Plane_XZ) 
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0)) 
		{
			IF_F_RET_F(	convert_arc2(cw, parser, 
				&(runner.position.z), &(runner.position.x), &(runner.position.y),
				end_z, end_x, end_y, AA_end, BB_end, CC_end,	u_end, v_end, w_end, k,i));
		}
		else if (first) 
		{
			IF_F_RET_F( convert_arc_comp1(cw, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else 
		{
			IF_F_RET_F(convert_arc_comp2(cw, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));
			
		}
	}
	else if (runner.plane == Plane_YZ) {
		IF_F_RET_F(convert_arc2(cw, parser,
				&(runner.position.y), &(runner.position.z), &(runner.position.x),
				end_y, end_z, end_x,AA_end, BB_end, CC_end,	u_end, v_end, w_end, j,k));
	}
	else
		RET_F_SETSTATE(PARAMETER_ERROR, "Bug plane not xy yz or xz");
	return true;
}

/****************************************************************************/

/*! convert_arc2

Returned Value: int
   If arc_data_ijk or arc_data_r returns an error code,
   this returns that code.
   Otherwise, it returns INTERP_OK.

Side effects:
   This executes an arc command at feed rate. It also updates the
   setting of the position of the tool point to the end point of the move.

Called by: convert_arc.

This converts a helical or circular arc.

*/


bool GCodeInterpreter::convert_arc2(bool cw,       //!< either G_2 (cw arc) or G_3 (ccw arc)    
	const CmdParser &parser,
	double *current1,       //!< pointer to current value of coordinate 1
	double *current2,       //!< pointer to current value of coordinate 2
	double *current3,       //!< pointer to current value of coordinate 3
	double &end1,    //!< coordinate 1 value at end of arc        
	double &end2,    //!< coordinate 2 value at end of arc        
	double &end3,    //!< coordinate 3 value at end of arc        
	double &AA_end,  //!< a-value at end of arc                   
	double &BB_end,  //!< b-value at end of arc                   
	double &CC_end,  //!< c-value at end of arc                   
	double &u, double &v, double &w, //!< values at end of arc
	double &offset1, //!< center, either abs or offset from current
	double &offset2)
{
	double center1;
	double center2;
	int turn;                     // number of full or partial turns CCW in arc 
	
	// Spiral tolerance is the amount of "spiral" allowed in a given arc segment, or (r2-r1)/theta
	//double spiral_abs_tolerance = (settings->length_units == CANON_UNITS_INCHES) ?
		//settings->center_arc_radius_tolerance_inch : settings->center_arc_radius_tolerance_mm;

	// Radius tolerance allows a bit of leeway on the minimum radius for a radius defined arc.
	//double radius_tolerance = (settings->length_units == CANON_UNITS_INCHES) ?
		//RADIUS_TOLERANCE_INCH : RADIUS_TOLERANCE_MM;

	double rval;
	int p_int = 1;
	if (parser.getRParam(PARAM_P, &rval) )
		p_int = static_cast<int>(std::nearbyint(rval));

		
	
	double radius_tolerance = 0.001;  //bb xbz
	double spiral_abs_tolerance = 0.001;

	if (parser.getRParam(PARAM_R, &rval))
	{
		rval = to_mm(rval);
		IF_F_RET_F(arc_data_r(cw, *current1, *current2, end1, end2,
			rval, p_int, &center1, &center2, &turn, radius_tolerance));
	}
	else 
	{
		IF_F_RET_F(arc_data_ijk(cw, *current1, *current2, end1, end2,
			offset1, offset2, p_int,
			&center1, &center2, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
	}

	//inverse_time_rate_arc(*current1, *current2, *current3, center1, center2,
//		turn, end1, end2, end3, block, settings);

	executor->arc_feed(&runner, end1, end2, center1, center2, turn, end3, AA_end, BB_end, CC_end, u ,v);
//	ARC_FEED(block->line_number, end1, end2, center1, center2, turn, end3,
//		AA_end, BB_end, CC_end, u, v, w);
	
	*current1 = end1;
	*current2 = end2;
	*current3 = end3;

	runner.position.a = AA_end;
	runner.position.b = BB_end;
	runner.position.c = CC_end;

	return true;
}


char GCodeInterpreter::arc_axis1(Plane plane)
{
	switch (plane) 
	{
	case Plane_XY: return 'X';
	case Plane_XZ: return 'Z';
	case Plane_YZ: return 'Y';
	default: return '!';
	}
}

char GCodeInterpreter::arc_axis2(Plane plane) 
{
	switch (plane) 
	{
	case Plane_XY: return 'Y';
	case Plane_XZ: return 'X';
	case Plane_YZ: return 'Z';
	default: return '!';
	}
}


bool GCodeInterpreter::arc_data_ijk(bool cw,       //!< either G_2 (cw arc) or G_3 (ccw arc)
	double &current_x,       //!< first coordinate of current point
	double &current_y,       //!< second coordinate of current point
	double &end_x,   //!< first coordinate of arc end point
	double &end_y,   //!< second coordinate of arc end point
	double &i_number,        //!<first coordinate of center (abs or incr)
	double &j_number,        //!<second coordinate of center (abs or incr)
	int p_number,
	double *center_x,       //!< pointer to first coordinate of center of arc
	double *center_y,       //!< pointer to second coordinate of center of arc
	int *turn,      //!< pointer to no. of full or partial circles CCW
	double radius_tolerance, //!<minimum radius tolerance
	double spiral_abs_tolerance,  //!<tolerance of start and end radius difference
	double spiral_rel_tolerance)
{
	double radius;                // radius to current point 
	double radius2;               // radius to end point    
	char a = arc_axis1(runner.plane), b = arc_axis2(runner.plane);

	if (runner.ij_absolute) {
		*center_x = (i_number);
		*center_y = (j_number);
	}
	else {
		*center_x = (current_x + i_number);
		*center_y = (current_y + j_number);
	}
	radius = hypot((*center_x - current_x), (*center_y - current_y));
	radius2 = hypot((*center_x - end_x), (*center_y - end_y));

	IF_T_RET_F_SETSTATE(((radius < radius_tolerance) || (radius2 < radius_tolerance)), PARAMETER_ERROR,
		"Zero-radius arc: start=(%c%.4f,%c%.4f) center=(%c%.4f,%c%.4f) end=(%c%.4f,%c%.4f) r1=%.4f r2=%.4f",
		a, current_x, b, current_y,
		a, *center_x, b, *center_y,
		a, end_x, b, end_y, radius, radius2);

	double abs_err = fabs(radius - radius2);
	double rel_err = abs_err / std::max(radius, radius2);
	IF_T_RET_F_SETSTATE((abs_err > spiral_abs_tolerance * 100.0) ||
		(rel_err > spiral_rel_tolerance && abs_err > spiral_abs_tolerance), PARAMETER_ERROR,
		"Radius to end of arc differs from radius to start: start=(%c%.4f,%c%.4f) center=(%c%.4f,%c%.4f) end=(%c%.4f,%c%.4f) r1=%.4f r2=%.4f abs_err=%.4g rel_err=%.4f%%",
		a, current_x, b, current_y,	a, *center_x, b, *center_y,	a, end_x, b, end_y, radius, radius2,abs_err, rel_err * 100);

	if (cw)
		*turn = -1 * p_number;
	else 
		*turn = 1 * p_number;
	return true;
}

/****************************************************************************/

/*! arc_data_r

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The radius is too small to reach the end point:
	  NCE_ARC_RADIUS_TOO_SMALL_TO_REACH_END_POINT
   2. The current point is the same as the end point of the arc
	  (so that it is not possible to locate the center of the circle):
	  NCE_CURRENT_POINT_SAME_AS_END_POINT_OF_ARC

Side effects:
   This finds and sets the values of center_x, center_y, and turn.

Called by:
   convert_arc2
   convert_arc_comp2

This finds the center coordinates and number of full or partial turns
counterclockwise of a helical or circular arc in the r format. This
function is used by convert_arc2 for all three planes, so "x" and
"y" really mean "first_coordinate" and "second_coordinate" wherever
they are used here as suffixes of variable names.

If the value of the radius argument is negative, that means [NCMS,
page 21] that an arc larger than a semicircle is to be made.
Otherwise, an arc of a semicircle or less is made.

The algorithm used here is based on finding the midpoint M of the line
L between the current point and the end point of the arc. The center
of the arc lies on a line through M perpendicular to L.

*/


bool GCodeInterpreter::arc_data_r(bool cw, //!< either G_2 (cw arc) or G_3 (ccw arc)	
	double &current_x, //!< first coordinate of current point
	double &current_y, //!< second coordinate of current point
	double &end_x,     //!< first coordinate of arc end point
	double &end_y,     //!< second coordinate of arc end point
	double &radius,    //!< radius of arc
	int p_number,
	double *center_x, //!< pointer to first coordinate of center of arc
	double *center_y, //!< pointer to second coordinate of center of arc
	int *turn,        //!< pointer to number of full or partial circles CCW
	double &tolerance) //!< tolerance of differing radii
{
	double abs_radius;            /* absolute value of given radius */
	double half_length;           /* distance from M to end point   */
	double mid_x;                 /* first coordinate of M          */
	double mid_y;                 /* second coordinate of M         */
	double offset;                /* distance from M to center      */
	double theta;                 /* angle of line from M to center */
	double turn2;                 /* absolute value of half of turn */

	IF_T_RET_F_SETSTATE(((end_x == current_x) && (end_y == current_y)), PARAMETER_ERROR, "Current point same as end point of arc");
	abs_radius = fabs(radius);
	mid_x = (end_x + current_x) / 2.0;
	mid_y = (end_y + current_y) / 2.0;
	half_length = hypot((mid_x - end_x), (mid_y - end_y));
	
	IF_T_RET_F_SETSTATE(((half_length - abs_radius) > tolerance), PARAMETER_ERROR, "Arc radius too small to reach end point");

	if ((half_length / abs_radius) > (1 - TINY))
		half_length = abs_radius;   /* allow a small error for semicircle */
	  /* check needed before calling asin   */
	if (((cw) && (radius > 0)) || ((!cw) && (radius < 0)))
		theta = atan2((end_y - current_y), (end_x - current_x)) - M_PI_2l;
	else
		theta = atan2((end_y - current_y), (end_x - current_x)) + M_PI_2l;

	turn2 = asin(half_length / abs_radius);
	offset = abs_radius * cos(turn2);
	*center_x = mid_x + (offset * cos(theta));
	*center_y = mid_y + (offset * sin(theta));
	*turn = (cw) ? -1 * p_number : 1 * p_number;

	return true;
}


/****************************************************************************/

/*! convert_arc_comp1

Returned Value: int
   If arc_data_comp_ijk or arc_data_comp_r returns an error code,
   this returns that code.
   Otherwise, it returns INTERP_OK.

Side effects:
   This executes an arc command at
   feed rate. It also updates the setting of the position of
   the tool point to the end point of the move.

Called by: convert_arc.

This function converts a helical or circular arc, generating only one
arc. This is called when cutter radius compensation is on and this is
the first cut after the turning on.

The arc which is generated is derived from a second arc which passes
through the programmed end point and is tangent to the cutter at its
current location. The generated arc moves the tool so that it stays
tangent to the second arc throughout the move.

*/

bool GCodeInterpreter::convert_arc_comp1(bool cw,  //!< either G_2 (cw arc) or G_3 (ccw arc)            
	const CmdParser &parser,
	double &end_x,      //!< x-value at end of programmed (then actual) arc  
	double &end_y,      //!< y-value at end of programmed (then actual) arc  
	double &end_z,      //!< z-value at end of arc
	double &offset_x, double offset_y,
	double &AA_end,     //!< a-value at end of arc
	double &BB_end,     //!< b-value at end of arc
	double &CC_end,     //!< c-value at end of arc
	double &u_end, double &v_end, double &w_end) //!< uvw at end of arc
{
	return false;
}
//	double center_x, center_y;
//	double gamma;                 /* direction of perpendicular to arc at end */
//	int side;                     /* offset side - right or left              */
//	double tool_radius;
//	int turn;                     /* 1 for counterclockwise, -1 for clockwise */
//	double cx, cy, cz; // current
//	int plane = settings->plane;
//
//	side = settings->cutter_comp_side;
//	tool_radius = settings->cutter_comp_radius;   /* always is positive */
//
//	double spiral_abs_tolerance = (settings->length_units == CANON_UNITS_INCHES) ? settings->center_arc_radius_tolerance_inch : settings->center_arc_radius_tolerance_mm;
//	double radius_tolerance = (settings->length_units == CANON_UNITS_INCHES) ? RADIUS_TOLERANCE_INCH : RADIUS_TOLERANCE_MM;
//
//	comp_get_current(settings, &cx, &cy, &cz);
//
//	CHKS((hypot((end_x - cx), (end_y - cy)) <= tool_radius),
//		_("Radius of cutter compensation entry arc is not greater than the tool radius"));
//
//	if (block->r_flag) {
//		CHP(arc_data_comp_r(move, plane, side, tool_radius, cx, cy, end_x, end_y,
//			block->r_number, block->p_flag ? round_to_int(block->p_number) : 1,
//			&center_x, &center_y, &turn, radius_tolerance));
//	}
//	else {
//		CHP(arc_data_comp_ijk(move, plane, side, tool_radius, cx, cy, end_x, end_y,
//			(settings->ijk_distance_mode == MODE_ABSOLUTE),
//			offset_x, offset_y, block->p_flag ? round_to_int(block->p_number) : 1,
//			&center_x, &center_y, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
//	}
//
//	inverse_time_rate_arc(cx, cy, cz, center_x, center_y,
//		turn, end_x, end_y, end_z, block, settings);
//
//
//	// the tool will end up in gamma direction from the programmed arc endpoint
//	if TOOL_INSIDE_ARC(side, turn) {
//		// tool inside the arc: ends up toward the center
//		gamma = atan2((center_y - end_y), (center_x - end_x));
//	}
//	else {
//		// outside: away from the center
//		gamma = atan2((end_y - center_y), (end_x - center_x));
//	}
//
//	settings->cutter_comp_firstmove = false;
//
//	comp_set_programmed(settings, end_x, end_y, end_z);
//
//	// move endpoint to the compensated position.  This changes the radius and center.
//	end_x += tool_radius * cos(gamma);
//	end_y += tool_radius * sin(gamma);
//
//	/* To find the new center:
//	   imagine a right triangle ABC with A being the endpoint of the
//	   compensated arc, B being the center of the compensated arc, C being
//	   the midpoint between start and end of the compensated arc. AB_ang
//	   is the direction of A->B.  A_ang is the angle of the triangle
//	   itself.  We need to find a new center for the compensated arc
//	   (point B). */
//
//	double b_len = hypot(cy - end_y, cx - end_x) / 2.0;
//	double AB_ang = atan2(center_y - end_y, center_x - end_x);
//	double A_ang = atan2(cy - end_y, cx - end_x) - AB_ang;
//
//	CHKS((fabs(cos(A_ang)) < TOLERANCE_EQUAL), NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);
//
//	double c_len = b_len / cos(A_ang);
//
//	// center of the arc is c_len from end in direction AB
//	center_x = end_x + c_len * cos(AB_ang);
//	center_y = end_y + c_len * sin(AB_ang);
//
//	/* center to endpoint distances matched before - they still should. */
//	CHKS((fabs(hypot(center_x - end_x, center_y - end_y) -
//		hypot(center_x - cx, center_y - cy)) > spiral_abs_tolerance),
//		NCE_BUG_IN_TOOL_RADIUS_COMP);
//
//	// need this move for lathes to move the tool origin first.  otherwise, the arc isn't an arc.
//	if (settings->cutter_comp_orientation != 0 && settings->cutter_comp_orientation != 9) {
//		enqueue_STRAIGHT_FEED(settings, block->line_number,
//			0, 0, 0,
//			cx, cy, cz,
//			AA_end, BB_end, CC_end, u_end, v_end, w_end);
//		set_endpoint(cx, cy);
//	}
//
//	enqueue_ARC_FEED(settings, block->line_number,
//		find_turn(cx, cy, center_x, center_y, turn, end_x, end_y),
//		end_x, end_y, center_x, center_y, turn, end_z,
//		AA_end, BB_end, CC_end, u_end, v_end, w_end);
//
//	comp_set_current(settings, end_x, end_y, end_z);
//	settings->AA_current = AA_end;
//	settings->BB_current = BB_end;
//	settings->CC_current = CC_end;
//	return INTERP_OK;
//}
//
///****************************************************************************/
//
///*! convert_arc_comp2
//
//Returned Value: int
//   If arc_data_ijk or arc_data_r returns an error code,
//   this returns that code.
//   If any of the following errors occurs, this returns the error code shown.
//   Otherwise, it returns INTERP_OK.
//   1. A concave corner is found: NCE_CONCAVE_CORNER_WITH_CUTTER_RADIUS_COMP
//   2. The tool will not fit inside an arc:
//	  NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP
//
//Side effects:
//   This executes an arc command feed rate. If needed, at also generates
//   an arc to go around a convex corner. It also updates the setting of
//   the position of the tool point to the end point of the move.
//Called by: convert_arc.
//
//This function converts a helical or circular arc. The axis must be
//parallel to the z-axis. This is called when cutter radius compensation
//is on and this is not the first cut after the turning on.
//
//If one or more rotary axes is moved in this block and an extra arc is
//required to go around a sharp corner, all the rotary axis motion
//occurs on the main arc and none on the extra arc.  An alternative
//might be to distribute the rotary axis motion over the extra arc and
//the programmed arc in proportion to their lengths.
//
//If the Z-axis is moved in this block and an extra arc is required to
//go around a sharp corner, all the Z-axis motion occurs on the main arc
//and none on the extra arc.  An alternative might be to distribute the
//Z-axis motion over the extra arc and the main arc in proportion to
//their lengths.
//
//*/
//
bool GCodeInterpreter::convert_arc_comp2(bool cw,  //!< either G_2 (cw arc) or G_3 (ccw arc)          
	const CmdParser &parser,
	double end_x,      //!< x-value at end of programmed (then actual) arc
	double end_y,      //!< y-value at end of programmed (then actual) arc
	double end_z,      //!< z-value at end of arc 
	double offset_x, double offset_y,
	double AA_end,     //!< a-value at end of arc
	double BB_end,     //!< b-value at end of arc
	double CC_end,     //!< c-value at end of arc
	double u, double v, double w) //!< uvw at end of arc
{
	return false;
}
//	double alpha;                 /* direction of tangent to start of arc */
//	double arc_radius;
//	double beta;                  /* angle between two tangents above */
//	double centerx, centery;              /* center of arc */
//	double delta;                 /* direction of radius from start of arc to center of arc */
//	double gamma;                 /* direction of perpendicular to arc at end */
//	double midx, midy;
//	int side;
//	double small = TOLERANCE_CONCAVE_CORNER;      /* angle for testing corners */
//	double opx, opy, opz;
//	double theta;                 /* direction of tangent to last cut */
//	double tool_radius;
//	int turn;                     /* number of full or partial circles CCW */
//	int plane = settings->plane;
//	double cx, cy, cz;
//	double new_end_x, new_end_y;
//
//	double spiral_abs_tolerance = (settings->length_units == CANON_UNITS_INCHES) ? settings->center_arc_radius_tolerance_inch : settings->center_arc_radius_tolerance_mm;
//	double radius_tolerance = (settings->length_units == CANON_UNITS_INCHES) ? RADIUS_TOLERANCE_INCH : RADIUS_TOLERANCE_MM;
//
//	/* find basic arc data: center_x, center_y, and turn */
//
//	comp_get_programmed(settings, &opx, &opy, &opz);
//	comp_get_current(settings, &cx, &cy, &cz);
//
//
//	if (block->r_flag) {
//		CHP(arc_data_r(move, plane, opx, opy, end_x, end_y,
//			block->r_number, block->p_flag ? round_to_int(block->p_number) : 1,
//			&centerx, &centery, &turn, radius_tolerance));
//	}
//	else {
//		CHP(arc_data_ijk(move, plane,
//			opx, opy, end_x, end_y,
//			(settings->ijk_distance_mode == MODE_ABSOLUTE),
//			offset_x, offset_y, block->p_flag ? round_to_int(block->p_number) : 1,
//			&centerx, &centery, &turn, radius_tolerance, spiral_abs_tolerance, SPIRAL_RELATIVE_TOLERANCE));
//	}
//
//	inverse_time_rate_arc(opx, opy, opz, centerx, centery,
//		turn, end_x, end_y, end_z, block, settings);
//
//	side = settings->cutter_comp_side;
//	tool_radius = settings->cutter_comp_radius;   /* always is positive */
//	arc_radius = hypot((centerx - end_x), (centery - end_y));
//	theta = atan2(cy - opy, cx - opx);
//	theta = (side == LEFT) ? (theta - M_PI_2l) : (theta + M_PI_2l);
//	delta = atan2(centery - opy, centerx - opx);
//	alpha = (move == G_3) ? (delta - M_PI_2l) : (delta + M_PI_2l);
//	beta = (side == LEFT) ? (theta - alpha) : (alpha - theta);
//
//	// normalize beta -90 to +270?
//	beta = (beta > (1.5 * M_PIl)) ? (beta - (2 * M_PIl)) : (beta < -M_PI_2l) ? (beta + (2 * M_PIl)) : beta;
//
//	if (((side == LEFT) && (move == G_3)) || ((side == RIGHT) && (move == G_2))) {
//		// we are cutting inside the arc
//		gamma = atan2((centery - end_y), (centerx - end_x));
//		CHKS((arc_radius <= tool_radius),
//			NCE_TOOL_RADIUS_NOT_LESS_THAN_ARC_RADIUS_WITH_COMP);
//	}
//	else {
//		gamma = atan2((end_y - centery), (end_x - centerx));
//		delta = (delta + M_PIl);
//	}
//
//	// move arc endpoint to the compensated position
//	new_end_x = end_x + tool_radius * cos(gamma);
//	new_end_y = end_y + tool_radius * sin(gamma);
//
//	if (beta < -small ||
//		beta > M_PIl + small ||
//		// special detection for convex corner on tangent arc->arc (like atop the middle of "m" shape)
//		// or tangent line->arc (atop "h" shape)
//		(fabs(beta - M_PIl) < small && !TOOL_INSIDE_ARC(side, turn))
//		) {
//		// concave
//		if (qc().front().type != QARC_FEED) {
//			// line->arc
//			double cy = arc_radius * sin(beta - M_PI_2l);
//			double toward_nominal;
//			double dist_from_center;
//			double angle_from_center;
//
//			if TOOL_INSIDE_ARC(side, turn) {
//				// tool is inside the arc
//				dist_from_center = arc_radius - tool_radius;
//				toward_nominal = cy + tool_radius;
//				double l = toward_nominal / dist_from_center;
//				CHKS((l > 1.0 || l < -1.0), _("Arc move in concave corner cannot be reached by the tool without gouging"));
//				if (turn > 0) {
//					angle_from_center = theta + asin(l);
//				}
//				else {
//					angle_from_center = theta - asin(l);
//				}
//			}
//			else {
//				dist_from_center = arc_radius + tool_radius;
//				toward_nominal = cy - tool_radius;
//				double l = toward_nominal / dist_from_center;
//				CHKS((l > 1.0 || l < -1.0), _("Arc move in concave corner cannot be reached by the tool without gouging"));
//				if (turn > 0) {
//					angle_from_center = theta + M_PIl - asin(l);
//				}
//				else {
//					angle_from_center = theta + M_PIl + asin(l);
//				}
//			}
//
//			midx = centerx + dist_from_center * cos(angle_from_center);
//			midy = centery + dist_from_center * sin(angle_from_center);
//
//			CHP(move_endpoint_and_flush(settings, midx, midy));
//		}
//		else {
//			// arc->arc
//			struct arc_feed &prev = qc().front().data.arc_feed;
//			double oldrad = hypot(prev.center2 - prev.end2, prev.center1 - prev.end1);
//			double newrad;
//			if TOOL_INSIDE_ARC(side, turn) {
//				newrad = arc_radius - tool_radius;
//			}
//			else {
//				newrad = arc_radius + tool_radius;
//			}
//
//			double arc_cc, pullback, cc_dir, a;
//			arc_cc = hypot(prev.center2 - centery, prev.center1 - centerx);
//
//			CHKS((oldrad == 0 || arc_cc == 0), _("Arc to arc motion is invalid because the arcs have the same center"));
//			a = (SQ(oldrad) + SQ(arc_cc) - SQ(newrad)) / (2 * oldrad * arc_cc);
//
//			CHKS((a > 1.0 || a < -1.0), (_("Arc to arc motion makes a corner the compensated tool can't fit in without gouging")));
//			pullback = acos(a);
//			cc_dir = atan2(centery - prev.center2, centerx - prev.center1);
//
//			double dir;
//			if TOOL_INSIDE_ARC(side, prev.turn) {
//				if (turn > 0)
//					dir = cc_dir + pullback;
//				else
//					dir = cc_dir - pullback;
//			}
//			else {
//				if (turn > 0)
//					dir = cc_dir - pullback;
//				else
//					dir = cc_dir + pullback;
//			}
//
//			midx = prev.center1 + oldrad * cos(dir);
//			midy = prev.center2 + oldrad * sin(dir);
//
//			CHP(move_endpoint_and_flush(settings, midx, midy));
//		}
//		enqueue_ARC_FEED(settings, block->line_number,
//			find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
//			new_end_x, new_end_y, centerx, centery, turn, end_z,
//			AA_end, BB_end, CC_end, u, v, w);
//	}
//	else if (beta > small) {           /* convex, two arcs needed */
//		midx = opx + tool_radius * cos(delta);
//		midy = opy + tool_radius * sin(delta);
//		dequeue_canons(settings);
//		enqueue_ARC_FEED(settings, block->line_number,
//			0.0, // doesn't matter since we won't move this arc's endpoint
//			midx, midy, opx, opy, ((side == LEFT) ? -1 : 1),
//			cz,
//			AA_end, BB_end, CC_end, u, v, w);
//		dequeue_canons(settings);
//		set_endpoint(midx, midy);
//		enqueue_ARC_FEED(settings, block->line_number,
//			find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
//			new_end_x, new_end_y, centerx, centery, turn, end_z,
//			AA_end, BB_end, CC_end, u, v, w);
//	}
//	else {                      /* convex, one arc needed */
//		dequeue_canons(settings);
//		set_endpoint(cx, cy);
//		enqueue_ARC_FEED(settings, block->line_number,
//			find_turn(opx, opy, centerx, centery, turn, end_x, end_y),
//			new_end_x, new_end_y, centerx, centery, turn, end_z,
//			AA_end, BB_end, CC_end, u, v, w);
//	}
//
//	comp_set_programmed(settings, end_x, end_y, end_z);
//	comp_set_current(settings, new_end_x, new_end_y, end_z);
//	settings->AA_current = AA_end;
//	settings->BB_current = BB_end;
//	settings->CC_current = CC_end;
//	settings->u_current = u;
//	settings->v_current = v;
//	settings->w_current = w;
//
//	return INTERP_OK;
//}
