/* 
Mediator Coding Exercise
Our system has any number of instances of Participant  classes. Each Participant has a value  integer, initially zero.

A participant can say()  a particular value, which is broadcast to all other participants. At this point in time, 
every other participant is obliged to increase their value  by the value being broadcast.

Example:

Two participants start with values 0 and 0 respectively
Participant 1 broadcasts the value 3. We now have Participant 1 value = 0, Participant 2 value = 3
Participant 2 broadcasts the value 2. We now have Participant 1 value = 2, Participant 2 value = 3

*/
#include <iostream>
#include <vector>

using namespace std;

struct Participant;

struct Mediator
{
  vector<Participant*> participants;
  
};

struct IParticipant
{
    
};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void say(int value)
    {
      for (auto& p_participant : mediator.participants)
      {
        if (p_participant != this)
        {
          p_participant->value += value;
        }
      }
    }
};

int main()
{
  Mediator mediator;
  Participant p1{mediator};
  Participant p2{mediator};

  p1.say(2);

  p2.say(3);

    cout << "Participant 1 value: " << p1.value << endl; // Should be 3
    cout << "Participant 2 value: " << p2.value << endl; // Should be 2
}