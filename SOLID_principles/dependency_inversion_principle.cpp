// Dependency inversion principle: 
// A) High level modules should not depend on low level modules. Both should depend on abstractions.
// B) Abstractions should not depend on details (implementations). Details should depend on abstractions.
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class Person
{
  public:
    string name;
     Person(string name): name (name) {};

};

enum class Relationship
{
  parent, child, sibling
};


// In this case they way to search in relationship does not depend on how the relationships are stored.
class RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(string& name) = 0;
};


class Relationships : RelationshipBrowser
{
  public:
  vector<tuple<Person, Relationship, Person>> relations;
  void add_parent_and_child(Person& parent, Person& child)
  {
    relations.push_back({parent, Relationship::parent, child}); 
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(string& name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if((first.name == name) && (rel == Relationship::parent))
        result.push_back(second);
    }
    return result;
  }
};

int main()
{

  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;

  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  vector<Person> result = relationships.find_all_children_of(parent.name);

  for (auto& it : result)
  {
    cout << parent.name << " has a child called " << it.name << endl; 
  }
  getchar();
  return 0;
}