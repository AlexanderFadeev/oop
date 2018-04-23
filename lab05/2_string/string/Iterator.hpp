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

	CIterator(ValueType* ptr = nullptr);
	CIterator(const CIterator&);
#ifndef NDEBUG
	CIterator(ValueType* ptr, ValueType* begin, ValueType* end);
#endif // !NDEBUG

	CIterator& operator=(const CIterator&);

	ValueType& operator*();
	ValueType& operator[](size_t);

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
	ValueType* m_ptr;
#ifndef NDEBUG
	ValueType* m_begin;
	ValueType* m_end;
#endif // !NDEBUG
};
