#include "Dictionary.hpp"
#include <sstream>
#include <string>

bool StringLess::operator()(const std::string& a, const std::string& b) const
{
	auto charLess = [](char a, char b) {
		return std::tolower(a, std::locale("")) < std::tolower(b, std::locale(""));
	};

	return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), charLess);
}

void CDictionary::Add(const std::string& word, const std::string& translation)
{
	m_data.insert({ word, translation });
	if (word != translation)
	{
		m_data.insert({ translation, word });
	}
}

bool CDictionary::Has(const std::string& word) const
{
	return m_data.find(word) != m_data.end();
}

CDictionary::Range CDictionary::Find(const std::string& word) const
{
	return m_data.equal_range(word);
}

void CDictionary::ReadData(std::istream& input)
{
	std::string word, translation;

	while (std::getline(input, word) && std::getline(input, translation))
	{
		Add(word, translation);
	}
}

void CDictionary::WriteData(std::ostream& output) const
{
	for (auto& relation : m_data)
	{
		if (relation.first <= relation.second)
		{
			output << relation.first << std::endl
				   << relation.second << std::endl;
		}
	}

	if (!output)
	{
		throw std::runtime_error("Failed to write out dictionary data");
	}
}

void SetCodePage(int cp)
{
	if (!SetConsoleCP(cp) || !SetConsoleOutputCP(cp))
	{
		std::ostringstream buf;
		buf << "Failed to set codepage to " << cp;
		throw std::runtime_error(buf.str());
	}
}
