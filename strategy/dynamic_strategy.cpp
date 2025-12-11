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
   <li>Element 2</li>
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

class TextProcessor
{
  ostringstream oss;
  unique_ptr<ListStrategy> list_strategy;

public:

    TextProcessor(OutputFormat format)
    {
        set_output_format(format);
    }
    
    void append_list(const vector<string>& items)
    {
        list_strategy->start(oss);
        for (const auto& item : items)
        {
        list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }
    
    string str() const
    {
        return oss.str();
    }

    void set_output_format(OutputFormat format)
    {
      switch(format)
      {
        case OutputFormat::markdown:
          list_strategy = make_unique<MarkdownListStrategy>();
          break;
        case OutputFormat::html:
          list_strategy = make_unique<HtmlListStrategy>();
          break;
      }
   }
};

int main()
{
  TextProcessor tp{OutputFormat::markdown};
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  TextProcessor tp2{OutputFormat::html};
  tp2.append_list({"foo", "bar", "baz"});
  cout << tp2.str() << endl;
}

