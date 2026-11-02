#include "Shape.h"

Shape::Shape(std::string n) : name(n), area(0.0), perimeter(0.0), userArea(-1.0), userPerimeter(-1.0), isAnswered(false), isCorrect(false) {}
Shape::~Shape() {}