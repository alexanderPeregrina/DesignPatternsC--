#include <iostream>
#include <vector>
#include <string>

//Pattern : Open for extension close for modification, extension through inheritance and polymorfism
// This example shows how to filter products by specification using two interfaces Filter and Specification instead of creating
// class with different filter types

using namespace std;

enum class Color
{
  red, green, blue
};

enum class Size
{
  small, medium, large
};

class Product
{
  public:
    string name;
    Color color;
    Size size;

};

// Interfaces: Abstract classes
template <typename T>
class Specification
{
  public:
  virtual bool is_satisfied(T* item) const = 0;
};

template <typename T>
class Filter
{
  public:
  virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;

};

class ColorAndSizeSpecification : public Specification<Product>
{
  public:
  Color color;
  Size size;
  ColorAndSizeSpecification(Color color, Size size): color(color), size(size){};
  bool is_satisfied(Product *p_item) const override
  {
    return (p_item->color == color && p_item->size == size);
  }
};

class FilterProductBySpecification : public Filter<Product>
{
  public:
  vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override 
  {
    vector<Product*> result;
    for (auto& it : items)
    {
      if (spec.is_satisfied(it))
        result.push_back(it);
    }

    return result;
  }

};

int main ()
{
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const vector<Product*> products {&apple, &tree, &house};

  vector<Product*> result;

  ColorAndSizeSpecification color_size_sp{Color::green, Size::large};

  FilterProductBySpecification filter_by_sp;

  result = filter_by_sp.filter(products, color_size_sp);

  for (auto& it : result)
    cout << "Name: " << it->name << endl;
  
  getchar();
  return 0;
}