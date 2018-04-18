#pragma once

#include "Dictionary.hpp"
#include <iostream>
#include <optional>
#include <string>

const std::string COMMAND_END = "...";

class CDictionaryControl
{
public:
	CDictionaryControl(CDictionary& dictionary,
		const std::string& dictionaryFilePath, std::istream& input = std::cin, std::ostream& output = std::cout);

	void HandleCommands();

private:
	void Load();
	void Save();

	void PrintTranslations(const std::string& word);
	std::optional<std::string> GetTranslation();
	void GetAndAddTranslation(const std::string& word);
	bool ShouldBeSaved();

	std::string m_path;
	std::istream& m_input;
	std::ostream& m_output;
	bool m_wasChanged = false;
	CDictionary& m_dictionary;
};
