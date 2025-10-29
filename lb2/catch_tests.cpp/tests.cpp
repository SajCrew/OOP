#define CATCH_CONFIG_MAIN // Генерация main() для Catch2
#include "catch.hpp" // Подключение заголовочного файла с интерфейсами
#include "Decode/get_html_entities.h"
#include "Decode/html_utils.h"
#include "Decode/html_decode.h"


TEST_CASE("GetHtmlEntities returns correct map", "[GetHtmlEntities]")
{
    auto htmlEntities = GetHtmlEntities();

    SECTION("Check size of the map")
    {
        REQUIRE(htmlEntities.size() == 5);
    }

    SECTION("Check individual entities")
    {
        REQUIRE(htmlEntities.at("&quot;") == '"');
        REQUIRE(htmlEntities.at("&apos;") == '\'');
        REQUIRE(htmlEntities.at("&lt;") == '<');
        REQUIRE(htmlEntities.at("&gt;") == '>');
        REQUIRE(htmlEntities.at("&amp;") == '&');
    }
}

TEST_CASE("TryDecodeHtmlEntity correctly decodes entities", "[TryDecodeHtmlEntity]")
{
    char decodedChar;
    size_t entityLength;
    auto htmlEntities = GetHtmlEntities();

    SECTION("Valid entities")
    {
        REQUIRE(TryDecodeHtmlEntity("&quot;", 0, htmlEntities, decodedChar, entityLength) == true);
        REQUIRE(decodedChar == '"');
        REQUIRE(entityLength == 6);

        REQUIRE(TryDecodeHtmlEntity("&amp;", 0, htmlEntities, decodedChar, entityLength) == true);
        REQUIRE(decodedChar == '&');
        REQUIRE(entityLength == 5);
    }

    SECTION("Invalid entities")
    {
        REQUIRE(TryDecodeHtmlEntity("&unknown;", 0, htmlEntities, decodedChar, entityLength) == false);
        REQUIRE(TryDecodeHtmlEntity("Hello", 0, htmlEntities, decodedChar, entityLength) == false);
    }

    SECTION("Partial match")
    {
        REQUIRE(TryDecodeHtmlEntity("&ampersand;", 0, htmlEntities, decodedChar, entityLength) == false);
    }
}

TEST_CASE("HtmlDecode correctly decodes HTML entities", "[HtmlDecode]")
{
    SECTION("Decode basic entities")
    {
        REQUIRE(HtmlDecode("&quot;Hello&quot;") == "\"Hello\"");
        REQUIRE(HtmlDecode("&apos;World&apos;") == "'World'");
        REQUIRE(HtmlDecode("&lt;tag&gt;") == "<tag>");
        REQUIRE(HtmlDecode("&gt;tag&lt;") == ">tag<");
        REQUIRE(HtmlDecode("&amp;") == "&");
    }

    SECTION("Decode multiple entities in one string")
    {
        REQUIRE(HtmlDecode("&lt;&quot;&amp;&quot;&gt;") == "<\"&\">");
        REQUIRE(HtmlDecode("&amp;&amp;&amp;") == "&&&");
    }

    SECTION("Ignore unknown entities")
    {
        REQUIRE(HtmlDecode("&unknown;") == "&unknown;");
        REQUIRE(HtmlDecode("Hello &world;") == "Hello &world;");
    }

    SECTION("Empty string")
    {
        REQUIRE(HtmlDecode("") == "");
    }

    SECTION("String without entities")
    {
        REQUIRE(HtmlDecode("Hello, World!") == "Hello, World!");
    }
}

TEST_CASE("PrintDecode outputs decoded string", "[PrintDecode]")
{
    SECTION("Output decoded string")
    {
        // Перенаправляем вывод в строку для проверки
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        PrintDecode("Hello, World!");

        std::cout.rdbuf(old); // Восстанавливаем стандартный вывод

        REQUIRE(buffer.str() == "Hello, World!\n");
    }
}