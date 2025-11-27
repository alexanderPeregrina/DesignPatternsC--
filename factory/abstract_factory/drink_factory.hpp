#pragma once
#include "hot_drink_factory.hpp"
#include <map>
#include <string>

using namespace std;

// Facilitator class for all the factories we have
class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_drink_factories;
  public:
    DrinkFactory()
    {
      hot_drink_factories["coffee"] = make_unique<CoffeFactory>();
      hot_drink_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name, int volume = 50)
    {
      auto drink = hot_drink_factories[name]->make();
      drink->prepare(volume);
      return drink;
    }
};

