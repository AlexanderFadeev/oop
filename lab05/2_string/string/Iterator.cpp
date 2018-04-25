#include "Iterator.hpp"
#include <cassert>

template <typename T>
using CIterator = CString::CIterator<T>;

template <typename T>
CIterator<T>::CIterator(const CIterator<T>& it)
	: m_ptr(it.m_ptr)
#ifndef NDEBUG
	, m_begin(it.m_begin)
	, m_end(it.m_end)
#endif // !NDEBUG
{
}

#ifndef NDEBUG
template <typename T>
CIterator<T>::CIterator(T* ptr, T* begin, T* end)
	: m_ptr(ptr)
	, m_begin(begin)
	, m_end(end)
{
}
#else
template <typename T>
CIterator<T>::CIterator(T* ptr)
	: m_ptr(ptr)
{
}
#endif // !NDEBUG


template <typename T>
CIterator<T>& CIterator<T>::operator=(const CIterator& rhs)
{
	m_ptr = rhs.m_ptr;

#ifndef NDEBUG
	m_begin = rhs.m_begin;
	m_end = rhs.m_end;
#endif // !NDEBUG

	return *this;
}

#include <iostream>

template <typename T>
T& CIterator<T>::operator*() const
{
	assert(m_begin <= m_ptr && m_ptr < m_end);
	return *m_ptr;
}

template <typename T>
T& CIterator<T>::operator[](size_t index) const
{
	assert(m_begin <= m_ptr + index && m_ptr + index < m_end);
	return m_ptr[index];
}

template <typename T>
CIterator<T>& CIterator<T>::operator++()
{
	m_ptr++;
	return *this;
}

template <typename T>
CIterator<T>& CIterator<T>::operator--()
{
	m_ptr--;
	return *this;
}

template <typename T>
CIterator<T>& CIterator<T>::operator+=(size_t rhs)
{
	m_ptr += rhs;
	return *this;
}

template <typename T>
CIterator<T>& CIterator<T>::operator-=(size_t rhs)
{
	m_ptr -= rhs;
	return *this;
}

template <typename T>
const CIterator<T> CIterator<T>::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

template <typename T>
const CIterator<T> CIterator<T>::operator--(int)
{
	auto copy = *this;
	--(*this);
	return copy;
}

template <typename T>
bool CIterator<T>::operator==(const CIterator& rhs) const
{
	return m_ptr == rhs.m_ptr;
}

template <typename T>
bool CIterator<T>::operator!=(const CIterator& rhs) const
{
	return m_ptr != rhs.m_ptr;
}

template <typename T>
bool CIterator<T>::operator<(const CIterator& rhs) const
{
	return m_ptr < rhs.m_ptr;
}

template <typename T>
bool CIterator<T>::operator>(const CIterator& rhs) const
{
	return rhs < *this;
}

template <typename T>
bool CIterator<T>::operator<=(const CIterator& rhs) const
{
	return !(*this > rhs);
}

template <typename T>
bool CIterator<T>::operator>=(const CIterator& rhs) const
{
	return !(*this < rhs);
}

template <typename T>
const CIterator<T> operator+(size_t lhs, const CIterator<T>& rhs)
{
	return rhs + lhs;
}

template <typename T>
const CIterator<T> CIterator<T>::operator+(size_t rhs) const
{
	auto copy = *this;
	copy.m_ptr += rhs;
	return copy;
}

template <typename T>
const CIterator<T> CIterator<T>::operator-(size_t rhs) const
{
	auto copy = *this;
	copy.m_ptr -= rhs;
	return copy;
}

template <typename T>
size_t CIterator<T>::operator-(const CIterator& rhs) const
{
	return m_ptr - rhs.m_ptr;
}

template class CString::CIterator<char>;
template class CString::CIterator<const char>;
