#include "Circle.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Circle::Circle() : Shape("圆形"), r(0) {}
Circle::Circle(double radius) : Shape("圆形"), r(radius) { calcArea(); calcPerimeter(); }

void Circle::calcArea() { area = 3.14 * r * r; }
void Circle::calcPerimeter() { perimeter = 2 * 3.14 * r; }
void Circle::genData() { r = rand() % 10 + 1; calcArea(); calcPerimeter(); }

void Circle::printQuestion() const { cout << "题目：一个圆形，半径为 " <<(int) r << "。" << endl; }
void Circle::printShapeArt() const { cout << "  ***\n *   *\n  ***" << endl; }

void Circle::saveData(std::ostream& out) const { out << r << " " << userArea << " " << userPerimeter << " " << isAnswered << " " << isCorrect << "\n"; }
void Circle::loadData(std::istream& in) {
    in >> r >> userArea >> userPerimeter >> isAnswered >> isCorrect;
    calcArea(); calcPerimeter();
}