#pragma once
#include "hot_drinks.hpp"

class HotDrinkFactory
{
  public:
  virtual std::unique_ptr<HotDrink> make() const = 0;
  
};

class TeaFactory : public HotDrinkFactory
{
  public:
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>(); // This return a unique ptr to a Tea object
    }

};

class CoffeFactory : public HotDrinkFactory
{
  public:
    std::unique_ptr<HotDrink> make() const override
    {
      return std::make_unique<Coffee>();
    }
};

