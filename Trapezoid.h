#pragma once
#include "Shape.h"

class Trapezoid : public Shape {
private:
    double top, bot, h, l1, l2;
public:
    Trapezoid();
    Trapezoid(double t, double b, double h, double l1, double l2);
    void calcArea() override;
    void calcPerimeter() override;
    void genData() override;
    void printQuestion() const override;
    void printShapeArt() const override;
    std::string getType() const override { return "Trapezoid"; }
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
};