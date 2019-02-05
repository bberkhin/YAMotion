#ifndef IENVIRONMENT_H
#define IENVIRONMENT_H
#include "iexecutor.h"

// ����� ��������� �������
class IEnvironment
{
 public:
     virtual Coords GetG54G58 ( int index  ) = 0; // ���������� ���������������� ������� ���������
	 virtual void SetG54G58(int index, Coords &pos, bool incremental) = 0;
	 virtual void SetVariable(int index, double &value) = 0;
	 virtual double GetVariable(int index ) = 0;
};

#endif // IENVIRONMENT_H
