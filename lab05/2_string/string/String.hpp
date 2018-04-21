#pragma once

#include <string>
#include <iostream>

class CString
{
public:
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

private:
	void Resize(size_t size);
	void Reserve(size_t capacity);
	void ReserveAtLeast(size_t capacity);

	char* m_pData;
	size_t m_size;
	size_t m_capacity;
};