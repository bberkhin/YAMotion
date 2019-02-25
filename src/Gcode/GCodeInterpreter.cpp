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
		RET_F_SETSTATE( NO_VALUE, "G93 Inverse Time Mode not supported");
	}
	else if( gc == G_94 )
	{
		// ok do nothing
		;
	}
	else if( gc == G_95 )
	{
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
	case G_98: runner.cycleLevel = CannedLevel_HIGH; break; //Отмена G99
	case G_99: runner.cycleLevel = CannedLevel_LOW; break; // Return to R level in canned cycle
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

//	if (!is_a_cycle(motion))
//		runner.cycle_il_flag = false;
	
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
		//settings->motion_mode = G_80;
		runner.motion_mode = G_80;
	}
	else if (is_a_cycle(motion)) 
	{
		;// CHP(convert_cycle(motion, block, settings));
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
bool  GCodeInterpreter::move_to(int motion, const Coords &position, const CmdParser &parser)
{

	if (executor)
	{
		if (motion == G_0)
		{
			executor->straight_traverce(position);
		}
		else
			executor->straight_feed(position);
	}
	runner.position = position;
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

bool GCodeInterpreter::arc_to(int motion, const Coords &position, const CmdParser &parser)       //!< either G_2 (cw arc) or G_3 (ccw arc)    
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
	runner.motion_mode = motion;

	double i = 0,j=0,k=0;
	if( parser.getRParam(PARAM_I, &i) )  i = to_mm(i);
	if( parser.getRParam(PARAM_J, &j) )  j = to_mm(j);
	if( parser.getRParam(PARAM_K, &k) )  k = to_mm(k);
	
	if (runner.plane == Plane_XY) 
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0)) 
		{
			IF_F_RET_F(convert_arc2(motion, parser,
					&(runner.position.x), &(runner.position.y), &(runner.position.z),
					end_x, end_y, end_z,
					AA_end, BB_end, CC_end,	
					u_end, v_end, w_end, i, j));
		}
		else if (first) 
		{
			IF_F_RET_F( convert_arc_comp1(motion, parser, end_x, end_y, end_z,
				i, j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else {
			IF_F_RET_F( convert_arc_comp2(motion, parser, end_x, end_y, end_z,
				i,j, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
	}
	else if (runner.plane == Plane_XZ) 
	{
		if ((!runner.cutter_comp_side) ||
			(runner.cutter_comp_radius == 0.0)) 
		{
			IF_F_RET_F(	convert_arc2(motion, parser,
				&(runner.position.z), &(runner.position.x), &(runner.position.y),
				end_z, end_x, end_y, AA_end, BB_end, CC_end,	u_end, v_end, w_end, k,i));
		}
		else if (first) 
		{
			IF_F_RET_F( convert_arc_comp1(motion, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));
		}
		else 
		{
			IF_F_RET_F(convert_arc_comp2(motion, parser, end_z, end_x, end_y,
				k, i, AA_end, BB_end, CC_end, u_end, v_end, w_end));
			
		}
	}
	else if (runner.plane == Plane_YZ) {
		IF_F_RET_F(convert_arc2(motion, parser,
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


bool GCodeInterpreter::convert_arc2(int motion,       //!< either G_2 (cw arc) or G_3 (ccw arc)    
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
		IF_F_RET_F(arc_data_r(motion, *current1, *current2, end1, end2,
			rval, p_int, &center1, &center2, &turn, radius_tolerance));
	}
	else 
	{
		IF_F_RET_F(arc_data_ijk(motion, *current1, *current2, end1, end2,
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


bool GCodeInterpreter::arc_data_ijk(int motion,       //!< either G_2 (cw arc) or G_3 (ccw arc)
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

	if (runner.ijk_incremental ) 
	{
		*center_x = (current_x + i_number);
		*center_y = (current_y + j_number);
	}
	else 
	{
		*center_x = (i_number);
		*center_y = (j_number);
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

	if (motion == G_2)
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


bool GCodeInterpreter::arc_data_r(int motion, //!< either G_2 (cw arc) or G_3 (ccw arc)	
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
	if (((motion == G_2) && (radius > 0)) || ((motion != G_2) && (radius < 0)))
		theta = atan2((end_y - current_y), (end_x - current_x)) - M_PI_2l;
	else
		theta = atan2((end_y - current_y), (end_x - current_x)) + M_PI_2l;

	turn2 = asin(half_length / abs_radius);
	offset = abs_radius * cos(turn2);
	*center_x = mid_x + (offset * cos(theta));
	*center_y = mid_y + (offset * sin(theta));
	*turn = (motion==G_2) ? -1 * p_number : 1 * p_number;

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

bool GCodeInterpreter::convert_arc_comp1(int motion,  //!< either G_2 (cw arc) or G_3 (ccw arc)            
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
bool GCodeInterpreter::convert_arc_comp2(int motion,  //!< either G_2 (cw arc) or G_3 (ccw arc)          
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
