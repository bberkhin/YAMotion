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
	env(penv), executor(ix), logger(log), gfile(0), cq(ix,&runner)
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
		logger->log(LOG_WARNING, nline, "No end of programm command ");
		executor->set_end_programm();
	}
	if (substack.size() != 1)
	{
		logger->log(LOG_WARNING, nline, "The programm end being in subrotinue" );
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
			logger->log(LOG_WARNING, lineNumber, "Line is too long.");
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
			logger->log(LOG_ERROR, lineNumber, state.description.c_str());

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

	int ival;
	IF_F_RET_F_SETSTATE(parser.getIParam(PARAM_P, &ival), PARAMETER_ERROR, "There is no 'P' parameter for m98");
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
		runner.feed_mode = FeedMode_UnitPerRevolution;
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

bool GCodeInterpreter::run_cutter_comp(const CmdParser &parser)
{
	int gc = parser.getGCode(ModalGroup_CUTTER_COMP);
	if (gc == G_40)
		IF_F_RET_F(run_cutter_comp_off());
	else if (gc == G_41)
		IF_F_RET_F(run_cutter_comp_on(CutterCompType_LEFT, parser));
	else if (gc == G_42)
		IF_F_RET_F(run_cutter_comp_on(CutterCompType_RIGHT, parser));
	else if (gc == G_41_1)
		IF_F_RET_F(run_cutter_comp_on(CutterCompType_LEFT, parser));
	else if (gc == G_42_1)
		IF_F_RET_F(run_cutter_comp_on(CutterCompType_RIGHT, parser));
	else
		RET_F_SETSTATE(INTERNAL_ERROR, "GCodeInterpreter::run_cutter_comp can notbe called here");
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
		IF_F_RET_F(run_cutter_comp(parser));
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
	case G_28:  //run_to_home()
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

	if (parser.contain_m(2))
	{
		state.code = PRAGRAMM_END;
	}
	else if (parser.contain_m(30))
	{
		state.code = PRAGRAMM_ENDCLEAR;

	}
	else
		return false;

	double cx, cy, cz;
	comp_get_current( &cx, &cy, &cz);
	if (!cq.move_endpoint_and_flush(cx, cy))
	{
		state = cq.get_state();
	}
	cq.dequeue_canons();
	executor->set_end_programm();
	return true;
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
			logger->log(LOG_WARNING, lineNumber, "Line is very long");
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
				logger->log(LOG_WARNING, lineNumber, "'(' inside comment");
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
		logger->log(LOG_WARNING, lineNumber, "Unclosed comment");

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


bool GCodeInterpreter::run_cutter_comp_off()      //!< pointer to machine settings
{

	if (runner.cutter_comp_side && runner.cutter_comp_radius > 0.0 && !runner.cutter_comp_firstmove)
	{
		double cx, cy, cz;
		comp_get_current( &cx, &cy, &cz);
		if ( !cq.move_endpoint_and_flush(cx, cy) )
		{
			state = cq.get_state();
			return false;
		}
		cq.dequeue_canons();
		runner.position = runner.program;
		//runner.arc_not_allowed = true;
	}
	runner.cutter_comp_side = CutterCompType_NONE;
	runner.cutter_comp_firstmove = true;
	return true;
}

bool GCodeInterpreter::run_cutter_comp_on(CutterCompType side, const CmdParser &parser)
{
	
	double radius;
	int tool;
	int orientation;

	IF_T_RET_F_SETSTATE((runner.plane != Plane_XY && runner.plane != Plane_XZ),
		PARAMETER_ERROR, "Invalid plane for cutter compensation not XY no XZ");
	IF_T_RET_F_SETSTATE((runner.cutter_comp_side), PARAMETER_ERROR, "Cutter radius compensation already ON");

	int gc = parser.getGCode(ModalGroup_CUTTER_COMP);
	if ( gc == G_41_1 || gc == G_42_1)
	{
		IF_F_RET_F_SETSTATE( parser.hasParam(PARAM_D), PARAMETER_ERROR, "G%d.1 with no D word",gc / 10);
		
		parser.getRParam(PARAM_D, &radius);
		radius = radius / 2;
		if ( parser.hasParam(PARAM_L) )
		{
			IF_T_RET_F_SETSTATE((runner.plane != Plane_XZ), PARAMETER_ERROR, "G%d.1 with L word, but plane is not G18", gc / 10);
			parser.getIParam(PARAM_L, &orientation);
		}
		else {
			orientation = 0;
		}
	}
	else 
	{
		if (!parser.hasParam(PARAM_D))
		{
			tool = 0;
		}
		else 
		{
			parser.getIParam(PARAM_D, &tool);
			IF_T_RET_F_SETSTATE((tool < 0), PARAMETER_ERROR, "Negative Value D for tool number");
		}
		radius = env->getToolById(tool).diameter / 2.0;
		//orientation = settings->tool_table[pocket_number].orientation;
		//CHKS((settings->plane != CANON_PLANE_XZ && orientation != 0 && orientation != 9), _("G%d with lathe tool, but plane is not G18"), block->g_modes[7] / 10);
	}
	if (radius < 0.0) 
	{ /* switch side & make radius positive if radius negative */
		radius = -radius;
		if (side == CutterCompType_RIGHT)
			side = CutterCompType_LEFT;
		else
			side = CutterCompType_RIGHT;
	}
	runner.cutter_comp_radius = radius;
	//runner.cutter_comp_orientation = orientation;
	runner.cutter_comp_side = side;
	return true;
}

