#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

using namespace std;

class Tag
{
  public:
    string name, text;
    vector<pair<string, string>> attributes;
    vector<Tag> children;

    Tag(const string& name, const string& text): name(name), text(text){};
    Tag(const string& name, const vector<Tag>& children) : name(name), children(children){};

    friend ostream& operator<<(ostream& os, const Tag& tag)
    {
      os << "<" << tag.name;
      for (const auto& att : tag.attributes)
      {
        os << " " << att.first << "=\"" << att.second << "\"";
      }

      // No nested tags and no text to show
      if (tag.children.size() == 0 && tag.text.length() == 0)
        os << "/>" << endl;
      else
      {
        os << ">" << endl;
        if (tag.text.length())
          os << tag.text << endl;
        for (const auto& child : tag.children)
        {
          os << child;
        }

        os << "</" << tag.name << ">" << endl;
      } 
      return os;
    }
};

class P : public Tag
{
  public:
    P(const string& text): Tag("p", text){};
    P(initializer_list<Tag> children): Tag("p", children){};
};

class IMG : public Tag
{
  public:
    IMG(const string&& url) : Tag("img", "")
    {
      attributes.emplace_back(make_pair("src", url));
    }
};

int main()
{

cout << 
  P {
    IMG {"http://pokemon.com/pikachu"}
  }
<< endl;
  return 0;
}