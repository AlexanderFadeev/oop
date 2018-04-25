#include "Identifier.hpp"
#include <queue>
#include <stack>

void CIdentifier::Uses(std::weak_ptr<CIdentifier> idWPtr)
{
	m_usesIDs.push_back(idWPtr);
	if (auto idSPtr = idWPtr.lock())
	{
		idSPtr->m_usedInIDs.push_back(weak_from_this());
	}
}

void CIdentifier::Update() const
{
	if (m_value)
	{
		return;
	}

	for (auto& idWPtr : m_usesIDs)
	{
		if (auto idSPtr = idWPtr.lock())
		{
			idSPtr->Update();
		}
	}

	m_value = CalcValue();

	return;
}

void CIdentifier::Expire() const
{
	if (!m_value)
	{
		return;
	}
	m_value = std::nullopt;

	for (auto& idWPtr : m_usedInIDs)
	{
		if (auto idSPtr = idWPtr.lock())
		{
			idSPtr->Expire();
		}
	}
}

double CIdentifier::GetValue() const
{
	Update();
	return *m_value;
}
