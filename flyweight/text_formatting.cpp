#include <iostream>
#include <vector>

using namespace std;

class FormattedText
{
public:
  FormattedText(const string& plain_text): plain_text(plain_text){}
  struct TextRange
  {
    int start, end;
    bool capitalize;

    TextRange(int start, int end): start(start), end(end)
    {
      capitalize = false;
    }
    bool covers_range(const int position)
    {
      return position >= start && position <= end; 
    }
  };

  TextRange& get_range(int start, int end)
  {
    formatting.emplace_back(TextRange{start, end}); //Emplace back: Avoid creating a temporary obj
    return *formatting.rbegin();
  }

  friend ostream& operator<<(ostream& os, FormattedText& text)
  {
    string s{};
    for (int i = 0; i < text.plain_text.length(); i++)
    {
      auto c = text.plain_text[i];
      for (auto& rng : text.formatting)
      {
        if(rng.covers_range(i) && rng.capitalize)
        {
          c = toupper(c);
        }
      }
      s += c;
    }
    os << s;

    return os;
  }
private:
  string plain_text;
  vector<TextRange> formatting;
  
};
int main()
{
  FormattedText ft{"This is a brave world"};
  ft.get_range(10, 15).capitalize = true;
  cout << ft << endl;

}