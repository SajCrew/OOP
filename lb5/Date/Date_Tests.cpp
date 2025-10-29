#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CDate.h"

TEST_CASE("Constructors and basic methods") 
{
    // Конструктор по умолчанию
    CDate def;
    CHECK(def.GetDay() == 1);
    CHECK(def.GetMonth() == Month::JANUARY);
    CHECK(def.GetYear() == 1970);
    CHECK(def.IsValid());

    // Конструктор с параметрами
    CDate date(25, Month::DECEMBER, 2025);
    CHECK(date.GetDay() == 25);
    CHECK(date.GetMonth() == Month::DECEMBER);
    CHECK(date.GetYear() == 2025);
    CHECK(date.IsValid());

    // Конструктор через timestamp
    CDate date2(2);
    CHECK(date2.GetDay() == 3);
    CHECK(date2.GetMonth() == Month::JANUARY);
    CHECK(date2.GetYear() == 1970);
    CHECK(date2.IsValid());

    // Невалидная дата
    CHECK_THROWS(CDate(32, Month::JANUARY, 2023));
}

TEST_CASE("Increment & Decrement")
{
    SECTION("Prefix increment")
    {
        CDate date(31, Month::DECEMBER, 2025);
        CHECK((++date).GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);
        CHECK(date.GetYear() == 2026);
    }
     
    SECTION("Postfix increment")
    {
        CDate date(31, Month::DECEMBER, 2025);
        CHECK((date++).GetDay() == 31);
        CHECK((date++).GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);
        CHECK(date.GetYear() == 2026);
    }

    SECTION("Prefix decrement")
    {
        CDate date(31, Month::DECEMBER, 2025);
        CHECK((--date).GetDay() == 30);
        CHECK(date.GetMonth() == Month::DECEMBER);
        CHECK(date.GetYear() == 2025);
    }

    SECTION("Postfix decrement")
    {
        CDate date3(31, Month::DECEMBER, 2025);
        CHECK((date3--).GetDay() == 31);
        CHECK((date3--).GetDay() == 30);
        CHECK(date3.GetMonth() == Month::DECEMBER);
        CHECK(date3.GetYear() == 2025);
    }  
}

TEST_CASE("Arithmetic operators") 
{
    CDate date(1, Month::JANUARY, 2023);

    // +
    CDate newDate = date + 5;
    CHECK(newDate.GetDay() == 6);
    CHECK(5 + date == newDate);  

    // -
    CHECK((newDate - 5) == date);
    CHECK((newDate - date) == 5);

    // += и -=
    date += 365;
    CHECK(date.GetYear() == 2024);
    date -= 366;
    CHECK(date.GetYear() == 2022);

    SECTION("Overflow cases")
    {
        CDate date1(31, Month::DECEMBER, 9999); 
        CDate date2 = ++date1;
        CHECK(date2.IsValid() == false);
    }
}

TEST_CASE("output operators") 
{
    std::stringstream ss;
    SECTION("Correct dates") 
    {
        CDate date1(1, Month::JANUARY, 1970);
        ss << date1;
        CHECK(ss.str() == "01.01.1970");

        ss.str("");
        CDate date3(7, Month::MARCH, 2023);
        ss << date3;
        CHECK(ss.str() == "07.03.2023");
    } 

    SECTION("Constructor throws for invalid date") 
    {
        CHECK_THROWS_AS(CDate(32, Month::JANUARY, 2023), std::runtime_error);
        CHECK_THROWS_WITH(CDate(32, Month::JANUARY, 2023), "INVALID");
    }
}

TEST_CASE("input operators")
{
    CDate date;
    std::stringstream ss;

    SECTION("Correct dates")
    {   
        ss << "05.06.2005";
        ss >> date;
        CHECK(date.GetDay() == 5);
        CHECK(date.GetMonth() == Month::JUNE);
        CHECK(date.GetYear() == 2005);
        CHECK(date.IsValid());
    }

    SECTION("Edge cases") 
    {
        ss << "31.12.9999";
        ss >> date;
        CHECK(date.IsValid());
        CHECK(date.GetYear() == 9999);
    }
}

TEST_CASE("Leap year handling") 
{

    SECTION("Leap year detection") {
        CHECK(CDate::IsLeapYear(2000) == true);  // Кратно 400
        CHECK(CDate::IsLeapYear(2020) == true);   // Кратно 4, но не 100
        CHECK(CDate::IsLeapYear(1900) == false);   // Кратно 100, но не 400
        CHECK(CDate::IsLeapYear(2021) == false);   // Не кратно 4
    }

    SECTION("February in leap years") 
    {
        // Корректные даты
        CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2020));
        CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2000));

        // Некорректные даты
        CHECK_THROWS(CDate(29, Month::FEBRUARY, 2021));
        CHECK_THROWS(CDate(29, Month::FEBRUARY, 1900));
    }

    SECTION("Date calculations in leap years") {
        // 28.02.2020 -> 29.02.2020
        CDate date1(28, Month::FEBRUARY, 2020);
        CHECK((++date1).GetDay() == 29);
        CHECK(date1.GetMonth() == Month::FEBRUARY);

        // 29.02.2020 -> 01.03.2020
        CHECK((++date1).GetDay() == 1);
        CHECK(date1.GetMonth() == Month::MARCH);

        // 01.01.2020 -> 31.12.2020 = 366 дней (високосный)
        CDate start(1, Month::JANUARY, 2020);
        CDate end(31, Month::DECEMBER, 2020);
        CHECK((end - start) == 365);  // 366 дней между датами, но разница 365
    }

    SECTION("Leap year transitions") {
        // переход через високосный год
        CDate date(31, Month::DECEMBER, 2019);
        CHECK((++date).GetYear() == 2020);  // 2020 - високосный
        CHECK(date.GetDay() == 1);
        CHECK(date.GetMonth() == Month::JANUARY);

        // 365 дней после 01.01.2020 = 31.12.2020 (366-й день)
        CDate date2 = CDate(1, Month::JANUARY, 2020) + 365;
        CHECK(date2.GetDay() == 31);
        CHECK(date2.GetMonth() == Month::DECEMBER);
    }

    SECTION("Year transition with leap years") {
        // 365 дней в 2021
        CDate date1(1, Month::JANUARY, 2021);
        CDate date2 = date1 + 365;
        CHECK(date2.GetDay() == 1);
        CHECK(date2.GetMonth() == Month::JANUARY);
        CHECK(date2.GetYear() == 2022);

        // 366 дней в 2020
        CDate date3(1, Month::JANUARY, 2020);
        CDate date4 = date3 + 366;
        CHECK(date4.GetDay() == 1);
        CHECK(date4.GetMonth() == Month::JANUARY);
        CHECK(date4.GetYear() == 2021);
    }
}