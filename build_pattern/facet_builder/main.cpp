#include <iostream>
#include "Person.hpp"
#include "PersonBuilder.hpp"

// Builder facets are used when complex objects needs to be constructed 
// avoiding passing all attributes to a single constructor
using namespace std;

int main ()
{

  Person p = Person::create().set_name("Robert California")
                              .lives()
                              .at("123 London Road")
                              .with_post_code("SW1 1GB")
                              .in("London").works().at("PragmaSoft")
                              .as_a("Consultant")
                              .earning(1'000'000);
    
  cout << p << endl;

  return 0;  
}