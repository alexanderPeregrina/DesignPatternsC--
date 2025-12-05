/*

Command Coding Exercise
Implement the Account::process()  function to process different account commands. 
The rules are obvious:

success  indicates whether the operation was successful
You can only withdraw money if you have enough in your account

Solution 1:
*/
#include <iostream>

using namespace std;

struct Command
{
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};

  Command(Action action, int amount):
  action(action), amount(amount)
  {

  }
};

struct Account
{
  int balance{0};

  void process(Command& cmd)
  {
    switch (cmd.action)
    {
      case Command::deposit:
        balance += cmd.amount;  
        cmd.success = true;
        break;
    
      case Command::withdraw:
        if (balance >= cmd.amount)
        {
          balance -= cmd.amount;
          cmd.success = true;
        }
        else
        {
          cmd.success = false;
        }

        break;
    }
  }
};


int main()
{
  Account account{100}; 
  Command cm1{Command::deposit, 50};
  Command cm2{Command::withdraw, 25};
  Command cm3{Command::withdraw, 50};

  account.process(cm1);
  account.process(cm2);
  account.process(cm3);


  // Action should be 75, last command shall not be executed
  cout << account.balance << endl;

}
