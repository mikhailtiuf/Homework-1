#include "structs.h"
#include <cmath>
#include <iostream>

using namespace std;

const double EPSILON = 1e-5;

// Функции для точки
Point readPoint() {
    Point p;
    cout << "Введите координату x: ";
    cin >> p.x;
    cout << "Введите координату y: ";
    cin >> p.y;
    return p;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

// Функции для круга
Circle readCircle() {
    Circle c;
    cout << "Введите координату x центра: ";
    cin >> c.center.x;
    cout << "Введите координату y центра: ";
    cin >> c.center.y;
    cout << "Введите радиус: ";
    cin >> c.radius;
    return c;
}

void printCircle(const Circle& c) {
    cout << "Круг: центр ";
    printPoint(c.center);
    cout << ", радиус = " << c.radius;
}

double circleCircumference(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

// Функции для квадрата
Square readSquare() {
    Square s;
    cout << "Введите координату x левого верхнего угла: ";
    cin >> s.topLeft.x;
    cout << "Введите координату y левого верхнего угла: ";
    cin >> s.topLeft.y;
    cout << "Введите длину стороны: ";
    cin >> s.side;
    return s;
}

void printSquare(const Square& s) {
    cout << "Квадрат: левый верхний угол ";
    printPoint(s.topLeft);
    cout << ", сторона = " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Вспомогательная функция для сравнения чисел с учетом погрешности
bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

// Вспомогательная функция для вычисления расстояния между точками
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
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
    return areEqual(distance(p, c.center), c.radius);
}

bool isPointOnSquare(const Point& p, const Square& s) {
    // Проверка на левой границе
    bool onLeft = areEqual(p.x, s.topLeft.x) &&
        (p.y <= s.topLeft.y + EPSILON) &&
        (p.y >= s.topLeft.y - s.side - EPSILON);

    // Проверка на правой границе
    bool onRight = areEqual(p.x, s.topLeft.x + s.side) &&
        (p.y <= s.topLeft.y + EPSILON) &&
        (p.y >= s.topLeft.y - s.side - EPSILON);

    // Проверка на верхней границе
    bool onTop = areEqual(p.y, s.topLeft.y) &&
        (p.x >= s.topLeft.x - EPSILON) &&
        (p.x <= s.topLeft.x + s.side + EPSILON);

    // Проверка на нижней границе
    bool onBottom = areEqual(p.y, s.topLeft.y - s.side) &&
        (p.x >= s.topLeft.x - EPSILON) &&
        (p.x <= s.topLeft.x + s.side + EPSILON);

    return onLeft || onRight || onTop || onBottom;
}

// Пересечение фигур
bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dist = distance(c1.center, c2.center);
    return dist <= c1.radius + c2.radius + EPSILON &&
        dist >= fabs(c1.radius - c2.radius) - EPSILON;
}

bool squaresIntersect(const Square& s1, const Square& s2) {
    // Проверка пересечения по оси X
    bool xOverlap = (s1.topLeft.x <= s2.topLeft.x + s2.side + EPSILON) &&
        (s1.topLeft.x + s1.side >= s2.topLeft.x - EPSILON);

    // Проверка пересечения по оси Y
    bool yOverlap = (s1.topLeft.y >= s2.topLeft.y - s2.side - EPSILON) &&
        (s1.topLeft.y - s1.side <= s2.topLeft.y + EPSILON);

    return xOverlap && yOverlap;
}

bool circleSquareIntersect(const Circle& c, const Square& s) {
    // Находим ближайшую точку квадрата к центру круга
    double closestX = max(s.topLeft.x, min(c.center.x, s.topLeft.x + s.side));
    double closestY = min(s.topLeft.y, max(c.center.y, s.topLeft.y - s.side));

    // Проверяем расстояние от центра круга до ближайшей точки квадрата
    Point closestPoint = { closestX, closestY };
    return distance(c.center, closestPoint) <= c.radius + EPSILON;
}

// Принадлежность фигур
bool isCircleInCircle(const Circle& c1, const Circle& c2) {
    double dist = distance(c1.center, c2.center);
    return dist + c1.radius <= c2.radius + EPSILON;
}

bool isSquareInSquare(const Square& s1, const Square& s2) {
    return (s1.topLeft.x >= s2.topLeft.x - EPSILON) &&
        (s1.topLeft.x + s1.side <= s2.topLeft.x + s2.side + EPSILON) &&
        (s1.topLeft.y <= s2.topLeft.y + EPSILON) &&
        (s1.topLeft.y - s1.side >= s2.topLeft.y - s2.side - EPSILON);
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    // Проверяем все вершины квадрата
    Point vertices[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };

    for (int i = 0; i < 4; i++) {
        if (distance(vertices[i], c.center) > c.radius - EPSILON) {
            return false;
        }
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    // Проверяем, что круг полностью внутри квадрата
    return (c.center.x - c.radius >= s.topLeft.x - EPSILON) &&
        (c.center.x + c.radius <= s.topLeft.x + s.side + EPSILON) &&
        (c.center.y + c.radius <= s.topLeft.y + EPSILON) &&
        (c.center.y - c.radius >= s.topLeft.y - s.side - EPSILON);
}