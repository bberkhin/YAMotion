#include "environmentsimple.h"

EnvironmentSimple::EnvironmentSimple()
{

}


Coords EnvironmentSimple::GetG54G58 ( int origin)
{ //origin [1;9]
	Coords cs;
	for (int i = 0; i < MAX_AXES; ++i)
	{
		cs.r[i] = GetVariable(5201 + i + (origin * 20));
	}
	return cs;
}

void EnvironmentSimple::SetG54G58(int origin, Coords &cs)
{ //origin [1;9]
	for (int i = 0; i < MAX_AXES; ++i)
	{
		SetVariable(5201 + i + (origin * 20), cs.r[i] );
	}
}


void EnvironmentSimple::SetVariable(int index, double value)
{
	vars[index] = value;
}

double EnvironmentSimple::GetVariable(int index)
{
	auto iter = vars.find(index);
	if (iter == vars.end())
		return 0;
	else
		return iter->second;
}
