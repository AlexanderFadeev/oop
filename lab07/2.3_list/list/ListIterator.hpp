#pragma once

#include "List.hpp"
#include <iterator>

template <typename ListValueType>
template <typename ValueType>
class CList<ListValueType>::CIterator
{
public:
#pragma region STLSupport
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ValueType                       value_type;
	typedef ptrdiff_t                       difference_type;
	typedef ValueType*                      pointer;
	typedef ValueType&                      reference;
#pragma endregion

	using SNodeSPtr = CList<ListValueType>::SNodeSPtr;

	CIterator(const CList<ListValueType>::CIterator<ListValueType>& it);

	bool operator==(const CIterator& other) const;
	bool operator!=(const CIterator& other) const;

	ValueType& operator*() const;
	ValueType* operator->() const;

	CIterator& operator++();
	CIterator& operator--();
	const CIterator operator++(int);
	const CIterator operator--(int);

private:
	friend class CList<ListValueType>;

	CIterator(const CList<ListValueType>* pList, SNodeSPtr pNode);

	SNodeSPtr m_pNode;
	const CList* m_pList;
};

#include "ListIterator.ipp"
