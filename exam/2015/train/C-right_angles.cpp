#include <iostream>
#include <string>
#include <vector>

using TVec = std::vector<long int>;

struct TPoint {
    std::string Name;
    TVec Coords;
};

bool right(const TVec& A, const TVec& B, const TVec& C) {
    long int res = 0;
    for (size_t k = 0; k != A.size(); ++k)
        res += (A[k] - B[k]) * (C[k] - B[k]);
    return res == 0;
}

bool right(const TPoint& A, const TPoint& B, const TPoint& C) {
    return right(A.Coords, B.Coords, C.Coords);
}

int main() {
    size_t N;
    std::cin >> N;
    size_t M;
    std::cin >> M;

    std::vector<TPoint> points(M);
    for (size_t k = 0; k != M; ++k) {
        std::cin >> points[k].Name;
        points[k].Coords.resize(N);
        for (auto& coord : points[k].Coords)
            std::cin >> coord;
    }

    for (size_t i = 0; i != M; ++i) {
        for (size_t j = 0; j != M; ++j) {
            if (j == i)
                continue;
            for (size_t k = i + 1; k != M; ++k) {
                if (k == i || k == j)
                    continue;
                if (right(points[i], points[j], points[k]))
                    std::cout << points[i].Name << " " << points[j].Name << " " << points[k].Name << "\n";
            }
        }
    }
}

