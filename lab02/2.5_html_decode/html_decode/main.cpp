#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <string>

const std::map<std::string, std::string> HTML_ESCAPE_CHARACTERS_MAPPING = {
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" },
};

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

bool HtmlDecode(std::istream& input, std::ostream& output)
{
	std::string html(std::istreambuf_iterator<char>(input), {});

	output << HtmlDecode(html);

	output.flush();
	return static_cast<bool>(output);
}

int main()
{
	bool ok = HtmlDecode(std::cin, std::cout);

	if (!ok)
	{
		std::cerr << "Error occured\n";
		return 1;
	}

	return 0;
}
