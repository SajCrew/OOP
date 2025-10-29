#include "CDate.h"
#include <string>

const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;

CDate::CDate(unsigned day, Month month, unsigned year)
{
    m_isValid = IsValidDate(day, month, year);
    if (m_isValid)
    {
        m_daysSinceEpoch = DateToDays(day, month, year);
    }
    else
    {
        m_daysSinceEpoch = 0;
        throw std::runtime_error("INVALID");
    }
}

CDate::CDate(unsigned timestamp)
{
    unsigned day;
    Month month;
    unsigned year;
    DaysToDate(timestamp, day, month, year);
    m_isValid = IsValidDate(day, month, year);
    if (m_isValid)
    {
        m_daysSinceEpoch = timestamp;
    }
    else
    {
        m_daysSinceEpoch = 0;
        throw std::runtime_error("INVALID");
    }
}

bool CDate::IsLeapYear(unsigned year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::DaysInMonth(unsigned m, unsigned year)
{
    if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12))
        return 31;

    if ((m == 4) || (m == 6) || (m == 9) || (m == 11))
        return 30;

    if (m == 2)
        return (IsLeapYear(year)) ? 29 : 28;

    return 0;
}

//добавить логику с високосными годами
unsigned CDate::DateToDays(unsigned day, Month month, unsigned year)
{
    if (year < 1970 || year > 9999)
        return 0;

    unsigned m = static_cast<unsigned>(month);
    if (m < 1 || m > 12)
        return 0;

    // Вычисляем количество дней с 1 января 1970 года до 1 января текущего года
    unsigned yearsPassed = year - 1970;
    unsigned leapYears = (yearsPassed + 1) / 4 - (yearsPassed + 69) / 100 + (yearsPassed + 369) / 400;
    unsigned totalDays = yearsPassed * 365 + leapYears;

    // Добавляем дни за месяцы текущего года
    static const unsigned daysUpToMonth[13] = 
    {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
    };
    totalDays += daysUpToMonth[m - 1];
    if (m > 2 && IsLeapYear(year))
        totalDays += 1;

    // Добавляем дни текущего месяца
    totalDays += day - 1;

    return totalDays;
}

bool CDate::IsValidDate(unsigned day, Month month, unsigned year)
{
    if (year < MIN_YEAR || year > MAX_YEAR)
        return false;

    unsigned m = static_cast<unsigned>(month);
    if (m < MIN_MONTH || m > MAX_MONTH)
        return false;

    unsigned daysInMonth = DaysInMonth(m, year);
    return day >= 1 && day <= daysInMonth;
}

unsigned CountLeapYears(unsigned startYear, unsigned endYear)
{
    return (endYear - 1) / 4 - (endYear - 1) / 100 + (endYear - 1) / 400
        - (startYear - 1) / 4 + (startYear - 1) / 100 - (startYear - 1) / 400;
}

void CDate::DaysToDate(unsigned days, unsigned& day, Month& month, unsigned& year)
{
    if (days > 365 * (9999 - 1970 + 1) + 2424) // проверка на переполнение (2424 високосных дней)
    {
        day = 0;
        month = Month::JANUARY;
        year = 0;
        return;
    }

    // вычисляем год без цикла по формуле
    year = 1970 + days / 366; // нач приближение
    while (days >= (year - 1970) * 365 + CountLeapYears(1970, year))
    {
        year++;
    }
    year--;
    days -= (year - 1970) * 365 + CountLeapYears(1970, year);

    // вычисляем месяц
    static const unsigned daysUpToMonth[13] = 
    {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
    };
    unsigned m = 1;
    unsigned daysInMonth = daysUpToMonth[m] - daysUpToMonth[m - 1];
    if (m == 2 && IsLeapYear(year))
        daysInMonth += 1;

    while (days >= daysInMonth)
    {
        days -= daysInMonth;
        m++;
        daysInMonth = daysUpToMonth[m] - daysUpToMonth[m - 1];
        if (m == 2 && IsLeapYear(year))
            daysInMonth += 1;
    }
    month = static_cast<Month>(m);

    // Вычисляем день
    day = days + 1;
}



unsigned CDate::GetDay() const
{
    if (m_isValid)
    {
        unsigned day;
        Month month;
        unsigned year;
        DaysToDate(m_daysSinceEpoch, day, month, year);
        return day;
    }
    else
        return 0;
}

Month CDate::GetMonth() const
{
    if (m_isValid)
    {
        unsigned day;
        Month month;
        unsigned year;
        DaysToDate(m_daysSinceEpoch, day, month, year);
        return month;
    }
    else
        return Month::JANUARY;
}

unsigned CDate::GetYear() const
{
    if (m_isValid)
    {
        unsigned day;
        Month month;
        unsigned year;
        DaysToDate(m_daysSinceEpoch, day, month, year);
        return year;
    }
    else
        return 0;
}

WeekDay CDate::GetWeekDay() const
{
    if (m_isValid)
        return static_cast<WeekDay>((m_daysSinceEpoch + 4) % 7);
    else
        return WeekDay::SUNDAY;
}

bool CDate::IsValid() const
{
    return m_isValid;
}

//префикс инк
CDate& CDate::operator++()
{
    if (m_isValid)
    {
        if (m_daysSinceEpoch + 1 > DateToDays(31, Month::DECEMBER, 9999))
        {
            m_isValid = false;
        }
        else
        {
            ++m_daysSinceEpoch;
        }
    }
    return *this;
}
//префикс декрем
CDate& CDate::operator--()
{
    if (m_isValid)
    {
        if (m_daysSinceEpoch == 0)
        {
            m_isValid = false;
        }
        else
        {
            --m_daysSinceEpoch;
        }
    }
    return *this;
}

//постфикс инк
CDate CDate::operator++(int)
{
    CDate temp = *this;
    ++(*this);
    return temp;
}

// Постфиксный декремент
CDate CDate::operator--(int)
{
    CDate temp = *this;
    --(*this);
    return temp;
}

CDate& CDate::operator+=(int days)
{
    if (m_isValid)
    {
        if (days >= 0)
        {
            if (m_daysSinceEpoch + days > DateToDays(31, Month::DECEMBER, 9999))
            {
                m_isValid = false;
            }
            else
            {
                m_daysSinceEpoch += days;
            }
        }
        else
        {
            *this -= -days;
        }
    }
    return *this;
}

CDate& CDate::operator-=(int days)
{
    if (m_isValid)
    {
        if (days >= 0)
        {
            if (m_daysSinceEpoch < days)
            {
                m_isValid = false;
            }
            else
            {
                m_daysSinceEpoch -= days;
            }
        }
        else
        {
            *this += -days;
        }
    }
    return *this;
}

CDate operator+(CDate date, int days)
{
    date += days;
    return date;
}

CDate operator+(int days, CDate date)
{
    date += days;
    return date;
}

CDate operator-(CDate date, int days)
{
    date -= days;
    return date;
}

int operator-(const CDate& lhs, const CDate& rhs)
{
    if (!lhs.m_isValid || !rhs.m_isValid)
        return 0;
    return lhs.m_daysSinceEpoch - rhs.m_daysSinceEpoch;
}

std::ostream& operator<<(std::ostream& out, const CDate& date)
{
    if (!date.m_isValid)
        out << "INVALID";
    else
    {
        out << (date.GetDay() < 10 ? "0" : "") << date.GetDay() << "."
            << (static_cast<unsigned>(date.GetMonth()) < 10 ? "0" : "") << static_cast<unsigned>(date.GetMonth())
            << "." << date.GetYear();
    }
    return out;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
    unsigned day, month, year;
    char sep1, sep2;
    if (is >> day >> sep1 >> month >> sep2 >> year && sep1 == '.' && sep2 == '.')
    {
        try
        {
            date = CDate(day, static_cast<Month>(month), year);
        }
        catch (std::exception& e)
        {
            date = CDate();
            is.setstate(std::ios::failbit);
        }
    }
    else
    {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        date = CDate();
        is.setstate(std::ios::failbit);
        return is;
    }
}

bool operator==(const CDate& lhs, const CDate& rhs)
{
    return lhs.m_isValid == rhs.m_isValid && lhs.m_daysSinceEpoch == rhs.m_daysSinceEpoch;
}

bool operator!=(const CDate& lhs, const CDate& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const CDate& lhs, const CDate& rhs)
{
    if (!lhs.m_isValid || !rhs.m_isValid)
        return false;
    return lhs.m_daysSinceEpoch > rhs.m_daysSinceEpoch;
}

bool operator<(const CDate& lhs, const CDate& rhs)
{
    if (!lhs.m_isValid || !rhs.m_isValid)
        return false;
    return lhs.m_daysSinceEpoch < rhs.m_daysSinceEpoch;
}

bool operator>=(const CDate& lhs, const CDate& rhs)
{
    return !(lhs < rhs);
}

bool operator<=(const CDate& lhs, const CDate& rhs)
{
    return !(lhs > rhs);
}