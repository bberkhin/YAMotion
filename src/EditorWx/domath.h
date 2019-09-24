#pragma once
#include <vector>
#include <map>
#include <memory>
#include "gcodedefs.h"
#include <tchar.h>
#include <muParser.h>


struct ORIGIN_PARAM
{
	enum { ParamNonChanged = 0, ParamChanged, ParamNew };
	Interpreter::IndexParam index;
	double val;
	double val_new;
	int posstart;
	int posend;
	int status;
};

typedef std::vector<ORIGIN_PARAM>  OriginParamList;


class ConfigData;

class DoMathBase
{
public:
	DoMathBase();
	virtual ~DoMathBase();
	void SetMinMax(double minv, double maxv) { minvalue = minv; maxvalue = maxv; }
	void GetMinMax(double *pminv, double *pmaxv) { *pminv = minvalue; *pmaxv = maxvalue; }	
	bool InSelected() { return in_selected;  }
	void SetSelected(bool insel) { in_selected = insel; }
	bool Process(const char *strin, char *strout);
	void LoadConfig();
	void SaveConfig();
protected:
	virtual void do_load_config(ConfigData *config) = 0;
	virtual void do_save_config(ConfigData *config) = 0;
	virtual bool do_math() = 0;
	ORIGIN_PARAM *get_origin(Interpreter::IndexParam index);
protected:
	bool read_real(const char *line, int &position, double *pdbl);
	bool is_param_letter(char c, Interpreter::IndexParam *index );
	bool is_int_param(Interpreter::IndexParam index);
	void write_result(char *strout, int &outpos, double valnew, bool isint);
	bool write_param(char *strout, int &outpos, int index);
	bool AddNewParam(Interpreter::IndexParam index, const double &val);
	void SetAddParam(ORIGIN_PARAM *p, Interpreter::IndexParam param, const double &newval);
	bool ScanParameters(const char *line);
protected:
	double minvalue;
	double maxvalue;
	bool in_selected;
	OriginParamList origin_params;
	OriginParamList new_params;
};



typedef std::vector<Interpreter::IndexParam>  ParamList;
enum MathOperationType
{
	MOT_PLUS,
	MOT_MINUS,
	MOT_MULTIPLY,
	MOT_DIVIDE,
	MOT_ASSIGN
};

class DoMathSimple : public DoMathBase
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


typedef std::map<Interpreter::IndexParam,std::wstring>  ParamExpressionList;
typedef std::map<Interpreter::IndexParam, double>  SavedParam;


class DoMathExpression : public DoMathBase
{
public:
	DoMathExpression();
	~DoMathExpression();
	void ClearParams();
	void AddParam(Interpreter::IndexParam param,const  wchar_t *s);
	bool HasParemeter(Interpreter::IndexParam p, std::wstring &str_expr);
	double *create_new_variable(const wchar_t *a_szName);

protected:
	virtual void do_load_config(ConfigData *config);
	virtual void do_save_config(ConfigData *config);
	virtual bool do_math();
private:
	ParamExpressionList  params;
	SavedParam saved_val;
	mu::Parser  parser;

};


class DoMathRotate : public DoMathBase
{
public:
	DoMathRotate();
	~DoMathRotate();
	const double &GetAngle()  const { return m_angle; }
	void SetAngle(const double &angle, bool degree = true);
	void SetPlane(Interpreter::Plane plane) { m_plane = plane; }
	Interpreter::Plane GetPlane()  const { return m_plane; }
	const Interpreter::Coords &GetCenter() const { return  m_center; }
	void SetCenter(const Interpreter::Coords &center) { m_center = center; }

protected:
	virtual void do_load_config(ConfigData *config);
	virtual void do_save_config(ConfigData *config);
	virtual bool do_math();
	const Interpreter::Coords rotate_point(const Interpreter::Coords &src) const;
	double m_angle;
	Interpreter::Plane m_plane;
	Interpreter::Coords m_center;
	Interpreter::Coords m_curposnew;
	Interpreter::Coords m_curposold;
};
