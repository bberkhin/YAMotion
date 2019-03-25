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

class ConfigData;

class DoMathBase
{
public:
	DoMathBase();
	virtual ~DoMathBase();
	void SetMinMax(double minv, double maxv) { minvalue = minv; maxvalue = maxv; }
	void GetMinMax(double *pminv, double *pmaxv) { *pminv = minvalue; *pmaxv = maxvalue; }	
	bool Process(const char *strin, char *strout);
	void LoadConfig();
	void SaveConfig();
protected:
	virtual void do_load_config(ConfigData *config) = 0;
	virtual void do_save_config(ConfigData *config) = 0;
	virtual bool do_math() = 0;
private:
	bool read_real(const char *line, int &position, double *pdbl);
	bool is_param_letter(char c, Interpreter::IndexParam *index, bool *isint);
	void write_result(char *strout, int &outpos, double valnew, bool isint);
	bool ScanParameters(const char *line);
protected:
	double minvalue;
	double maxvalue;
};


class DoMathSimple
{
public:
	DoMathSimple();
	~DoMathSimple();
	void AddParam(Interpreter::IndexParam param);
	void SetOperation(MathOperationType op) { operation = op; }
	void SetOperand(double val) { operand = val; }
	double GetOperand() { return operand;  }
	MathOperationType GetOperation() { return operation; }	
	void ClearParams();
	bool HasParemeter(Interpreter::IndexParam p);

protected:
	virtual void do_load_config(ConfigData *config);
	virtual void do_save_config(ConfigData *config);
	virtual bool do_math();
private:
	ParamList  params;
	MathOperationType operation;
	double operand;
};

