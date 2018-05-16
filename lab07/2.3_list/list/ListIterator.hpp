#pragma once

#include "List.hpp"
#include <iterator>

template <typename T>
template <typename ValueType>
class CList<T>::CIterator
{
public:
#pragma region STLSupport
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ValueType                       value_type;
	typedef ptrdiff_t                       difference_type;
	typedef ValueType*                      pointer;
	typedef ValueType&                      reference;
#pragma endregion

	bool operator==(const CIterator& other) const;
	bool operator!=(const CIterator& other) const;

	ValueType& operator*() const;

	CIterator& operator++();
	CIterator& operator--();
	const CIterator operator++(int);
	const CIterator operator--(int);

private:
	friend class CList<T>;

	using SNodeSPtr = CList<T>::SNodeSPtr;

	CIterator(SNodeSPtr);

	SNodeSPtr m_ptr;
	SNodeSPtr m_prev;
	SNodeSPtr m_next;
};

#include "ListIterator.ipp"
