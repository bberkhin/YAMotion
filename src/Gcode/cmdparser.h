#pragma once

//#define IF_F_RET_F(A) A
//#define IF_F_RET_F(A)       \
//	do {                    \
//	  if( !A )										\
//		return false;          \                     
//    } while(0)

#define IF_F_RET_F(fun)                             \
    do {                                                   \
        if( !fun )            \
			return false;                                      \
    } while(0)


#define RET_F_SETSTATE(error, fmt, ...)                             \
    do {                                                   \
        make_error_state(error, fmt, ## __VA_ARGS__);            \
        return false;                                      \
    } while(0)

#define IF_F_RET_F_SETSTATE(fun, error, fmt, ...)                             \
    do {                                                   \
		if( !fun )                                     \
		{ make_error_state(error, fmt, ## __VA_ARGS__);            \
		  return false; }                                   \
    } while(0)


namespace Interpreter
{

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
		PARAM_L,
		PARAM_H,
		PARAM_T,
		PARAM_MAX
	};



	union ParamType
	{
		double dval;
		int ival;
	};
	
	typedef std::optional<ParamType> optparam;


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
			MUITYPLIE_PARAM,
			NO_VALUE,
		};

		Code code;
		std::string description;
		InterError() :code(ALL_OK) { }
		InterError(Code code, std::string description) : code(code), description(description) {}
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
		CmdParser();
		bool parse(const char *frame); //читает коды и значения параметров
		bool contain_cmd(ModalGroup group) const;
		bool contain_cmd(char letter, int ival) const;
		InterError get_state() const;
		bool getRParam(IndexParam param, double *pr) const;
		bool getIParam(IndexParam param, int *pi) const;
	private:
		bool init();
		bool parse_codes(const char *frame);
		bool parse_code(); //следующий код

		void find_significal_symbol(); //пропускает комментарии, пробелы
		ModalGroup get_modal_group(const GKey &key) const;
		bool check_modal_group() const;

		bool read_n_number();
		bool read_set_param();
		bool read_dollars();
		bool read_semicolon();
		bool read_atsign();
		bool read_m(); 
		bool read_g();
		bool read_real_param(IndexParam param);
		bool read_int_param(IndexParam param);
		bool read_int_value(int *pint);
		bool read_real_value(double *pdbl);
		bool read_integer(int *pint);
		bool read_real(double *pdbl);

		void make_error_state(InterError::Code cod, const char *fmt, ...);

	
	private:
		const char *line;
		int position;
		mutable InterError  state;
		optparam params[PARAM_MAX];
		int n_number; // N - value
		std::string comment;
		

	};

};