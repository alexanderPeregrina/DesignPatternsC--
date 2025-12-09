/*
Observer Pattern: The purpose of this pattern is to get notifications of particular changes in the system.
*/

#include <iostream>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;

template <typename T>
class Observer
{
  public:
  virtual void field_changed(const T& obj, const string& field_name)=0;
};

template <typename T>
class Observable
{
  vector<Observer<T> *> observers;
  mutex mtx;
public:
  vector<Observer<T>*> get_observers()
  {
    lock_guard<mutex> lock{mtx};
    return observers;
  }
  void subscribe(Observer<T> *p_observer)
  {
    lock_guard<mutex> lock{mtx};
    observers.push_back(p_observer);
  }

  void unsubscribe(Observer<T> *p_observer)
  {
    lock_guard<mutex> lock{mtx};
    observers.erase(remove(observers.begin(), observers.end(), p_observer), observers.end());
  }

  void notify(Observer<T> *p_observer, const T& obj, const string& field_name)
  {
    p_observer->field_changed(obj, field_name);
  }
};

class Person : public Observable<Person>
{
  int age;
public:
  Person(int age): age(age){}

  int getAge() const {return age;}

  void setAge(int age)
  {
    if (this->age == age)
      return;
    this->age = age;
    for(auto p_observer : get_observers())
    {
      notify(p_observer, *this, "age");
    }
  }

};

class PersonObserver : public Observer<Person>
{
  void field_changed(const Person& person, const string& field_name) override
  {
    cout <<"Person's " << field_name << " has changed to " ;
    if (field_name == "age")
      cout << person.getAge() << endl;
  }
};

int main()
{
  Person person{20};
  PersonObserver observer;
  person.subscribe(&observer);
  person.setAge(21);
  person.setAge(22);
  person.unsubscribe(&observer);
  person.setAge(23);
  return 0;
}