/*

Observer Coding Exercise
Imagine a game where one or more rats can attack a player. Each individual rat has an attack  value of 1. 
However, rats attack as a swarm, so each rat's attack  value is equal to the total number of rats in play.

Given that a rat enters play through the constructor and leaves play (dies) via its destructor, 
please implement the Game and Rat  classes so that, at any point in the game, the attack value 
of a rat is always consistent.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct IRat
{
  virtual ~IRat()=default;
};

struct Rat;

struct Game
{
  vector<Rat*> rats;
};

struct Rat : IRat
{
  Game& game;
  int attack{1};

  Rat(Game &game) : game(game)
  {
    game.rats.push_back(this);
    for (auto rat : game.rats)
    {
      rat->attack = game.rats.size();
    }
  }

    ~Rat() 
  { 
      // Remove this rat from the game's rat list
      // call notify
      game.rats.erase(remove(game.rats.begin(), game.rats.end(), this), game.rats.end());

      for(auto& rat: game.rats)
      {
        rat->attack = game.rats.size();
      }
  }  
};

int main()
{
  Game game;
  Rat rat1{game};
  Rat rat2{game};
  cout << rat1.attack << endl; // outputs 2
  Rat *rat3 = new Rat{game};
  cout << rat1.attack << endl; // outputs 2
  delete rat3;
  cout << rat1.attack << endl; // outputs 2
}

