#include "Controller.hpp"
#include "Dictionary.hpp"
#include <exception>
#include <iostream>

void ShowUsage()
{
	std::cerr << "Usage: dictionary.exe <filename>" << std::endl;
}

const int ARGS_COUNT = 1;

int main(int argc, char* argv[])
{
	if (argc < ARGS_COUNT + 1)
	{
		std::cerr << "Not enough arguments" << std::endl;
		ShowUsage();
		return 1;
	}

	try
	{
		SetCodePage(1251);
		CDictionary dict;
		CController control(dict, argv[1]);
		control.HandleCommands();
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return 1;
	}
}
