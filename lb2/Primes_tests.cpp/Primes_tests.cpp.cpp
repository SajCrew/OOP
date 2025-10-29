#define CATCH_CONFIG_MAIN // Генерация main() для Catch2
#include "catch.hpp" // Подключение заголовочного файла с интерфейсами
#include "../Primes/Utils.h"
#include "../Primes/ProccesPrimes.h"


TEST_CASE("FindPrimeNumbers correctly return array of primes ")
{
    std::vector<bool> isPrime(11, true);
    isPrime = FindPrimeNumbers(10);
    REQUIRE(isPrime[2] == true); // 2 — простое
    REQUIRE(isPrime[4] == false); // 4 — составное
    REQUIRE(isPrime[6] == false); // 6 — составное
    REQUIRE(isPrime[8] == false); // 8 — составное
    REQUIRE(isPrime[10] == false); // 10 — составное
}

TEST_CASE("GeneratePrimeNumbersSet - Basic functionality") {
    SECTION("Primes up to 10") {
        std::set<int> expected = { 2, 3, 5, 7 };
        REQUIRE(GeneratePrimeNumbersSet(10) == expected);
    }

    SECTION("Primes up to 20") {
        std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19 };
        REQUIRE(GeneratePrimeNumbersSet(20) == expected);
    }
}

TEST_CASE("InputErrors - Invalid input") {
    SECTION("Negative number") {
        char* argv[] = { (char*)"program_name", (char*)"-100" };
        REQUIRE_THROWS_AS(InputErrors(2, argv, -100), std::out_of_range);
        REQUIRE_THROWS_WITH(InputErrors(2, argv, -100),
            "Upper bound must be between 1 and 100000000");
    }

    SECTION("Number too large") {
        char* argv[] = { (char*)"program_name", (char*)"100000001" };
        REQUIRE_THROWS_AS(InputErrors(2, argv, 100'000'001), std::out_of_range);
    }

    SECTION("No arguments provided") {
        char* argv[] = { (char*)"program_name" };
        REQUIRE_THROWS_AS(InputErrors(1, argv, 0), std::invalid_argument);
        REQUIRE_THROWS_WITH(InputErrors(1, argv, 0),
            "Usage: program_name <upperBound>");
    }
}

TEST_CASE("GeneratePrimeNumbersSet - Large numbers") {
    SECTION("Primes up to 1'000'000 (check count)") {
        auto primes = GeneratePrimeNumbersSet(1'000'000);
        REQUIRE(primes.size() == 78'498); // Известное количество простых чисел до 1 млн
    }

    SECTION("Primes up to 10'000 (check last prime)") {
        auto primes = GeneratePrimeNumbersSet(10'000);
        REQUIRE(*primes.rbegin() == 9973); // Последнее простое число ≤ 10 000
    }
}

TEST_CASE("GeneratePrimeNumbersSet - Known primes") {
    SECTION("Contains known primes") {
        auto primes = GeneratePrimeNumbersSet(100);
        REQUIRE(primes.count(17)); // 17 — простое
        REQUIRE(primes.count(97)); // 97 — простое
    }

    SECTION("Excludes known non-primes") {
        auto primes = GeneratePrimeNumbersSet(100);
        REQUIRE_FALSE(primes.count(1));  // 1 — не простое
        REQUIRE_FALSE(primes.count(91)); // 91 = 7 × 13
    }
}

TEST_CASE("GeneratePrimeNumbersSet - Invalid input") {
    SECTION("Upper bound is 1 (no primes)") {
        REQUIRE(GeneratePrimeNumbersSet(1).empty());
    }
}