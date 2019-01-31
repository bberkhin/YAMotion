#ifndef IENVIRONMENT_H
#define IENVIRONMENT_H
#include "iexecutor.h"

// Общие настройки системы
class IEnvironment
{
 public:
     virtual Coords GetG54G58 ( int index  ) = 0; // возвращает пользовательскую систему координат
};

#endif // IENVIRONMENT_H
