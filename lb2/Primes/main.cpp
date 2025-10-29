#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include "Utils.h"
#include "ProccesPrimes.h"

//убрать из заголовочных файлов лишние обьявления
int main(int argc, char* argv[])
{
    try {
        int array = std::atoi(argv[1]);
        InputErrors(argc, argv, array);
        std::set<int> primes = GeneratePrimeNumbersSet(array);

        PrintPrimes(primes);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}