// ConsoleTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "environmentsimple.h"
#include "logconsole.h"
#include "GCodeInterpreter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
namespace fs = std::filesystem;



using namespace Interpreter;

int main(int argc, char *argv[] )
{
    
	ExecutorLog exec;
	EnvironmentSimple env;
	LoggerConsole logger;
	GCodeInterpreter ipret(&env, &exec, &logger);
	if (argc == 2)
	{
		exec.setneedprint(true);
		std::string str(argv[1]);
		std::wstring csFile(str.begin(), str.end());
		ipret.open_nc_file( csFile.c_str() );
		ipret.execute_file();
	}
	else
	{
		//setup converter//setup converter
		exec.setneedprint(false);
		std::wstring path;
		for (const auto & entry : fs::directory_iterator(path))
		{
			std::cout << "Start file: " << entry.path() << "\n";		
			std::wstring csFile = entry.path().wstring();			
			ipret.open_nc_file( csFile.c_str() );
			ipret.execute_file();
			std::cout << "End file: " << entry.path() << "\n" << "\n";
			getchar();
		}
			

	}
	getchar();
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
