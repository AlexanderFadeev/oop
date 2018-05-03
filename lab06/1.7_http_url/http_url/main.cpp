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
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}
}