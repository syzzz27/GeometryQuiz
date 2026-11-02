#include "Triangle.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Triangle::Triangle() : Shape("三角形"), a(0), b(0), c(0) {}
Triangle::Triangle(double a, double b, double c) : Shape("三角形"), a(a), b(b), c(c) { calcArea(); calcPerimeter(); }

void Triangle::calcArea() {
    double p = (a + b + c) / 2.0;
    area = sqrt(p * (p - a) * (p - b) * (p - c));
}
void Triangle::calcPerimeter() { perimeter = a + b + c; }
void Triangle::genData() { int k = rand() % 5 + 1; a = 3 * k; b = 4 * k; c = 5 * k; calcArea(); calcPerimeter(); }

void Triangle::printQuestion() const { cout << "题目：一个直角三角形，三边长分别为 " << (int)a << ", " <<(int) b << ", " <<(int) c << "。" << endl; }
void Triangle::printShapeArt() const { cout << "    /|\n   / |\n  /__|" << endl; }

void Triangle::saveData(std::ostream& out) const { out << a << " " << b << " " << c << " " << userArea << " " << userPerimeter << " " << isAnswered << " " << isCorrect << "\n"; }
void Triangle::loadData(std::istream& in) {
    in >> a >> b >> c >> userArea >> userPerimeter >> isAnswered >> isCorrect;
    calcArea(); calcPerimeter();
}