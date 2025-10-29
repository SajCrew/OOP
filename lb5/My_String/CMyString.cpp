#include "catch.hpp"
#include "CMyString.h"

char CMyString::s_emptyString = '\0';

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
    os.write(str.GetStringData(), str.GetLength());
    return os;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
    str.Clear();
    char buffer[1024];

    while (is.get(buffer, sizeof(buffer)))
    {
        size_t readCount = is.gcount();
        str += CMyString(buffer, readCount);

        if (is.peek() == EOF)
            break;
    }

    return is;
}

size_t CMyString::GetLength() const
{
    return m_length;
}

const char* CMyString::GetStringData() const
{
    return m_pChars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    if (start >= m_length)
        return CMyString();

    size_t actualLength = std::min(length, m_length - start);
    return CMyString(m_pChars + start, actualLength);
}

void CMyString::Clear()
{
    if (m_pChars != &s_emptyString)
        delete[] m_pChars;

    m_pChars = &s_emptyString;
    m_length = 0;
    m_capacity = 0;
}

size_t CMyString::GetCapacity()
{
    return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& other)
{
    if (this == &other)
        return *this;

    if (other.m_length == 0)
    {
        Clear();
        return *this;
    }

    if (m_capacity >= other.m_length)
    {
        m_length = other.m_length;
        memcpy(m_pChars, other.m_pChars, m_length);
        m_pChars[m_length] = '\0';
    }
    else
    {
        if (m_pChars != &s_emptyString)
            delete[] m_pChars;

        m_length = other.m_length;
        m_capacity = other.m_length;
        m_pChars = new char[m_capacity + 1];
        memcpy(m_pChars, other.m_pChars, m_length);
        m_pChars[m_length] = '\0';
    }

    return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
    if (other.m_length == 0)
        return *this;

    size_t newLength = m_length + other.m_length;
    if (newLength > m_capacity)
    {
        size_t newCapacity = std::max(m_capacity * 2, newLength);
        Reallocate(newCapacity);
    }

    memcpy(m_pChars + m_length, other.m_pChars, other.m_length);
    m_length = newLength;
    m_pChars[m_length] = '\0';

    return *this;
}

CMyString CMyString::operator+(const CMyString& other) const
{
    CMyString result(*this);
    result += other;
    return result;
}

bool CMyString::operator==(const CMyString& other) const
{
    if (m_length != other.m_length)
        return false;

    return memcmp(m_pChars, other.m_pChars, m_length) == 0;
}

bool CMyString::operator<(const CMyString& other) const
{
    size_t minLength = std::min(m_length, other.m_length);
    int cmpResult = memcmp(m_pChars, other.m_pChars, minLength);

    if (cmpResult < 0) return true;
    if (cmpResult > 0) return true;
    return (m_length < other.m_length);
}

bool CMyString::operator>(const CMyString& other) const
{
    return other < *this;
}

bool CMyString::operator<=(const CMyString& other) const
{
    return !(*this > other);
}
bool CMyString::operator>=(const CMyString& other) const
{
    return !(*this < other);
}

char& CMyString::operator[](size_t index)
{
    if (index >= m_length)
        throw std::out_of_range("Index out of range");

    return m_pChars[index];
}

const char& CMyString::operator[](size_t index) const
{
    if (index >= m_length)
        throw std::out_of_range("Index out of range");

    return m_pChars[index];
}

CMyString operator+(const char* lhs, const CMyString& rhs)
{
    return CMyString(lhs) + rhs;
}

CMyString operator+(const std::string& lhs, const CMyString rhs)
{
    return CMyString(lhs) + rhs;
}

void CMyString::Reallocate(size_t newCapacity)
{
    if (newCapacity <= m_capacity)
        return;

    char* newData = new char[newCapacity + 1];
    if (m_length > 0)
        memcpy(newData, m_pChars, m_length);
    newData[m_length] = '\0';

    if (m_pChars != &s_emptyString)
        delete[] m_pChars;

    m_pChars = newData;
    m_capacity = newCapacity;
}