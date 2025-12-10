/*

State Coding Exercise
A combination lock is a lock that opens after the right digits have been entered. A lock is preprogrammed with a combination (e.g., 12345 ) and the user is expected to enter this combination to unlock the lock.

The lock has a status  field that indicates the state of the lock. The rules are:

If the lock has just been locked (or at startup), the status is LOCKED.
If a digit has been entered, that digit is shown on the screen. As the user enters more digits, they are added to Status.
If the user has entered the correct sequence of digits, the lock status changes to OPEN.
If the user enters an incorrect sequence of digits, the lock status changes to ERROR.
Please implement the CombinationLock  class to enable this behavior. Be sure to test both correct and incorrect inputs.

*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class LockState
{
  LOCKED,
  ENTERING,
  OPEN,
  ERROR
};


class CombinationLock
{
    vector<int> combination;
    LockState state;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination) {
      state = LockState::LOCKED;
      state_machine_handler();
    }

    void enter_digit(int digit)
    {
      if(state == LockState::LOCKED)
      {
          state = LockState::ENTERING;
      }
      state_machine_handler(digit);
    }
private:
    void state_machine_handler(int digit = 0)
    {
       static size_t count = 0u;
       switch(state)
       {
          case LockState::LOCKED:
            status = "LOCKED";
            break;  
          case LockState::ENTERING:
            if(count == 0u)
            {
              status = to_string(digit);
              count++;
      
            }
            else
            {
              status += to_string(digit);
              count++;
              if(count >= combination.size())
              {
                 bool combination_ok = true;
                 // Check if combination is OK
                 for(size_t i = 0; i < combination.size(); ++i)
                 {
                  if((status[i] - '0') != combination[i])
                  {
                    combination_ok = false;
                    break;
                  }
                }
                if (combination_ok)
                {
                  status = "OPEN";
                  state = LockState::OPEN;
                  count = 0;
                }
                else
                {
                  count = 0;
                  status = "ERROR";
                  state = LockState::ERROR;
                }
              }
            }
          break;
          case LockState::OPEN:
          // handle OPEN state
          break;
          case LockState::ERROR:
          // handle ERROR state
          break;
       }
    }
};

int main()
{
  CombinationLock lock({1,2,3});
  cout << lock.status << endl; // LOCKED
  lock.enter_digit(1);
  cout << lock.status << endl; // 1
  lock.enter_digit(2);
  cout << lock.status << endl; // 12
  lock.enter_digit(3);
  cout << lock.status << endl; // OPEN

  return 0;
}