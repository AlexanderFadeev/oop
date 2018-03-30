#include "Identifier.hpp"
#include <queue>
#include <stack>

void CIdentifier::Uses(std::weak_ptr<const CIdentifier> id) const
{
	m_usesIDs.push_back(id);
	id.lock()->m_usedInIDs.push_back(weak_from_this());
}

void CIdentifier::InitRelations() const
{
	if (m_relationsInitialized)
	{
		return;
	}

	InitRelationsImpl();
}

void CIdentifier::Update() const
{
	if (m_isActual)
	{
		return;
	}
	InitRelations();

	for (auto& id : m_usesIDs)
	{
		id.lock()->Update();
	}

	m_value = CalcValue();
	m_isActual = true;
}

void CIdentifier::Expire() const
{
	if (!m_isActual)
	{
		return;
	}

	m_isActual = false;

	for (auto& id : m_usedInIDs)
	{
		id.lock()->Expire();
	}
}

double CIdentifier::GetValue() const
{
	Update();
	return m_value;
}
