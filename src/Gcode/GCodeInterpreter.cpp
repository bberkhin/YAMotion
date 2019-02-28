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
		cursubr_ = sname; //restore current sub
		int nline = substack.top().nline;
		execute_file_int(substack.top().startpos, &GCodeInterpreter::execute_frame, nline );
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

	// chexk & run subrotins
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


	// check 
	motion_to_be = -1;
	if (!enhance_frame(parser))
		return get_state();

	if (!check_frame(parser))
		return get_state();
	

	//====================================================================================================
	//Actions are executed in the following order:
		//2. a feed mode setting (g93, g94, g95)
	//3. a feed rate (f) setting if in units_per_minute feed mode.
	//4. a spindle speed (s) setting.
	//5. a tool selection (t).
	// Set Plane
	//6. "m" commands as described in convert_m (includes tool change).
	//7. any g_codes (except g93, g94, g95) as described in .
	
	//	STEP_SPINDLE_MODE,
	if (!run_spindle_mode(parser) )
		return get_state();
	//	STEP_FEED_MODE,
	if ( !run_feed_mode(parser) )
	return get_state();
	//	STEP_SET_FEED_RATE
	if (!run_feed_rate(parser))
		return get_state();
	//	STEP_SET_SPINDLE_SPEED,
	if (!run_speed(parser))
		return get_state();
	//	STEP_PREPARE,
	//	STEP_M_5,M3 M4
	if (!run_start_stop_spindle(parser))
		return get_state();
		//STEP_M_6,
	if (!run_tool_cmd(parser))
		return get_state();
//		STEP_RETAIN_G43,
	//all other M
	if (!run_mcode(parser))
		return get_state();
	if (!run_gcode(parser))
		return get_state();
	//	STEP_MGROUP4,	
	return InterError();
}

bool GCodeInterpreter::check_frame(const CmdParser &parser)
{
	//to do
	return true;
}

bool GCodeInterpreter::enhance_frame(const CmdParser &parser)
{
	
	bool axis_flag = (parser.hasParam(PARAM_X) || parser.hasParam(PARAM_Y) ||
		parser.hasParam(PARAM_Z) || parser.hasParam(PARAM_A) ||
		parser.hasParam(PARAM_B) || parser.hasParam(PARAM_C));

	bool ijk_flag = (parser.hasParam(PARAM_I) || parser.hasParam(PARAM_J) || parser.hasParam(PARAM_K));

	int  mode0 = parser.getGCode(ModalGroup_MODAL_0);
	int  mode1 = parser.getGCode(ModalGroup_MOVE);
	
	bool mode_zero_covets_axes =
		((mode0 == G_10) || (mode0 == G_28) || (mode0 == G_30)
			|| (mode0 == G_52) || (mode0 == G_92));

	if (mode1 != -1) 
	{
		if (mode1 == G_80) 
		{
			IF_T_RET_F_SETSTATE((axis_flag && !mode_zero_covets_axes), PARAMETER_ERROR, "Can not use axis values with G80");
			IF_T_RET_F_SETSTATE(((!axis_flag) && (mode0 == G_52 || mode0 == G_92)), PARAMETER_ERROR, "All Axis missing with G52 or G92");		
		}
		else 
		{
			IF_T_RET_F_SETSTATE(mode_zero_covets_axes, PARAMETER_ERROR, "Can not use two G codes that both use axis value");
			IF_T_RET_F_SETSTATE((!axis_flag  && mode1 != G_0 && mode1 != G_1 &&
				mode1 != G_2 && mode1 != G_3 && mode1 != G_5_2), PARAMETER_ERROR, "All Axis missing with motion code");
		}
		motion_to_be = mode1;
	}
	else if (mode_zero_covets_axes) 
	{   /* other 3 can get by without axes but not G92 */
		IF_T_RET_F_SETSTATE(((!axis_flag) &&
			(mode0 == G_52 || mode0 == G_92)), PARAMETER_ERROR, "All Axis missing with G52 or G92 code");
	}
	else if (axis_flag ) 
	{
		IF_T_RET_F_SETSTATE(((runner.motion_mode == -1)
			|| (runner.motion_mode == G_80)) && (parser.getGCode(ModalGroup_TOOL_LENGTH_CORRECTION) != G_43_1),
				PARAMETER_ERROR, "Can not use axis values with out a G code");

		if (parser.getGCode(ModalGroup_TOOL_LENGTH_CORRECTION) != G_43_1) 
		{
			motion_to_be = runner.motion_mode;
		}
	}
	else if (!axis_flag && ijk_flag && (runner.motion_mode == G_2 || runner.motion_mode == G_3)) {
		// this is a block like simply "i1" which should be accepted if we're in arc mode
		motion_to_be = runner.motion_mode;
	}	
	return true;
}


bool GCodeInterpreter::run_feed_mode( CmdParser &parser )
{
	//G93, G94, G95
	//G93  is Inverse Time Mode.In inverse time feed rate mode, an F word means the move should be completed in[one divided by the F number] minutes.
	//G94 - is Units per Minute Mode.
	//G95 - is Units per Revolution Mode 
	int gc = parser.getGCode(ModalGroup_FEEDMODE);
	if( gc == G_93 )
	{
		//G96 D2500 S250
		runner.feed_mode = FeedMode_InverseTime;
		RET_F_SETSTATE( NO_VALUE, "G93 Inverse Time Mode not supported");
	}
	else if( gc == G_94 )
	{
		runner.feed_mode = FeedMode_UnitPerMin;// ok do nothing
	}
	else if( gc == G_95 )
	{
		runner.feed_mode = FeedMode_UnitPerRevolution
		RET_F_SETSTATE(NO_VALUE, "G95 - is Units per Revolution Mode not supported");	
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
	
	if (parser.getGCode(ModalGroup_MODAL_0) == G_4)
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
		parser.remove_params();
	}
	return true;

}


bool GCodeInterpreter::run_spindle_mode( CmdParser &parser)
{
	int gc = parser.getGCode(ModalGroup_SPINDLEMODE);
	if ( gc == G_96 )
	{
		//G96 D2500 S250
		double diam, speed;
		IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_D, &diam), NO_VALUE, "Parametr 'D' must be defined for G96 (CSS mode)");
		IF_F_RET_F_SETSTATE(parser.getRParam(PARAM_S, &speed), NO_VALUE, "Parametr 'S' must be defined for G96 (CSS mode)");
		executor->set_css_spindlemode(diam, speed);		
		parser.remove_param(PARAM_D);
		parser.remove_param(PARAM_S);
	}
	else if (gc == G_97)
	{
		executor->set_regular_spindlemode();
	}
	return true;
}

bool GCodeInterpreter::run_input_mode( CmdParser &parser )
{
	if (parser.getGCode(ModalGroup_MODAL_0) == G_10)
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
		setcoordinates(newpos, parser,false);
		env->SetG54G58(ip - 1, newpos );
		parser.clear();
	}
	return true;
}

bool GCodeInterpreter::run_tool_crc(const CmdParser &parser)
{
//G_40:	runner.tool_crc = TCRC_NONE;	//Tool radius compensation off
//G_41:	runner.tool_crc = TCRC_LEFT;	//Turn on cutter radius compensation left
//G_42:	runner.tool_crc = TL_RIGHT;	    //Turn on cutter radius compensation right
	
	int gc = parser.getGCode(ModalGroup_CUTTER_COMP);
	if (gc == G_40)
	{
		runner.tool_crc_type = CutterCompType_NONE;
		runner.tool_crc = 0;
		return true;
	}
	else if(gc == G_41)
	{
		runner.tool_crc_type = CutterCompType_LEFT;	//Turn on cutter radius compensation left
	}
	else if(gc == G_42)
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
	int gc = parser.getGCode(ModalGroup_TOOL_LENGTH_CORRECTION);
	if ( gc == G_49 )
	{
		runner.tool_length_offset = 0;
	}
	else if (gc == G_43)
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G43 ");
		if  ( h > 0 )
			runner.tool_length_offset = -h;
		else
			runner.tool_length_offset = h;
	}
	else if (gc == G_44)
	{
		IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_H, &h), NO_VALUE, "Parametr 'H' must be defined for G44 ");
		runner.tool_length_offset = h;
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "GCodeInterpreter::run_tool_height_offset can notbe called here");

	return true;
}

bool GCodeInterpreter::run_start_stop_spindle(const CmdParser &parser)
{
	//M_5, M3 M4
	const m_container &mcodes = parser.getMCodes();
	for (auto iter = mcodes.begin(); iter != mcodes.end(); ++iter)
	{
		switch (*iter)
		{
		case 3:
		case 4:
		case 5:
			executor->run_mcode(*iter);
			return true;
		}
			
	}
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
		case 3:
		case 4:
		case 5://already processed
			return true;
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



			//case G_17: runner.plane = Plane_XY; break;
			//case G_18: runner.plane = Plane_XZ; break;
			//case G_19: runner.plane = Plane_YZ; break;

//		STEP_SET_PLANE,
//		STEP_LENGTH_UNITS,
//		STEP_LATHE_DIAMETER_MODE,
//		STEP_CUTTER_COMP,
//	STEP_TOOL_LENGTH_OFFSET,
//		STEP_COORD_SYSTEM,
//		STEP_CONTROL_MODE,
//		STEP_DISTANCE_MODE,
//		STEP_IJK_DISTANCE_MODE,
//		STEP_RETRACT_MODE,
//		STEP_MODAL_0,
//		STEP_MOTION,

bool GCodeInterpreter::run_gcode( CmdParser &parser)
{
	// STEP_DWELL,
	if (parser.getGCode(ModalGroup_MODAL_0) == G_4)
	{
		IF_F_RET_F(run_dwell(parser));
	}
	if (parser.hasGCode(ModalGroup_ACTIVE_PLANE))
	{
		IF_F_RET_F(run_set_plane(parser.getGCode(ModalGroup_ACTIVE_PLANE)));
	}
	if (parser.hasGCode(ModalGroup_UNITS))
	{
		IF_F_RET_F(run_set_units(parser.getGCode(ModalGroup_UNITS)));
	}
	if (parser.hasGCode(ModalGroup_LATHE_DIAMETER))
	{
		IF_F_RET_F(run_set_lathe_diam(parser));
	}
	if (parser.hasGCode(ModalGroup_CUTTER_COMP))
	{
		IF_F_RET_F(run_tool_crc(parser));
	}
	if (parser.hasGCode(ModalGroup_TOOL_LENGTH_CORRECTION))
	{
		IF_F_RET_F(run_tool_height_offset(parser));
	}
	if (parser.hasGCode(ModalGroup_COORD_SYSTEM))
	{
		IF_F_RET_F(run_set_coord_sys(parser));
	}
	if (parser.hasGCode(ModalGroup_CONTROL))
	{
		IF_F_RET_F(run_control_mode(parser.getGCode(ModalGroup_CONTROL)));
	}
	if (parser.hasGCode(ModalGroup_DISTANCE))
	{
		IF_F_RET_F(run_set_dist_mode(parser.getGCode(ModalGroup_DISTANCE)));
	}

	if (parser.hasGCode(ModalGroup_IJK_DISTANCE))
	{
		IF_F_RET_F(run_set_dist_ijk(parser.getGCode(ModalGroup_IJK_DISTANCE)));
	}

	if (parser.hasGCode(ModalGroup_CYCLE_RETURN))
	{
		IF_F_RET_F(run_set_cycle_return(parser.getGCode(ModalGroup_CYCLE_RETURN)));
	}

	if ( parser.hasGCode(ModalGroup_MODAL_0) )
	{
		IF_F_RET_F(run_modal_0(parser));
	}

	if (motion_to_be != -1)
	{
		IF_F_RET_F(run_motion(motion_to_be, parser));
	}
	return true;
}

bool GCodeInterpreter::run_set_plane(int gc)
{
	// Src Plane
	switch (gc)
	{
	case G_17: runner.plane = Plane_XY; break;
	case G_18: runner.plane = Plane_XZ; break;
	case G_19: runner.plane = Plane_YZ; break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "No g17, g18, g19");
	}
	return true;
}

bool GCodeInterpreter::run_set_lathe_diam(const CmdParser &parser)
{
	RET_F_SETSTATE(INTERNAL_ERROR, "G7 and G8 does not support yet");
}


bool GCodeInterpreter::run_modal_0(CmdParser &parser)
{
	
	int gc = parser.getGCode(ModalGroup_MODAL_0);
	switch (gc)
	{
	case G_10: 
		IF_F_RET_F(run_input_mode(parser));
	case G_4:
	case G_53: // did it just skip
		break;

	case G_52:
	case G_92:
	case G_92_1:
	case G_92_2:
	case G_92_3:
		IF_F_RET_F(convert_axis_offsets(gc, parser));
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_modal_0 with no GCode");
	}
	return true;
}

bool GCodeInterpreter::convert_axis_offsets(int gc, const CmdParser &parser)
{
	IF_T_RET_F_SETSTATE(runner.cutter_comp_side, PARAMETER_ERROR, " Can not change axis offset with cuitter compensation mode");
	
	Coords axis_offset;
	setcoordinates(axis_offset, parser, false);

	if ((gc == G_52) || (gc == G_92)) 
	{
		double val;
		if (gc == G_52)
		{
			// update current position
			for (int i = 0; i < MAX_AXES; ++i)
			{
				runner.position.r[i] -= (runner.axis_offset.r[i] + axis_offset.r[i]);
			}
			
			if (parser.getRParam(PARAM_X, &val)) runner.axis_offset.x = axis_offset.x;
			if (parser.getRParam(PARAM_Y, &val)) runner.axis_offset.y = axis_offset.y;
			if (parser.getRParam(PARAM_Z, &val)) runner.axis_offset.z = axis_offset.z;
			if (parser.getRParam(PARAM_A, &val)) runner.axis_offset.a = axis_offset.a;
			if (parser.getRParam(PARAM_B, &val)) runner.axis_offset.b = axis_offset.b;
			if (parser.getRParam(PARAM_C, &val)) runner.axis_offset.c = axis_offset.c;
		}
		else
		{
			if (parser.getRParam(PARAM_X, &val))
			{
				runner.axis_offset.x = runner.position.x - axis_offset.x;
				runner.position.x = axis_offset.x;
			}

			if (parser.getRParam(PARAM_Y, &val))
			{
				runner.axis_offset.y = runner.position.y - axis_offset.y;
				runner.position.y = axis_offset.y;
			}
			if (parser.getRParam(PARAM_Z, &val))
			{
				runner.axis_offset.z = runner.position.z - axis_offset.z;
				runner.position.z = axis_offset.z;
			}
			if (parser.getRParam(PARAM_A, &val))
			{
				runner.axis_offset.a = runner.position.a - axis_offset.a;
				runner.position.a = axis_offset.a;
			}
			if (parser.getRParam(PARAM_B, &val))
			{
				runner.axis_offset.b = runner.position.b - axis_offset.b;
				runner.position.b = axis_offset.b;
			}
			if (parser.getRParam(PARAM_C, &val))
			{
				runner.axis_offset.c = runner.position.c - axis_offset.c;
				runner.position.c = axis_offset.c;
			}
		}
	}
	else
	{
		RET_F_SETSTATE(INTERNAL_ERROR, "G92.1 and G92.2 not implemented yet");	
	}
	return true;
}


bool GCodeInterpreter::run_set_units(int gc)
{
	switch (gc)
	{
		// Units
	case G_20: runner.units = UnitSystem_INCHES; break;
	case G_21: runner.units = UnitSystem_MM; break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_set_units no G20 or G21");
	}
	return true;
}


bool GCodeInterpreter::run_set_coord_sys(const CmdParser &parser)
{
	IF_T_RET_F_SETSTATE(runner.cutter_comp_side, PARAMETER_ERROR, " Cannot change coordinate systems with cuitter compensation mode");

	int origin;
	int gc = parser.getGCode(ModalGroup_COORD_SYSTEM);
	switch (gc)
	{
	case G_54:	origin = 1;	break;
	case G_55:	origin = 2;	break;
	case G_56:	origin = 3;	break;
	case G_57:	origin = 4;	break;
	case G_58:	origin = 5;	break;
	case G_59:	origin = 6;	break;
	case G_59_1: origin = 7; break;
	case G_59_2: origin = 8; break;
	case G_59_3: origin = 9; break;
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_modal_0 with no GCode");
	}
	if (runner.coordinate_index == origin) // the same as now
		return true;

	runner.coordinate_index = origin;
	env->SetVariable(5220, static_cast<double>(origin)); //  save selected system
	runner.origin = env->GetG54G58(origin);				 // load the origin of the newly-selected system
	//runner.rotation_xy = env->GetVariable(5210 + (origin * 20));
	return true;
}

bool GCodeInterpreter::run_control_mode(int gc)
{
	//g61, g61.1, g64 - control mode
	switch (gc)
	{
	case G_61: runner.accuracy = AccuracyExactStop;
	case G_64: runner.accuracy = AccuracyNormal;
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_control_mode with no g61, g61.1, g64");
	}
	return true;
}

bool GCodeInterpreter::run_set_dist_mode(int gc)
{
	switch (gc)
	{
	case G_90: runner.incremental = false; break;
	case G_91: runner.incremental = true; break;
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_set_dist_mode with no g90, g91");
	}
	return true;
}

bool GCodeInterpreter::run_set_dist_ijk(int gc)
{
	switch (gc)
	{
	case G_90_1: runner.ijk_incremental = false; break;
	case G_91_1: runner.ijk_incremental = true; break;
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_set_dist_ijk with no g91.1, g92.1");
	}
	return true;
}

bool GCodeInterpreter::run_set_cycle_return(int gc)
{
	//g98, g99
	switch (gc)
	{
	case G_98: runner.retract_mode = CannedLevel_Z; break; //Отмена G99
	case G_99: runner.retract_mode = CannedLevel_R; break; // Return to R level in canned cycle
		break;
	default: RET_F_SETSTATE(INTERNAL_ERROR, "run_set_cycle_return with no g98, g99");
	}
	return true;
}


bool GCodeInterpreter::run_motion(int motion, const CmdParser &parser)
{
	Coords newPos;

	IF_F_RET_F( get_new_coordinate(parser, newPos));

	int xyzuvw_flag = (parser.hasParam(PARAM_X) || parser.hasParam(PARAM_Y) || parser.hasParam(PARAM_Z) ||
		parser.hasParam(PARAM_U) || parser.hasParam(PARAM_V) || parser.hasParam(PARAM_W));

	if (!is_a_cycle(motion))
		runner.cycle_il.reset();
	
	if ((motion == G_0) || (motion == G_1) || (motion == G_33) || (motion == G_33_1) || (motion == G_76)) 
	{
		IF_F_RET_F(move_to(motion, newPos, parser)); 
	}
	else if ((motion == G_3) || (motion == G_2)) {
		IF_F_RET_F(arc_to(motion, newPos,  parser));
	}
	else if ( motion == G_38_2 || motion == G_38_3 || //motion == GG_31 ||
		motion == G_38_4 || motion == G_38_5) 
	{
		IF_F_RET_F(probe_to(motion, newPos, parser));
	}
	else if (motion == G_80) 
	{		
		runner.motion_mode = G_80;
	}
	else if (is_a_cycle(motion)) 
	{
		IF_F_RET_F(run_cycle(motion, newPos, parser));
	}
	else if ((motion == G_5) || (motion == G_5_1)) 
	{
		;// CHP(convert_spline(motion, block, settings));
	}
	else if (motion == G_5_2) {
		;// CHP(convert_nurbs(motion, block, settings));
	}
	else
	{
		RET_F_SETSTATE(INTERNAL_ERROR, "run_motion with no motion codes");
	}
	return true;
}

//====================================================================================================
//чтение новых координат с учётом модальных кодов

void GCodeInterpreter::setcoordinates(Coords &newpos, const CmdParser &parser, bool doofesett) const
{
	double val;
	if (parser.getRParam(PARAM_X, &val))
	{
		newpos.x = to_mm(val);
		if (doofesett)
			newpos.x += (runner.origin.x + runner.axis_offset.x + runner.tool_xoffset);
	}
	if (parser.getRParam(PARAM_Y, &val))
	{
		newpos.y = to_mm(val);
		if (doofesett)
			newpos.y += (runner.origin.y + runner.axis_offset.y + runner.tool_yoffset);
	}

	if (parser.getRParam(PARAM_Z, &val))
	{
		newpos.z = to_mm(val);
		if (doofesett)
			newpos.z += (runner.origin.z + runner.axis_offset.z + runner.tool_length_offset);
	}

	if (parser.getRParam(PARAM_A, &val))
	{
		newpos.a = to_mm(val);
		if (doofesett)
			newpos.a += (runner.origin.a + runner.axis_offset.a);
	}
	if (parser.getRParam(PARAM_B, &val)) 
	{
		newpos.b = to_mm(val);
		if (doofesett)
			newpos.b += (runner.origin.b + runner.axis_offset.b);
	}
	if (parser.getRParam(PARAM_C, &val)) 
	{
		newpos.c = to_mm(val);
		if (doofesett)
			newpos.c += (runner.origin.c + runner.axis_offset.c);
	}
}




bool GCodeInterpreter::get_new_coordinate(const CmdParser &parser, Coords &newpos )
{
	
	//bool middle = !runner.cutter_comp_firstmove;
	//bool comp = (runner.cutter_comp_side);
	if (parser.getGCode(ModalGroup_MODAL_0) == G_53)
	{
		newpos = runner.position;
		setcoordinates(newpos,  parser, false );
	}

	else if (!runner.incremental)  // absolute position
	{
		newpos = runner.position;
		setcoordinates(newpos, parser, true);
	}
	else // incremental
	{
		newpos = runner.position;
		Coords move;
		setcoordinates(move, parser, false);
		for (int i = 0; i < MAX_AXES; ++i)
			newpos.r[i] += move.r[i];
	}
	return true;
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


bool GCodeInterpreter::probe_to(int motion, const Coords &position, const CmdParser &parser)
{
	if (executor)
		executor->process_probe(position);
	
	//executor->straight_traverce(position);
	//runner.position = position; //??
	runner.motion_mode = motion;
	return true;
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

//====================================================================================================
bool  GCodeInterpreter::move_to(int motion, const Coords &position, const CmdParser &parser)
{

	if (motion == G_1)
	{
		IF_T_RET_F_SETSTATE((runner.feed_rate == 0.0), PARAMETER_ERROR, "Ca not do G1 with  zero feed rate");
		IF_T_RET_F_SETSTATE((runner.feed_mode == FeedMode_UnitPerRevolution) && (spindlespeed == 0.0)), PARAMETER_ERROR, "Can not feed with zero spindle speed in feed per rev mode");
	}

	runner.motion_mode = motion;

	if ((runner.cutter_comp_side) && (runner.cutter_comp_radius > 0.0))    /* radius always is >= 0 */
	{
		IF_T_RET_F_SETSTATE((parser.getGCode(ModalGroup_MODAL_0) == G_53), PARAMETER_ERROR, "Can not use G53 with cutter radius compenstion");

		if (runner.plane == Plane_XZ)
		{
			if (runner.cutter_comp_firstmove)
				IF_F_RET_F(run_straight_comp1(motion, position.z, position.x, position.y, position.a, position.b, position.c);
			else
					IF_F_RET_F(run_straight_comp2(motion, position.z, position.x, position.y, position.a, position.b, position.c);
		}
		else if (runner.plane == Plane_XY)
		{
			if (runner.cutter_comp_firstmove)
				IF_F_RET_F(run_straight_comp1(motion, position.x, position.y, position.z, position.a, position.b, position.c);
			else
					IF_F_RET_F(run_straight_comp2(motion, position.x, position.y, position.z, position.a, position.b, position.c);
		}
		else
						RET_F_SETSTATE(PARAMETER_ERROR, "Invalid plane for cutter compensation");
	}
	else if (motion == G_0)
	{
		executor->straight_traverce(position);
		runner.position = position;
	}
	else if (motion == G_1)
	{
		executor->straight_feed(position);
		runner.position = position;
	}
	else if (motion == G_33)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G33 not supported");
	}
	else if (motion == G_33_1)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G33.1 not supported");
	}
	else if (motion == G_76)
	{
		RET_F_SETSTATE(PARAMETER_ERROR, "G76 not supported");
	}
	else
	{	
		RET_F_SETSTATE(PARAMETER_ERROR, "Undefened motion G%f", motion/10.);
	}
	return true;
}



/****************************************************************************/

/*! convert_straight_comp1

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The side is not RIGHT or LEFT:
	  NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT
   2. The destination tangent point is not more than a tool radius
	  away (indicating gouging): NCE_CUTTER_GOUGING_WITH_CUTTER_RADIUS_COMP
   3. The value of move is not G_0 or G_1
	  NCE_BUG_CODE_NOT_G0_OR_G1

Side effects:
   This executes a STRAIGHT_MOVE command at cutting feed rate
   or a STRAIGHT_TRAVERSE command.
   It also updates the setting of the position of the tool point
   to the end point of the move and updates the programmed point.

Called by: convert_straight.

This is called if cutter radius compensation is on and
settings->cutter_comp_firstmove is true, indicating that this is the
first move after cutter radius compensation is turned on.

The algorithm used here for determining the path is to draw a straight
line from the destination point which is tangent to a circle whose
center is at the current point and whose radius is the radius of the
cutter. The destination point of the cutter tip is then found as the
center of a circle of the same radius tangent to the tangent line at
the destination point.

*/

void GCodeInterpreter::comp_get(Coords *srs, double *x, double *y, double *z)
{
	if (plane == Plane_XZ)
	{
		*x = srs->z;
		*y = srs->x;
		*z = srs->y;
	}
	else
	{
		*x = srs->x;
		*y = srs->y;
		*z = srs->z;
	}
}


void GCodeInterpreter::comp_set(Coords *srs, double x, double y, double z)
{
	if (plane == Plane_XZ)
	{
		srs->z = x;
		srs->x = y;
		srs->y = z;
	}
	else
	{ 
		srs->x = x;
		srs->y = y;
		srs->z = z;
	}
}
void GCodeInterpreter::comp_set_current(Coords *srs, double x, double y, double z)
{
	comp_set(&runner.position, x, y, z);
}
void GCodeInterpreter::comp_set_programmed(Coords *srs, double x, double y, double z)
{
	comp_set(&runner.program, x, y, z);
}
void GCodeInterpreter::comp_get_current(Coords *srs, double *x, double *y, double *z)
{
	comp_set(&runner.position, x, y, z);
}
void GCodeInterpreter::comp_get_programmed(Coords *srs, double *x, double *y, double *z)
{
	comp_set(&runner.program, x, y, z);
}


//void set_endpoint(double x, double y) 
//{
//	endpoint[0] = x; endpoint[1] = y;
//	endpoint_valid = 1;
//}

bool GCodeInterpreter::run_straight_comp1(int move, double px, double py, double pz )
{
	double alpha;
	double end_x, end_y;
	double cx, cy, cz;


	double radius = runner.cutter_comp_radius; /* always will be positive */
	int side = runner.cutter_comp_side;
	double distance = hypot((px - cx), (py - cy));
	
	comp_get_current( &cx, &cy, &cz);

	IF_T_RET_F_SETSTATE(((side != CutterCompType_LEFT) && (side != CutterCompType_LEFT)), 
		PARAMETER_ERROR, "Compensation type not left and not right "););
	IF_T_RET_F_SETSTATE((distance <= radius), PARAMETER_ERROR, "Length of cutter compensation entry move is not greater than the tool radius");

	alpha = atan2(py - cy, px - cx) + (CutterCompType_LEFT == LEFT ? M_PIl / 2. : -M_PIl / 2.);

	end_x = (px + (radius * cos(alpha)));
	end_y = (py + (radius * sin(alpha)));

	//set_endpoint(cx, cy);
	set_endpoint(cx, cy);

	if (move == G_0) {
		enqueue_STRAIGHT_TRAVERSE(settings, block->line_number,
			cos(alpha), sin(alpha), 0,
			end_x, end_y, pz,
			AA_end, BB_end, CC_end, u_end, v_end, w_end);
	}
	else if (move == G_1) {
		enqueue_STRAIGHT_FEED(settings, block->line_number,
			cos(alpha), sin(alpha), 0,
			end_x, end_y, pz,
			AA_end, BB_end, CC_end, u_end, v_end, w_end);
	}
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "Not G0 nor G!");
	
	runner.cutter_comp_firstmove = false;

	comp_set_current(end_x, end_y, pz);
	comp_set_programmed( px, py, pz);
	return true;
}
/****************************************************************************/

/*! convert_straight_comp2

Returned Value: int
   If any of the following errors occur, this returns the error shown.
   Otherwise, it returns INTERP_OK.
   1. The compensation side is not RIGHT or LEFT:
	  NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT
   2. A concave corner is found:
	  NCE_CONCAVE_CORNER_WITH_CUTTER_RADIUS_COMP

Side effects:
   This executes a STRAIGHT_FEED command at cutting feed rate
   or a STRAIGHT_TRAVERSE command.
   It also generates an ARC_FEED to go around a corner, if necessary.
   It also updates the setting of the position of the tool point to
   the end point of the move and updates the programmed point.

Called by: convert_straight.

This is called if cutter radius compensation is on and
settings->cutter_comp_firstmove is not true, indicating that this is not
the first move after cutter radius compensation is turned on.

The algorithm used here is:
1. Determine the direction of the last motion. This is done by finding
   the direction of the line from the last programmed point to the
   current tool tip location. This line is a radius of the tool and is
   perpendicular to the direction of motion since the cutter is tangent
   to that direction.
2. Determine the direction of the programmed motion.
3. If there is a convex corner, insert an arc to go around the corner.
4. Find the destination point for the tool tip. The tool will be
   tangent to the line from the last programmed point to the present
   programmed point at the present programmed point.
5. Go in a straight line from the current tool tip location to the
   destination tool tip location.

This uses an angle tolerance of TOLERANCE_CONCAVE_CORNER (0.01 radian)
to determine if:
1) an illegal concave corner exists (tool will not fit into corner),
2) no arc is required to go around the corner (i.e. the current line
   is in the same direction as the end of the previous move), or
3) an arc is required to go around a convex corner and start off in
   a new direction.

If a rotary axis is moved in this block and an extra arc is required
to go around a sharp corner, all the rotary axis motion occurs on the
arc.  An alternative might be to distribute the rotary axis motion
over the arc and the straight move in proportion to their lengths.

If the Z-axis is moved in this block and an extra arc is required to
go around a sharp corner, all the Z-axis motion occurs on the straight
line and none on the extra arc.  An alternative might be to distribute
the Z-axis motion over the extra arc and the straight line in
proportion to their lengths.

This handles the case of there being no XY motion.

This handles G0 moves. Where an arc is inserted to round a corner in a
G1 move, no arc is inserted for a G0 move; a STRAIGHT_TRAVERSE is made
from the current point to the end point. The end point for a G0
move is the same as the end point for a G1 move, however.

*/

bool GCodeInterpreter::convert_straight_comp2(int move,
	double px,    //!< X coordinate of programmed end point     
	double py,    //!< Y coordinate of programmed end point     
	double pz,    //!< Z coordinate of end point                
	
{
	double alpha;
	double beta;
	double end_x, end_y, end_z;                 /* x-coordinate of actual end point */
	double gamma;
	double mid_x, mid_y;                 /* x-coordinate of end of added arc, if needed */
	double radius;
	int side;
	double small = TOLERANCE_CONCAVE_CORNER;      /* radians, testing corners */
	double opx, opy, opz;      /* old programmed beginning point */
	double theta;
	double cx, cy, cz;
	int concave;

	comp_get_current(&cx, &cy, &cz);
	comp_get_current(&end_x, &end_y, &end_z);
	comp_get_programmed(&opx, &opy, &opz);

	
	if ((py == opy) && (px == opx)) 
	{     /* no XY motion */
		if (move == G_0) {
			enqueue_STRAIGHT_TRAVERSE(settings, block->line_number,
				px - opx, py - opy, pz - opz,
				cx, cy, pz,
				AA_end, BB_end, CC_end, u_end, v_end, w_end);
		}
		else if (move == G_1) {
			enqueue_STRAIGHT_FEED(settings, block->line_number,
				px - opx, py - opy, pz - opz,
				cx, cy, pz, AA_end, BB_end, CC_end, u_end, v_end, w_end);
		}
		else
			ERS(NCE_BUG_CODE_NOT_G0_OR_G1);
		// end already filled out, above
	}
	else 
	{
		// some XY motion
		side = runner.cutter_comp_side;
		radius = runner.cutter_comp_radius;      /* will always be positive */
		theta = atan2(cy - opy, cx - opx);
		alpha = atan2(py - opy, px - opx);

		if (side == LEFT) {
			if (theta < alpha)
				theta = (theta + (2 * M_PIl));
			beta = ((theta - alpha) - M_PI_2l);
			gamma = M_PI_2l;
		}
		else if (side == RIGHT) {
			if (alpha < theta)
				alpha = (alpha + (2 * M_PIl));
			beta = ((alpha - theta) - M_PI_2l);
			gamma = -M_PI_2l;
		}
		else
			ERS(NCE_BUG_SIDE_NOT_RIGHT_OR_LEFT);
		end_x = (px + (radius * cos(alpha + gamma)));
		end_y = (py + (radius * sin(alpha + gamma)));
		mid_x = (opx + (radius * cos(alpha + gamma)));
		mid_y = (opy + (radius * sin(alpha + gamma)));

		if ((beta < -small) || (beta > (M_PIl + small))) {
			concave = 1;
		}
		else if (beta > (M_PIl - small) &&
			(!qc().empty() && qc().front().type == QARC_FEED &&
			((side == RIGHT && qc().front().data.arc_feed.turn > 0) ||
				(side == LEFT && qc().front().data.arc_feed.turn < 0)))) {
			// this is an "h" shape, tool on right, going right to left
			// over the hemispherical round part, then up next to the
			// vertical part (or, the mirror case).  there are two ways
			// to stay to the "right", either loop down and around, or
			// stay above and right.  we're forcing above and right.
			concave = 1;
		}
		else {
			concave = 0;
			mid_x = (opx + (radius * cos(alpha + gamma)));
			mid_y = (opy + (radius * sin(alpha + gamma)));
		}

		if (!concave && (beta > small))
		{       /* ARC NEEDED */
			CHP(move_endpoint_and_flush( cx, cy));			
		}
		else if (concave) 
		{
			if (qc().front().type != QARC_FEED) 
			{
				// line->line
				double retreat;
				// half the angle of the inside corner
				double halfcorner = (beta + M_PIl) / 2.0;
				CHKS((halfcorner == 0.0), (_("Zero degree inside corner is invalid for cutter compensation")));
				retreat = radius / tan(halfcorner);
				// move back along the compensated path
				// this should replace the endpoint of the previous move
				mid_x = cx + retreat * cos(theta + gamma);
				mid_y = cy + retreat * sin(theta + gamma);
				// we actually want to move the previous line's endpoint here.  That's the same as 
				// discarding that line and doing this one instead.
				CHP(move_endpoint_and_flush(settings, mid_x, mid_y));
			}
			else 
			{
				// arc->line
				// beware: the arc we saved is the compensated one.
				arc_feed prev = qc().front().data.arc_feed;
				double oldrad = hypot(prev.center2 - prev.end2, prev.center1 - prev.end1);
				double oldrad_uncomp;

				// new line's direction
				double base_dir = atan2(py - opy, px - opx);
				double theta;
				double phi;

				theta = (prev.turn > 0) ? base_dir + M_PI_2l : base_dir - M_PI_2l;
				phi = atan2(prev.center2 - opy, prev.center1 - opx);
				if TOOL_INSIDE_ARC(side, prev.turn) {
					oldrad_uncomp = oldrad + radius;
				}
				else {
					oldrad_uncomp = oldrad - radius;
				}

				double alpha = theta - phi;
				// distance to old arc center perpendicular to the new line
				double d = oldrad_uncomp * cos(alpha);
				double d2;
				double angle_from_center;

				if TOOL_INSIDE_ARC(side, prev.turn) {
					d2 = d - radius;
					double l = d2 / oldrad;
					CHKS((l > 1.0 || l < -1.0), _("Arc to straight motion makes a corner the compensated tool can't fit in without gouging"));
					if (prev.turn > 0)
						angle_from_center = -acos(l) + theta + M_PIl;
					else
						angle_from_center = acos(l) + theta + M_PIl;
				}
				else {
					d2 = d + radius;
					double l = d2 / oldrad;
					CHKS((l > 1.0 || l < -1.0), _("Arc to straight motion makes a corner the compensated tool can't fit in without gouging"));
					if (prev.turn > 0)
						angle_from_center = acos(l) + theta + M_PIl;
					else
						angle_from_center = -acos(l) + theta + M_PIl;
				}
				mid_x = prev.center1 + oldrad * cos(angle_from_center);
				mid_y = prev.center2 + oldrad * sin(angle_from_center);
				CHP(move_endpoint_and_flush(settings, mid_x, mid_y));
			}
		}
		else {
			// no arc needed, also not concave (colinear lines or tangent arc->line)
			dequeue_canons(settings);
			set_endpoint(cx, cy);
		}
		(move == G_0 ? enqueue_STRAIGHT_TRAVERSE : enqueue_STRAIGHT_FEED)
			(settings, block->line_number,
				px - opx, py - opy, pz - opz,
				end_x, end_y, pz,
				AA_end, BB_end, CC_end,
				u_end, v_end, w_end);
	}

	comp_set_current( end_x, end_y, pz);
	comp_set_programmed( px, py, pz);
	return true;
}