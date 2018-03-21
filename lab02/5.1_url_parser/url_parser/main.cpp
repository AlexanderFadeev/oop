#include "URLParser.hpp"
#include <iostream>

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

void ParseURLs(std::istream& input, std::ostream& output)
{
	std::string url;
	while (std::getline(input, url))
	{
		if (url.empty())
		{
			break;
		}

		URLInfo info;
		if (!ParseURL(url, info))
		{
			output << "URL parsing failed" << std::endl;
			continue;
		}

		PrintURLInfo(output, url, info);
	}
}

int main()
{
	try
	{
		ParseURLs(std::cin, std::cout);
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
