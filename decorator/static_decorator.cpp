#include <iostream>
#include <string>
#include <cstdint>

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

template<typename T>
struct ColorShape : T
{
  string color;
  ColorShape(){}
  template<typename... Args>
  ColorShape(const string& color, Args... args):
  color(color), T(forward<Args>(args)...)
  {

  }

  string str() const override
  {
    return T::str() + " has color " + color;
  }
};

template<typename T>
struct TransparentShape : T
{
  uint8_t transparency;
  TransparentShape(){}
  template<typename... Args>
  TransparentShape(const uint8_t transparency, Args... args):
  transparency(transparency), T(forward<Args>(args)...)
  {

  }

  string str() const override
  {
    return T::str() + " has transparency " + to_string((float)transparency * 100.f / 255.f);
  }
};


int main()
{
  TransparentShape<ColorShape<Circle>> green_t_circle{52, "green", 3};
  cout << green_t_circle.str() << endl;
  return 0;
}