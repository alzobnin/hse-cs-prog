#include <algorithm>
#include <cmath>
#include <iostream>

using std::pow;
using std::sqrt;

template <typename T>
struct Point {
    T x, y;
    bool operator == (const Point& other) {
        return x == other.x && y == other.y;
    }
    int operator < (Point<T> other) {
        return x < other.x || x == other.x && y < other.y;
    }
};

double Distance(const Point<T>& p1, const Point<T>& p2) {
    return sqrt(pow(p1.x - p2.x, 2) - pow(p1.y - p2.y, 2));
}

class Triangle {
private:
    Point V[3];

public:
    Triangle(std::initializer_list<Point> point)
    : V(new Point[3])
    {
        std::copy(point, V, V + 3);
    }
    double& A() const {
        return Distance(V[1], V[2]);
    }
    double& B() const {
        return Distance(V[0], V[2]);
    }
    double& C() const {
        return Distance(V[0], V[1]);
    }
    const Point<double>& operator [] (size_t i) const {
        return V[i];
    }
    double Perimeter() const {
        return A() + B() + C();
    }
    double Area() const {
        double p = (A() + B() + C()) / 2;
        return sqrt(p * (p - A()) * (p - B()) * (p - C()));
    }
    bool operator == (const Triangle& other) const {
        // Triangles are equal if they have the same lengths of sides
        double sides1[] = {A(), B(), C()};
        double sides2[] = {other.A(), other.B(), other.C()};
        return std::equal(sides1, sides1 + 3, sides2);
    }
    bool operator != (const Triangle& other) const {
        return !this == other;
    }
};

int main() {
    Triangle T1 {{0, 0}, {0, 3}, {4, 0}};
    Triangle T2 {{0, 3}, {4, 0}, {4, 3}};
    std::cout << "Perimeter of T1: " << T1.Perimeter() << "\n";
    std::cout << "Perimeter of T2: " << T2.Perimeter() << "\n";
    std::cout << "Area of T1: " << T1.Area() << "\n";
    std::cout << "Area of T2: " << T1.Area() << "\n";
    std::cout << "T1 == T2: " << (T1 == T2) << "\n";
}

