#include "HttpUrl.hpp"
#include <exception>
#include <iostream>
#include <string>

void PrintURLInfo(std::ostream& output, const CHttpUrl& url)
{
	output << "URL: " << url.GetUrl() << '\n'
		<< "HOST: " << url.GetDomain() << '\n'
		<< "PORT: " << url.GetPort() << '\n'
		<< "DOC: " << url.GetDocument() << std::endl;

	if (!output)
	{
		throw std::runtime_error("Failed to write to output stream");
	}
}

void HandleURL(const std::string& line, std::ostream& output)
{
	try
	{
		CHttpUrl url(line);
		PrintURLInfo(output, url);
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

void HandleURLs(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (line.empty())
		{
			continue;
		}

		HandleURL(line, output);
	}
}

int main()
{
	HandleURLs(std::cin, std::cout);
}