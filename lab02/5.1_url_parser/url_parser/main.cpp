#include "URLParser.hpp"
#include <iostream>

template <typename T>
T Read(std::istream& input)
{
	T value;
	if (!(input >> value))
	{
		throw std::runtime_error("Read failed");
	}
	return value;
}

void PrintURLInfo(std::ostream& output, const std::string& url, const URLInfo& info)
{
	output << url << '\n'
		   << "HOST: " << info.host << '\n'
		   << "PORT: " << info.port << '\n'
		   << "DOC: " << info.document << std::endl;

	if (!output)
	{
		throw std::runtime_error("Write failed");
	}
}

void ParseURL(std::istream& input, std::ostream& output)
{
	auto url = Read<std::string>(input);

	URLInfo info;
	if (!ParseURL(url, info))
	{
		throw std::runtime_error("URL parsing failed");
	}

	PrintURLInfo(output, url, info);
}

int main()
{
	try
	{
		ParseURL(std::cin, std::cout);
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

	return 0;
}
