#include "ExpandTemplate.hpp"
#include <algorithm>
#include <fstream>

namespace
{
	
struct SFindResult
{
	size_t pos;
	Mapping::const_iterator pair;
};

size_t SubstringPosition(const std::string& str, const std::string& substr, size_t startPos)
{
	return substr.empty() ? std::string::npos : str.find(substr, startPos);
}

SFindResult Find(const std::string& tpl, size_t startPos, const Mapping& params)
{
	auto min = std::min_element(params.begin(), params.end(), [&](auto a, auto b) {
		auto posA = SubstringPosition(tpl, a.first, startPos);
		auto posB = SubstringPosition(tpl, b.first, startPos);

		if (posA == posB)
		{
			return a.first.length() > b.first.length();
		}

		return posA < posB;
	});

	auto pos = SubstringPosition(tpl, min->first, startPos);
	return { pos, min };
}

} // namespace

std::string ExpandTemplate(const std::string& tpl, const Mapping& params)
{
	std::string result;
	size_t prevPos = 0;
	size_t pos = 0;

	while (pos != std::string::npos)
	{
		auto findResult = Find(tpl, pos, params);

		pos = findResult.pos;
		result.append(tpl, prevPos, pos - prevPos);

		if (pos != std::string::npos)
		{
			result.append(findResult.pair->second);
			pos += findResult.pair->first.length();
		}

		prevPos = pos;
	}

	return result;
}

void ExpandTemplate(std::istream& input, std::ostream& output, const Mapping& params)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ExpandTemplate(line, params) << '\n';
	}

	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output");
	}
}

void ExpandTemplate(const std::string& inputFilename, const std::string& outputFilename, const Mapping& params)
{
	std::ifstream inputFile(inputFilename);
	if (!inputFile)
	{
		throw std::runtime_error("Failed to open input file");
	}

	std::ofstream outputFile(outputFilename);
	if (!outputFile)
	{
		throw std::runtime_error("Failed to open output file");
	}

	ExpandTemplate(inputFile, outputFile, params);
}
