/* Here's a very synthetic example for you to try.

You are given a Rectangle  protocol and an extension method on it. Try to define a SquareToRectangleAdapter  that adapts the Square  to the Rectangle  interface.
*/

/* 
The Adapter Pattern allows incompatible interfaces to work together. 
It defines a wrapper class/struct (the adapter) that translates or adapts 
an existing interface into a form expected by the client, enabling reuse 
of existing functionality without modifying the original code. 
*/
#include <iostream>

struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{

  int side;

  SquareToRectangleAdapter(const Square& square)
  {
    side = square.side;
  }
  int width() const override
  {
    return side;
  }

  int height() const override
  {
    return side;
  }
};

int main()
{
  Square square{10};
  SquareToRectangleAdapter adapter{square};
  std::cout << "The Area of the square is: " << adapter.area();
  return 0;
}