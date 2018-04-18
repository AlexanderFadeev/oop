#include "Identifier.hpp"
#include <queue>
#include <stack>

void CIdentifier::Uses(std::weak_ptr<CIdentifier> id)
{
	m_usesIDs.push_back(id);
	id.lock()->m_usedInIDs.push_back(weak_from_this());
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
	m_value = {};

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
