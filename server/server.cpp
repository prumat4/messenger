#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

mp::cpp_int factorial(int n) {
    mp::cpp_int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    mp::cpp_int result = factorial(number);

    std::cout << "Factorial of " << number << " is: " << result << std::endl;

    return 0;
}
