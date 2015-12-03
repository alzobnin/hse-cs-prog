#include "poly.h"
#include <iostream>

int main() {
    typedef int T;
    std::vector<T> coeffs1, coeffs2;
    int n;

    std::cin >> n;
    coeffs1.resize(n + 1);
    for (size_t i = 0; i != coeffs1.size(); ++i)
        std::cin >> coeffs1[coeffs1.size() - i - 1];
    std::cin >> n;
    coeffs2.resize(n + 1);
    for (size_t i = 0; i != coeffs2.size(); ++i)
        std::cin >> coeffs2[coeffs2.size() - i - 1];
    Fraction<T> p(coeffs1, coeffs2);

    std::cin >> n;
    coeffs1.resize(n + 1);
    for (size_t i = 0; i != coeffs1.size(); ++i)
        std::cin >> coeffs1[coeffs1.size() - i - 1];
    std::cin >> n;
    coeffs2.resize(n + 1);
    for (size_t i = 0; i != coeffs2.size(); ++i)
        std::cin >> coeffs2[coeffs2.size() - i - 1];
    Fraction<T> q(coeffs1, coeffs2);

    std::cout << "p(x) = " << p << "\n";
    std::cout << "q(x) = " << q << "\n";

    std::cout << "p == q: " << (p == q) << "\n";
    std::cout << "p != q: " << (p != q) << "\n";

    auto sum = p + q;
    auto diff = p - q;

    std::cout << "(p + q) + (p - q) == 2*p: " << (sum + diff == (p + p)) << "\n";
    std::cout << "(p + q) - (p - q) == 2*q: " << (sum - diff == (q + q)) << "\n";

    auto squares = p*p - q*q;
    std::cout << "p*p - q*q == (p + q) * (p - q): " << (squares == sum * diff) << "\n";
    std::cout << "(p*p - q*q) / (p - q) == p + q: " << (squares / diff == sum) << "\n";

    Fraction<T> unit(1);
    std::cout << "(p / q) * (q / p) == 1: " << ((p / q) * (q / p) == unit) << "\n";
    std::cout << "(p / q) * (p / q) != 1: " << ((p / q) * (p / q) != unit) << "\n";

    (diff -= p) *= -1;
    std::cout << "Testing +=, -= and *=: " << (diff == q) << "\n";
}

