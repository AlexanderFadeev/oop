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
	VerifyIsEnglish(word);
	VerifyIsRussian(translation);
	m_data.insert({ word, translation });
	m_data.insert({ translation, word });
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
		if (IsEnglish(relation.first))
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

const std::regex CDictionary::m_russianRegex(R"(^\s*([À-ÿ]+(\s*|-))*[À-ÿ]+\s*$)");
const std::regex CDictionary::m_englishRegex(R"(^\s*([A-z]+(\s*|-))*[A-z]+\s*$)");

bool CDictionary::IsRussian(const std::string word)
{
	return std::regex_match(word, m_russianRegex);
}

bool CDictionary::IsEnglish(const std::string word)
{
	return std::regex_match(word, m_englishRegex);
}

void CDictionary::VerifyIsRussian(const std::string& word)
{
	if (!IsRussian(word))
	{
		std::ostringstream buf;
		buf << '"' << word << "\" is not a valid russian collocation";
		throw std::invalid_argument(buf.str());
	}
}

void CDictionary::VerifyIsEnglish(const std::string& word)
{
	if (!IsEnglish(word))
	{
		std::ostringstream buf;
		buf << '"' << word << "\" is not a valid english collocation";
		throw std::invalid_argument(buf.str());
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
