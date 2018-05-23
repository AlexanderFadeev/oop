#include "ExpandTemplate.hpp"
#include <algorithm>

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
	if (params.empty())
	{
		return tpl;
	}

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