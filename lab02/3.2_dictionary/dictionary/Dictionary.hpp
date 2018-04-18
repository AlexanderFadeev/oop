#pragma once

#include "Windows.h"
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <sstream>

struct StringLess
{
	bool operator()(const std::string&, const std::string&) const;
};

class CDictionary
{
public:
	using Container = std::multimap<std::string, std::string, ::StringLess>;
	using ContainerSPtr = std::shared_ptr<Container>;
	using Range = std::pair<Container::const_iterator, Container::const_iterator>;

	CDictionary();

	void Add(const std::string& word, const std::string& translation);
	bool Has(const std::string& word) const;
	Range Find(const std::string& word) const;

	const ContainerSPtr GetData();

private:
	ContainerSPtr m_data;
};

void SetCodePage(int cp);
