#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "iexecutor.h"
#include "ienvironment.h"
#include "ilogger.h"
#include "gcodedefs.h"
#include <stack>

namespace Interpreter
{


	enum Plane
	{
		Plane_NONE = 0,
		Plane_XY,
		Plane_YZ,
		Plane_XZ
	};

	enum UnitSystem //система единиц
	{
		UnitSystem_INCHES = 0,
		UnitSystem_MM, //метричекая
		UnitSystem_CM
	};

	enum CoordIndex //номера координат в массиве
	{
		X_AXIS = 0,
		Y_AXIS = 1,
		Z_AXIS = 2,
	};

	enum MotionMode //режимы перемещения
	{
		MotionMode_NONE = 0,
		MotionMode_FAST,      //быстрое позиционирование
		MotionMode_LINEAR,    //линейная интерполяция
		MotionMode_CW_ARC,    //круговая интерполяция
		MotionMode_CCW_ARC,
	};

	enum CannedCycle
	{
		CannedCycle_NONE = 0,
		CannedCycle_RESET,           //отмена цикла, G80
		CannedCycle_SINGLE_DRILL,    //простое сверление, G81
		CannedCycle_DRILL_AND_PAUSE, //сверление с задержкой на дне, G82
		CannedCycle_DEEP_DRILL,      //сверление итерациями, G83
	};

	enum CannedLevel
	{
		CannedLevel_NONE = 0,
		CannedLevel_HIGH,   //отвод к исходной плоскости, G98
		CannedLevel_LOW,    //отвод к плоскости обработки, G99
	};
	
	//=================================================================================================
	//интерпретатор работает следующим образом
	//читается вся строка, выбираются команды и для них ищутся параметры

	//здесь переменные для выполнения команд
	struct RunnerData
	{
		//параметры, нужные для кодов, которые действуют на несколько строк
		int toolid;                       // инструмент
		Coords position;         //"текущая" позиция устройства в миллиметрах
		UnitSystem units;        //текущая система единиц измерения
		bool incremental;        //абсолютная система координат?
		MotionMode motionMode;   //режим перемещения (линейная интерполяция и т.п.)
		Plane plane;             //текущая плоскость интерполяции
		double feed;             //подача в мм/мин
		double spindlespeed; // обороты шпиндля
		Coords origin;            //параметры команд G54..G58
		CannedCycle cycle;       //текущий цикл
	//    bool   cycleUseLowLevel; //использовать R вместо стартовой точки
	//    double cycleLowLevel;    //плоскость отвода (задаётся в R)
	//    double cycleHiLevel;     //исходная плоскость задаётся в стартовом Z
	//    double cycleDeepLevel;   //глубина сверления задаётся в Z
	//    double cycleStep;        //глубина одного шага Q
	//    int    cycleWait;        //задержка в цикле P
		RunnerData() :
			toolid(-1), units(UnitSystem_MM), incremental(false), motionMode(MotionMode_NONE), plane(Plane_XY), feed(0), spindlespeed(0),
			cycle(CannedCycle_NONE) { }

	};


	struct SubratinInfo
	{
		std::string name;
		unsigned int startpos;
		unsigned int endpos;
		int level;
		int type;
		SubratinInfo() : startpos(0), endpos(0), level(0), type(O_none) { }
	};

	typedef std::stack<SubratinInfo> substack;
	
	class CmdParser;

	class GCodeInterpreter  //несомненно, это интерпретатор г-кода )
	{
	public:
		GCodeInterpreter(IEnvironment *penv, IExecutor *executor, ILogger *logger);
		~GCodeInterpreter(void);

		bool read_file(const char *name);             //запоминает строки текстового файла
		void execute_file();
		void execute_file(const char *data);
		void execute_line(const  char *line, int lineNumber = 1);    //исполняет одну строку

	private:
		void init();                            //инициализация для нового файла
		const char *cpy_close_and_downcase(char *line, const char *src, int lineNumber);
		InterError execute_frame(const char *frame);    //выполнение строки
	//  void set_move_mode(MoveMode mode);      //изменение режима перемещения
		void local_deform(Coords &coords);      //преобразование масштаба, поворот в локальной системе координат
		void to_global(Coords &coords);         //сдвиг в глобальные координаты
		void to_local(Coords &coords);          //сдвиг в локальные координаты
		coord to_mm(coord value);               //переводит из текущих единиц в мм
		Coords to_mm(Coords value);
		void move_to(const Coords &position, bool fast);          //линейное перемещение
		void  arc_to(const Coords &position, bool cw);

		bool run_feed_mode(const CmdParser &parser);
		bool run_feed_rate(const CmdParser &parser);
		bool run_spindle_mode(const CmdParser &parser);
		bool run_speed(const CmdParser &parser);
		bool run_tool_cmd(const CmdParser &parser);
		bool run_mcode(const CmdParser &parser);
		bool run_gcode(const CmdParser &parser);
		bool run_stop(const CmdParser &parser);		
		void setcoordinates(Coords &newpos, const CmdParser &parser) const; 
		Coords get_new_coordinate(Coords &oldLocal, const CmdParser &parser);

		InterError get_state() { return state; }
	private:
		InterError state;
		std::list<std::string> inputFile;     //строки входного файла
		RunnerData  runner;                    //текущее состояние
		ILogger *logger;
		IEnvironment *env;
		IExecutor *executor; //устройство, которое исполняет команды   
		substack sstack; // 
	};

};
