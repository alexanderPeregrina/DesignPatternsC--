#include <iostream>
#include "drink_factory.hpp"

//Abstract factory pattern: 
/*
When to use it
• 	You need to create related objects that must work together (e.g., UI widgets for different OS themes).
• 	You want to isolate concrete classes from client code and support swapping product families easily.
• 	You want to centralize and encapsulate object creation logic so new variants can be added with minimal changes to clients.
*/

using namespace std;

int main()
{
  DrinkFactory drink_factory; // to keeo track of the factories we have ...

  drink_factory.make_drink("coffee", 100);

  drink_factory.make_drink("tea", 20);
  return 0;
}