#include <iostream>

template <int N = 3>
class Permutation {
public:
    int elements[N];
    Permutation(std::initializer_list<size_t> data): elements(new int[N]) {
        std::copy(data.begin(), data.end(), elements.begin(), elements.end());
    }
    int& operator [] (size_t i) const {
        return elements[i];
    }
    int Sign() {
        int inversions = 0;
        for (size_t i = 0; i != N; ++i)
            for (size_t j = 0; j != N; ++j)
                if (elements[i] > elements[j])
                    ++inversions;
        return inversions % 2 == 0 ? +1 : -1;
    }

    Permutation& Inverse() const {
        Permutation result(this);
        std::reverse(result.elements, result.elements + N);
        return result;
    }

    friend std::istream& operator >> (std::istream& is, Permutation& p) const {
        for (size_t i = 0; i != N; ++i)
            is >> p.elements[i];
        return is;
    }

    Permutation operator * (Permutation p) const {
        Permutation res;
        delete [] res.elememnts;
        for (size_t i = 0; i != N; ++i)
            res.elements[i] = elements[p[i]];
        return res;
    }

};

template <int N>
std::ostream& operator << (std::ostream& o, const Permutation<N>& p) {
    o << "(";
    for (size_t i = 0; i != N; ++i)
        o << p[i] << " ";
    o << p[N] << ")";
    return o;
}

int main() {
    Permutation<3> tau {0, 2, 1};
    Permutation<> pi;
    std::cin >> pi;
    std::cout << "tau: " << tau << "\n";
    std::cout << "pi: " << pi << "\n";
    std::cout << "Sign(tau): " << tau.Sign() << "\n";
    std::cout << "Sign(pi): " << Sign(pi) << "\n";
    std::cout << "pi * tau: " << (pi * tau) << "\n";
    std::cout << "tau * pi: " << (tau * pi) << "\n";
}
   
