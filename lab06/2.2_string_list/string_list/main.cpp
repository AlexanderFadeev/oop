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
		std::cerr << "Exception: " << e.what();
	}
	catch (...)
	{
		std::cerr << "Unknown exception";
	}
}