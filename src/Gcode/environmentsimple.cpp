#include "environmentsimple.h"

EnvironmentSimple::EnvironmentSimple()
{
	// add tools
	ToolDesc t;
	t.diameter = 6;
	tools.push_back(t);
}

EnvironmentSimple::~EnvironmentSimple()
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


ToolDesc& EnvironmentSimple::getToolById(int id )
{
	return tools.front();
}

double EnvironmentSimple::GetCenterArcRadiusTolerance()
{
	return CENTER_ARC_RADIUS_TOLERANCE_MM;
}

double EnvironmentSimple::GetDefaultFeedRate()
{
	return DEFAULT_FEED_RATE;
}
double EnvironmentSimple::GetDefaultMoveSpeed()
{
	//return DEFAULT_MOVE_SPEED;
	return DEFAULT_FEED_RATE*2;
}

