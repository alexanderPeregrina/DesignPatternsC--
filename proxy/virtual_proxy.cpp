#include <iostream>

/* In this example we have a Bitmap class that is already written, but there is a problem with it,
When calling the constructor it loads the image from file name, but we want to make sure the 
load function is only called when the draw function is called, so the way to fix this is through a
virtual proxy. Notice that Open/Close principle is not violated as well. */
using namespace std;

struct Image
{
  virtual void draw() = 0;
};

struct Bitmap : Image
{
  Bitmap(const string& filename)
  {
   cout << "Loading Bitmap from file" << filename << endl;
  }

  void draw() override
  {
    cout << "Drawing Bitmap" << endl;
  }

};

// Virtual Proxy

struct LazyBitmap : Image
{
  LazyBitmap(const string filename): filename(filename)
  {

  }
  void draw() override
  {
    if(!p_bitmap)
      p_bitmap = new Bitmap(filename);
    p_bitmap->draw();
  }
private:
  string filename;
  Bitmap* p_bitmap{nullptr};
};
int main()
{
  // Without checking drawing first
  Bitmap bmp1{"Pokemon.png"};
  // Checking drawing first
  LazyBitmap bmp2{"Pokemon.png"};
  bmp2.draw();
  return 0;
}