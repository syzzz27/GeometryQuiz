#pragma once
#include <string>
#include <iostream>

class Shape {
protected:
    std::string name;
    double area;
    double perimeter;
    double userArea;
    double userPerimeter;
    bool isAnswered;
    bool isCorrect;

public:
    Shape(std::string n);
    virtual ~Shape();

    virtual void calcArea() = 0;
    virtual void calcPerimeter() = 0;
    virtual void genData() = 0;
    virtual void printQuestion() const = 0;
    virtual void printShapeArt() const = 0;
    virtual std::string getType() const = 0;

    
    virtual void saveData(std::ostream& out) const = 0;
    virtual void loadData(std::istream& in) = 0;

    bool operator<(const Shape& other) const { return this->area < other.area; }

    void setUserAnswer(double ua, double up, bool correct) {
        userArea = ua; userPerimeter = up;
        isAnswered = true; isCorrect = correct;
    }
    bool getIsAnswered() const { return isAnswered; }
    bool getIsCorrect() const { return isCorrect; }
    double getUserArea() const { return userArea; }
    double getUserPerimeter() const { return userPerimeter; }
    double getArea() const { return area; }
    double getPerimeter() const { return perimeter; }
    std::string getName() const { return name; }
};