/*
Strategy design pattern: System behavior can be selected at runtime or compile time.
*/
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

/*
Markdown example:
 * Element 1
 * Element 2

 HTML example:
 <ul>
   <li>Element 1</li>
   <li>Element 2</li>
 </ul>
*/
enum class OutputFormat
{
  markdown,
  html
};

struct ListStrategy
{
  virtual void start(ostringstream& os)
  {

  }

  virtual void end(ostringstream& os)
  {

  }

  virtual void add_list_item(ostringstream& os, const string& item)=0;

};

class MarkdownListStrategy : public ListStrategy
{
public:
  void add_list_item(ostringstream& os, const string& item) override
  {
    os << " * " << item << "\n";
  }
};

class HtmlListStrategy : public ListStrategy
{
public:
  void start(ostringstream& os) override
  {
    os << "<ul>" << "\n";
  }

  void end(ostringstream& os) override
  {
    os << "</ul>" << "\n";
  }

  void add_list_item(ostringstream& os, const string& item) override
  {
    os << "  <li>" << item << "</li>" << "\n";
  }

};

template<typename LS>
class TextProcessor
{
  ostringstream oss;
  LS list_strategy;

public:

    TextProcessor()
    {

    }
    
    void append_list(const vector<string>& items)
    {
        list_strategy.start(oss);
        for (const auto& item : items)
        {
        list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }
    
    string str() const
    {
        return oss.str();
    }
};

int main()
{
  TextProcessor<MarkdownListStrategy> tp;
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  TextProcessor<HtmlListStrategy> tp2;
  tp2.append_list({"foo", "bar", "baz"});
  cout << tp2.str() << endl;
}

