#include "Iterator.hpp"
#include <cassert>

#ifndef NDEBUG
template <typename T>
CString::CIterator<T>::CIterator(T* ptr, T* begin, T* end)
	: m_ptr(ptr)
	, m_begin(begin)
	, m_end(end)
{
}
#else
template <typename T>
CString::CIterator<T>::CIterator(T* ptr)
	: m_ptr(ptr)
{
}
#endif // !NDEBUG

template <typename T>
T& CString::CIterator<T>::operator*() const
{
	assert(m_begin <= m_ptr && m_ptr < m_end);
	return *m_ptr;
}

template <typename T>
T& CString::CIterator<T>::operator[](ptrdiff_t index) const
{
	assert(m_begin <= m_ptr + index && m_ptr + index < m_end);
	return m_ptr[index];
}

template <typename T>
CString::CIterator<T>& CString::CIterator<T>::operator++()
{
	m_ptr++;
	return *this;
}

template <typename T>
CString::CIterator<T>& CString::CIterator<T>::operator--()
{
	m_ptr--;
	return *this;
}

template <typename T>
CString::CIterator<T>& CString::CIterator<T>::operator+=(ptrdiff_t rhs)
{
	m_ptr += rhs;
	return *this;
}

template <typename T>
CString::CIterator<T>& CString::CIterator<T>::operator-=(ptrdiff_t rhs)
{
	m_ptr -= rhs;
	return *this;
}

template <typename T>
const CString::CIterator<T> CString::CIterator<T>::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

template <typename T>
const CString::CIterator<T> CString::CIterator<T>::operator--(int)
{
	auto copy = *this;
	--(*this);
	return copy;
}

template <typename T>
bool CString::CIterator<T>::operator==(const CIterator& rhs) const
{
	return m_ptr == rhs.m_ptr;
}

template <typename T>
bool CString::CIterator<T>::operator!=(const CIterator& rhs) const
{
	return m_ptr != rhs.m_ptr;
}

template <typename T>
bool CString::CIterator<T>::operator<(const CIterator& rhs) const
{
	return m_ptr < rhs.m_ptr;
}

template <typename T>
bool CString::CIterator<T>::operator>(const CIterator& rhs) const
{
	return rhs < *this;
}

template <typename T>
bool CString::CIterator<T>::operator<=(const CIterator& rhs) const
{
	return !(*this > rhs);
}

template <typename T>
bool CString::CIterator<T>::operator>=(const CIterator& rhs) const
{
	return !(*this < rhs);
}

template <typename T>
const CString::CIterator<T> operator+(ptrdiff_t lhs, const CString::CIterator<T>& rhs)
{
	return rhs + lhs;
}

template <typename T>
const CString::CIterator<T> CString::CIterator<T>::operator+(ptrdiff_t rhs) const
{
	auto copy = *this;
	copy.m_ptr += rhs;
	return copy;
}

template <typename T>
const CString::CIterator<T> CString::CIterator<T>::operator-(ptrdiff_t rhs) const
{
	auto copy = *this;
	copy.m_ptr -= rhs;
	return copy;
}

template <typename T>
ptrdiff_t CString::CIterator<T>::operator-(const CIterator& rhs) const
{
	return m_ptr - rhs.m_ptr;
}
