#include <iostream>

#include <set>

const int LEFT_END = 0;
const int RIGHT_END = 100000000;

void InputErrors(int argc, char* argv[], const int array)
{
    if (argc != 2)
    {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <upperBound>");
    }

    if (array < LEFT_END || array > RIGHT_END)
    {
        throw std::out_of_range("Upper bound must be between 1 and 100000000");
    }
}

void PrintPrimes(const std::set<int>& primes)
{
    for (int prime : primes)
    {
        std::cout << prime << std::endl;
    }
    std::cout << "Total primes found: " << primes.size() << std::endl;
}

