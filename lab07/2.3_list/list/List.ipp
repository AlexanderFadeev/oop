#pragma once

#include "List.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
inline CList<T>::CList()
	: m_size(0)
	, m_begin(nullptr)
	, m_end(nullptr)
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
	Clear();

	for (auto& val : rhs)
	{
		PushBack(val);
	}

	return *this;
}

template <typename T>
inline CList<T>& CList<T>::operator=(CList&& rhs)
{
	std::swap(m_begin, rhs.m_begin);
	std::swap(m_end, rhs.m_end);
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
inline void CList<T>::PopFront()
{
	Erase(CBegin());
}

template <typename T>
inline void CList<T>::PopBack()
{
	Erase(--CEnd());
}

template <typename T>
inline typename CList<T>::Iterator CList<T>::Insert(const ConstIterator& it, const T& value)
{
	assert(!IsBeforeBegin(it));

	auto pNew = std::make_shared<SNode>(value);
	if (it == CBegin())
	{
		m_begin = pNew;
	}
	if (it == CEnd())
	{
		m_end = pNew;
	}

	if (it.m_prev)
	{
		pNew->prev = it.m_prev;
		pNew->prev->next = pNew;
		
	}
	if (it.m_ptr)
	{
		pNew->next = it.m_ptr;
		pNew->next->prev = pNew;
	}

	m_size++;
	return { pNew };
}

template <typename T>
inline typename CList<T>::Iterator CList<T>::Erase(const ConstIterator& it)
{
	assert(it.m_ptr && !IsEmpty());

	if (it == CBegin())
	{
		m_begin = m_begin->next;
	}
	if (it == --CEnd())
	{
		m_end = m_end->prev;
	}

	auto pCurr = it.m_ptr;
	if (auto pPrev = pCurr->prev)
	{
		pPrev->next = pCurr->next;
	}
	if (auto pNext = pCurr->next)
	{
		pNext->prev = pCurr->prev;
	}

	m_size--;
	return { it.m_next };
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
	return Iterator(m_begin);
}

template <typename T>
typename CList<T>::Iterator CList<T>::End()
{
	Iterator it(m_end);
	return m_end ? ++it : it;
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::CBegin() const
{
	return ConstIterator(m_begin);
}

template <typename T>
typename CList<T>::ConstIterator CList<T>::CEnd() const
{
	ConstIterator it(m_end);
	return m_end ? ++it : it;
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
inline bool CList<T>::IsBeforeBegin(const ConstIterator& it)
{
	return (m_begin) && (it == --CBegin());  
}

template <typename T>
inline CList<T>::SNode::SNode(const T& value)
	: data(value)
	, prev(nullptr)
	, next(nullptr)
{
}