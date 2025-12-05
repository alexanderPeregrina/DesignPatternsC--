/*
 Chain of responsability pattern: Decouple the sender of a request from its receivers by giving multiple
 objects the chance to handle the request, without the sender knowing which one will actually process it

*/
#include <iostream>
#include <memory>

using namespace std;

struct Creature
{
  string name;
  int attack, defense;

  Creature(const string& name, int attack, int defense):
  name(name), attack(attack), defense(defense)
  {

  }

  friend ostream& operator<<(ostream& os, const Creature& creature)
  {
    os << "Name: " << creature.name << " attack: " << creature.attack << " defense:" <<
    creature.defense << endl;

    return os;
  }
};

class CreatureModifier
{
  shared_ptr<CreatureModifier> p_next{nullptr};
protected:
  Creature& creature;
public:
  CreatureModifier(Creature& creature): creature(creature)
  {

  }

  void add(shared_ptr<CreatureModifier> p_creatureModifier)
  {
    if(p_next)
      p_next->add(p_creatureModifier);
    else
      p_next = p_creatureModifier;
  }

  virtual void handle() 
  {
    if(p_next)
      p_next->handle();
  }

  virtual ~CreatureModifier() = default;

};

class DoubleAttackModifier : public CreatureModifier
{
public:
  DoubleAttackModifier(Creature& creature): CreatureModifier(creature)
  {

  }

  void handle() override
  {
    creature.attack *= 2; 
    CreatureModifier::handle();
  }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
  IncreaseDefenseModifier(Creature& creature): CreatureModifier(creature)
  {

  }

  void handle() override
  {
    creature.defense += 1; 
    CreatureModifier::handle();
  }
};

class BlockModifiers : public CreatureModifier
{
public:
  BlockModifiers(Creature& creature): CreatureModifier(creature)
  {

  }

  void handle() override
  {

  }
};


int main()
{
  Creature goblin{"Goblin", 1, 1};
  
  cout << goblin;

  auto p_root = make_shared<CreatureModifier>(goblin);
  auto p_double_attack = make_shared<DoubleAttackModifier>(goblin);
  auto p_inc_defense = make_shared<IncreaseDefenseModifier>(goblin);
  auto p_block_modif = make_shared<BlockModifiers>(goblin);

  p_root->add(p_double_attack);
  p_root->add(p_inc_defense);
  p_root->add(p_block_modif);
  p_root->add(p_double_attack);

  p_root->handle();

  // Final result should be: attack: 2, defense: 2
  
  cout << goblin;

  return 0;
}