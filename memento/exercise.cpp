/*
Memento Coding Exercise
A TokenMachine  is in charge of keeping tokens. Each Token  is a reference type with a single numerical value. 
The machine supports adding tokens and, when it does, it returns a memento representing the state of that 
system at that given time.

You are asked to fill in the gaps and implement the Memento design pattern for this scenario. Pay close
attention to the situation where a token is fed in as a smart pointer and its value is subsequently changed 
on that pointer - you still need to return the correct system snapshot!

*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token
{
  int value;

  Token(int value) : value(value) {}
};

struct Memento
{
  vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
  vector<shared_ptr<Token>> tokens;

  Memento add_token(int value)
  {
    return add_token(make_shared<Token>(value));
  }

  // adds the token to the set of tokens and returns the
  // snapshot of the entire system
  Memento add_token(const shared_ptr<Token>& token)
  {

    tokens.push_back(token);
    Memento m;
    // memento should store the current value of all tokens
    for (const auto& t : tokens)
    {
      m.tokens.push_back(make_shared<Token>(t->value));
    }
    return m;
  }

  // reverts the system to a state represented by the token
  void revert(const Memento& m)
  {
    tokens = m.tokens;
  }
};

int main()
{
    TokenMachine machine;
    
    auto t1 = make_shared<Token>(5);
    auto m1 = machine.add_token(t1); // add token with value 5
    
    auto t2 = make_shared<Token>(10);
    auto m2 = machine.add_token(t2); // add token with value 10
    
    t1->value = 20; // change t1 value to 20
    
    auto m3 = machine.add_token(t1); // add token with value 20
    
    machine.revert(m1); // revert to state after adding t1 (value 5)
    
    for (const auto& token : machine.tokens)
    {
      cout << "Token value: " << token->value << endl; // should print only token with value 5
    }
    
    return 0;
}