#pragma once
#include <string>


#define MAX_GCODE_LINELEN 512


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
		if( !fun )                                     \
		{ state = InterError::CreateErrorCode(error, fmt, ## __VA_ARGS__);            \
		  return false; }                                   \
    } while(0)



namespace Interpreter
{

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
		//int value
		PARAM_L,
		PARAM_H,
		PARAM_T,
		PARAM_MAX
	};


	enum ModalGroup //некоторые операторы не могут одновременно содержаться в одном фрейме
	{
		ModalGroup_NONE = 0, //g4,g10,g28,g30,g53,g92.[0-3]
		ModalGroup_MOVE,  //g0..g3 //G38.2, G81..G89
		ModalGroup_STOPMOVE, // G80
		ModalGroup_INCREMENTAL, //g90..g91
		ModalGroup_UNITS, //g20..g21
		//ModalGroup_CYCLE, //g80..g85
		ModalGroup_COORD_SYSTEM, //g54..g58
		ModalGroup_TOOL_LENGTH_CORRECTION, //g43,g44,g49
		ModalGroup_TOOL_RADIUS_CORRECTION, //g40..g42
		ModalGroup_CYCLE_RETURN, //g98, g99
		ModalGroup_ACTIVE_PLANE, //g17..g19
		ModalGroup_STOP, //M0, M1, M2, M30, M60
		ModalGroup_ACCURACY, // aqccuracy 	//G61, G64
		ModalGroup_TURN_TOOL, //M3, M4, M5 
		ModalGroup_GREASER, //M7, M8, M9
		ModalGroup_FEEDMODE,  // g93, g94, g95
		ModalGroup_SPINDLEMODE  //G96 G97 spindle
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