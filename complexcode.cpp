#include <iostream>
#include <vector>

class Shape {
 public:
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
};

class Rectangle : public Shape {
 public:
  Rectangle(double length, double width)
      : length_(length), width_(width) {}
  double area() const override { return length_ * width_; }
  double perimeter() const override { return 2 * (length_ + width_); }

 private:
  double length_;
  double width_;
};

class Circle : public Shape {
 public:
  Circle(double radius) : radius_(radius) {}
  double area() const override { return 3.14159265358979323846 * radius_ * radius_; }
  double perimeter() const override { return 2 * 3.14159265358979323846 * radius_; }

 private:
  double radius_;
};

int main() {
  std::vector<Shape*> shapes;
  shapes.push_back(new Rectangle(3, 4));
  shapes.push_back(new Circle(5));
  
  for (const auto shape : shapes) {
    std::cout << "Area: " << shape->area() << std::endl;
    std::cout << "Perimeter: " << shape->perimeter() << std::endl;
  }
  
  for (auto shape : shapes) {
    delete shape;
  }
  return 0;
}
