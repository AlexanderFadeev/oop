#pragma once

#include "String.hpp"

template <typename ValueType>
class CString::CIterator final
{
public:
#pragma region STLSupport
	typedef std::random_access_iterator_tag iterator_category;
	typedef ValueType                       value_type;
	typedef size_t                          difference_type;
	typedef ValueType*                      pointer;
	typedef ValueType&                      reference;
#pragma endregion

	ValueType& operator*() const;
	ValueType& operator[](size_t) const;

	CIterator& operator++();
	CIterator& operator--();
	CIterator& operator+=(size_t);
	CIterator& operator-=(size_t);
	const CIterator operator++(int);
	const CIterator operator--(int);

	bool operator==(const CIterator&) const;
	bool operator!=(const CIterator&) const;
	bool operator< (const CIterator&) const;
	bool operator> (const CIterator&) const;
	bool operator<=(const CIterator&) const;
	bool operator>=(const CIterator&) const;

	friend const CIterator operator+(size_t, const CIterator&);
	const CIterator operator+(size_t) const;
	const CIterator operator-(size_t) const;
	size_t operator-(const CIterator&) const;

private:
	friend class CString;

#ifndef NDEBUG
	CIterator(ValueType* ptr = nullptr, ValueType* begin = nullptr, ValueType* end = nullptr);
#else
	CIterator(ValueType* ptr = nullptr);
#endif // !NDEBUG

	ValueType* m_ptr;
#ifndef NDEBUG
	ValueType* m_begin;
	ValueType* m_end;
#endif // !NDEBUG
};
