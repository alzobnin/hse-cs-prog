#include "poly.h"
#include <vector>
#include <iostream>

int main() {
    constexpr int N = 3;
    typedef std::array<int, N> Monomial;
    Monomial mon;

    typedef int T;
    std::map<Monomial, T> coeffs;
    int n;

    std::cin >> n;
    while (n-->0) {
        for (size_t i = 0; i != N; ++i)
            std::cin >> mon[i];
        std::cin >> coeffs[mon];
    }
    MultivariatePolynomial<T, N> p(coeffs);

    coeffs.clear();
    std::cin >> n;
    while (n-->0) {
        for (size_t i = 0; i != N; ++i)
            std::cin >> mon[i];
        std::cin >> coeffs[mon];
    }
    MultivariatePolynomial<T, N> q(coeffs);

    std::cout << "p(x) = " << p << "\n";
    std::cout << "q(x) = " << q << "\n";

    std::cout << "deg p = " << p.Degree() << "\n";
    std::cout << "deg q = " << q.Degree() << "\n";

    std::cout << "p(x) + q(x) = " << (p + q) << "\n";
    std::cout << "p(x) - q(x) = " << (p - q) << "\n";
    std::cout << "p(x) * q(x) = " << (p * q) << "\n";

    Monomial x;
    for (size_t i = 0; i != N; ++i)
        x[i] = 0;
    std::cout << "p(0,...,0) = " << p(x) << "\n";
    std::cout << "q(0,...,0) = " << q(x) << "\n";

    for (size_t i = 0; i != N; ++i)
        x[i] = i + 1;
    std::cout << "p(1,...,n) = " << p(x) << "\n";
    std::cout << "q(1,...,n) = " << q(x) << "\n";

    auto f = p - q;
    (f -=p );
    f *= -1;
    std::cout << "Testing +=, -=, *=, == and !=: " << (f == q) << " " << (f != q) << " " << (f - q == 0) << "\n";
}

