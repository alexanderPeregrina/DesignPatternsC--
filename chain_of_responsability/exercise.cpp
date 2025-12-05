/*
Chain of Responsibility Coding Exercise
You are given a game scenario with classes Goblin  and GoblinKing . Please implement the following rules:

A goblin has base 1 attack/1 defense (1/1), a goblin king is 3/3.
When the Goblin King is in play, every other goblin gets +1 Attack.
Goblins get +1 to Defense for every other Goblin in play (a GoblinKing is a Goblin!).
Example:

Suppose you have 3 ordinary goblins in play. Each one is a 1/3 (1/1 + 0/2 defense bonus).
A goblin king comes into play. Now every ordinary goblin is a 2/4 (1/1 + 0/3 defense bonus from each other + 1/0 from goblin king)
Meanwhile, the goblin king itself is 3/6 (3/3 + 0/3 defense bonus from other goblins)

*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Creature;
struct Game
{
  vector<Creature*> creatures;
};

struct Creature
{
protected:
  Game& game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                            base_defense(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;

  int get_base_attack()
  {
    return base_attack;
  }

  int get_base_defense()
  {
    return base_defense;
  }

  friend ostream& operator<<(ostream& os,  Creature& creature)
  {
    os <<"Attack: " << creature.get_attack() <<" Defense: " << creature.get_defense() << "\n";
    return os;
  }

};

struct StatQuery
{
  int base_statistic;
  enum Statistic { attack, defense } statistic;
  vector<Creature*> result;

  StatQuery(const int base_statistic, Statistic statistic): base_statistic(base_statistic), 
  statistic(statistic)
  {
  
  }

void queryStatistics(const Game& game)
{
    // back_inserter is used so that copy_if can push elements dynamically 
    // as query result is empty (needs to allocate space)
  if (this->statistic == StatQuery::Statistic::attack)
  {
    copy_if(game.creatures.begin(), game.creatures.end(), back_inserter(this->result),
            [&](Creature* const c)
            {
              return c->get_base_attack() == this->base_statistic;
            });
  }
  else
  {
   copy_if(game.creatures.begin(), game.creatures.end(), back_inserter(this->result),
            [&](Creature* const c)
            {
              return c->get_base_defense() == this->base_statistic;
            });
  }
}

};

class Goblin : public Creature
{
public:

  Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) 
  {

  }

  Goblin(Game &game) : Creature(game, 1, 1) 
  {

  }

  int get_attack() override {
    // Check all Goblin Kings
    StatQuery query{3, StatQuery::Statistic::attack};
    int result = 0;
    
    query.queryStatistics(this->game);

    result = static_cast<int>(query.result.size()) + 1;
    return result;
  }

  int get_defense() override {
    // Query normal goblines
    StatQuery query{1, StatQuery::Statistic::defense};
    // Query Goblin Kings
    StatQuery query2{3, StatQuery::Statistic::defense};
    int result;
    // perform queries
    query.queryStatistics(this->game);
    query2.queryStatistics(this->game);

    // Count all normal goblins
    result = (int)(query.result.size());

    // add goblin kings
    result += (int)(query2.result.size());

    return result;
  }
};

class GoblinKing : public Goblin
{
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) 
  {

  }

  
  int get_attack() override 
  {
    return 3;
  }

  
  int get_defense() override 
  {
    // Check all Goblins
    StatQuery query{1, StatQuery::Statistic::defense};
    // check all Goblin Kings
    StatQuery query2{3, StatQuery::Statistic::defense};
    int result;
    query.queryStatistics(this->game);
    query2.queryStatistics(this->game);

    result = (int)(query.result.size()) + 3;
    
    result += (int)(query2.result.size()) -1;

    return result;
  }

};

int main()
{
  Game game;
  Goblin g1 {game};
  Goblin g2 {game};
  Goblin g3 {game};
  GoblinKing gk1 {game};

  game.creatures.push_back(&g1);
  game.creatures.push_back(&g2);
  game.creatures.push_back(&g3);
  game.creatures.push_back(&gk1);

  cout << g1.get_defense() << endl;
  cout << g1.get_attack() << endl;
  
  for (auto& it : game.creatures)
  {
    cout << *it << endl;
  }

  return 0;
}