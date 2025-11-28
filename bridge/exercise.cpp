/*
You are given an example of an inheritance hierarchy which results in Cartesian-product duplication.

Please refactor this hierarchy, giving the base class Shape  an initializer that takes a Renderer  defined as

struct Renderer
{
  virtual string what_to_render_as() const = 0;
}
as well as VectorRenderer and RasterRenderer.

The expectation is that each constructed object has a member called str()  that returns its textual representation, for example,

Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels" 
*/
#include <iostream>
#include <string>
using namespace std;

struct Renderer
{
  Renderer()
  {

  }
  virtual string what_to_render_as() const = 0;
};

struct Shape
{
  string name;
  Renderer& renderer;
  Shape(string name, Renderer& renderer): name(name), renderer(renderer)
  {

  }
  string str()
  {
    return "Drawing " + name + " as " + renderer.what_to_render_as();
  }
};

struct Triangle : Shape
{
  Triangle(Renderer& renderer): Shape("", renderer)
  {
    name = "Triangle";
  }
};

struct Square : Shape
{
  Square(Renderer& renderer): Shape("", renderer)
  {
    name = "Square";
  }
};

struct RasterRender : Renderer
{
  string what_to_render_as() const override
  {
    return "pixels";
  }
};

struct VectorRender : Renderer
{
  string what_to_render_as() const override
  {
    return "lines";
  }
};
// imagine e.g. VectorTriangle/RasterTriangle etc. here

int main()
{
  RasterRender rr;
  VectorRender vr;
  Triangle vectorTriangle{vr};
  Triangle rasterTriangle{rr};
  Square   vectorSquare{vr};

  cout << vectorTriangle.str() << endl;
  cout << rasterTriangle.str() << endl;
  cout << vectorSquare.str() << endl;

  return 0;
}