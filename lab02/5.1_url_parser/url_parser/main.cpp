#include <exception>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool CharsAreEqualCaseInsensitive(char a, char b)
{
	return tolower(a) == tolower(b);
}

bool StringsAreEqualCaseInsensitive(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(), b.begin(), b.end(), CharsAreEqualCaseInsensitive);
}

void ParseProtocol(const std::string& str, Protocol& protocol)
{
	if (StringsAreEqualCaseInsensitive(str, "http"))
	{
		protocol = Protocol::HTTP;
	}
	else if (StringsAreEqualCaseInsensitive(str, "https"))
	{
		protocol = Protocol::HTTPS;
	}
	else if (StringsAreEqualCaseInsensitive(str, "ftp"))
	{
		protocol = Protocol::FTP;
	}
	else
	{
		throw std::exception("Unknown protocol");
	}
}

const int PORT_LOWER_BOUND = 1;
const int PORT_UPPER_BOUND = 65535;

const std::map<Protocol, int> PROTOCOL_TO_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

void ParsePort(const std::string& str, int& port, Protocol protocol)
{
	if (str.empty())
	{
		port = PROTOCOL_TO_PORT.at(protocol);
		return;
	}

	port = std::stoi(str);
	if (port < PORT_LOWER_BOUND || port > PORT_UPPER_BOUND)
	{
		std::stringstream buf;
		buf << "Port out of range [" << PORT_LOWER_BOUND << ", " << PORT_UPPER_BOUND << "]";
		throw std::runtime_error(buf.str());
	}
}

void MustParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"(^(http|https|ftp):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", std::regex::icase);
	std::smatch urlMatch;
	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw std::runtime_error("Match failed");
	}

	ParseProtocol(urlMatch[1], protocol);
	ParsePort(urlMatch[3], port, protocol);
	host = urlMatch[2];
	document = urlMatch[4];
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	try
	{
		MustParseURL(url, protocol, port, host, document);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return false;
	}
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
	std::string url;
	if (!(input >> url))
	{
		throw std::runtime_error("Read failed");
	}

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
