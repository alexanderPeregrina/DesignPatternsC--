// Command design pattern: Encapsulates requests/operations as objects.
#include <iostream>
#include <vector>

using namespace std;
 
class BankAccount 
{
  double balance;
  double overdraft_limit{-500};

public:
  BankAccount(double balance, double overdraft_limit): 
  balance(balance), overdraft_limit(overdraft_limit)
  {

  }

  BankAccount(double balance): balance(balance)
  {

  }

  bool deposit(double amount)
  {
    balance += amount;

    cout <<"Deposited amount: " << amount
        << ", balance is now " << balance << endl;

    return true; 
  }

  bool withdraw(double amount)
  {
    if ((balance - amount) >= overdraft_limit)
    {
      balance -= amount;
  
      cout << "Withdrew amount: " << amount
         << ", balance is now " << balance << endl;

      return true;
    }
    return false;
  }

};

class ICommand
{
  virtual void call() = 0;
  virtual void undo() = 0;
};

class BankAccountCommand : public ICommand
{
  BankAccount& account;

  double amount;

public:
  bool succeded{false};
  enum Action {deposit, withdraw} action;

  BankAccountCommand(BankAccount& account, Action action, double amount):
  account(account), action(action), amount(amount)
  {

  }
  void call() override
  {
    switch (action)
    {
      case deposit:
        succeded = account.deposit(amount);
        break;

      case withdraw:
        succeded = account.withdraw(amount);
        break;
    }
  }

  void undo() override
  {
    switch(action)
    {
      case deposit:
        if (succeded)
          account.withdraw(amount);
        break;
      case withdraw:
        if (succeded)
          account.deposit(amount);
        break;
    }
  }

};

class CompositeBankAccountCommand : public vector<BankAccountCommand>, ICommand
{
public:
  CompositeBankAccountCommand(const initializer_list<BankAccountCommand>& items):
  vector(items)
  {

  }

  void call() override
  {
    for(auto& it : *this)
    {
      it.call();
    }
  }

  void undo() override
  {
    for (auto it = this->rbegin(); it != this->rend(); ++it)
    {
      it->undo();
    }

  }
};

struct DependentCompositeCommand : public CompositeBankAccountCommand
{
  DependentCompositeCommand(const initializer_list<BankAccountCommand>& items):
  CompositeBankAccountCommand(items)
  {

  }

  void call() override
  {
    bool ok = true;
    for (auto& cmd : *this)
    {
     if (ok)
     {
        cmd.call();
        ok = cmd.succeded;
     }
     else
     {
        cmd.succeded = false;
     }
    }
  }

    void undo() override
  {
    for (auto it = this->rbegin(); it != this->rend(); ++it)
    {
      it->undo();
    }

  }
};

class MoneyTransferCommand : public DependentCompositeCommand
{
public:
  MoneyTransferCommand(BankAccount& from, BankAccount& to, double amount)
  : DependentCompositeCommand(
    {
      BankAccountCommand{from, BankAccountCommand::withdraw, amount},
      BankAccountCommand{to, BankAccountCommand::deposit, amount}
    })
  {

  }
};

int main()
{
  
  BankAccount account{200.0};
  BankAccountCommand ba_command{account, BankAccountCommand::withdraw, 100.0};
  ba_command.call();

  vector<BankAccountCommand> commands{BankAccountCommand{account, BankAccountCommand::deposit, 100.0},
                                      BankAccountCommand{account, BankAccountCommand::deposit, 300.0},
                                      BankAccountCommand{account, BankAccountCommand::withdraw, 20.0},
                                      BankAccountCommand{account, BankAccountCommand::withdraw, 80.0}};

  // Apply all canges in command
  for(auto& it : commands)
  {
    it.call();
  }                                      

  // Undo all operations in commands in reverse order
  for(auto it = commands.rbegin(); it != commands.rend(); ++it)  
  {
    it->undo();
  }
  

  // Simulate transfer
  cout << "***** Simulation of transfer ****\n";
  BankAccount account2{0.0};
  MoneyTransferCommand transfer{account, account2, 50.0};
  transfer.call();
  cout << "***** Simulation of transfer 2****\n";
  MoneyTransferCommand transfer2{account, account2, 5000.0};
  transfer2.call();

  return 0;
}