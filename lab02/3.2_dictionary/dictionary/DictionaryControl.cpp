#include "DictionaryControl.hpp"
#include <algorithm>

CDictionaryControl::CDictionaryControl(CFileDictionary& dictionary, std::istream& input, std::ostream& output)
	: m_dictionary(dictionary)
	, m_input(input)
	, m_output(output)
{
}

void CDictionaryControl::PrintTranslations(const std::string& word)
{
	auto range = m_dictionary.Find(word);
	bool first = true;

	std::for_each(range.first, range.second, [&](const std::pair<std::string, std::string>& pair) {
		if (!first)
		{
			m_output << ", ";
		}
		first = false;
		m_output << pair.second;
	});

	m_output << std::endl;
}

std::optional<std::string> CDictionaryControl::GetTranslation()
{
	std::string translation;
	std::getline(m_input, translation);
	if (translation.empty())
	{
		return {};
	}

	return { translation };
}

void CDictionaryControl::GetAndAddTranslation(const std::string& word)
{
	m_output << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������" << std::endl;
	auto translation = GetTranslation();
	if (!translation)
	{
		m_output << "����� \"" << word << "\" ���������������." << std::endl;
		return;
	}

	try
	{
		m_dictionary.Add(word, *translation);
		m_output << "����� \"" << word << "\" ��������� � ������� ��� \"" << *translation << "\"" << std::endl;
		m_wasChanged = true;
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	catch (...)
	{
		m_output << "Unknown exception" << std::endl;
	}
}

void CDictionaryControl::HandleCommands()
{
	std::string word;
	while (std::getline(m_input, word) && (word != COMMAND_END))
	{
		if (word.empty())
		{
			continue;
		}

		if (m_dictionary.Has(word))
		{
			PrintTranslations(word);
			continue;
		}

		GetAndAddTranslation(word);
	}

	if (ShouldBeSaved())
	{
		m_dictionary.Save();
	}
}

bool CDictionaryControl::ShouldBeSaved()
{
	if (!m_wasChanged)
	{
		return false;
	}

	m_output << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
	std::string answer;
	if (!(m_input >> answer))
	{
		return false;
	}

	if (answer != "y" && answer != "Y")
	{
		return false;
	}

	return true;
}