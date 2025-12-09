/*
Memento Design Pattern: A token or handle representing the system state. Lets us restore the system to that state later.
Used to implement undo/redo mechanisms.

*/
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Memento
{
  int balance;
public:
  Memento(int balance): balance(balance)
  {

  }
  friend class BankAccount;
};

class BankAccount
{
  int balance{0};
  vector<shared_ptr<Memento>> changes;
  int current{0};
public:
  BankAccount(int balance): balance(balance)
  {
    // store initial state
    changes.push_back(make_shared<Memento>(balance));
  }

  shared_ptr<Memento> deposit(int amount)
  {
    balance += amount;
    changes.push_back(make_shared<Memento>(balance));
    ++current;
    return changes[current];
  }

  void restore(shared_ptr<Memento> m)
  {
    if (m)
    {
      balance = m->balance;
      changes.push_back(m);
      ++current;
    }
  }

  shared_ptr<Memento> undo()
  {
    if(current > 0)
    {
      --current;
      balance = changes[current]->balance;
      
      return changes[current];
    }
    return {};
  }

  shared_ptr<Memento> redo()
  {
    if (current < static_cast<int>(changes.size()) - 1)
    {
      ++current;
      balance = changes[current]->balance;
      return changes[current];
    }

    return {};
  }

  friend ostream& operator<<(ostream& os, const BankAccount& ba)
  {
    os << "Balance: " << ba.balance;
    return os;
  }
  
};

int main()
{
  BankAccount ba{100};
  ba.deposit(50);
  ba.deposit(25); //175
  cout << ba << endl;
  (void)ba.undo();
  cout << "After undo: " << ba << endl;
  (void)ba.undo();
  cout << "After undo: " << ba << endl;
  return 0;
}
