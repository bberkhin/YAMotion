#ifndef IENVIRONMENT_H
#define IENVIRONMENT_H
#include "iexecutor.h"


struct ToolDesc
{
	double diameter;
};

// Общие настройки системы
class IEnvironment
{
 public:
	 IEnvironment() { }
	 virtual ~IEnvironment() { }
     virtual Coords GetG54G58 ( int index  ) = 0; // возвращает пользовательскую систему координат
	 virtual void SetG54G58(int index, Coords &pos ) = 0;
	 virtual void SetVariable(int index, double value) = 0;
	 virtual double GetVariable(int index ) = 0;
	 virtual ToolDesc& getToolById(int id) = 0;
	 virtual double GetCenterArcRadiusTolerance() = 0;
	 virtual double GetDefaultFeedRate() = 0;
	 virtual double GetDefaultMoveSpeed() = 0;
};

#endif // IENVIRONMENT_H
