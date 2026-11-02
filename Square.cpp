#include "Square.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Square::Square() : Shape("正方形"), side(0) {}
Square::Square(double s) : Shape("正方形"), side(s) { calcArea(); calcPerimeter(); }

void Square::calcArea() { area = side * side; }
void Square::calcPerimeter() { perimeter = 4 * side; }
void Square::genData() { side = rand() % 20 + 1; calcArea(); calcPerimeter(); }

void Square::printQuestion() const { cout << "题目：一个正方形，边长为 " << (int)side << "。" << endl; }
void Square::printShapeArt() const { cout << "  ----\n |    |\n  ----" << endl; }

void Square::saveData(std::ostream& out) const { out << side << " " << userArea << " " << userPerimeter << " " << isAnswered << " " << isCorrect << "\n"; }
void Square::loadData(std::istream& in) {
    in >> side >> userArea >> userPerimeter >> isAnswered >> isCorrect;
    calcArea(); calcPerimeter();
}