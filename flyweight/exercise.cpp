/*

You are given a class called Sentence , which takes a string such as "hello world".
You need to provide an interface such that the indexer (operator [] ) 
returns a WordToken  that can be used to capitalize a particular word in the sentence.

*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Sentence
{
  string text;
  struct WordToken
  {
    size_t start_index, last_index;
    bool capitalize;

    WordToken(size_t start_index, size_t last_index): start_index(start_index), last_index(last_index)
    {
      capitalize = false;
    }

    bool cover(size_t position)
    {
      return position >= start_index && position <= last_index;
    }
  };

  vector<WordToken> tokens;

  Sentence(const string& text)
  {
    this->text = text;
  }

  WordToken& operator[](size_t index)
  {
    istringstream iss{text};
    string word;
    for (size_t w_index = 0; w_index <= index; w_index++)
    {
      word = "";
      iss >> word;
    }
    size_t start_index = text.find(word);
    WordToken token{start_index, start_index + word.length()};
    tokens.push_back(token);
    return *(tokens.end() - 1);
  }

  string str() const
  {
    string result{};

    for(size_t i = 0; i < text.length(); i++)
    {
      auto c = text[i];
      for(auto token: tokens)
      {
        if (token.capitalize && token.cover(i))
        {
          c = toupper(c);
        }
      }

      result += c;

    }
    return result;
  }
};

int main()
{
  Sentence sentence("hello world princess");
  sentence[1].capitalize = true;
  cout << sentence.str(); // prints "hello WORLD"
  return 0;
}