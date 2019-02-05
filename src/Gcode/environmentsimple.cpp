#include "environmentsimple.h"

EnvironmentSimple::EnvironmentSimple()
{

}

Coords EnvironmentSimple::GetG54G58 ( int i  )
{
    if ( i == 0 )
        return Coords(70,70,70);
    else if ( i == 1 )
        return Coords(73,73,73);
    else
        return Coords(0,0,0);

}

void EnvironmentSimple::SetG54G58(int index, Coords &pos, bool incremental)
{
	SetVariable(index + 5000, pos.x);//
}


void EnvironmentSimple::SetVariable(int index, double &value)
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
