#include <iostream>
#include<vector>
#include<string>
#include <boost/lexical_cast.hpp>
#include <fstream>

using namespace std;
using namespace boost;

// Single responsability principle: A class shall have a single reason to change/serve/exist

class Journal
{
  private:
    string title;
    vector<string> entries;

  public:
    Journal(const string& title) : title(title){
      add_entry(title);
    };
    void add_entry(const string& entry)
    {
      static int count = 1;
      entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }

    string& getTitle()
    {
      return title;
    }

    vector<string>& getEntries()
    {
      return entries;
    }
  
};

// Separation of concerns 
class PersistenceManager
{
  public:
   void save(Journal& journal, const string& filename)
    {
      ofstream file(filename);
      if (file.is_open())
      {
        for (const auto& it : journal.getEntries())
          file << it << endl;
      }
      else
      {
        cout << "File not oppened" << endl;
      }
  
    }
};


int main()
{
  Journal journal{"The Gen Z crisis"};
  journal.add_entry("No future for Gen Z");
  journal.add_entry("Capitalism is reaching the end");
  vector<string> entries = journal.getEntries();

  for (const auto& it : entries )
    cout << it << endl;

  PersistenceManager pm;
  pm.save(journal, "journal.txt");
  getchar();
  return 0;
}