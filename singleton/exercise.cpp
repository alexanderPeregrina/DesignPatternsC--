/*

Implementing a singleton is a bit too easy, so you've got a different challenge. 

You are given the function SingletonTester::is_singleton()  defined below. This function takes a factory, and needs to return true  or false  depending on whether that factory produces singletons.

This one's actually easy. Ask yourself: what traits do two 'instances' of a singleton have in common?

*/
#include <iostream>
#include <functional>
#include <type_traits> // to check return types..

using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(T factory)
  {
    // create two instances using the factory
    // Note: decltype(auto)--> preserves referencess
    decltype(auto) instance_1 = factory();
    decltype(auto) instance_2 = factory();

    // compare the addresses of the underlying objects (works for references)
    return &instance_1 == &instance_2;
  }
};

template <typename T>
class Factory
{
  public:
  Factory()
  {

  }
  // Functor
  decltype(auto) operator()()
  {
    return T::get();
  }

};

// Example Singleton Class
class SingletonPrinter
{
  SingletonPrinter()
  {
    static int instance_counter = 0;
    cout << "Total instances " << ++instance_counter << endl;
  }

  SingletonPrinter(const SingletonPrinter& other) = delete;
  SingletonPrinter& operator=(const SingletonPrinter& other) = delete;

public:
  static SingletonPrinter& get()
  {
    static SingletonPrinter printer{};

    return printer;
  }
};
  // Non singleton class
  class Printer
  {
    Printer()
    {
      static int instances = 0;
      cout << "Total instances: " << ++instances << endl;
    }
    public:
    static Printer get()
    {
      Printer printer{};
      return printer;
    }

  };

  int main()
  {
    Factory<Printer> printerFactory{};
    Factory<SingletonPrinter> singletonPrinterFactory{};

    SingletonTester tester;

    cout << boolalpha;
    cout << "Printer is singleton: "
         << tester.is_singleton(printerFactory) << endl;

    cout << "SingletonPrinter is singleton: "
         << tester.is_singleton(singletonPrinterFactory) << endl;


    return 0;
  }