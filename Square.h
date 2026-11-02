#pragma once
#include "Shape.h"

class Square : public Shape {
private:
    double side;
public:
    Square();
    Square(double s);
    void calcArea() override;
    void calcPerimeter() override;
    void genData() override;
    void printQuestion() const override;
    void printShapeArt() const override;
    std::string getType() const override { return "Square"; }
    void saveData(std::ostream& out) const override;
    void loadData(std::istream& in) override;
};