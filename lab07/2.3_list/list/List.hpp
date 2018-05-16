#pragma once

#include <iterator>
#include <memory>
#include <cassert>

template <typename ValueType>
class CList
{
public:
	template <typename>
	class CIterator;

	using Iterator = CIterator<ValueType>;
	using ConstIterator = CIterator<const ValueType>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CList();
	CList(const CList&);
	CList(CList&&);
	CList& operator=(const CList&);
	CList& operator=(CList&&);

	~CList();

	void PushFront(const ValueType&);
	void PushBack(const ValueType&);
	void PopFront();
	void PopBack();

	Iterator Insert(const ConstIterator&, const ValueType&);
	Iterator Erase(const ConstIterator&);

	void Clear();

	size_t GetSize() const;
	bool IsEmpty() const;

#pragma region Iterators
	Iterator Begin();
	Iterator End();
	ConstIterator CBegin() const;
	ConstIterator CEnd() const;
	ReverseIterator RBegin();
	ReverseIterator REnd();
	ConstReverseIterator CRBegin() const;
	ConstReverseIterator CREnd() const;
#pragma endregion

#pragma region RangeBasedForSupport
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
#pragma endregion

#pragma region STLSupport
	typedef ValueType value_type;

	void push_front(const ValueType&);
	void push_back(const ValueType&);
#pragma endregion

private:
	struct SNode;
	using SNodeSPtr = std::shared_ptr<SNode>;

	bool IsBeforeBegin(const ConstIterator&);

	SNodeSPtr m_begin;
	SNodeSPtr m_end;

	size_t m_size;
};


template <typename ValueType>
struct CList<ValueType>::SNode
{
	using SPtr = std::shared_ptr<SNode>;

	SNode(const ValueType&);

	ValueType data;
	SPtr next;
	SPtr prev;
};

#include "ListIterator.hpp"
#include "List.ipp"