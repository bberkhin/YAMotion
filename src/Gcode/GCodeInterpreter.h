﻿#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "iexecutor.h"
#include "ienvironment.h"
#include "ilogger.h"
#include "gcodedefs.h"
#include <stack>
#include <map>

namespace Interpreter
{


	
	//=================================================================================================
	//интерпретатор работает следующим образом
	//читается вся строка, выбираются команды и для них ищутся параметры

	struct SubratinInfo
	{
		std::string name;
		long startpos;
		long callfrom;
		int nline;
		int type;
		SubratinInfo() : startpos(0), callfrom(0), type(O_none), nline(1) { }
	};

	typedef std::stack<SubratinInfo> substack_tp;
	typedef std::map<std::string, SubratinInfo> submap_tp;


	
	class CmdParser;

	//typedef bool GCodeInterpreter::(const char *)ExecFunction;
	class GCodeInterpreter;
	typedef InterError(GCodeInterpreter::*ExecFunction) (const char *);


	class GCodeInterpreter  //несомненно, это интерпретатор г-кода )
	{
	public:
		GCodeInterpreter(IEnvironment *penv, IExecutor *executor, ILogger *logger);
		~GCodeInterpreter(void);

		bool open_nc_file(const wchar_t *name = 0);             //запоминает строки текстового файла
		void execute_file();
	//	void execute_file(const char *data);
	//	void execute_line(const  char *line, int lineNumber = 1);    //исполняет одну строку

	private:
		void close_nc_file();
		void init();                            //инициализация для нового файла
		bool execute_file_int(long pos, ExecFunction fun, int &lineNumber);
		const char *cpy_close_and_downcase(char *line, const char *src, int lineNumber);
		InterError execute_frame(const char *frame);    //выполнение строки
		InterError is_subrotin_start(const char *str);    //выполнение строки при поиске
		bool execute_subrotinue(const  CmdParser parser);
		bool find_subrotinue(const char *subname, SubratinInfo *psub);
		void reset_motion_mode();
		//void set_move_mode(MotionMode mode);      //изменение режима перемещения
		void local_deform(Coords &coords);      //преобразование масштаба, поворот в локальной системе координат
		void to_global(Coords &coords);         //сдвиг в глобальные координаты
		void to_local(Coords &coords);          //сдвиг в локальные координаты
		coord to_mm(coord value) const;               //переводит из текущих единиц в мм
		Coords to_mm(Coords value) const;
		void move_to(const Coords &position, bool fast);          //линейное перемещение
		void probe_to(const Coords &position);
		bool arc_to(const Coords &position, bool cw, const CmdParser &parser);

		bool run_start_stop_spindle(const CmdParser &parser);
		bool run_set_plane(int gc);
		bool run_feed_mode(CmdParser &parser);
		bool run_feed_rate(const CmdParser &parser);
		bool run_spindle_mode(CmdParser &parser);
		bool run_dwell(CmdParser &parser);
		bool run_speed(const CmdParser &parser);
		bool run_tool_cmd(const CmdParser &parser);
		bool run_mcode(const CmdParser &parser);
		bool run_gcode( CmdParser &parser);
		bool run_stop(const CmdParser &parser);		
		bool run_input_mode(CmdParser &parser);
		bool run_tool_height_offset(const CmdParser &parser);
		bool run_tool_crc(const CmdParser &parser);
		bool run_set_lathe_diam(const CmdParser &parser);
		bool run_modal_0(CmdParser &parser);
		bool convert_axis_offsets(int gc, const CmdParser &parser);
		bool run_set_units(int gc);
		bool run_set_coord_sys(const CmdParser &parser);
		bool run_control_mode(int gc);
		bool run_set_dist_mode(int gc);
		bool run_set_dist_ijk(int gc);
		bool run_set_cycle_return(int gc);
		bool run_motion(const CmdParser &parser);

		void setcoordinates(Coords &newpos, const CmdParser &parser) const; 
		Coords get_new_coordinate(Coords &oldLocal, const CmdParser &parser);

		InterError get_state() { return state; }
		//Arc support
		bool convert_arc2(bool cw, const CmdParser &parser, double *current1, double *current2, double *current3,
			double &end1, double &end2, double &end3, double &AA_end, double &BB_end, double &CC_end, double &u, double &v, double &w,
			double &offset1, double &offset2);
		bool arc_data_ijk(bool cw, double &current_x, double &current_y, double &end_x, double &end_y,   //!< second coordinate of arc end point
			double &i_number, double &j_number, int p_number, double *center_x, double *center_y, int *turn,
			double radius_tolerance, double spiral_abs_tolerance, double spiral_rel_tolerance);
		bool arc_data_r(bool cw, double &current_x, double &current_y, double &end_x, double &end_y,
			double &radius, int p_number, double *center_x, double *center_y, int *turn, double &tolerance);
		bool convert_arc_comp1(bool cw, const CmdParser &parser, double &end_x, double &end_y, double &end_z, double &offset_x, double offset_y,
			double &AA_end, double &BB_end, double &CC_end, double &u_end, double &v_end, double &w_end);
		bool convert_arc_comp2(bool cw, const CmdParser &parser, double end_x, double end_y, double end_z, double offset_x, double offset_y,
			double AA_end, double BB_end, double CC_end, double u, double v, double w);

		char arc_axis1(Plane plane);
		char arc_axis2(Plane plane);
	private:
		InterError state;
		std::wstring file_name;     //строки входного файла
		FILE *gfile;
		submap_tp submap;
		substack_tp substack;
		std::string cursubr_;
		RunnerData  runner;                    //текущее состояние
		ILogger *logger;
		IEnvironment *env;
		IExecutor *executor; //устройство, которое исполняет команды   
		long fpos;
	};

};
