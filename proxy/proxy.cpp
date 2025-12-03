#include <iostream>

// Proxy: Provides a common placeholder to control access. The goal is to change the behavior
// of an object behinds the scenes but preserving the interface of the object
using namespace std;

template<typename T>
struct Property
{
  T value;
  Property(T value)
  {
    *this = value; // Calls the operator= instead of directly assigning
  }

  operator T()
  {
    // This is like a cast operator
    // This allows implicit conversion from Property<T> --> T
    return value;
  }
  
  T operator=(T new_value)
  {
    cout << "Assignment\n";
    value = new_value;
    return value;
  }
};

struct Creature
{
  Property<int> strength{10};
  Property<int> agility{10};
};

int main()
{
  Creature c;
  c.strength = 11;
  int x = c.agility;
  // Should be 3 assignments
  return 0;
}