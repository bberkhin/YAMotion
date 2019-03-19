#pragma once
#include <vector>
#include "gcodedefs.h"


typedef std::vector<Interpreter::IndexParam>  ParamList;
enum MathOperationType
{
	MOT_PLUS,
	MOT_MINUS,
	MOT_MULTIPLY,
	MOT_DIVIDE
};


class DoMath
{
public:
	DoMath();
	~DoMath();
	void AddParam(Interpreter::IndexParam param);
	void SetOperation(MathOperationType op) { operation = op; }
	void SetOperand(double val) { operand = val; }
	void SetMinMax(double minv, double maxv) { minvalue = minv; maxvalue = maxv; }
	double GetOperand() { return operand;  }
	MathOperationType GetOperation() { return operation; }
	void GetMinMax(double *pminv, double *pmaxv) { *pminv = minvalue; *pmaxv = maxvalue; }
	void ClearParams();
	bool HasParemeter(Interpreter::IndexParam p);

	bool Process(const char *strin, char *strout);
	void LoadConfig();
	void SaveConfig();
private:
	bool read_real(const char *line, int &position, double *pdbl);
	bool is_param_letter(char c, bool *isint);
	double do_math(double val);
	void write_result(char *strout, int &outpos, double valnew, bool isint);
private:
	ParamList  params;
	MathOperationType operation;
	double operand;
	double minvalue;
	double maxvalue;
};

