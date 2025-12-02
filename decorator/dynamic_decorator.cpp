// Decorator design Pattern: Facilitates the addition of behaviors to individual objects.
#include <iostream>
#include <string>
#include <cstdint> // For uint8_t and other bit based datatypes

using namespace std;

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;
  Circle()
  {

  }

  Circle (float radius): radius(radius)
  {

  }

  void resize(float factor)
  {
    radius *= factor;
  }

  string str() const override
  {
    return "A circle of radius " + to_string(radius);
  }
};

struct Square : Shape
{
  float side;
  Square()
  {

  }

  Square(float side): side(side)
  {

  }

  string str() const override
  {
    return "A square of size " + to_string(side);
  }
};

// Decorator: adds additional features/behaviors to base class Shape
struct ColoredShape : Shape
{
  Shape& shape;
  string color;

  ColoredShape(Shape& shape, string color): shape(shape), color(color)
  {

  }

  string str() const override
  {
    return  shape.str() + " has the color " + color;
  }

};

struct TransparentShape : Shape
{
  Shape &shape;
  uint8_t transparency;

  
  TransparentShape(Shape& shape, uint8_t transparency) : shape(shape), transparency(transparency)
  {

  }

  string str() const override
  {
    float transparency = ((float)transparency * 255.f) / 100.f;
    return shape.str() + " has a transparency of " + 
            to_string(transparency);
  }

};

int main()
{
  Circle circle{5.0f};
  ColoredShape red_circle{circle, "red"};
  TransparentShape red_t_circle{red_circle, 120u};

  // Side effect: A decorated object cannot access the other attributes of obj being decorated. 

  cout << red_t_circle.str() << endl;
  return 0;
}