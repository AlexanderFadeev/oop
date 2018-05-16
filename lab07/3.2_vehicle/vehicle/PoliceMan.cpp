#include "PoliceMan.hpp"

CPoliceMan::CPoliceMan(const std::string& name, const std::string& departamentName)
	: CPersonImpl(name)
	, m_departamentName(departamentName)
{
}

std::string CPoliceMan::GetDepartamentName() const
{
	return m_departamentName;
}