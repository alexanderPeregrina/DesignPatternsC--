#include <iostream>
#include <array>
#include <numeric> // For accumulate
#include <algorithm> // For max_element
#include <map>
using namespace std;


enum Abilities {strength = 0, agility, intelligence, count};


class Creature
{
  private:
  array<int, Abilities::count> abilities;

  public:

    int get_strength()
    {
      return abilities[strength];
    }
    
    int get_agility()
    {
      return abilities[agility];
    }

    int get_intelligence()
    {
      return abilities[intelligence];
    }

    void set_strength(int new_strength)
    {
      abilities[strength] = new_strength;
    }

    void set_agility(int new_agility)
    {
      abilities[agility] = new_agility ;
    }

    void set_intelligence(int new_intelligence)
    {
      abilities[intelligence] = new_intelligence;
    }

    int sum() const 
    {
      return accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const 
    {
      return static_cast<double>(sum()) / static_cast<double>(Abilities::count);  
    }

    int max()
    {
       return *max_element(abilities.begin(), abilities.end()); 
    }

    int min()
    {
      return *min_element(abilities.begin(), abilities.end());
    }

    int arg_max() const
    {
      const auto it = max_element(abilities.begin(), abilities.end());

      return distance(abilities.begin(), it);
    }


};

int main()
{
  map<Abilities, string> ability_names;
  ability_names[strength] = "Strength";
  ability_names[agility] = "Agility";
  ability_names[intelligence] = "Intelligence";

  Creature orc;
  orc.set_strength(16);
  orc.set_agility(11);
  orc.set_intelligence(9);

  cout  << "The orc has an average abilities of "
        << orc.average() << " and his max ability is " << ability_names[(Abilities)orc.arg_max()] 
        << " with a value of " << orc.max() << endl;
  return 0;
}