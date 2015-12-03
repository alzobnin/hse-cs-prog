#include "poly.h"
#include <vector>
#include <iostream>

int main() {
    typedef int T;
    std::vector<T> coeffs;
    int n;

    std::cin >> n;
    coeffs.resize(n + 1);
    for (size_t i = 0; i != coeffs.size(); ++i)
        std::cin >> coeffs[coeffs.size() - i - 1];
    SparsePolynomial<T> p(coeffs);

    std::cin >> n;
    coeffs.resize(n + 1);
    for (size_t i = 0; i != coeffs.size(); ++i)
        std::cin >> coeffs[coeffs.size() - i - 1];
    SparsePolynomial<T> q(coeffs);

    std::cout << "p(x) = " << p << "\n";
    std::cout << "q(x) = " << q << "\n";

    std::cout << "deg p = " << p.Degree() << "\n";
    std::cout << "deg q = " << q.Degree() << "\n";

    std::cout << "Some coeffs of p: " << p[0] << " " << p[1] << " " << p[2] << " " << p[10] << "\n";
    std::cout << "Some coeffs of q: " << q[0] << " " << q[1] << " " << q[2] << " " << q[10] << "\n";

    std::cout << "p(x) + q(x) = " << (p + q) << "\n";
    std::cout << "p(x) - q(x) = " << (p - q) << "\n";
    std::cout << "p(x) * q(x) = " << (p * q) << "\n";
    std::cout << "p(x) / q(x) = " << (p / q) << "\n";
    std::cout << "p(x) % q(x) = " << (p % q) << "\n";
    std::cout << "gcd(p, q) = " << (p, q) << "\n";

    std::cout << "p(0) = " << p(0) << "\n";
    std::cout << "p(1) = " << p(1) << "\n";
    std::cout << "p(3) = " << p(3) << "\n";
    std::cout << "p(-2) = " << p(-2) << "\n";
    std::cout << "q(0) = " << q(0) << "\n";
    std::cout << "q(1) = " << q(1) << "\n";
    std::cout << "q(3) = " << q(3) << "\n";
    std::cout << "q(-2) = " << q(-2) << "\n";

    auto f = p - q;
    (f -=p );
    f *= -1;
    std::cout << "Testing +=, -=, *=, == and !=: " << (f == q) << " " << (f != q) << " " << (f - q == 0) << "\n";
}

