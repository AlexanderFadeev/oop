#include "UrlParsingError.hpp"
#include <map>
#include <sstream>
#include <string>

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}

std::map<ErrorType, std::string> ERROR_STRING_REPRESENTATIONS{
	{ ErrorType::InvalidURL, "Invalid URL" },
	{ ErrorType::InvalidProtocol, "Invalid protocol" },
	{ ErrorType::InvalidDomain, "Invalid domain" },
	{ ErrorType::InvalidPort, "Invalid URL" },
	{ ErrorType::PortIsOutOfRange, "Port is out of range" },
};

std::string FormatErrorMessage(ErrorType type, const std::string& value)
{
	auto& mapping = ERROR_STRING_REPRESENTATIONS;
	auto it = mapping.find(type);
	if (it == mapping.end())
	{
		throw std::logic_error("Unknown error type");
	}

	std::ostringstream os;
	os << it->second << ": " << value;
	return os.str();
}