#include <string>
#include <iostream>

using namespace std;

struct Person
{
  int id;
  string name;
};

class PersonFactory
{
public:
  Person create_person(const string& name)
  {
    static int count = 0;
    return {count++, name};
  }
};

int main()
{
  PersonFactory pf;
  
  Person p1 = pf.create_person("Alexander");
  Person p2 = pf.create_person("Andres");
  Person p3 = pf.create_person("Roman");

  cout << p1.id <<" " << p1.name << endl;
  cout << p2.id <<" " << p2.name << endl;
  cout << p3.id <<" " << p3.name << endl;
  return 0;
}