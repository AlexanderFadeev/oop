#pragma once

#include "Dictionary.hpp"

class CFileDictionary : public CDictionary
{
public:
	CFileDictionary(const std::string& filename);

	void Save();

private:
	std::string m_filename;
};
