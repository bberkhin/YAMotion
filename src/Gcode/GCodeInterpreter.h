#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "iexecutor.h"
#include "ienvironment.h"
#include "ilogger.h"

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
	enum ModalGroup //некоторые операторы не могут одновременно содержаться в одном фрейме
	{
		ModalGroup_NONE = 0, //g4,g10,g28,g30,g53,g92.[0-3]
		ModalGroup_MOVE,                 //g0..g3 //G38.2, G80..G89
		ModalGroup_INCREMENTAL, //g90..g91
		ModalGroup_UNITS, //g20..g21
		//ModalGroup_CYCLE, //g80..g85
		ModalGroup_COORD_SYSTEM, //g54..g58
		ModalGroup_TOOL_LENGTH_CORRECTION, //g43,g44,g49
		ModalGroup_TOOL_RADIUS_CORRECTION, //g40..g42
		ModalGroup_CYCLE_RETURN, //g98, g99
		ModalGroup_ACTIVE_PLANE, //g17..g19
		ModalGroup_STOP, //M0, M1, M2, M30, M60
		ModalGroup_TOOL_CHANGE, //M6
		ModalGroup_TURN_TOOL, //M3, M4, M5
		ModalGroup_GREASER, //M7, M8, M9
		ModalGroup_FEEDMODE,  // g93, g94, g95
		ModalGroup_SPINDLEMODE  //G96 G97 spindle
	};


	struct InterError
	{
		enum Code
		{
			ALL_OK = 0,
			INVALID_STATEMENT, //неизвестная буква
			DOUBLE_DEFINITION, //буква повторилась
			WRONG_PLANE,       //задана неправильная плоскость
			WRONG_LETTER,
			WRONG_VALUE,
			NO_VALUE,
		};

		Code code;
		std::string description;
		InterError() :code(ALL_OK) { }
		InterError(Code code, std::string description) : code(code), description(description) {}
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
		int spindlespeed; // обороты шпиндля
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



	struct GKey
	{
		char letter;
		double value;
		int position;
	};

	//здесь переменные для чтения команд
	class  CmdParser
	{
	public:
		CmdParser() { }
		std::vector<GKey> codes;
		bool parse_codes(const char *frame); //читает коды и значения параметров
		bool check_modal_group() const;
		bool contain_cmd(ModalGroup group) const;
		bool contain_cmd(char letter, int ival) const;
		InterError get_state() const;
		bool getRValue(char ch, double *pr) const;
		bool getIValue(char ch, int *pi) const;
	private:
		bool parse_code(const char *string, int &position, GKey &key); //следующий код
		void find_significal_symbol(const char *string, int &position) const; //пропускает комментарии, пробелы
		bool parse_value(const char *string, int &position, double &value) const; //считывает число
		ModalGroup get_modal_group(const GKey &key) const;
	private:
		mutable InterError  state;
	};

	enum BitPos
	{
		BitPos_ERR = -1,
		BitPos_X = 0, BitPos_Y, BitPos_Z,
		BitPos_A, BitPos_B, BitPos_C,
		BitPos_I, BitPos_J, BitPos_K,
		BitPos_F, BitPos_P, BitPos_Q, BitPos_S, BitPos_R, BitPos_D, BitPos_L,
	};

	struct Flags
	{
		unsigned int flags;
		Flags() : flags(0) { }
		void reset() { flags = 0; }
		bool get(int pos)
		{
			return (flags & (1 << pos)) != 0;
		}
		void set(int pos, bool value)
		{
			if (value)
				flags |= (1 << pos);
			else
				flags &= ~(1 << pos);
		}
	};

	class GCodeInterpreter  //несомненно, это интерпретатор г-кода )
	{
	public:
		GCodeInterpreter(IEnvironment *penv, IExecutor *executor, ILogger *logger);
		~GCodeInterpreter(void);

		bool read_file(const char *name);             //запоминает строки текстового файла
		void execute_file(IExecutor *executor);                    //исполняет файл
		void execute_file(const char *data);
		void execute_line(const  char *line, int lineNumber = 1);    //исполняет одну строку

	private:
		void init();                            //инициализация для нового файла
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
		void setopionalcoordinate(Coords &newpos, optdouble *pvalss);
		Coords  get_new_coordinate(Coords &oldLocal, optdouble *pvalss);

		InterError get_state() { return error_; }
	private:
		InterError error_;
		std::list<std::string> inputFile;     //строки входного файла
		RunnerData  runner;                    //текущее состояние
		ILogger *logger;
		IEnvironment *env;
		IExecutor *executor; //устройство, которое исполняет команды   
	};

};
