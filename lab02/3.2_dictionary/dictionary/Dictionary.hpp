#pragma once

#include "Windows.h"
#include <iostream>
#include <map>
#include <regex>
#include <sstream>

struct StringLess
{
	bool operator()(const std::string&, const std::string&) const;
};

class CDictionary
{
public:
	using Container = std::multimap<std::string, std::string, StringLess>;
	using Range = std::pair<Container::const_iterator, Container::const_iterator>;

	void Add(const std::string& word, const std::string& translation);
	bool Has(const std::string& word) const;
	Range Find(const std::string& word) const;
	void ReadData(std::istream& input);
	void WriteData(std::ostream& output) const;

private:
	Container m_data;

	static const std::regex m_russianRegex;
	static const std::regex m_englishRegex;

	static bool IsRussian(const std::string word);
	static bool IsEnglish(const std::string word);
	static void VerifyIsRussian(const std::string& word);
	static void VerifyIsEnglish(const std::string& word);
};

void SetCodePage(int cp);
