#include "Racer.hpp"

CRacer::CRacer(const std::string& name, size_t awardsCount)
	: CPersonImpl(name)
	, m_awardsCount(awardsCount)
{
}

size_t CRacer::GetAwardsCount() const
{
	return m_awardsCount;
}
