#ifndef ENVIRONMENTSIMPLE_H
#define ENVIRONMENTSIMPLE_H
#include "ienvironment.h"
#include <map>
#include <vector>

typedef std::map<int,double> varsmap;

class EnvironmentSimple : public IEnvironment
{
public:
    EnvironmentSimple();
    Coords GetG54G58 ( int index  );
	void SetG54G58(int index, Coords &pos);
	void SetVariable(int index, double value);
	double GetVariable(int index);
	ToolDesc& getToolById(int id);
private:
	varsmap vars;
	std::vector<ToolDesc> tools;
	
};

#endif // ENVIRONMENTSIMPLE_H
