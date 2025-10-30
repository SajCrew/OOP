#include <vector>
#include <cmath>
#include "Utils.h"

const int MIN_PRIME = 2;

void SetPrimeElem(int prime, const int upperbound, std::vector<bool>& isPrime)
{
    for (int multiple = prime * prime; multiple <= upperbound; multiple += prime) {
        isPrime[multiple] = false;
    }
}
std::vector<bool>FindPrimeNumbers(const int upperbound) //array => upperbound
{
    std::vector<bool> isPrime(upperbound + 1, true);
    if (upperbound >= 1) isPrime[1] = false;
    if (upperbound >= MIN_PRIME) {
        for (int even = MIN_PRIME * 2; even <= upperbound; even += MIN_PRIME) {
            isPrime[even] = false;
        }
    }
    for (int num = 3; num * num <= upperbound; num += 2) {
        if (isPrime[num]) {
            SetPrimeElem(num, upperbound, isPrime);
        }
    }
    return isPrime;
}

std::set<int>ToPrimes(int array, std::set<int>& primes, std::vector<bool>& isPrime)
{
    for (int arrElem = MIN_PRIME; arrElem <= array; ++arrElem)
    {
        if (isPrime[arrElem])
        {
            primes.insert(arrElem);
        }
    }
    return primes;
}

std::set<int> GeneratePrimeNumbersSet(int upperbound)
{
    std::set<int> primes;

    std::vector<bool> isPrime = FindPrimeNumbers(upperbound);

    ToPrimes(upperbound, primes, isPrime);

    return primes;
}
