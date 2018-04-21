#include "String.hpp"
#include <algorithm>
#include <cstring>

CString::CString()
	: CString(nullptr, 0)
{
}

CString::CString(const char* pString)
	: CString(pString, std::strlen(pString))
{
}

CString::CString(const char* pString, size_t length)
	: m_pData(nullptr)
{
	Resize(length + 1);
	if (pString)
	{
		std::memcpy(m_pData, pString, m_size);
	}
}

CString::CString(const CString& other)
{
	*this = other;
}

CString::CString(CString&& other)
	: CString()
{
	*this = std::move(other);
}

CString::CString(const std::string& stlString)
	: CString(stlString.c_str(), stlString.size())
{
}

CString::~CString()
{
	delete[] m_pData;
}

CString& CString::operator=(const CString& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Resize(rhs.GetLength() + 1);
	std::memcpy(m_pData, rhs.GetData(), rhs.GetLength());
	return *this;
}

CString& CString::operator=(CString&& rhs)
{
	std::swap(m_pData, rhs.m_pData);
	std::swap(m_size, rhs.m_size);
	return *this;
}

void CString::Clear()
{
	Resize(1);
}

size_t CString::GetLength() const
{
	return m_size - 1;
}

const char* CString::GetData() const
{
	return m_pData;
}

CString CString::SubString(size_t start, size_t length) const
{
	start = std::min(start, m_size);
	length = std::min(length, m_size - 1 - start);
	return CString(m_pData + start, length);
}

void CString::Resize(size_t newSize)
{
	auto newPData = new char[newSize];

	if (m_pData)
	{
		std::memcpy(newPData, m_pData, std::min(m_size, newSize));
		delete[] m_pData;
	}

	newPData[newSize - 1] = '\0';
	m_pData = newPData;
	m_size = newSize;
}
