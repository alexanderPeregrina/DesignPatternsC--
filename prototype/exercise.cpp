#include <iostream>

using namespace std;
struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    Line result{new Point {}, new Point{}};

    *result.start = *start;
    *result.end   = *end;  

    return result;

  }
};

int main()
{
  Line l1{new Point{5, 7}, new Point{10, 5}};
  Line l2 = l1.deep_copy();

  cout << "Start (x, y): (" << l1.start->x <<", " << l1.start->y <<") End (x, y): ("<<l1.end->x << ", " << l1.end->y << ")"<< endl;
  cout << "Start (x, y): (" << l2.start->x <<", " << l2.start->y <<") End (x, y): ("<<l2.end->x << ", " << l2.end->y << ")"<< endl;
}