#include "HttpUrl.hpp"
#include "UrlParsingError.hpp"
#include <algorithm>
#include <map>
#include <regex>
#include <sstream>

namespace
{

using Protocol = CHttpUrl::Protocol;

std::regex URL_REGEX(R"(^(http|https):\/\/([^\s:\/]+)(?::(\d+))?(?:\/(\S*))?$)", std::regex::icase);
std::regex DOMAIN_REGEX(R"(^([^\s:\/]+)$)");

const int PORT_LOWER_BOUND = 1;
const int PORT_UPPER_BOUND = 65535;

const std::map<Protocol, uint16_t> PROTOCOL_DEFAULT_PORTS = {
	{ Protocol::HTTP, 80ui16 },
	{ Protocol::HTTPS, 443ui16 },
};

const std::map<Protocol, std::string> PROTOCOL_STRING_REPRESENTATIONS = {
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" },
};

void ValidateDomain(const std::string& domain)
{
	if (!std::regex_match(domain, DOMAIN_REGEX))
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::InvalidDomain, domain));
	}
}

void ValidatePort(uint16_t port)
{
	if (port < PORT_LOWER_BOUND || PORT_UPPER_BOUND < port)
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::PortIsOutOfRange, std::to_string(port)));
	}
}

bool CharsAreEqualCaseInsensitive(char a, char b)
{
	return tolower(a) == tolower(b);
}

bool StringsAreEqualCaseInsensitive(const std::string& a, const std::string& b)
{
	return std::equal(a.begin(), a.end(), b.begin(), b.end(), CharsAreEqualCaseInsensitive);
}

CHttpUrl::Protocol ParseProtocol(const std::string& protocol)
{
	if (StringsAreEqualCaseInsensitive(protocol, "http"))
	{
		return Protocol::HTTP;
	}
	if (StringsAreEqualCaseInsensitive(protocol, "https"))
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError(FormatErrorMessage(ErrorType::InvalidProtocol, protocol));
}

std::optional<uint16_t> ParsePort(const std::string& str)
{
	if (str.empty())
	{
		return std::nullopt;
	}

	int port;
	try
	{
		port = std::stoi(str);
	}
	catch (const std::out_of_range&)
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::PortIsOutOfRange, str));
	}
	catch (const std::invalid_argument&)
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::InvalidPort, str));
	}

	if (port < PORT_LOWER_BOUND || PORT_UPPER_BOUND < port)
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::PortIsOutOfRange, str));
	}

	return static_cast<uint16_t>(port);
}

std::string ParseDocument(const std::string& document)
{
	if (document.empty())
	{
		return "/";
	}

	if (document[0] == '/')
	{
		return document;
	}

	return "/" + document;
}

} // namespace

CHttpUrl::CHttpUrl(const std::string& url)
{
	std::smatch urlMatch;
	if (!std::regex_match(url, urlMatch, URL_REGEX))
	{
		throw CUrlParsingError(FormatErrorMessage(ErrorType::InvalidURL, url));
	}

	ValidateDomain(urlMatch[2]);

	m_protocol = ParseProtocol(urlMatch[1]);
	m_domain = urlMatch[2];
	m_optPort = ParsePort(urlMatch[3]);
	m_document = ParseDocument(urlMatch[4]);

}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: m_protocol(protocol)
	, m_domain(domain)
	, m_document(ParseDocument(document))
{
	ValidateDomain(domain);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, uint16_t port)
	: CHttpUrl(domain, document, protocol)
{
	ValidatePort(port);
	m_optPort = port;
}

std::string CHttpUrl::GetUrl() const
{
	std::ostringstream buf;
	buf << PROTOCOL_STRING_REPRESENTATIONS.at(m_protocol) << "://" << m_domain;
	if (m_optPort && !PortIsDefault())
	{
		buf << ":" << *m_optPort;
	}
	buf << m_document;

	return buf.str();
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

uint16_t CHttpUrl::GetPort() const
{
	if (m_optPort)
	{
		return *m_optPort;
	}

	return PROTOCOL_DEFAULT_PORTS.at(m_protocol);
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

bool CHttpUrl::PortIsDefault() const
{
	if (!m_optPort)
	{
		return true;
	}

	if (*m_optPort == PROTOCOL_DEFAULT_PORTS.at(m_protocol))
	{
		return true;
	}

	return false;
}
