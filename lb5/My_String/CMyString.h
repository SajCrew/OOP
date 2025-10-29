#include <string>
#include <stdexcept>

class CMyString
{

public:
    // конструктор по умолчанию
    CMyString()
        : m_pChars(&s_emptyString), m_length(0), m_capacity(0)
    {}

    // конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
    CMyString(const char* pString)
        : CMyString(pString, pString ? strlen(pString) : 0)
    {}

    // конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
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

    // конструктор копирования
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

    // перемещающий конструктор
    //  реализуется совместно с перемещающим оператором присваивания 
    CMyString(CMyString&& other) noexcept
        : m_pChars(other.m_pChars),
        m_length(other.m_length),
        m_capacity(other.m_capacity)
    {
        other.m_pChars = &s_emptyString;
        other.m_length = 0;
        other.m_capacity = 0;
    }

    // конструктор, инициализирующий строку данными из 
    // строки стандартной библиотеки C++
    CMyString(const std::string& stlString)
        : CMyString(stlString.data(), stlString.length())
    {}

    // деструктор класса - освобождает память, занимаемую символами строки
    ~CMyString()
    {
        if (m_pChars != &s_emptyString)
            delete[] m_pChars;
    }

    // возвращает длину строки (без учета завершающего нулевого символа)
    size_t GetLength() const;

    // возвращает указатель на массив символов строки.
    // В конце массива обязательно должен быть завершающий нулевой символ
    // даже если строка пустая 
    const char* GetStringData() const;

    // возвращает подстроку с заданной позиции длиной не больше length символов
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    // очистка строки (строка становится снова нулевой длины)
    void Clear();

    // Возвращает вместимость строки
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
