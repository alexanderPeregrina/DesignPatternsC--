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

  Command(Action action, int amount): action(action), amount(amount)
  {

  }
  bool success{false};

  virtual void call()=0;
};

struct Account
{
  int balance{0};

  void process(Command* cmd)
  {
    cmd->call();
  }
};


struct BankAccountCommand : Command
{
  Account& account;
   BankAccountCommand(Account& account, Command::Action action, int amount):
   account(account), Command(action, amount)
   {

   }

   void call()
   {
    switch (action)
    {
      case Command::deposit:
        account.balance += amount;  
        success = true;
        break;
    
      case Command::withdraw:
        if (account.balance >= amount)
        {
          account.balance -= amount;
          success = true;
        }
        else
        {
          success = false;
        }

        break;
    }
   }
};

int main()
{
  Account account{100}; 
  BankAccountCommand cm1{account, Command::deposit, 50};
  BankAccountCommand cm2{account, Command::withdraw, 25};
  BankAccountCommand cm3{account, Command::withdraw, 50};

  account.process(&cm1);
  account.process(&cm2);
  account.process(&cm3);


  // Action should be 75, last command shall not be executed
  cout << account.balance << endl;

}
