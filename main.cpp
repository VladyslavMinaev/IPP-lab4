#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    const int vectorSize = 10000;
    std::vector<int> numbers(vectorSize);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = 1 + (std::rand() % 50);
    }

    std::vector<unsigned long long> factorials(vectorSize);
    unsigned long long minFactorial = factorial(numbers[0]);
    unsigned long long maxFactorial = minFactorial;
    int minIndex = 0;
    int maxIndex = 0;

#pragma omp parallel for
    for (int i = 0; i < vectorSize; i++) {
        factorials[i] = factorial(numbers[i]);

#pragma omp critical
        {
            if (factorials[i] < minFactorial) {
                minFactorial = factorials[i];
                minIndex = i;
            }
            if (factorials[i] > maxFactorial) {
                maxFactorial = factorials[i];
                maxIndex = i;
            }
        }
    }

    std::cout << "Minimum factorial: " << minFactorial << " at index: " << minIndex << std::endl;
    std::cout << "Maximum factorial: " << maxFactorial << " at index: " << maxIndex << std::endl;

    return 0;
}