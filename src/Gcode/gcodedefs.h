#pragma once
#include <string>
#include <list>
#include <queue>
#include <memory>
#include "stdint.h"
#include <optional>

#define MAX_GCODE_LINELEN 512
#define MM_PER_INCHES 2.54
#define PI 3.14159265358979323846
#define M_PIl	3.1415926535897932384626433832795029L  /* pi */
#define TWO_PI (2.0*3.141592653589793238)
#define HALF_PI 1.5707963267948966
#define M_PI_2l 1.570796326794896619231321691639751442L /* pi/2 */
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)
#define TINY 1e-12              /* for arc_data_r */
#define THETA_SIGMA 1e-13
#define SPIRAL_RELATIVE_TOLERANCE 0.001
//#define NUM_AXES   4 //сколько осей используем (координаты плюс подчиненные им оси)
#define MAX_AXES   6 //сколько всего есть осей на контроллере
#define MAX_FEED_RATE 10000
#define MAX_SPINDELSPEED 60000
#define G83_RAPID_DELTAMM 0.254
#define TOLERANCE_CONCAVE_CORNER 0.05   /* radians, testing corners */
#define RADIUS_TOLERANCE_MM 0.00127


/* Equivalent metric constants */
#define CENTER_ARC_RADIUS_TOLERANCE_MM (2 * 0.01 * M_SQRT2)
//#define MIN_CENTER_ARC_RADIUS_TOLERANCE_MM 0.001


#define N_CHANNELS 8                  // number of channels/board


#define IF_F_RET_F(fun)                             \
    do {                                                   \
        if( !fun )            \
			return false;                                      \
    } while(0)


#define RET_F_SETSTATE(error, fmt, ...)                             \
    do {                                                   \
        state = InterError::CreateErrorCode(error, fmt, ## __VA_ARGS__);            \
        return false;                                      \
    } while(0)

#define IF_F_RET_F_SETSTATE(fun, error, fmt, ...)                             \
    do {                                                   \
		if( !(fun) )                                     \
		{ state = InterError::CreateErrorCode(error, fmt, ## __VA_ARGS__);            \
		  return false; }                                   \
    } while(0)

#define IF_T_RET_F_SETSTATE(fun, error, fmt, ...)                             \
    do {                                                   \
		if( fun )                                     \
		{ state = InterError::CreateErrorCode(error, fmt, ## __VA_ARGS__);            \
		  return false; }                                   \
    } while(0)


#ifndef MAX_PATH
#define MAX_PATH 256
#endif

template<class T>
T SQ(T a) { return a * a; }


enum
{
	KMOTION_OK = 0,
	KMOTION_TIMEOUT = 1,
	KMOTION_READY = 2,
	KMOTION_ERROR = 3,
};

enum
{
	BOARD_TYPE_UNKNOWN = 0,
	BOARD_TYPE_KMOTION = 1,
	BOARD_TYPE_KFLOP = 2,
};

enum // KMotionLocked Return Codes
{
	KMOTION_LOCKED = 0,        // (and token is locked) if KMotion is available for use
	KMOTION_IN_USE = 1,        // if already in use
	KMOTION_NOT_CONNECTED = 2, // if error or not able to connect
};

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


	enum CannedLevel
	{
		CannedLevel_NONE = 0,
		CannedLevel_Z,   //Return to current Z level in canned cycle
		CannedLevel_R,    //Return to R level in canned cycle
	};
	enum CutterCompType
	{
		CutterCompType_NONE = 0,
		CutterCompType_LEFT,
		CutterCompType_RIGHT
	};
	enum MoveAccuracy
	{
		AccuracyNormal = 0,
		AccuracyExactStop
	};
	enum FeedMode
	{
		FeedMode_UnitPerMin = 0,
		FeedMode_UnitPerRevolution,
		FeedMode_InverseTime

	};

	enum ErrorCode
	{
		ALL_OK = 0,
		PRAGRAMM_END,       // M02
		PRAGRAMM_ENDCLEAR, // M30
		SUBROTINE_END,
		ERROR_FILEREAD,
		INVALID_STATEMENT, //неизвестная буква
		DOUBLE_DEFINITION, //буква повторилась
		WRONG_PLANE,       //задана неправильная плоскость
		WRONG_LETTER,
		WRONG_VALUE,
		NO_VALUE,
		MUITYPLIE_PARAM,
		NOTSUPPORTEDYET,
		UNKNOWN_OPERATOR,
		PARAMETER_ERROR,
		EXPRESSION_ERROR,
		SUBROUTINE_ERROR,
		INTERNAL_ERROR
	};

	enum IndexParam
	{
		PARAM_A = 0,
		PARAM_B,
		PARAM_C,
		PARAM_X,
		PARAM_Y,
		PARAM_Z,
		PARAM_D,
		PARAM_E,
		PARAM_F,
		PARAM_I,
		PARAM_J,
		PARAM_K,
		PARAM_P,
		PARAM_Q,
		PARAM_R,
		PARAM_S,
		PARAM_U,
		PARAM_V,
		PARAM_W,
		PARAM_AT,
		PARAM_MAX_R_PARAM,
		//int value
		PARAM_L,
		PARAM_H,
		PARAM_T,
		PARAM_MAX
	};

	enum GModalGroup //некоторые операторы не могут одновременно содержаться в одном фрейме
	{
		ModalGroup_MODAL_0 = 0, //g4, g10, g28, g30, g53, g92 g92.1, g92.2, g92.3 - misc
		ModalGroup_MOVE,  //g0, g1, g2, g3, g38.2, g5, g6 g80, g81, g82, g83, g84, g85, g86, g87, g88, g89 - motion
		ModalGroup_ACTIVE_PLANE, // g17, g18, g19 - plane selection
		ModalGroup_DISTANCE, //g90..g91
		ModalGroup_IJK_DISTANCE, //g90.1, g91.1 - IJK distance mode for arcs
		ModalGroup_FEEDMODE,  // g93, g94, g95 - feed rate mode
		ModalGroup_UNITS, //g20..g21
		ModalGroup_CUTTER_COMP, //G40, G41, G41.1, G42, G42.1
		ModalGroup_TOOL_LENGTH_CORRECTION, //G43, G43.1, G43.2, G44 or G49 tool length offse
		ModalGroup_NONDEFINED,
		ModalGroup_CYCLE_RETURN, //g98, g99
		ModalGroup_NONDEFINED1,
		ModalGroup_COORD_SYSTEM, //g54, g55, g56, g57, g58, g59, g59.1, g59.2, g59.3
		ModalGroup_CONTROL,//g61, g61.1, g64 - control mode
		ModalGroup_SPINDLEMODE,  //G96 G97 spindle
		ModalGroup_LATHE_DIAMETER, //G7 or G8
		ModalGroup_Size
		
	};

// M Group
	enum MModalGroup //некоторые операторы не могут одновременно содержаться в одном фрейме
	{
		ModalGroup_NONE,
		ModalGroup_STOP, //M0, M1, M2, M30, M60
		ModalGroup_TURN_TOOL, //M3, M4, M5 
		ModalGroup_GREASER //M7, M8, M9
	};

	struct InterError
	{
		ErrorCode code;
		std::string description;
		InterError() :code(ALL_OK) { }
		void clear() { code = ALL_OK; description.clear(); }

		InterError(ErrorCode code, std::string description) : code(code), description(description) {}
		static InterError CreateErrorCode(ErrorCode cod, const char *fmt, ...);
	};

	typedef double coord;//чтобы не путаться, координатный тип введём отдельно
	typedef std::optional<double> optdouble;

	struct Coords   //все координаты устройства
	{
		union
		{
			struct
			{
				coord x, y, z, a, b, c;
			};
			struct
			{
				coord r[MAX_AXES];
			};
		};

		Coords() { for (int i = 0; i < MAX_AXES; ++i) r[i] = 0; }
		Coords(const coord &x_, const coord &y_, const coord &z_) { Set(x_, y_, z_); }
		void Set(const coord &x_, const coord &y_, const coord &z_, bool settozero = true) 
		{
			x = x_; y = y_; z = z_; 
			if (settozero) { for (int i = 3; i < MAX_AXES; ++i) r[i] = 0; }// лучше memset
		}
	};

	struct CoordsBox
	{
		Coords Min;
		Coords Max;
		CoordsBox() : empty(true) { }
		CoordsBox(Coords Min, Coords Max) : empty(true) {
			addCoords(Min); addCoords(Max);
		}
		bool isEmpty() { return empty; }
		void setEmpty() { empty = true; }
		void addCoords(const Coords & pt)
		{
			if (empty)
			{
				Min = pt; Max = pt; empty = false;
			}
			else
			{
				for (int i = 0; i < MAX_AXES; ++i) Min.r[i] = std::min(Min.r[i], pt.r[i]);
				for (int i = 0; i < MAX_AXES; ++i) Max.r[i] = std::max(Max.r[i], pt.r[i]);
			}
		}
	private:
		bool empty;
	};

	//здесь переменные для выполнения команд
	struct RunnerData
	{
		//параметры, нужные для кодов, которые действуют на несколько строк
		int toolid;                       // инструмент
		Coords position;         //"текущая" позиция устройства в миллиметрах
		UnitSystem units;        //текущая система единиц измерения
		bool incremental;        //абсолютная система координат?
		bool ijk_incremental;
		int motion_mode;   //режим перемещения (линейная интерполяция и т.п.)
		Plane plane;             //текущая плоскость интерполяции
		double feed;             //подача в мм/мин
		FeedMode feed_mode;
		double spindlespeed; // обороты шпиндля
		Coords origin;     
		Coords axis_offset;
		int tool_length_offset;  // Tool height offset compensation
		double tool_yoffset;
		double tool_xoffset;
		MoveAccuracy accuracy;
		bool cutter_comp_firstmove;
		CutterCompType cutter_comp_side;
		double cutter_comp_radius;
		Coords program;      
		int coordinate_index ;
		int retract_mode;
		double cycle_r;
		double cycle_q;
		double cycle_p;
		int cycle_l;
		double cycle_cc;
		optdouble cycle_il;
		bool cycle_il_flag;
	
		//CannedCycle cycle;       //текущий цикл
		//CannedLevel cycleLevel;
		//    bool   cycleUseLowLevel; //использовать R вместо стартовой точки
		//    double cycleLowLevel;    //плоскость отвода (задаётся в R)
		//    double cycleHiLevel;     //исходная плоскость задаётся в стартовом Z
		//    double cycleDeepLevel;   //глубина сверления задаётся в Z
		//    double cycleStep;        //глубина одного шага Q
		//    int    cycleWait;        //задержка в цикле P
		RunnerData() :
			toolid(-1), units(UnitSystem_MM), incremental(false), ijk_incremental(true), motion_mode(-1), feed_mode(FeedMode_UnitPerMin), plane(Plane_XY), 
			feed(0), spindlespeed(0),tool_length_offset(0), tool_yoffset(0), tool_xoffset(0), cycle_il_flag(false), cutter_comp_side(CutterCompType_NONE),
			accuracy(AccuracyNormal), cutter_comp_firstmove(true), cutter_comp_radius(0.0), coordinate_index(-1), 
			retract_mode(CannedLevel_NONE),cycle_r(0.0), cycle_q(0.0), cycle_cc (0.0) { }
	};
};

#define RS274NGC_MAX_PARAMETERS 5602
#define TOLERANCE_EQUAL 0.0001 

#define ABS 1
#define ACOS 2
#define ASIN 3
#define ATAN 4
#define COS 5
#define EXP 6
#define FIX 7
#define FUP 8
#define LN 9
#define ROUND 10
#define SIN 11
#define SQRT 12
#define TAN 13
#define EXISTS 14


// binary operations
#define NO_OPERATION 0
#define DIVIDED_BY 1
#define MODULO 2
#define POWER 3
#define TIMES 4
#define AND2 5
#define EXCLUSIVE_OR 6
#define MINUS 7
#define NON_EXCLUSIVE_OR 8
#define PLUS 9
#define RIGHT_BRACKET 10

/* relational operators (are binary operators)*/
#define LT 11
#define EQ 12
#define NE 13
#define LE 14
#define GE 15
#define GT 16
#define RELATIONAL_OP_FIRST 11
#define RELATIONAL_OP_LAST  16

// O code
#define O_none      0
#define O_sub       1
#define O_endsub    2
#define O_call      3
#define O_do        4
#define O_while     5
#define O_if        6
#define O_elseif    7
#define O_else      8
#define O_endif     9
#define O_break    10
#define O_continue 11
#define O_endwhile 12
#define O_return   13
#define O_repeat   14
#define O_endrepeat 15
#define M_98       16
#define M_99       17
#define O_         18


#define G_0      0
#define G_1     10
#define G_2     20
#define G_3     30
#define G_4     40
#define G_5     50
#define G_5_1   51
#define G_5_2   52
#define G_5_3   53
#define G_7     70
#define G_8     80
#define G_10   100
#define G_17   170
#define G_17_1 171
#define G_18   180
#define G_18_1 181
#define G_19   190
#define G_19_1 191
#define G_20   200
#define G_21   210
#define G_28   280
#define G_28_1 281
#define G_30   300
#define G_31   310
#define G_32   320
#define G_30_1 301
#define G_33   330
#define G_33_1 331
#define G_38_2 382
#define G_38_3 383
#define G_38_4 384
#define G_38_5 385
#define G_40   400
#define G_41   410
#define G_41_1 411
#define G_42   420
#define G_42_1 421
#define G_43   430
#define G_43_1 431
#define G_43_2 432
#define G_44   440
#define G_48   480
#define G_49   490
#define G_50   500
#define G_51   510
#define G_52   520
#define G_53   530
#define G_54   540
#define G_55   550
#define G_56   560
#define G_57   570
#define G_58   580
#define G_59   590
#define G_59_1 591
#define G_59_2 592
#define G_59_3 593
#define G_61   610
#define G_61_1 611
#define G_64   640
#define G_73   730
#define G_74   740
#define G_76   760
#define G_80   800
#define G_81   810
#define G_82   820
#define G_83   830
#define G_84   840
#define G_85   850
#define G_86   860
#define G_87   870
#define G_88   880
#define G_89   890
#define G_90   900
#define G_90_1 901
#define G_91   910
#define G_91_1 911
#define G_92   920
#define G_92_1 921
#define G_92_2 922
#define G_92_3 923
#define G_93   930
#define G_94   940
#define G_95   950
#define G_96   960
#define G_97   970
#define G_98   980
#define G_99   990