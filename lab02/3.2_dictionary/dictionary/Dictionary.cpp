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

CDictionary::CDictionary()
	: m_data(std::make_shared<Container>())
{
}

void CDictionary::Add(const std::string& word, const std::string& translation)
{
	m_data->insert({ word, translation });
	if (word != translation)
	{
		m_data->insert({ translation, word });
	}
}

bool CDictionary::Has(const std::string& word) const
{
	return m_data->find(word) != m_data->end();
}

CDictionary::Range CDictionary::Find(const std::string& word) const
{
	return m_data->equal_range(word);
}

const CDictionary::ContainerSPtr CDictionary::GetData()
{
	return m_data;
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
