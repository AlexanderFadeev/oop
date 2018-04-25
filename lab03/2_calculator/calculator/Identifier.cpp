#include "Identifier.hpp"
#include <queue>
#include <stack>

void CIdentifier::Uses(const WeakPtr& idWPtr)
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
	m_value.emplace();

	using SharedConstPtr = std::shared_ptr<const CIdentifier>;
	using WeakConstPtrVecIter = WeakConstPtrVec::const_iterator;

	std::stack<std::pair<SharedConstPtr, WeakConstPtrVecIter>> st;

	st.push(std::make_pair(shared_from_this(), m_usesIDs.begin()));

	while (!st.empty())
	{
		auto& id = st.top().first;
		auto& it = st.top().second;

		if (!id)
		{
			st.pop();
			continue;
		}

		if (it == id->m_usesIDs.end())
		{
			id->m_value = id->CalcValue();

			st.pop();
			continue;
		}

		auto idShPtr = it->lock();
		if (idShPtr && !idShPtr->m_value)
		{
			st.push(std::make_pair(idShPtr, idShPtr->m_usesIDs.begin()));
		}

		it++;
	}
}

void CIdentifier::Expire() const
{
	if (!m_value)
	{
		return;
	}

	std::queue<std::shared_ptr<const CIdentifier>> q;
	q.push(shared_from_this());

	while (!q.empty())
	{
		auto currPtr = q.front();
		q.pop();

		currPtr->m_value = std::nullopt;

		for (auto& idWPtr : currPtr->m_usedInIDs)
		{
			auto idSPtr = idWPtr.lock();
			if (!idSPtr)
			{
				continue;
			}

			if (idSPtr->m_value)
			{
				q.push(idSPtr);
			}
		}
	}

}

double CIdentifier::GetValue() const
{
	Update();
	return *m_value;
}
