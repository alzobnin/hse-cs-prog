#include <iostream>

class Minesweeper {
private:
    size_t M, N;
    int ** Table;

public:
    Minesweeper(size_t m, size_t n): M(m), N(n) {
        Table = new int * [M];
        for (size_t i = 0; i != M; ++i) {
            Table[i] = new int * [N];
        }
    }

    ~Minesweeper() {
        delete [] Table;
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
    for (size_t i = 0; i != ms.Rows(); ++i) {
        for (size_t j = 0; j != ms.Columns(); ++j)
            out << (ms(i, j) == -1 ? '*' : ms(i, j));
        out << "\n";
    }
    return out;
}

int main() {
    size_t m, n;
    std::cin >> m >> n;
    Minesweeper ms(m, n);

    int minesCount;
    std::cin >> minesCount;
    while (minesCount-->0) {
        size_t x, y;
        std::cin >> x >> y;
        ms.SetMine(x, y);
    }

    ms.CheckForMinesAround();

    std::cout << ms;
}

