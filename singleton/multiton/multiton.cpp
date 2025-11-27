#include <map>
#include <memory>
#include <iostream>

// Multiton Patern: Like Singleton, 
// but this can provide certain number of instances
using namespace std;

// This class represent the maximum 
// number of instances the multiton will provide
// One singleton per enum
enum class Importance
{
  primary,
  secondary,
  tertiary
};

// T: type of instance, Key: Importance (or number of instance)
template <typename T, typename Key = string>
class Multiton
{
  static map<Key, shared_ptr<T>> instances;

  Multiton()
  {

  }

  Multiton(const Multiton& other) = delete;
  Multiton& operator=(const Multiton& other) = delete;

public:
  static shared_ptr<T> get(const Key& key)
  {
    const auto it = instances.find(key);
    if (it != instances.end())
    {
      return instances[key];
    }

    instances[key] = make_shared<T>();
    return instances[key];
  }
};

// Initializing instances map from Multiton class
template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

// Class to test (T)
class Printer
{
  static int totalInstanceCount;
public:
 Printer()
 {
  ++totalInstanceCount;
  cout << "The total number of instances is "<< totalInstanceCount <<endl;
 }
};

int Printer::totalInstanceCount = 0;

int main()
{
  // To avoid writing a lot
  typedef Multiton<Printer, Importance> Mt;

  auto main = Mt::get(Importance::primary);
  auto second = Mt::get(Importance::secondary);
  auto second_1 = Mt::get(Importance::secondary);
  auto third = Mt::get(Importance::tertiary);
  return 0;
}

