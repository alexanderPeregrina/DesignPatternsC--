//Singleton Pattern: Used when a single instance of a class is needed like a complex object, configuration objects, etc 
// This program reads information from a file and stores them in a container (using singleton)
#include <iostream>
#include "city_populations.hpp"

SingletonDatabase::SingletonDatabase()
{
  cout << "initializing database" << endl;
  ifstream ifs("capitals.txt");
  string line1, line2;
  while (getline(ifs, line1)) {
    if (!getline(ifs, line2)) {
        cerr << "Missing population for city: " << line1 << endl;
        break;
    }
    int population = stoi(line2);
    capitals[line1] = population;
  }


}

SingletonDatabase& SingletonDatabase::get()
{
  static SingletonDatabase db = SingletonDatabase();
  return db;
}

int SingletonDatabase::get_population(const string& name)
{
  return capitals[name];
}

DummyDatabase::DummyDatabase()
{
  capitals["alpha"] = 1;
  capitals["beta"] = 2;
  capitals["gamma"] = 3;
}

int DummyDatabase::get_population(const string& name)
{
  auto it = capitals.find(name);
  if (it != capitals.end())
  {
    return capitals[name];
  }
  return 0;
}

int SingletonRecordFinder::total_population(const vector<string>& cities)
{
  int total= 0;
  for (auto& it :  cities)
  {
    total += SingletonDatabase::get().get_population(it);
  }
  return total;
}

int ConfigurableRecordFinder::total_population(const vector<string>& cities)
{
  int total= 0;
  for (auto& it :  cities)
  {
    total += get_database().get_population(it);
  }
  return total;
}

#ifndef UNIT_TESTING
int main()
{
  cout << "Lima's population is: " << SingletonDatabase::get().get_population("Lima") << endl;
  cout << "Quito's population is: " << SingletonDatabase::get().get_population("Quito") << endl;

  cout << "The address of the singleton is: " << &SingletonDatabase::get() << endl;
  cout << "The address of the singleton is: " << &SingletonDatabase::get() << endl;

  //Withouth dependency injection
  SingletonRecordFinder srf;
  int population = srf.total_population(vector<string>{"Tokyo", "Buenos Aires"});
  cout << population << endl;

  //With dependency injection
  ConfigurableRecordFinder crf(SingletonDatabase::get());
  population = crf.total_population(vector<string>{"Mexico City", "Seoul"});
  cout << population << endl;
  return 0;
}
#endif