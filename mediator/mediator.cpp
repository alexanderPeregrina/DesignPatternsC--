/*
Mediator Design Pattern: A component that facilitates communication between different other components
without them needing to refer to each other directly.

ChatRoom example: A chat room where users can send messages to each other through the chat room mediator.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declarations
struct ChatRoom;

struct Person
{
  string name;
  ChatRoom* room{nullptr};

  Person(const string& name);

  void say(const string& message);

  void receive(const Person& origin, const string& message);

  void private_message(Person& who, const string& message);
};

// The mediator
class ChatRoom
{
  vector<Person*> people;
  Person room{"room"};
public:
  ChatRoom()
  {

  }
  // A message to everyone in the chat room
  void broadcast(const Person& origin, const string& message)
  {
    for (auto& p : people)
    {
      if(p->name != origin.name)
      {
        p->receive(origin, message);
      }
    }
  }
  // a message to a specific person
  void message(const Person& origin, Person& who, const string& message)
  {
    who.receive(origin, message);
  }

  void join(Person& p)
  {
    p.room = this;
    broadcast(room, p.name + " joins the chat");
    people.push_back(&p);
  }
};



  Person::Person(const string& name): name(name)
  {

  }

  void Person::say(const string& message)
  {
    if(room)
    {
      room->broadcast(*this, message);
    }
  }

  void Person::receive(const Person& origin, const string& message)
  {
    string s{origin.name + ": " + message};

    cout << "[" << name << "'s chat session] " << s << endl;
  }

  void Person::private_message(Person& who, const string& message)
  {
    if(room)
    {
      room->message(*this, who, message);
    }
  }

int main()
{
  ChatRoom room;
  Person john{"John"};
  Person jane{"Jane"};
  Person simon{"Simon"};

  room.join(john);
  room.join(jane);
  john.say("Hello Everyone!");
  jane.say("Hi, John!");
  room.join(simon);
  simon.say("Hello folks, I'm glad to join you!");
  john.say("Welcome Simon!");
  jane.private_message(simon, "Welcome my friend!");
  simon.private_message(jane, "Thank you Jane!");

  return 0;
}