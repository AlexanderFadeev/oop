#pragma once

#include "List.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
inline CList<T>::CList()
	: m_size(0)
	, m_pBegin(nullptr)
	, m_pEnd(nullptr)
{
}

template <typename T>
inline CList<T>::CList(const CList& other)
	: CList()
{
	*this = other;
}

template <typename T>
inline CList<T>::CList(CList&& other)
	: CList()
{
	*this = std::move(other);
}

template <typename T>
inline CList<T>& CList<T>::operator=(const CList& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	auto oldSize = m_size;
	size_t copiedCount = 0;
	
	try
	{
		for (auto& val : rhs)
		{
			PushBack(val);
			copiedCount++;
		}
	}
	catch (...)
	{
		PopBack(copiedCount);
		throw;
	}

	PopFront(oldSize);

	return *this;
}

template <typename T>
inline CList<T>& CList<T>::operator=(CList&& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	std::swap(m_pBegin, rhs.m_pBegin);
	std::swap(m_pEnd, rhs.m_pEnd);
	std::swap(m_size, rhs.m_size);

	rhs.Clear();

	return *this;
}

template <typename T>
inline CList<T>::~CList()
{
	Clear();
}

template <typename T>
inline void CList<T>::PushFront(const T& value)
{
	Insert(CBegin(), value);
}

template <typename T>
inline void CList<T>::PushBack(const T& value)
{
	Insert(CEnd(), value);
}

template <typename T>
inline void CList<T>::PopFront(size_t count)
{
	while (count--)
	{
		Erase(CBegin());
	}
}

template <typename T>
inline void CList<T>::PopBack(size_t count)
{
	while (count--)
	{
		Erase(--CEnd());
	}
}

template <typename T>
inline typename CList<T>::Iterator CList<T>::Insert(const ConstIterator& it, const T& value)
{
	assert(this == it.m_pList);

	auto pNew = std::make_shared<SNode>(value);

	auto& pPrev = it.m_pNode ? it.m_pNode->prev : m_pEnd;
	if (pPrev)
	{
		pNew->prev = pPrev;
		pPrev->next = pNew;
	}
	auto& pNext = it.m_pNode;
	if (pNext)
	{
		pNew->next = pNext;
		pNext->prev = pNew;
	}

	if (it == CBegin())
	{
		m_pBegin = pNew;
	}
	if (it == CEnd())
	{
		m_pEnd = pNew;
	}

	m_size++;
	return Iterator(this, pNew);
}

template <typename T>
inline typename CList<T>::Iterator CList<T>::Erase(const ConstIterator& it)
{
	assert(this == it.m_pList);
	assert(it.m_pNode);
	assert(!IsEmpty());

	if (it == CBegin())
	{
		m_pBegin = m_pBegin->next;
	}
	if (it == --CEnd())
	{
		m_pEnd = m_pEnd->prev;
	}

	auto pCurr = it.m_pNode;
	if (auto pPrev = pCurr->prev)
	{
		pPrev->next = pCurr->next;
	}
	if (auto pNext = pCurr->next)
	{
		pNext->prev = pCurr->prev;
	}

	m_size--;
	return Iterator(this, pCurr->next);
}

template <typename T>
inline void CList<T>::Clear()
{
	while (!IsEmpty())
	{
		PopFront();
	}
}

template <typename T>
inline size_t CList<T>::GetSize() const
{
	return m_size;
}

template <typename T>
inline bool CList<T>::IsEmpty() const
{
	return m_size == 0;
}

#pragma region Iterators
template <typename T>
typename CList<T>::Iterator CList<T>::Begin()
{
	return Iterator(this, m_pBegin);
}

template <typename T>
typename CList<T>::Iterator CList<T>::End()
{
	return Iterator(this, nullptr);
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::CBegin() const
{
	return ConstIterator(this, m_pBegin);
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::CEnd() const
{
	return ConstIterator(this, nullptr);
}

template <typename T>
typename CList<T>::ReverseIterator CList<T>::RBegin()
{
	return ReverseIterator(End());
}

template <typename T>
typename CList<T>::ReverseIterator CList<T>::REnd()
{
	return ReverseIterator(Begin());
}

template <typename T>
typename CList<T>::ConstReverseIterator CList<T>::CRBegin() const
{
	return ConstReverseIterator(CEnd());
}

template <typename T>
typename CList<T>::ConstReverseIterator CList<T>::CREnd() const
{
	return ConstReverseIterator(CBegin());
}
#pragma endregion

#pragma region RangeBasedForSupport
template <typename T>
typename CList<T>::Iterator CList<T>::begin()
{
	return Begin();
}

template <typename T>
typename CList<T>::Iterator CList<T>::end()
{
	return End();
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::begin() const
{
	return CBegin();
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::end() const
{
	return CEnd();
}
#pragma endregion

#pragma region STLSupport
template <typename T>
inline void CList<T>::push_front(const T& value)
{
	PushFront(value);
}

template <typename T>
inline void CList<T>::push_back(const T& value)
{
	PushBack(value);
}
#pragma endregion

template <typename T>
inline CList<T>::SNode::SNode(const T& value)
	: data(value)
	, prev(nullptr)
	, next(nullptr)
{
}
