//Конструкторы: по умолчанию, копирования и перемещения
//Операторы присваивания(копирующий и перемещающий)
//Деструктор
//Добавление строки в начало и в конец списка(за время O(1))
//Узнать количество элементов(за время O(1)), а также узнать пуст список или нет
//Удалить все элементы из списка(за время О(N) с использованием памяти O(1) в области стека)
//Вставка элемента в позицию, задаваемую итератором(за время О(1))
//Удаление элемента в позиции, задаваемой итератором(за время О(1))
//Получение итераторов, указывающих на начало списка и его конец(константные и некостантные), совместимых со алгоритмами STL и range - based for
//Реверсированные итераторы(константные и неконстантные)

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CStringList.h"

TEST_CASE("Default constructor creates empty list") 
{
    CStringList list;
    REQUIRE(list.GetSize() == 0);
    REQUIRE(list.IsEmpty());
    REQUIRE(list.begin() == list.end());
}

TEST_CASE("PushBack and PushFront") 
{
    CStringList list;
    SECTION("Pushback adds to end")
    {
        list.PushBack("first");
        REQUIRE(list.GetSize() == 1);
        REQUIRE(*list.begin() == "first");

        list.PushBack("second");
        REQUIRE(list.GetSize() == 2);
        REQUIRE(*--list.end() == "second");

        list.PushBack("third");
        REQUIRE(list.GetSize() == 3);
        REQUIRE(*--list.end() == "third");
    }

    SECTION("PushFront adds to beginning") 
    {
        list.PushFront("first");
        REQUIRE(*list.begin() == "first");

        list.PushFront("second");
        REQUIRE(*list.begin() == "second");
        REQUIRE(*++list.begin() == "first");
    }
}

TEST_CASE("Copy constructor/assignment") 
{
    CStringList original;
    original.PushBack("one");
    original.PushBack("two");

    SECTION("Copy constructor") 
    {
        CStringList copy(original);
        REQUIRE(copy.GetSize() == 2);
        REQUIRE(*copy.begin() == "one");
        REQUIRE(*++copy.begin() == "two");
    }

    SECTION("Copy assignment") 
    {
        CStringList copy;
        copy = original;
        REQUIRE(copy.GetSize() == 2);
        REQUIRE(*copy.begin() == "one");
        REQUIRE(*++copy.begin() == "two");
    }

    SECTION("Self-assignment") 
    {
        original = original;
        REQUIRE(original.GetSize() == 2);
    }
}

TEST_CASE("Move constructor/assignment") 
{
    CStringList original;
    original.PushBack("one");
    original.PushBack("two");

    SECTION("Move constructor") 
    {
        CStringList moved(std::move(original));
        REQUIRE(moved.GetSize() == 2);
        REQUIRE(original.GetSize() == 0);
    }

    SECTION("Move assignment") 
    {
        CStringList moved;
        moved = std::move(original);
        REQUIRE(moved.GetSize() == 2);
        REQUIRE(original.GetSize() == 0);
    }
}

TEST_CASE("Insert/Erase operations") 
{
    CStringList list;
    list.PushBack("first");
    list.PushBack("third");

    SECTION("Insert in middle") 
    {
        auto it = list.Insert(++list.begin(), "second");
        REQUIRE(list.GetSize() == 3);
        REQUIRE(*it == "second");
        REQUIRE(*++it == "third");
    }

    SECTION("Insert at begin/end") 
    {
        list.Insert(list.begin(), "zero");
        list.Insert(list.end(), "fourth");
        REQUIRE(list.GetSize() == 4);
        REQUIRE(*list.begin() == "zero");
        REQUIRE(*--list.end() == "fourth");
    }

    SECTION("Erase elements") 
    {
        auto it = list.Erase(list.begin());
        REQUIRE(list.GetSize() == 1);
        REQUIRE(*it == "third");

        it = list.Erase(list.begin());
        REQUIRE(list.IsEmpty());
        REQUIRE(it == list.end());
    }
}

TEST_CASE("Iterator functionality") 
{
    CStringList list;
    list.PushBack("one");
    list.PushBack("two");
    list.PushBack("three");

    SECTION("Forward iteration") 
    {
        auto it = list.begin();
        REQUIRE(*it == "one");
        REQUIRE(*++it == "two");
        REQUIRE(*++it == "three");
        REQUIRE(++it == list.end());
    }

    SECTION("Reverse iteration") 
    {
        auto rit = list.rbegin();
        REQUIRE(*rit == "three");
        REQUIRE(*++rit == "two");
        REQUIRE(*++rit == "one");
        REQUIRE(++rit == list.rend());
    }

    SECTION("Range-based for loop") 
    {
        std::vector<std::string> result;
        for (const auto& str : list) 
        {
            result.push_back(str);
        }
        REQUIRE(result == std::vector<std::string>{"one", "two", "three"});
    }

    SECTION("STL algorithms compatibility") 
    {
        CStringList list;
        list.PushBack("apple");
        list.PushBack("banana");
        list.PushBack("cherry");

        // Проверка std::find
        auto it = std::find(list.begin(), list.end(), "banana");
        REQUIRE(it != list.end());
        REQUIRE(*it == "banana");

        // Проверка std::count
        size_t count = std::count(list.begin(), list.end(), "apple");
        REQUIRE(count == 1);

        // Проверка std::for_each
        std::string concatenated;
        std::for_each(list.begin(), list.end(), [&](const std::string& s) 
            {
              concatenated += s + " ";
            });
        REQUIRE(concatenated == "apple banana cherry ");

        // Проверка std::copy
        std::vector<std::string> vec;
        std::copy(list.begin(), list.end(), std::back_inserter(vec));
        REQUIRE(vec == std::vector<std::string>{"apple", "banana", "cherry"});
    }
}

TEST_CASE("Exception safety") 
{
    SECTION("Invalid iterator access") 
    {
        CStringList list;
        list.PushBack("test");

        REQUIRE_THROWS_AS(*list.end(), std::out_of_range);
        REQUIRE_THROWS_AS(++list.end(), std::out_of_range);
        REQUIRE_THROWS_AS(--list.begin(), std::out_of_range);
    }

    SECTION("Iterator dereference exceptions") 
    {
        CStringList list;
        list.PushBack("test");

        SECTION("Dereference end iterator") 
        {
            auto it = list.end();
            REQUIRE_THROWS_AS(*it, std::out_of_range);
            REQUIRE_THROWS_WITH(*it, "Dereferencing end iterator");
        }

        SECTION("Arrow operator on end iterator") 
        {
            auto it = list.end();
            REQUIRE_THROWS_AS(it->empty(), std::out_of_range);
            REQUIRE_THROWS_WITH(it->empty(), "Accessing end iterator");
            REQUIRE_THROWS_WITH(++it, "Incrementing end iterator");
        }
    }
}

