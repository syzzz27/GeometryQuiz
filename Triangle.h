#pragma once
#include "Shape.h"

class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle();
    Triangle(double a, double b, double c);
    void calcArea() override;
    void calcPerimeter() override;
    void genData() override;
    void printQuestion() const override;
    void printShapeArt() const override;
    std::string getType() const override { return "Triangle"; }
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
};