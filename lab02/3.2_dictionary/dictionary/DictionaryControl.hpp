#pragma once

#include "FileDictionary.hpp"
#include <iostream>
#include <optional>
#include <string>

const std::string COMMAND_END = "...";

class CDictionaryControl
{
public:
	CDictionaryControl(CFileDictionary& dictionary, std::istream& input = std::cin, std::ostream& output = std::cout);

	void HandleCommands();

private:
	CFileDictionary& m_dictionary;
	std::istream& m_input;
	std::ostream& m_output;
	bool m_wasChanged = false;

	void PrintTranslations(const std::string& word);
	std::optional<std::string> GetTranslation();
	void GetAndAddTranslation(const std::string& word);
	bool ShouldBeSaved();
};
