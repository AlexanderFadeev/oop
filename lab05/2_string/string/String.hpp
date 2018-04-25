#pragma once

#include <iostream>
#include <iterator>
#include <string>

class CString
{
public:
	template <typename ValueType>
	class CIterator;

	using Iterator = CIterator<char>;
	using ConstIterator = CIterator<const char>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CString();
	CString(const char*);
	CString(const char*, size_t);
	CString(const CString&);
	CString(CString&&);
	CString(const std::string&);
	~CString();

	CString& operator=(const CString&);
	CString& operator=(CString&&);
	CString& operator+=(const CString&);

	char& operator[](size_t);
	const char& operator[](size_t) const;

	friend const CString operator+(CString, const CString&);

	friend bool operator==(const CString&, const CString&);
	friend bool operator!=(const CString&, const CString&);
	friend bool operator<(const CString&, const CString&);
	friend bool operator>(const CString&, const CString&);
	friend bool operator<=(const CString&, const CString&);
	friend bool operator>=(const CString&, const CString&);

	friend std::istream& operator>>(std::istream&, CString&);
	friend std::ostream& operator<<(std::ostream&, const CString&);
	
	void Clear();
	void PushBack(char ch);

	size_t GetLength() const;
	const char* GetData() const;
	CString SubString(size_t start, size_t length = SIZE_MAX) const;

	Iterator Begin();
	Iterator End();
	ConstIterator CBegin() const;
	ConstIterator CEnd() const;
	ReverseIterator RBegin();
	ReverseIterator REnd();
	ConstReverseIterator CRBegin() const;
	ConstReverseIterator CREnd() const;

#pragma region RangeBasedForSupport
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
#pragma endregion

private:
	void Resize(size_t size);
	void ReserveAtLeast(size_t capacity);
	void Reserve(size_t capacity);
	void Reallocate(size_t capacity, bool shouldCopyData = true);
	void Allocate(size_t capacity);

	template <typename T>
	T GetIterator(size_t) const;

	char* m_pData;
	size_t m_size;
	size_t m_capacity;
};

#include "Iterator.hpp"