#pragma once

#include <stdexcept>

class CUrlParsingError
	: public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& message);
};

enum class ErrorType
{
	InvalidURL,
	InvalidProtocol,
	InvalidDomain,
	InvalidPort,
	PortIsOutOfRange,
};

std::string FormatErrorMessage(ErrorType type, const std::string& value);