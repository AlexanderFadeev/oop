#pragma once

#include <iterator>
#include <memory>
#include <cassert>

template <typename ValueType>
class CList
{
public:
	template <typename ValueType>
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
	void PopFront(size_t count = 1);
	void PopBack(size_t count = 1);

	Iterator Insert(const ConstIterator&, const ValueType&);
	Iterator Erase(const ConstIterator&);

	void Clear();

	size_t GetSize() const;
	bool IsEmpty() const;

#pragma region Iterators
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;
#pragma endregion

#pragma region STLSupport
	typedef ValueType value_type;

	void push_front(const ValueType&);
	void push_back(const ValueType&);
#pragma endregion

private:
	template <typename T>
	friend class CIterator;

	struct SNode;
	using SNodeSPtr = std::shared_ptr<SNode>;

	SNodeSPtr m_pBegin;
	SNodeSPtr m_pEnd;

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