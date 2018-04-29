#include "ExpandTemplate.hpp"
#include <exception>
#include <iostream>

Mapping GetMapping(char* params[], size_t paramsCount)
{
	Mapping result;
	for (size_t index = 0; index < paramsCount; index += 2)
	{
		result.insert({ params[index], params[index + 1] });
	}

	return result;
}

void ExpandTemplate(std::string inputFilename, std::string outputFilename, char* params[], size_t paramsCount)
{
	auto mapping = GetMapping(params, paramsCount);
	ExpandTemplate(inputFilename, outputFilename, mapping);
}

void ShowUsage()
{
	std::cerr << "Usage: expand_template.exe <input file> <output file> (<param> <value>)*" << std::endl;
}

const int MIN_ARGS_COUNT = 2;

int main(int argc, char* argv[])
{
	try
	{
		if ((argc < MIN_ARGS_COUNT + 1) || !(argc % 2))
		{
			std::cerr << argc << std::endl;
			throw std::invalid_argument("Wrong number of arguments");
		}
		
		ExpandTemplate(argv[1], argv[2], argv + 3, argc - MIN_ARGS_COUNT - 1);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		ShowUsage();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		ShowUsage();
		return 1;
	}
}
