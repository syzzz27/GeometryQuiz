#include "Rectangle.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Rectangle::Rectangle() : Shape("长方形"), len(0), wid(0) {}
Rectangle::Rectangle(double l, double w) : Shape("长方形"), len(l), wid(w) { calcArea(); calcPerimeter(); }

void Rectangle::calcArea() { area = len * wid; }
void Rectangle::calcPerimeter() { perimeter = 2 * (len + wid); }
void Rectangle::genData() { len = rand() % 15 + 5; wid = rand() % 10 + 1; calcArea(); calcPerimeter(); }

void Rectangle::printQuestion() const { cout << "题目：一个长方形，长为 " << (int)len << "，宽为 " << (int)wid << "。" << endl; }
void Rectangle::printShapeArt() const { cout << "  ------\n |      |\n  ------" << endl; }

void Rectangle::saveData(std::ostream& out) const { out << len << " " << wid << " " << userArea << " " << userPerimeter << " " << isAnswered << " " << isCorrect << "\n"; }
void Rectangle::loadData(std::istream& in) {
    in >> len >> wid >> userArea >> userPerimeter >> isAnswered >> isCorrect;
    calcArea(); calcPerimeter();
}