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
