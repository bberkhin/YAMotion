#ifndef IENVIRONMENT_H
#define IENVIRONMENT_H
#include "iexecutor.h"

// ����� ��������� �������
class IEnvironment
{
 public:
     virtual Coords GetG54G58 ( int index  ) = 0; // ���������� ���������������� ������� ���������
};

#endif // IENVIRONMENT_H
