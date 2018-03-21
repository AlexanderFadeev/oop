#include "HTMLDecode.hpp"
#include <array>
#include <regex>
#include <string>

const std::array<std::pair<std::string, std::string>, 5> HTML_ESCAPE_CHARACTERS_MAPPING = { {
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" },
} };

std::string ReplaceAll(const std::string& str, const std::string& from, const std::string& to)
{
	std::string result;
	std::regex_replace(std::back_inserter(result), str.begin(), str.end(), std::regex(from), to);
	return result;
}

std::string HtmlDecode(const std::string& html)
{
	std::string result = html;
	for (auto& relation : HTML_ESCAPE_CHARACTERS_MAPPING)
	{
		result = ReplaceAll(result, relation.second, relation.first);
	}

	return result;
}
