#pragma once

#include "ListIterator.hpp"

template <typename T>
template <typename U>
inline bool CList<T>::CIterator<U>::operator==(const CIterator& other) const
{
	assert(m_pList == other.m_pList);
	return m_pNode == other.m_pNode;
}

template <typename T>
template <typename U>
inline bool CList<T>::CIterator<U>::operator!=(const CIterator& other) const
{
	return !(*this == other);
}

template <typename T>
template <typename U>
inline U& CList<T>::CIterator<U>::operator*() const
{
	assert(m_pNode);
	return m_pNode->data;
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>& CList<T>::CIterator<U>::operator++()
{
	assert(m_pNode);
	m_pNode = m_pNode->next;
	return *this;
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>& CList<T>::CIterator<U>::operator--()
{
	if (!m_pNode)
	{
		assert(m_pList->m_pEnd);
		m_pNode = m_pList->m_pEnd;
		return *this;
	}

	assert(m_pNode->prev);
	m_pNode = m_pNode->prev;
	return *this;
}

template <typename T>
template <typename U>
inline const CList<T>::CIterator<U> CList<T>::CIterator<U>::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

template <typename T>
template <typename U>
inline const CList<T>::CIterator<U> CList<T>::CIterator<U>::operator--(int)
{
	auto copy = *this;
	--(*this);
	return copy;
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>::CIterator(const CIterator<T>& it)
	: m_pNode(it.m_pNode)
	, m_pList(it.m_pList)
{
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>::CIterator(const CList<T>* pList, CIterator::SNodeSPtr pNode)
	: m_pNode(std::move(pNode))
	, m_pList(pList)
{
}
