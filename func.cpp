#include "func.h"
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const double EPSILON = 1e-5;
const double M_PI = 3.14159265358979323846;

// Вспомогательные функции
bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Функции ввода-вывода
Point readPoint() {
    Point p;
    cout << "Введите координаты точки (x y): ";
    cin >> p.x >> p.y;
    return p;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

Circle readCircle() {
    Circle c;
    cout << "Введите координаты центра круга (x y): ";
    cin >> c.center.x >> c.center.y;
    cout << "Введите радиус круга: ";
    cin >> c.radius;
    return c;
}

void printCircle(const Circle& c) {
    cout << "Круг: центр ";
    printPoint(c.center);
    cout << ", радиус = " << c.radius;
}

Square readSquare() {
    Square s;
    cout << "Введите координаты левого верхнего угла квадрата (x y): ";
    cin >> s.topLeft.x >> s.topLeft.y;
    cout << "Введите длину стороны квадрата: ";
    cin >> s.side;
    return s;
}

void printSquare(const Square& s) {
    cout << "Квадрат: левый верхний угол ";
    printPoint(s.topLeft);
    cout << ", сторона = " << s.side;
}

// Вычисления для круга
double circleLength(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

// Вычисления для квадрата
double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c) {
    return distance(p, c.center) < c.radius - EPSILON;
}

bool isPointInSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x + EPSILON) &&
        (p.x < s.topLeft.x + s.side - EPSILON) &&
        (p.y < s.topLeft.y - EPSILON) &&
        (p.y > s.topLeft.y - s.side + EPSILON);
}

// Нахождение точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c) {
    return fabs(distance(p, c.center) - c.radius) < EPSILON;
}

bool isPointOnSquare(const Point& p, const Square& s) {
    bool onLeft = areEqual(p.x, s.topLeft.x) && (p.y <= s.topLeft.y + EPSILON) && (p.y >= s.topLeft.y - s.side - EPSILON);
    bool onRight = areEqual(p.x, s.topLeft.x + s.side) && (p.y <= s.topLeft.y + EPSILON) && (p.y >= s.topLeft.y - s.side - EPSILON);
    bool onTop = areEqual(p.y, s.topLeft.y) && (p.x >= s.topLeft.x - EPSILON) && (p.x <= s.topLeft.x + s.side + EPSILON);
    bool onBottom = areEqual(p.y, s.topLeft.y - s.side) && (p.x >= s.topLeft.x - EPSILON) && (p.x <= s.topLeft.x + s.side + EPSILON);

    return onLeft || onRight || onTop || onBottom;
}

// Пересечение фигур
bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dist = distance(c1.center, c2.center);
    return dist < c1.radius + c2.radius + EPSILON &&
        dist > fabs(c1.radius - c2.radius) - EPSILON;
}

bool squaresIntersect(const Square& s1, const Square& s2) {
    // Проверяем пересечение по осям
    bool xOverlap = (s1.topLeft.x < s2.topLeft.x + s2.side + EPSILON) &&
        (s1.topLeft.x + s1.side > s2.topLeft.x - EPSILON);
    bool yOverlap = (s1.topLeft.y > s2.topLeft.y - s2.side - EPSILON) &&
        (s1.topLeft.y - s1.side < s2.topLeft.y + EPSILON);

    return xOverlap && yOverlap;
}

bool circleSquareIntersect(const Circle& c, const Square& s) {
    // Находим ближайшую точку квадрата к центру круга
    double closestX = max(s.topLeft.x, min(c.center.x, s.topLeft.x + s.side));
    double closestY = max(s.topLeft.y - s.side, min(c.center.y, s.topLeft.y));

    // Проверяем, находится ли эта точка внутри круга
    double distX = c.center.x - closestX;
    double distY = c.center.y - closestY;
    double distanceSquared = distX * distX + distY * distY;

    return distanceSquared <= (c.radius * c.radius + EPSILON);
}

// Принадлежность фигур
bool isCircleInCircle(const Circle& c1, const Circle& c2) {
    double dist = distance(c1.center, c2.center);
    return dist + c1.radius < c2.radius + EPSILON;
}

bool isSquareInSquare(const Square& s1, const Square& s2) {
    return (s1.topLeft.x >= s2.topLeft.x - EPSILON) &&
        (s1.topLeft.x + s1.side <= s2.topLeft.x + s2.side + EPSILON) &&
        (s1.topLeft.y <= s2.topLeft.y + EPSILON) &&
        (s1.topLeft.y - s1.side >= s2.topLeft.y - s2.side - EPSILON);
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    // Проверяем все углы квадрата
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };

    for (int i = 0; i < 4; i++) {
        if (distance(corners[i], c.center) > c.radius - EPSILON) {
            return false;
        }
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    return (c.center.x - c.radius >= s.topLeft.x - EPSILON) &&
        (c.center.x + c.radius <= s.topLeft.x + s.side + EPSILON) &&
        (c.center.y + c.radius <= s.topLeft.y + EPSILON) &&
        (c.center.y - c.radius >= s.topLeft.y - s.side - EPSILON);
}