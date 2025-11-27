#include <iostream>
#include <string>
#include <ostream>
#include <vector>

using namespace std;

class CodeBuilder
{
  string class_name;
  vector<pair<string, string>> attributes;
public:
  CodeBuilder(const string& class_name): class_name(class_name)
  {

  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    attributes.push_back(make_pair(name, type));
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.class_name << endl;
    os << "{" << endl;
    for (const auto& it : obj.attributes)
    {
      os << "  " << it.second << " " << it.first << ";" << endl;
    }

    os << "};" << endl;
    return os;
  }
};

int main()
{
  auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
  cout << cb;
  return 0;
}