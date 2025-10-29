#include <iostream>
#include <stdexcept>
#include <string>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
private:
    unsigned m_daysSinceEpoch;

    bool m_isValid;
   
    static unsigned DaysInMonth(unsigned m, unsigned year);

    static unsigned DateToDays(unsigned day, Month month, unsigned year);

    static bool IsValidDate(unsigned day, Month month, unsigned year);

    static void DaysToDate(unsigned days, unsigned& day, Month& month, unsigned& year);

public:

    CDate(unsigned day, Month month, unsigned year);

    explicit CDate(unsigned timestamp);

    CDate()
       : m_daysSinceEpoch(0), m_isValid(true) {}

    unsigned GetDay() const;

    Month GetMonth() const;

    unsigned GetYear() const;

    WeekDay GetWeekDay() const;

    bool IsValid() const;

    CDate& operator++();

    CDate& operator--();
 
    CDate operator++(int);
  
    CDate operator--(int);

    CDate& operator+=(int days);

    CDate& operator-=(int days);

    friend CDate operator+(CDate date, int days);

    friend CDate operator+(int days, CDate date);

    friend CDate operator-(CDate date, int days);

    friend int operator-(const CDate& lhs, const CDate& rhs);

    friend std::ostream& operator<<(std::ostream& out, const CDate& date);

    friend std::istream& operator>>(std::istream& is, CDate& date);

    friend bool operator==(const CDate& lhs, const CDate& rhs);

    friend bool operator!=(const CDate& lhs, const CDate& rhs);

    friend bool operator>(const CDate& lhs, const CDate& rhs);

    friend bool operator<(const CDate& lhs, const CDate& rhs);

    friend bool operator>=(const CDate& lhs, const CDate& rhs);

    friend bool operator<=(const CDate& lhs, const CDate& rhs);

    static bool IsLeapYear(unsigned year);

};