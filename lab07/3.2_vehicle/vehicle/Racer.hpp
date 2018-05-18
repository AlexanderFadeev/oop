#pragma once

#include "IRacer.hpp"
#include "PersonImpl.hpp"

class CRacer
	: public CPersonImpl<IRacer>
{
public:
	CRacer(const std::string& name, size_t awardsCount);

	size_t GetAwardsCount() const override;

private:
	size_t m_awardsCount;
};