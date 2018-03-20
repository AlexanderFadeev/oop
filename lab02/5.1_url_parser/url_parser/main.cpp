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

void PrintURLInfo(std::ostream& output,
	const std::string& url, int port, const std::string& host, const std::string& document)
{
	output << url << '\n'
		   << "HOST: " << host << '\n'
		   << "PORT: " << port << '\n'
		   << "DOC: " << document << std::endl;

	if (!output)
	{
		throw std::runtime_error("Write failed");
	}
}

void ParseURL(std::istream& input, std::ostream& output)
{
	auto url = Read<std::string>(input);

	Protocol protocol;
	std::string host;
	int port;
	std::string document;
	if (!ParseURL(url, protocol, port, host, document))
	{
		throw std::runtime_error("URL parsing failed");
	}

	PrintURLInfo(output, url, port, host, document);
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
