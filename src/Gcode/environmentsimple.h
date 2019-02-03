#ifndef ENVIRONMENTSIMPLE_H
#define ENVIRONMENTSIMPLE_H
#include "ienvironment.h"
#include <map>

typedef std::map<int,double> varsmap;

class EnvironmentSimple : public IEnvironment
{
public:
    EnvironmentSimple();
    Coords GetG54G58 ( int index  );
	void SetVariable(int index, double &value);
	double GetVariable(int index);
private:
	varsmap vars;
	
};

#endif // ENVIRONMENTSIMPLE_H
