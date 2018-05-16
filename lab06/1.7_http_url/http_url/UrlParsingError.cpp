#include "UrlParsingError.hpp"

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}

CUrlParsingError CUrlParsingError::PortOutOfRange()
{
	return CUrlParsingError("Port is out of range");
}

CUrlParsingError CUrlParsingError::InvalidURL(const std::string& url)
{
	return CUrlParsingError("Invalid URL: " + url);
}

CUrlParsingError CUrlParsingError::InvalidProtocol(const std::string& protocol)
{
	return CUrlParsingError("Invalid protocol: " + protocol);
}

CUrlParsingError CUrlParsingError::InvalidDomain(const std::string& domain)
{
	return CUrlParsingError("Invalid domain: " + domain);
}

CUrlParsingError CUrlParsingError::InvalidPort(const std::string& port)
{
	return CUrlParsingError("Invalid port: " + port);
}
