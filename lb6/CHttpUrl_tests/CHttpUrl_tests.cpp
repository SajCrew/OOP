#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../HTTP_URL//CHttpUrl.h"

TEST_CASE("Valid HTTP URLs parsing")
{
    SECTION("Simple HTTP URL")
    {
        CHttpUrl url("http://example.com");
        REQUIRE(url.GetURL() == "http://example.com/");
        REQUIRE(url.GetProtocol() == Protocol::HTTP);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetDocument() == "/");
    }

    SECTION("HTTPS with port and document")
    {
        CHttpUrl url("https://example.com:8080/api/data");
        REQUIRE(url.GetURL() == "https://example.com:8080/api/data");
        REQUIRE(url.GetProtocol() == Protocol::HTTPS);
        REQUIRE(url.GetDomain() == "example.com");
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetDocument() == "/api/data");
    }

    SECTION("URL with query parameters")
    {
        CHttpUrl url("http://example.com/search?q=test");
        REQUIRE(url.GetDocument() == "/search?q=test");
    }
}

TEST_CASE("URL construction from parts")
{
    SECTION("Default HTTP port")
    {
        CHttpUrl url("example.com", "/index.html", Protocol::HTTP);
        REQUIRE(url.GetPort() == 80);
        REQUIRE(url.GetURL() == "http://example.com/index.html");
        REQUIRE(url.GetDomain() == "example.com");
    }

    SECTION("Invalid case: empty domain (constr from parts)")
    {    
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("", "/index.html", Protocol::HTTP),
            CUrlParsingError,
            Catch::Matchers::Message("Empty domain")
        );
    }

    SECTION("Invalid case: empty doc (constr from parts)")
    {
        CHttpUrl url("example.com", "", Protocol::HTTP);
        REQUIRE(url.GetDocument() == "/");
    }

    SECTION("Custom HTTPS port")
    {
        CHttpUrl url("example.com", "/", Protocol::HTTPS, 8080);
        REQUIRE(url.GetPort() == 8080);
        REQUIRE(url.GetURL() == "https://example.com:8080/");
    }

    SECTION("Invalid case: empty domain (constr from parts WITH PORT)")
    {       
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("", "/index.html", Protocol::HTTPS, 8080),
            CUrlParsingError,
            Catch::Matchers::Message("Empty domain")
        );
    }

    SECTION("Invalid case: invalid port (constr from parts WITH PORT)")
    {
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("example.com", "/index.html", Protocol::HTTPS, 65536),
            std::invalid_argument,
            Catch::Matchers::Message("Port is out of range")
        );
    }
}

TEST_CASE("Invalid URLs handling")
{
    SECTION("Missing protocol")
    {
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("://example.com"),
            CUrlParsingError,
            Catch::Matchers::Message("Missing protocol")
        );
    }

    SECTION("Empty domain")
    {
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://"),
            CUrlParsingError,
            Catch::Matchers::Message("Empty domain")
        );
    }

    SECTION("invalid domain")
    {
        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://doma!n.com"),
            CUrlParsingError,
            Catch::Matchers::Message("Invalid domain")
        );
    }

    SECTION("Invalid port values")
    {
       /* REQUIRE_THROWS_AS(CHttpUrl("http://example.com:0"), CUrlParsingError); */

        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://example.com:0"),
            CUrlParsingError,
            Catch::Matchers::Message("Port is out of range!!!")
        );

        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://example.com:65536000000"),
            CUrlParsingError,
            Catch::Matchers::Message("Port is out of range!!!")
        );

        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://example.com:80a80"),
            CUrlParsingError,
            Catch::Matchers::Message("Invalid port: contains non-digit characters")
        );

        REQUIRE_THROWS_MATCHES(
            CHttpUrl("http://example.com:abc"),
            CUrlParsingError,
            Catch::Matchers::Message("Invalid port: contains non-digit characters")
        );
    }

    SECTION("Invalid protocols")
    {
        REQUIRE_THROWS_AS(CHttpUrl("ftp://example.com"), CUrlParsingError);
        REQUIRE_THROWS_AS(CHttpUrl("httpx://example.com"), CUrlParsingError);
    }
}

