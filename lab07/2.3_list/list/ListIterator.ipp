#pragma once

#include "ListIterator.hpp"

template <typename T>
template <typename U>
bool CList<T>::CIterator<U>::operator==(const CIterator& other) const
{
	return m_ptr == other.m_ptr
		&& m_prev == other.m_prev
		&& m_next == other.m_next;
}

template <typename T>
template <typename U>
bool CList<T>::CIterator<U>::operator!=(const CIterator& other) const
{
	return !(*this == other);
}

template <typename T>
template <typename U>
inline U& CList<T>::CIterator<U>::operator*() const
{
	assert(m_ptr);
	return m_ptr->data;
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>& CList<T>::CIterator<U>::operator++()
{
	assert(m_ptr || m_next);
	m_prev = m_ptr;
	m_ptr = m_next;
	if (m_ptr)
	{
		m_next = m_ptr->next;
	}
	return *this;
}

template <typename T>
template <typename U>
inline CList<T>::CIterator<U>& CList<T>::CIterator<U>::operator--()
{
	assert(m_ptr || m_prev);
	m_next = m_ptr;
	m_ptr = m_prev;
	if (m_ptr)
	{
		m_prev = m_ptr->prev;
	}
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
inline CList<T>::CIterator<U>::CIterator(CList<T>::SNodeSPtr ptr)
	: m_ptr(ptr)
	, m_prev(ptr ? ptr->prev : nullptr)
	, m_next(ptr ? ptr->next : nullptr)
{
}
