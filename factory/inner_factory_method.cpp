#include <iostream>
#include <cmath>
#include <ostream>

using namespace std;

// The idea of Factory method is to add extra functions/classes that handle the object creation
// in cases where multiple constructor with the same number and type of parameters are required
// as c++ does not allow this type of constructor override

class Point
{
  Point(float x, float y) : x(x), y(y)
  {

  }
  public:
  float x, y;

  friend ostream& operator<<(ostream& os, const Point& p)
  {
    os << "x: " << p.x << " y: " << p.y << endl;
    return os;
  }

  class PointFactory
  {
    public:
    PointFactory()
    {

    }
    static Point NewCartesian(float x, float y)
    {
      return {x, y};
    }
  
    static Point NewPolar(float rho, float theta)
    {
      return {rho * cos (theta), rho *  sin(theta)};
    }

  };
};

int main()
{
  auto p = Point::PointFactory::NewCartesian(5.0f, 7.0f);
  cout << p ;
  return 0;
}
