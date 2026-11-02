#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
    double r;
public:
    Circle();
    Circle(double radius);
    void calcArea() override;
    void calcPerimeter() override;
    void genData() override;
    void printQuestion() const override;
    void printShapeArt() const override;
    std::string getType() const override { return "Circle"; }
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
};