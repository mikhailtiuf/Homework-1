#include <iostream>
#include "func.h"

using namespace std;

void demonstratePoint() {
    cout << "=== Демонстрация работы с точкой ===" << endl;
    Point p = readPoint();
    cout << "Точка: ";
    printPoint(p);
    cout << endl << endl;
}

void demonstrateCircle() {
    cout << "=== Демонстрация работы с кругом ===" << endl;
    Circle c = readCircle();
    printCircle(c);
    cout << endl;
    cout << "Длина окружности: " << circleLength(c) << endl;
    cout << "Площадь круга: " << circleArea(c) << endl << endl;
}

void demonstrateSquare() {
    cout << "=== Демонстрация работы с квадратом ===" << endl;
    Square s = readSquare();
    printSquare(s);
    cout << endl;
    cout << "Периметр квадрата: " << squarePerimeter(s) << endl;
    cout << "Площадь квадрата: " << squareArea(s) << endl << endl;
}

void demonstratePointInFigures() {
    cout << "=== Принадлежность точки фигурам ===" << endl;
    Point p = readPoint();
    Circle c = readCircle();
    Square s = readSquare();

    cout << "Точка ";
    printPoint(p);
    cout << " в круге: " << (isPointInCircle(p, c) ? "ДА" : "НЕТ") << endl;
    cout << "Точка ";
    printPoint(p);
    cout << " в квадрате: " << (isPointInSquare(p, s) ? "ДА" : "НЕТ") << endl;
    cout << "Точка ";
    printPoint(p);
    cout << " на круге: " << (isPointOnCircle(p, c) ? "ДА" : "НЕТ") << endl;
    cout << "Точка ";
    printPoint(p);
    cout << " на квадрате: " << (isPointOnSquare(p, s) ? "ДА" : "НЕТ") << endl << endl;
}

void demonstrateIntersections() {
    cout << "=== Пересечение фигур ===" << endl;
    Circle c1 = readCircle();
    Circle c2 = readCircle();
    Square s1 = readSquare();
    Square s2 = readSquare();

    cout << "Круги пересекаются: " << (circlesIntersect(c1, c2) ? "ДА" : "НЕТ") << endl;
    cout << "Квадраты пересекаются: " << (squaresIntersect(s1, s2) ? "ДА" : "НЕТ") << endl;
    cout << "Круг и квадрат пересекаются: " << (circleSquareIntersect(c1, s1) ? "ДА" : "НЕТ") << endl << endl;
}

void demonstrateContainment() {
    cout << "=== Принадлежность фигур ===" << endl;
    Circle c1 = readCircle();
    Circle c2 = readCircle();
    Square s1 = readSquare();
    Square s2 = readSquare();

    cout << "Круг 1 в круге 2: " << (isCircleInCircle(c1, c2) ? "ДА" : "НЕТ") << endl;
    cout << "Квадрат 1 в квадрате 2: " << (isSquareInSquare(s1, s2) ? "ДА" : "НЕТ") << endl;
    cout << "Квадрат в круге: " << (isSquareInCircle(s1, c1) ? "ДА" : "НЕТ") << endl;
    cout << "Круг в квадрате: " << (isCircleInSquare(c1, s1) ? "ДА" : "НЕТ") << endl << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    demonstratePoint();
    demonstrateCircle();
    demonstrateSquare();
    demonstratePointInFigures();
    demonstrateIntersections();
    demonstrateContainment();

    return 0;
}