#include "DictionaryControl.hpp"
#include <algorithm>
#include <fstream>

CDictionaryControl::CDictionaryControl(CDictionary& dictionary,
	const std::string& dictionaryFilePath, std::istream& input, std::ostream& output)
	: m_dictionary(dictionary)
	, m_path(dictionaryFilePath)
	, m_input(input)
	, m_output(output)
{
	Load();
}

void CDictionaryControl::Load()
{
	std::ifstream file(m_path);
	if (!file.is_open())
	{
		return;
	}

	m_dictionary.ReadData(file);
}

void CDictionaryControl::Save()
{
	std::ofstream file(m_path);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open output file");
	}

	m_dictionary.WriteData(file);
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
	m_output << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа" << std::endl;
	auto translation = GetTranslation();
	if (!translation)
	{
		m_output << "Слово \"" << word << "\" проигнорировано." << std::endl;
		return;
	}

	try
	{
		m_dictionary.Add(word, *translation);
		m_output << "Слово \"" << word << "\" сохранено в словаре как \"" << *translation << "\"" << std::endl;
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
		Save();
		m_output << "Изменения сохранены. До свидания." << std::endl;
	}
}

bool CDictionaryControl::ShouldBeSaved()
{
	if (!m_wasChanged)
	{
		return false;
	}

	m_output << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
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
