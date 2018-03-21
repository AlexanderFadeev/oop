#include "Dictionary.hpp"
#include <exception>
#include <iostream>

int main()
{
	try
	{
		// TODO
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
