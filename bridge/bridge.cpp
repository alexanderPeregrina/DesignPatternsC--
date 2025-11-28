/*
Bridge pattern: 
Separate an object's abstraction (what it does) from its implementation (how it does it) 
so you can extend either side without changing the other

*/
 /* In this example There are two ways of render shapes and different type of shapes
   So the idea is to implement a bridge between shape abstraction and render abstraction
   This way we avoid the need to implement all possible combinations of shapes and render forms
 */
#include <iostream>
#include <memory>

using namespace std;

// Renderer: raster (pixels), vector(lines)
struct Renderer
{
  virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override
  {
    cout << "Rendering circle by vectors c(x, y) = ("<< x << ", "<< y<< ") r = " << radius <<endl;
  }
};

struct RasterRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override
  {
    cout << "Rendering circle by points (rasters) c(x, y) = ("<< x << ", "<< y<< ") r = " << radius <<endl;
  }
};

struct Shape
{
  virtual void draw() = 0;
  virtual void resize(float factor) = 0;
  virtual float get_area() = 0; 
  protected:
   Shape(Renderer& renderer): renderer(renderer)
  {

  }
    Renderer& renderer;
};

struct Circle : Shape
{
  float x, y, radius;
  Circle(float x, float y, float radius, Renderer& renderer): 
  Shape(renderer), x(x), y(y), radius(radius)
  {

  }

  void resize(float factor) override
  {
    radius = factor * radius;
  }

  void draw() override
  {
    renderer.render_circle(x, y, radius);
  }

  float get_area() override
  {
    return 3.141592f * radius * radius;
  }
};


int main()
{
  VectorRenderer v_renderer{};
  RasterRenderer r_renderer{};
  Circle c1{5.0f, 5.0f, 5.0f, v_renderer};
  Circle c2{5.0f, 5.0f, 5.0f, r_renderer};

  cout << "Circle 1: ";
  c1.draw();

  cout << "Circle 2: ";
  c2.draw();
  return 0;
}

