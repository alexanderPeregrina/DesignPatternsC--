#include <iostream>
#include <vector>

/* Composite pattern: Individual objects and collection of objects all behave 
in the same manner (They have the same API) */
using namespace std;

struct GeometricShape
{
  virtual void draw() = 0;
};

struct Circle : GeometricShape
{
  void draw() override
  {
    cout << "Circle" << endl;
  }
};

struct Square : GeometricShape
{
  void draw() override
  {
    cout << "Square" << endl;
  }
};

struct Triangle : GeometricShape
{
  void draw() override
  {
    cout << "Triangle" << endl;
  }
};

struct Group : GeometricShape
{
  string name;
  vector<GeometricShape*> objects;
  Group(const string& name): name(name)
  {

  }
  void draw() override
  {
    cout << "This is group called " << name << endl;
    for (auto& it : objects)
    {
      it->draw();
    }
  }
};

int main()
{
  Group root{"root"};
  Circle circle, circle2;
  Square square;
  Triangle triangle;
  Group subgroup{"subgroup"};

  root.objects.push_back(&circle);
  root.objects.push_back(&square);
  root.objects.push_back(&triangle);

  subgroup.objects.push_back(&circle2);

  root.objects.push_back(&subgroup);

  root.draw();

  return 0;
}