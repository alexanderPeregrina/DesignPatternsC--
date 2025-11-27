// Livkov principle: A derived class should be able to be subtituted
// into any location where its base clase it's being used.

#include <iostream>

using namespace std;

class Rectangle
{
  protected:
    int width;
    int height;
  public:
    Rectangle(int width, int height) : width(width), height(height){};

    int get_width()
    {
      return width;
    };

    int get_height()
    {
      return height;
    }
    virtual void set_width(int width)
    {
      this->width = width;
    }
    virtual void set_height(int height)
    {
      this->height = height;
    }

    int get_area()
    {
      return width * height;
    }
};

class Square : public Rectangle
{
  private:
    int size;
  public:
    Square(int size) : size(size), Rectangle(size, size){};
    void set_width(int width) override
    {
      this->width = width;
      this->height = width;
      this->size = width;
    }

    void set_height(int height) override
    {
      this->width = height;
      this->height = height;
      this->size = height;
    }
};

void process(Rectangle& r)
{
  constexpr int new_height = 10;
  int w = r.get_width();
  r.set_height(new_height);
  if (dynamic_cast<Square*>(&r))
    cout << "Expected Area: " << new_height * new_height << ", got " << r.get_area() << endl;
  else
    cout << "Expected Area: " << w * new_height << ", got " << r.get_area() << endl;
}

int main()
{
  Rectangle rectangle{5, 4};
  Square square{5};
  process(rectangle);
  process(square);
  getchar();
  return 0;
}