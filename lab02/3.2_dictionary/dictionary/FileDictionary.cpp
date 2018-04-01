#include "FileDictionary.hpp"
#include <fstream>

CFileDictionary::CFileDictionary(const std::string& filename)
	: m_filename(filename)
{
	std::ifstream file(m_filename);
	if (!file.is_open())
	{
		return;
	}

	ReadData(file);
}

void CFileDictionary::Save()
{
	std::ofstream file(m_filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open output file");
	}

	WriteData(file);
}
