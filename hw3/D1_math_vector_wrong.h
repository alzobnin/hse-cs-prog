#include <iostream>

template <typename T = double, int N>
class MathVector {
public:
    T coords[N];
    MathVector(std::initializer_list<T> data) {
        coords = new T[n];
        std::copy(coords, data.begin(), data.end());
    }
    const T& operator [] (size_t i) {
        return coords[i];
    }
    T& operator [] (size_t i) const {
        return coords[i];
    }
    friend T& operator * (MathVector u, MathVector v) {
        T res = 0;
        for (size_t i = 0; i != N; ++i)
            res += u[i] * v[i];
        return res;
    }
    T Abs() const {
        T res;
        for (const T& xi : coords)
            res += xi * xi;
        return sqrt(res);
    }
};

std::ostream& operator << (std::ostream& o, MathVector& v) {
    o << "(";
    for (size_t i = 0; i != N; ++i)
        o << v[i] << ", ";
    o << v[N] << ")";
    return o;
}

template <typename T, int N>
std::istream& operator >> (std::istream& i, MathVector<T, N>& v) {
    for (size_t i = 0; i != N; ++i)
        i >> v[i];
    return i;
}

template <typename T, int N>
double Cos(const MathVector<T, N>& u, const MathVector<T, N>& v) {
    auto uAbs = u.Abs();
    auto vAbs = v.Abs();
    return u * v / uAbs * vAbs;
}

int main() {
    MathVector<int, 3> u {1, 2, -3};
    MathVector<int, 3> v;
    std::cin >> v;
    std::cout << "Vector u: " << u << "\n";
    std::cout << "Vector v: " << v << "\n";
    std::cout << "Length of u: " << u.Abs() << "\n";
    std::cout << "Length of v: " << v.Abs() << "\n";
    std::cout << "Scalar product: " << (u * v) << "\n";
    std::cout << "Cosinus of angle: " << Cos(u, v) << "\n";
}

