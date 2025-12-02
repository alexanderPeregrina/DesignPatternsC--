/*
Flyweight design pattern: Space optimization, avoid redundancy when storing data.
A space optimization techique that let us use less memory by storing externally the data
associated with similar objects.
*/
#include <iostream>
#include <boost/bimap.hpp>
#include <cstdint>

using namespace std;
using namespace boost;


// Bimap is a bidirectional dictionary (map), you retrive information by key or by value 
class User
{
public:
  User(const string& first_name, const string& last_name):
  f_name(add(first_name)), l_name(add(last_name)) 
  {

  }
  const string& get_first_name() const
  {
    auto it = names.left.find(f_name);
    return it->second;
  }

  const string& get_last_name() const
  {
    auto it = names.left.find(l_name);
    return it->second;
  }

  friend ostream& operator<<(ostream& os, const User& user)
  {
    string s;
    s = "First Name: " + user.get_first_name() + "(" + to_string(user.f_name)
    + ") Last Name: " + user.get_last_name() +"(" + to_string(user.l_name)
    + ")\n";
    os << s;
    return os;
  }


protected:
  uint32_t f_name, l_name;
  static bimap<uint32_t, string> names;
  static uint32_t seed;

  static uint32_t add(const string& s)
  {
    // check if string already exist in bimap
    auto it = names.right.find(s);
    if (it != names.right.end())
    {
      return it->second;
    }
    else
    {
      seed++;
      names.insert({seed, s});
      return seed;
    }
  }
};

// Initialize static members
bimap<uint32_t, string> User::names{};
uint32_t User::seed = 0u;

int main()
{
  User john{"John", "Smith"};
  User jane{"Jane", "Smith"};

  cout << john << jane;

  return 0;
}
