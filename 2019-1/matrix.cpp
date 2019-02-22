#include <array>
#include <iostream>

using namespace std;

template <typename T, size_t N>
class Matrix;

template <typename T, size_t N>
class MatrixIterator {
private:
    Matrix<T, N>& matrix;
    size_t row, column;

public:
    MatrixIterator(
        Matrix<T, N>& m,
        size_t i,
        size_t j
    ) : matrix(m), row(i), column(j)
    {
    }

    bool operator == (MatrixIterator other) const {
        return row == other.row
                && column == other.column;
    }

    bool operator != (MatrixIterator other) const {
        return !(*this == other);
    }

    T& operator * () {
        return matrix[row][column];
    }

    MatrixIterator& operator ++ () {
        ++column;
        if (column == N) {
            ++row;
            column = 0;
        }
        return *this;
    }

    MatrixIterator operator ++ (int) {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
};

template <typename T, size_t N>
class Matrix {
private:
    array<array<T, N>, N> data;

public:
    MatrixIterator<T, N> begin() {
        return {*this, 0, 0};
    }

    MatrixIterator<T, N> end() {
        return {*this, N, 0};
    }
    const array<T, N>&
    operator [] (size_t row) const {
        return data[row];
    }

    array<T, N>&
    operator [] (size_t row) {
        return data[row];
    }
};

template <typename T, size_t N>
ostream& operator << (
    ostream& out,
    const Matrix<T, N>& m
) {
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != N; ++j) {
            if (j > 0)
                out << '\t';
            out << m[i][j];
        }
        out << '\n';
    }
    return out;
}

template <typename T, size_t N>
Matrix<T, N> operator - (
    const Matrix<T, N>& m1,
    const Matrix<T, N>& m2
) {
    Matrix<T, N> result;
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != N; ++j)
            result[i][j] = m1[i][j] - m2[i][j];
    }
    return result;
}

template <typename T, size_t N>
Matrix<T, N>& operator -= (
    Matrix<T, N>& m1,
    const Matrix<T, N>& m2
) {
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != N; ++j)
            m1[i][j] -= m2[i][j];
    }
    return m1;
}



int main() {
    Matrix<int, 2> A;
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    std::cout << A << "\n\n";

    Matrix<int, 2> B;
    B[0][0] = B[1][1] = 0;
    B[1][0] = B[0][1] = 1;
    std::cout << B << "\n\n";

    A -= B;
    std::cout << A << "\n";

    for (auto& elem : A)
        ++elem;

    std::cout << A << "\n";
}
