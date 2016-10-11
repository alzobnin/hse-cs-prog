#include <iostream>
#include <vector>

using std::vector;

class Minesweeper {
private:
    size_t M, N;
    vector<vector<int>> Table;

public:
    Minesweeper(size_t m, size_t n): M(m), N(n) {
        Table.resize(M);
        for (auto row : Table)
            row.resize(N);
    }

    size_t Rows() {
        return M;
    }

    size_t Columns() {
        return N;
    }
    
    void SetMine(size_t i, size_t j) {
        Table[i][j] = -1;
    }

    int operator () (size_t i, size_t j) const {
        return Table[i][j];
    }

    void CheckForMinesAround() {
        for (size_t i = 0; i != M; ++i)
            for (size_t j = 0; j != N; ++j)
                CheckForMinesAround(i, j);
    }

private:
    void CheckForMinesAround(size_t i, size_t j) {
        int counter = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy)
                if (0 <= i + dx && i + dx < M &&
                    0 <= j + dy && j + dy < N &&
                    Table[i + dx][j + dy] == -1
                ) {
                    ++counter;
                }
        }
        Table[i][j] = counter;
    }
};

std::ostream& operator << (std::ostream& out, const Minesweeper& ms) {
    for (size_t i = 0; i != ms.Rows(); ++i)
        for (size_t j = 0; j != ms.Columns(); ++j)
            out << (ms(i, j) == -1 ? '*' : ms(i, j));
        out << "\n";
    return out;
}

