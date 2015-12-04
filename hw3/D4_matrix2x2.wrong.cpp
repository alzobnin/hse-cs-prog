#include <algorithm>
#include <cmath>
#include <iostream>

template <typename T>
class Matrix2x2 {
public:
    size_t N = 2;
    T entries[N][N];

    Matrix2x2(std::initializer_list<T> data)
    : entries (new T[N][N])
    {
        auto iter = data.begin();
        for (size_t i = 0; i != N; ++i)
            for (size_t j = 0; j != N; ++j)
                entries[i][j] = *++iter;
    }
    Matrix2x2(const T& lambda = 0) {
        if (entries != nullptr)
            delete [] entries;
        for (size_t k = 0; k != N; ++k)
            entries[k][k] = lambda;
    }
    T& operator [] (size_t i, size_t j) {
        return entries[i][j];
    }
    const T& operator () (size_t i, size_t j) const {
        return entries[i][j];
    }
    T& Det() const {
        return entries[0][0] * entries[1][1] - entries[0][1] * entries[1][0];
    }
    Matrix2x2 operator * (const Matrix2x2& other) {
        Matrix2x2 res;
        for (size_t i = 0; i != N; ++i)
            for (size_t j = 0; j != N; ++j)
                for (size_t k = 0; k != N; ++k)
                    res(i, j) += other(i, k) * other(k, j);
        return res;
    }
    bool operator == (Matrix2x2 other) const {
        for (size_t i = 0; i != N; ++i)
            for (size_t j = 0; j != N; ++j)
                if (entries[i][j] == other.entries[i][j])
                    return true;
        return false;
    }
    bool operator != (Matrix2x2 other) const {
        return !operator==(other);
    }
};

T Det(const Matrix& a) {
    return a.Det();
}

int main() {
    Matrix2x2<int> A {1, 2, 3, 4};
    Matrix2x2<int> B {-2, 1, -4, 3};
    std::cout << "det(A): " << Det(A) << "\n";
    std::cout << "det(B): " << Det(B) << "\n";
    std::cout << "det(A*B): " << Det(A*B) << "\n";
    std::cout << "det(B*A): " << Det(B*A) << "\n";
    std::cout << "A*B == B*A: " << (A*B == B*A) << "\n";
}

