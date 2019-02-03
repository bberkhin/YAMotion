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
