#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Database
{
public:
  virtual int get_population(const string& name) = 0;
}; 

class SingletonDatabase : public Database
{
  SingletonDatabase();

  map<string, int> capitals;

  public:
  // Delete copy assignment and copy constructor definitions

  SingletonDatabase(const SingletonDatabase& other) = delete;
  SingletonDatabase& operator=(const SingletonDatabase& other) = delete;

  static SingletonDatabase& get();

  int get_population(const string& name) override;
};

class SingletonRecordFinder
{
public:
  int total_population(const vector<string>& cities);
};

// Dependency injection, allows this function/class depends generic database,
// instead of ou singleton db
class ConfigurableRecordFinder
{
  Database& database;
public:
  ConfigurableRecordFinder(Database& database): database(database)
  {

  }
  int total_population(const vector<string>& cities);

  Database& get_database()
  {
    return database;
  }
};

class DummyDatabase : public Database
{
  map<string, int> capitals;
public:
  DummyDatabase();
  int get_population(const string& name) override;
};
