//#include "wx/wx.h"
#include "domath.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <math.h>

#pragma warning(disable:4996)
#include "configdata.h"



using namespace Interpreter;


DoMathBase::DoMathBase() 
{
	minvalue = -1000000.0;
	maxvalue = 1000000.0;
	in_selected = false;
}


DoMathBase::~DoMathBase()
{
}


void DoMathBase::LoadConfig()
{
	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) == NULL)	
		return;
	wxString strOldPath = config->GetPath();
	config->SetPath("/DoMath");

	minvalue = config->ReadDouble("MinValue", minvalue);
	maxvalue = config->ReadDouble("MaxValue", maxvalue);
	in_selected = config->ReadBool ("InSelected", in_selected);
	do_load_config(config);
	config->SetPath(strOldPath);
}

void DoMathBase::SaveConfig()
{
	ConfigData *config;
	if ((config = dynamic_cast<ConfigData *>(wxConfigBase::Get())) == NULL)
		return;

	wxString strOldPath = config->GetPath();
	config->SetPath("/DoMath");

	config->Write("MinValue", minvalue);
	config->Write("MaxValue", maxvalue);
	config->Write("InSelected", in_selected);
	do_save_config(config);
	config->SetPath(strOldPath);
}


ORIGIN_PARAM *DoMathBase::get_origin(Interpreter::IndexParam index)
{
	//return NULL;
	
	auto it = std::find_if(origin_params.begin(), origin_params.end(), [index](ORIGIN_PARAM &p)
	{ return p.index == index;  });
	return  (it == origin_params.end()) ? NULL : &(*it);
	
}

bool DoMathBase::ScanParameters(const char *line)
{	
	int length = static_cast<int>(strlen(line));
	bool comment = false;
	double val;
	Interpreter::IndexParam index;
	origin_params.clear();
	for (int position = 0; position < length;)
	{
		//skip spaces
		while (line[position] == ' ' || line[position] == '\t' || line[position] == '\r')
		{
			position++;
		}

		if (line[position] == '/' && line[position + 1] == '/')
		{
			break;
		}
		if (line[position] == '(')
		{
			comment = true;
			position++; 
		}
		else if (comment)
		{
			position++;
			if (line[position] == ')')
				comment = false;
		}
		else
		{
			// check letter
			if ((position == 0 || !isalpha(line[position - 1])) && position + 1 < length && !isalpha(line[position + 1]) && is_param_letter(line[position], &index))
			{
				position++; 
				ORIGIN_PARAM param;
				param.posstart = position;
				param.index = index;
				param.status = ORIGIN_PARAM::ParamNonChanged;
				if (read_real(line, position, &val))
				{

					param.val = val;
					param.val_new = val;
					param.posend = position;
					origin_params.push_back(param);					
				}
			}
			else //just move
			{
				position++;
			}
		}
	}
	return !origin_params.empty();
}

bool DoMathBase::Process(const char *strin, char *strout)
{
	if (!ScanParameters(strin))
		return false;
	
	new_params.clear();

	if ( !do_math() )
		return false;

	*strout = 0;
	int outpos = 0, inpos = 0, n = 0;
	memset(strout, 0, MAX_GCODE_LINELEN);


	for (auto it = origin_params.begin(); it != origin_params.end(); ++it)
	{
		if(it->status == ORIGIN_PARAM::ParamChanged)
		{ // copy beforo
			n = it->posstart - inpos;
			strncpy(strout + outpos, strin + inpos, n);
			outpos += n;
			inpos += n;
			//insert new result
			n = it->posend - it->posstart;
			write_result(strout, outpos, it->val_new, is_int_param(it->index));
			inpos += n;
		}
	}

	// write down new param
	for (auto it = new_params.begin(); it != new_params.end(); ++it)
	{
		if (write_param(strout, outpos, it->index))
			write_result(strout, outpos, it->val_new, is_int_param(it->index));
	}

	// write down the end of string
	strcat(strout, strin + inpos);
	return true;
}


bool DoMathBase::read_real(const char *line, int &position, double *pdbl)
{
	const char *start = line + position;
	size_t after;

	after = strspn(start, "+-");
	after = strspn(start + after, "0123456789.") + after;

	//size_t len = after - start;
	std::string st(start, after);
	std::stringstream s(st);
	double val;
	if (!(s >> val))
		return false;

	if (s.get() != std::char_traits<char>::eof())
		return false;

	*pdbl = val;
	position = static_cast<int>(start + after - line);
	return true;
}

bool DoMathBase::is_int_param(Interpreter::IndexParam index)
{
	switch (index)
	{
	case PARAM_T:
	case PARAM_H:
	case PARAM_L:
	case PARAM_N:
		return true;
	}
	return false;
}

bool DoMathBase::is_param_letter(char c, IndexParam *index )
{
	if ((64 < c) && (c < 91))   /* downcase upper case letters */
		c += 32;
	switch (c)
	{
		case 'a':	*index = PARAM_A; break;
		case 'b':	*index = PARAM_B; break;
		case 'c':	*index = PARAM_C; break;
		case 'x':	*index = PARAM_X; break;
		case 'y':	*index = PARAM_Y; break;
		case 'z':	*index = PARAM_Z; break;
		case '@':	*index = PARAM_AT; break;
		case 'd':   *index = PARAM_D; break;
		case 'e':   *index = PARAM_E; break;
		case 'f':   *index = PARAM_F; break;
		case 'i':   *index = PARAM_I; break;
		case 'j':   *index = PARAM_J; break;
		case 'k':   *index = PARAM_K; break;
		case 'p':   *index = PARAM_P; break;
		case 'q':   *index = PARAM_Q; break;
		case 'r':   *index = PARAM_R; break;
		case 's':   *index = PARAM_S; break;
		case 'u':   *index = PARAM_U; break;
		case 'v':   *index = PARAM_V; break;
		case 'w':   *index = PARAM_W; break;
		case 't':   *index = PARAM_T; break;
		case 'h':   *index = PARAM_H; break;
		case 'l':   *index = PARAM_L; break;
		case 'n':   *index = PARAM_N; break;
		default:
			return false;
	}
	return true;
}

void DoMathBase::SetAddParam(ORIGIN_PARAM *p, Interpreter::IndexParam param, const double &newval)
{
	if (p)
	{
		p->val_new = newval;
		p->status = ORIGIN_PARAM::ParamChanged;
	}
	else // we need add x coordinate
	{
		AddNewParam(param, newval);
	}
}

bool DoMathBase::AddNewParam(Interpreter::IndexParam index, const double &val)
{
	
	ORIGIN_PARAM param;
	param.posstart = -1;
	param.index = index;
	param.status = ORIGIN_PARAM::ParamNew;
	param.val = val;
	param.val_new = val;
	new_params.push_back(param);

	return true;
}

bool DoMathBase::write_param(char *strout, int &outpos, int index)
{
	std::string st;
	if (index == PARAM_X)
		st = " X";
	else if (index == PARAM_Y)
		st = " Y";
	else if (index == PARAM_Z)
		st = " Z";

	if ( st.empty())
		return false;
	
	strcpy(strout + outpos, st.c_str());
	outpos = static_cast<int>(outpos + st.length());
	return true;
}


void DoMathBase::write_result(char *strout, int &outpos, double val, bool isint)
{
	//size_t len = after - start;
	std::string st;
	std::stringstream s(st);
	if (isint)
	{
		if (!(s << static_cast<int>(val)))
			return;
	}
	else
	{
		if (!(s << val))
			return;
	}
	strcpy(strout + outpos, s.str().c_str());
	outpos = static_cast<int>(outpos + s.str().length() );	
}



DoMathSimple::DoMathSimple() : DoMathBase()
{
	LoadConfig();
}
DoMathSimple::~DoMathSimple()
{

}

bool DoMathSimple::HasParemeter(Interpreter::IndexParam index)
{
	return (std::find(params.begin(), params.end(), index) != params.end());
}

bool DoMathSimple::do_math()
{
	double result;
	double val;
	bool did = false;

	for (auto it = params.begin(); it != params.end(); ++it)
	{
		ORIGIN_PARAM *p = get_origin(*it);
		if (p)
		{
			val = p->val;
			switch (operation)
			{
			case MOT_PLUS:      result = operand + val; break;
			case MOT_MINUS:     result = val - operand; break;
			case MOT_DIVIDE:	result = operand == 0.0 ? val : (val / operand); break;
			case MOT_MULTIPLY:  result = val * operand; break;
			case MOT_ASSIGN:  result = operand; break;
			}
			result = std::max(result, minvalue);
			result = std::min(result, maxvalue);
			p->val_new = result;
			p->status = ORIGIN_PARAM::ParamChanged;
			did = true;
		}
	}
	return did;
}

void DoMathSimple::ClearParams()
{
	params.clear();
}

void DoMathSimple::AddParam(Interpreter::IndexParam param)
{
	params.push_back(param);
}

void DoMathSimple::do_load_config(ConfigData *config)
{
	params.clear();
	wxString strKey;
	wxString strval;
	long dummy;
	long val;

	operation = static_cast<MathOperationType>(config->Read("Operation", static_cast<long>(operation)));
	operand = config->ReadDouble("Operand", operand);

	config->SetPath("/DoMath/Params");
	bool bCont = config->GetFirstEntry(strKey, dummy);
	while (bCont)
	{
		if (config->Read(strKey, &strval))
		{
			strval.ToLong(&val);
			params.push_back(static_cast<IndexParam>(val));
			bCont = config->GetNextEntry(strKey, dummy);
		}
	}
}

void DoMathSimple::do_save_config(ConfigData *config)
{
	config->Write("Operation", static_cast<long>(operation));
	config->Write("Operand", operand);

	config->DeleteGroup("/DoMath/Params");
	config->SetPath("/DoMath/Params");

	int n = 1;
	std::for_each(params.begin(), params.end(), [config, &n](IndexParam &p)
	{ config->Write(wxString::Format("Param%d", n), static_cast<int>(p));  ++n; });
}



static mu::value_type* AddVariable(const mu::char_type *a_szName, void *pUserData)
{
	DoMathExpression *pFactory = (DoMathExpression*)pUserData;
	return pFactory->create_new_variable(a_szName);
}

DoMathExpression::DoMathExpression()
{
	LoadConfig();
	parser.SetVarFactory(&AddVariable, this);
}

DoMathExpression::~DoMathExpression()
{
}

bool DoMathExpression::HasParemeter(Interpreter::IndexParam index, std::wstring &expr)
{
	auto it = params.find(index);
	if (it != params.end())
		expr = it->second;
	return (it != params.end());
}



double *DoMathExpression::create_new_variable( const wchar_t *a_szName )
{
	Interpreter::IndexParam index;
	if (wcslen(a_szName) != 1 || !is_param_letter(char(a_szName[0]), &index))
	{
		throw mu::ParserError(L"Unknown variable.");
	}
	ORIGIN_PARAM *p = get_origin(index);
	if (!p)
	{
		// check this in saved param
		
		if (saved_val.find(index) != saved_val.end())
		{
			return &(saved_val[index]);
		}
		else
		{
			mu::string_type str(a_szName);
			str += L"does not exist in the input string";
			throw mu::ParserError(str);
		}
		
	}
	return &(p->val);
}

bool DoMathExpression::do_math()
{
	double result;
	bool did = false;
	// saved all param 

	SavedParam *sav = &saved_val;
	std::for_each(origin_params.begin(), origin_params.end(), [sav](ORIGIN_PARAM &p)
	{ (*sav)[p.index] = p.val; });


	for (auto it = params.begin(); it != params.end(); ++it)
	{
		ORIGIN_PARAM *p = get_origin((*it).first);
		if (p)
		{
			parser.SetExpr(it->second);
			result = parser.Eval();
			result = std::max(result, minvalue);
			result = std::min(result, maxvalue);
			p->val_new = result;
			(*sav)[p->index] = result;
			p->status = ORIGIN_PARAM::ParamChanged;
			did = true;
		}
	}	
	return did;
}


void DoMathExpression::ClearParams()
{
	params.clear();
}

void DoMathExpression::AddParam(Interpreter::IndexParam param,const wchar_t *s)
{
	params.insert(std::make_pair(param, std::wstring(s)));
}

void DoMathExpression::do_load_config(ConfigData *config)
{
	params.clear();
	wxString strKey;
	wxString strval;
	long dummy;
	long val;

	config->SetPath("/DoMath/EpressionParams");
	bool bCont = config->GetFirstEntry(strKey, dummy);
	while (bCont)
	{
		if (config->Read(strKey, &strval))
		{
			strKey.ToLong(&val);
			params.insert(std::make_pair(static_cast<IndexParam>(val), std::wstring(strval.wc_str())));
			bCont = config->GetNextEntry(strKey, dummy);
		}
	}
}


void DoMathExpression::do_save_config(ConfigData *config)
{
	config->DeleteGroup("/DoMath/EpressionParams");
	config->SetPath("/DoMath/EpressionParams");

	std::for_each(params.begin(), params.end(), [config](auto &p)
	{ config->Write(wxString::Format("%d", p.first), p.second.c_str() );  });
}


DoMathRotate::DoMathRotate() :
	m_plane(Plane_XY), m_angle_rad(0), m_angle_degree(0)
{
	LoadConfig();
}


DoMathRotate::~DoMathRotate()
{

}

void DoMathRotate::SetAngle(const double &angle, bool degree)
{
	if (degree)
	{
		m_angle_degree = angle;
		m_angle_rad = m_angle_degree * PI / 180.0;
	}
	else
	{
		m_angle_rad = angle;
		m_angle_degree = m_angle_rad * 180.0/PI;
	}
}

void DoMathRotate::do_load_config(ConfigData *config)
{
	double angle = config->ReadDouble("Angle", m_angle_degree);
	SetAngle(angle, true);
	m_plane = static_cast<Interpreter::Plane>( config->ReadLong("Plane", static_cast<long>(m_plane)));

	m_center.x = config->ReadDouble("RotateX", m_center.x);
	m_center.y = config->ReadDouble("RotateY", m_center.y);
	m_center.z = config->ReadDouble("RotateZ", m_center.z);
	

	//SetAngle(0, true);
}

void DoMathRotate::do_save_config(ConfigData *config)
{
	config->Write("Angle", m_angle_degree);
	config->Write("Plane", static_cast<int>(m_plane));
	config->Write("RotateX", m_center.x);
	config->Write("RotateY", m_center.y);
	config->Write("RotateZ", m_center.z);
}

static void DoRound(double &val)
{
	val = round(val * 1000) / 1000.;
}
const Interpreter::Coords DoMathRotate::rotate_point(const Interpreter::Coords &src) const
{
	Interpreter::Coords out;
	if (m_plane == Plane_XY)
	{
		out.x = m_center.x + (src.x - m_center.x) * cos(m_angle_rad) + (m_center.y - src.y) * sin(m_angle_rad);
		//p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
		out.y = m_center.y + (src.x - m_center.x) * sin(m_angle_rad) + (src.y - m_center.y) * cos(m_angle_rad);
	}
	else if (m_plane == Plane_XZ)
	{
		out.x = m_center.x + (src.x - m_center.x) * cos(m_angle_rad) + (m_center.z - src.z) * sin(m_angle_rad);
		//p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
		out.z = m_center.z + (src.x - m_center.x) * sin(m_angle_rad) + (src.z - m_center.z) * cos(m_angle_rad);
	}
	else if (m_plane == Plane_YZ)
	{
		out.z = m_center.z + (src.z - m_center.z) * cos(m_angle_rad) + (m_center.y - src.y) * sin(m_angle_rad);
		//p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
		out.y = m_center.y + (src.z - m_center.z) * sin(m_angle_rad) + (src.y - m_center.y) * cos(m_angle_rad);
	}
	else
	{
		// error!
		wxASSERT_MSG(false,"UNKNOWN PLAN");
	}


	DoRound(out.x);
	DoRound(out.y);
	DoRound(out.z);

	return out;

}



bool DoMathRotate::do_math()
{
	ORIGIN_PARAM *px = get_origin(PARAM_X);
	ORIGIN_PARAM *py = get_origin(PARAM_Y);
	ORIGIN_PARAM *pz = get_origin(PARAM_Z);
	if (px == 0 && py == 0 && pz == 0)
		return false;

	ORIGIN_PARAM *pi = get_origin(PARAM_I);
	ORIGIN_PARAM *pj = get_origin(PARAM_J);
	ORIGIN_PARAM *pk = get_origin(PARAM_K);
	if (pi != 0 || pj != 0 || pk != 0)
	{
		Interpreter::Coords arcCenter = m_curposold;
		if ((m_plane == Plane_XY || m_plane == Plane_XZ) && pi )
			arcCenter.x += pi->val;
		if ((m_plane == Plane_XY || m_plane == Plane_YZ) && pj)
			arcCenter.y += pj->val;
		if ((m_plane == Plane_XZ || m_plane == Plane_YZ) && pk)
			arcCenter.z += pk->val;

		Interpreter::Coords arcnewCenter = rotate_point(arcCenter);
		double newi = arcnewCenter.x - m_curposnew.x;
		double newj = arcnewCenter.y - m_curposnew.y;
		double newk = arcnewCenter.z - m_curposnew.z;
		if (m_plane == Plane_XY || m_plane == Plane_XZ)
			SetAddParam(pi, PARAM_I, newi);
		if (m_plane == Plane_XY || m_plane == Plane_YZ)
			SetAddParam(pj, PARAM_J, newj);
		if (m_plane == Plane_XZ || m_plane == Plane_YZ)
			SetAddParam(pk, PARAM_K, newk);
	}
	
	if (px)
		m_curposold.x = px->val;
	if (py)
		m_curposold.y = py->val;
	if (pz)
		m_curposold.z = pz->val;

	// do rotation
	m_curposnew = rotate_point(m_curposold);
	if (m_plane == Plane_XY || m_plane == Plane_XZ)
		SetAddParam(px, PARAM_X, m_curposnew.x);
	if (m_plane == Plane_XY || m_plane == Plane_YZ)
		SetAddParam(py, PARAM_Y, m_curposnew.y);
	if (m_plane == Plane_XZ || m_plane == Plane_YZ)
		SetAddParam(pz, PARAM_Z, m_curposnew.y);
	return true;
}
