#pragma once

#include <stdexcept>

class CUrlParsingError
	: public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& message);

	static CUrlParsingError PortOutOfRange();
	static CUrlParsingError InvalidURL(const std::string& url);
	static CUrlParsingError InvalidProtocol(const std::string& protocol);
	static CUrlParsingError InvalidDomain(const std::string& domain);
	static CUrlParsingError InvalidPort(const std::string& port);
};