#pragma once

#include <string>

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

	void Clear();

	size_t GetLength() const;
	const char* GetData() const;
	CString SubString(size_t start, size_t length = SIZE_MAX) const;

private:
	void Resize(size_t newSize);

	char* m_pData;
	size_t m_size;
};