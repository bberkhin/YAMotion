#ifndef ENVIRONMENTSIMPLE_H
#define ENVIRONMENTSIMPLE_H
#include "..\Gcode\ienvironment.h"

class EnvironmentSimple : public IEnvironment
{
public:
    EnvironmentSimple();
    Coords GetG54G58 ( int index  );
};

#endif // ENVIRONMENTSIMPLE_H
