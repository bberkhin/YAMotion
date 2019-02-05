#pragma once
#include "gcodedefs.h"
#include <optional>
#include <vector>

class IEnvironment;

namespace Interpreter
{

	
	union ParamType
	{
		double dval;
		int ival;
	};

	typedef std::optional<ParamType> optparam;
	typedef  std::vector<int> m_container;
	typedef  std::vector<int> g_container;
	

	class  CmdParser
	{
	public:
		CmdParser(IEnvironment *env_ = 0);
		bool parse(const char *frame); //читает коды и значения параметров
		bool contain_cmd(ModalGroup group) const;
		bool contain_m( int val ) const;
		bool contain_g( int val)  const;
		bool getRParam(IndexParam param, double *pr) const;
		bool getIParam(IndexParam param, int *pi) const;
		const m_container &getMCodes() const { return mcodes; }
		const g_container &getGCodes() const { return gcodes; }
		InterError get_state() const;		
		bool neead_execute()  const;
		std::string getSubName() const { return o_name; }
		
		// helpers
		bool real_to_int(double *pdbl, int *pint) const;

	private:
		bool init();
		bool parse_codes(const char *frame);
		bool parse_code(); //следующий код
		bool check_modal_group() const;
		ModalGroup get_gmodal_group(int n) const;
		ModalGroup get_mmodal_group(int n) const;
		void find_significal_symbol(); //пропускает комментарии, пробелы
		bool read_n_number();
		bool read_dollars();
		bool read_semicolon();
		bool read_subrotinue();
		bool read_m(); 
		bool read_g();
		bool read_real_param(IndexParam param);
		bool read_int_param(IndexParam param);
		bool read_int_value(int *pint);
		bool read_real_value(double *pdbl);
		bool read_integer(int *pint);
		bool read_real(double *pdbl);
		bool read_comment_eol();
		bool acsept_gcode(int num) const;

// Macro B fsupport
		bool read_set_param();
		bool read_parameter(double *pdbl, bool check_exists);
		bool isreadonly_param(int num) const;
		bool read_real_expression(double *pdbl);
		bool read_unary(double *pdbl);
		int precedence(int an_operator);
		bool read_operation(int *operation);
		bool read_atan(double *pdbl);
		bool execute_unary(double *double_ptr, int operation);
		bool read_bracketed_parameter(double *double_ptr, bool check_exists);
		bool read_operation_unary(int *operation);
		bool execute_binary(double *left, int operation, double *right);
		bool execute_binary1(double *left, int operation, double *right);
		bool execute_binary2(double *left, int operation, double *right);
		
	
	private:		
		m_container mcodes;
		g_container gcodes;
		optparam params[PARAM_MAX];
		int n_number; // N - value
		std::string comment;
		std::string o_name;
		int o_type;
		
		const char *line;
		int position;
		mutable InterError  state;
		IEnvironment *env;
		

	};

};