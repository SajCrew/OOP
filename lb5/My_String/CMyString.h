#include <string>
#include <stdexcept>

class CMyString
{

public:
    // ����������� �� ���������
    CMyString()
        : m_pChars(&s_emptyString), m_length(0), m_capacity(0)
    {}

    // �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
    CMyString(const char* pString)
        : CMyString(pString, pString ? strlen(pString) : 0)
    {}

    // �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
    CMyString(const char* pString, size_t length)
        : m_length(length), m_capacity(length)
    {
        if (length == 0)
        {
            m_pChars = &s_emptyString;
            m_capacity = 0;
        }
        else
        {
            m_pChars = new char[m_capacity + 1]; //+/0
            if (pString)
                memcpy(m_pChars, pString, length);
            m_pChars[length] = '\0';
        }
    }

    // ����������� �����������
    CMyString(const CMyString& other)
        : m_length(other.m_length), m_capacity(other.m_length)
    {
        if (m_length == 0)
        {
            m_pChars = &s_emptyString;
            m_capacity = 0;
        }
        else
        {
            m_pChars = new char[m_capacity + 1];
            memcpy(m_pChars, other.m_pChars, m_length);
            m_pChars[m_length] = '\0';
        }
    };

    // ������������ �����������
    //  ����������� ��������� � ������������ ���������� ������������ 
    CMyString(CMyString&& other) noexcept
        : m_pChars(other.m_pChars),
        m_length(other.m_length),
        m_capacity(other.m_capacity)
    {
        other.m_pChars = &s_emptyString;
        other.m_length = 0;
        other.m_capacity = 0;
    }

    // �����������, ���������������� ������ ������� �� 
    // ������ ����������� ���������� C++
    CMyString(const std::string& stlString)
        : CMyString(stlString.data(), stlString.length())
    {}

    // ���������� ������ - ����������� ������, ���������� ��������� ������
    ~CMyString()
    {
        if (m_pChars != &s_emptyString)
            delete[] m_pChars;
    }

    // ���������� ����� ������ (��� ����� ������������ �������� �������)
    size_t GetLength() const;

    // ���������� ��������� �� ������ �������� ������.
    // � ����� ������� ����������� ������ ���� ����������� ������� ������
    // ���� ���� ������ ������ 
    const char* GetStringData() const;

    // ���������� ��������� � �������� ������� ������ �� ������ length ��������
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    // ������� ������ (������ ���������� ����� ������� �����)
    void Clear();

    // ���������� ����������� ������
    size_t GetCapacity();

    CMyString& operator=(const CMyString& other);

    CMyString& operator+=(const CMyString& other);

    CMyString operator+(const CMyString& other) const;

    bool operator==(const CMyString& other) const;

    bool operator<(const CMyString& other) const;

    bool operator>(const CMyString& other) const;

    bool operator<=(const CMyString& other) const;

    bool operator>=(const CMyString& other) const;

    char& operator[](size_t index);

    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const CMyString& str);

    friend std::istream& operator>>(std::istream& is, CMyString& str);

    friend CMyString operator+(const char* lhs, const CMyString& rhs);

    friend CMyString operator+(const std::string& lhs, const CMyString rhs);

    private:
        char* m_pChars;
        size_t m_length;
        size_t m_capacity;
        static char s_emptyString;
        void Reallocate(size_t newCapacity);
};
