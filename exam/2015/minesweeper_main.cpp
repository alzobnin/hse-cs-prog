#include "minesweeper.h"
#include <iostream>

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

