/*

Proxy Coding Exercise
You are given the Person  class and asked to write a ResponsiblePerson  wrapper/proxy that 
does the following:

Allows person to drink unless they are younger than 18 (in that case, return "too young")

Allows person to drive unless they are younger than 16 (otherwise, "too young")

In case of driving while drink, returns "dead"

The interface of ResponsiblePerson  has to match that of Person , except for the constructor, 
which takes an underlying Person object..

*/
#include <iostream>

using namespace std;

class Person
{
  friend class ResponsiblePerson;
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:    
  ResponsiblePerson(const Person &person) : person(person) {}  
  string drive() const
  {
    if (person.get_age() >= 16)
    {
      return person.drive();
    }  
    else 
    {
      return "too young";
    }
  }  
  string drink() const
  {
    if (person.get_age() >= 18)
    {
      return person.drink();
    }
    else
    {
      return "too young";
    }
  }  
  string drink_and_drive() const { return "dead";}

  int get_age() const { return person.age; }
  void set_age(int age) { person.set_age(age); }
private:
    Person person;
};

int main()
{
  Person person{12};
  cout << person.drink() << endl;
  cout << person.drink_and_drive() << endl;

  ResponsiblePerson r_person{17};
  cout << r_person.drink() << endl;
  cout << r_person.drive() << endl;
  
  return 0;
}