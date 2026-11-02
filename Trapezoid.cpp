#include "Trapezoid.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Trapezoid::Trapezoid() : Shape("梯形"), top(0), bot(0), h(0), l1(0), l2(0) {}
Trapezoid::Trapezoid(double t, double b, double h, double l1, double l2) : Shape("梯形"), top(t), bot(b), h(h), l1(l1), l2(l2) { calcArea(); calcPerimeter(); }

void Trapezoid::calcArea() { area = (top + bot) * h / 2.0; }
void Trapezoid::calcPerimeter() { perimeter = top + bot + l1 + l2; }
void Trapezoid::genData() {
    top = rand() % 10 + 2; bot = rand() % 10 + 5; h = rand() % 10 + 2;
    l1 = rand() % 5 + 3; l2 = rand() % 5 + 3; calcArea(); calcPerimeter();
}

void Trapezoid::printQuestion() const { cout << "题目：一个梯形，上底 " << (int)top << "，下底 " <<(int) bot << "，高 " <<(int) h << "，两腰 " <<(int) l1 << " 和 " <<(int) l2 << "。" << endl; }
void Trapezoid::printShapeArt() const { cout << "   ----\n  /    \\\n /______\\" << endl; }

void Trapezoid::saveData(std::ostream& out) const { out << top << " " << bot << " " << h << " " << l1 << " " << l2 << " " << userArea << " " << userPerimeter << " " << isAnswered << " " << isCorrect << "\n"; }
void Trapezoid::loadData(std::istream& in) {
    in >> top >> bot >> h >> l1 >> l2 >> userArea >> userPerimeter >> isAnswered >> isCorrect;
    calcArea(); calcPerimeter();
}