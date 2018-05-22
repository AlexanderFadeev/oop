#include "UrlParsingError.hpp"
#include <string>

CUrlParsingError::CUrlParsingError(const std::string& message)
	: invalid_argument(message)
{
}
