#pragma once
#include "Shape.h"

class Rectangle : public Shape {
private:
    double len, wid;
public:
    Rectangle();
    Rectangle(double l, double w);
    void calcArea() override;
    void calcPerimeter() override;
    void genData() override;
    void printQuestion() const override;
    void printShapeArt() const override;
    std::string getType() const override { return "Rectangle"; }
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
};