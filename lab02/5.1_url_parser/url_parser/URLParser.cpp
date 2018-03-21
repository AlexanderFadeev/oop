#include "URLParser.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>

bool CharsAreEqualCaseInsensitive(char a, char b)
{
	return tolower(a) == tolower(b);
}

bool StringsAreEqualCaseInsensitive(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(), b.begin(), b.end(), CharsAreEqualCaseInsensitive);
}

Protocol ParseProtocol(const std::string& str)
{
	if (StringsAreEqualCaseInsensitive(str, "http"))
	{
		return Protocol::HTTP;
	}
	if (StringsAreEqualCaseInsensitive(str, "https"))
	{
		return Protocol::HTTPS;
	}
	if (StringsAreEqualCaseInsensitive(str, "ftp"))
	{
		return Protocol::FTP;
	}
	throw std::exception("Unknown protocol");
}

const int PORT_LOWER_BOUND = 1;
const int PORT_UPPER_BOUND = 65535;

const std::map<Protocol, int> PROTOCOL_TO_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

int ParsePort(const std::string& str, Protocol protocol)
{
	if (str.empty())
	{
		return PROTOCOL_TO_PORT.at(protocol);
	}

	int port = std::stoi(str);
	if (port < PORT_LOWER_BOUND || port > PORT_UPPER_BOUND)
	{
		std::stringstream buf;
		buf << "Port out of range [" << PORT_LOWER_BOUND << ", " << PORT_UPPER_BOUND << "]";
		throw std::runtime_error(buf.str());
	}
	return port;
}

void MustParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"(^(http|https|ftp):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", std::regex::icase);
	std::smatch urlMatch;
	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw std::runtime_error("Match failed");
	}

	protocol = ParseProtocol(urlMatch[1]);
	host = urlMatch[2];
	port = ParsePort(urlMatch[3], protocol);
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

bool ParseURL(const std::string& url, URLInfo& info)
{
	return ParseURL(url, info.protocol, info.port, info.host, info.document);
}
