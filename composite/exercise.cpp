/*
Consider the code presented below. The sum()  function takes a vector of pointers 
to either SingleValue or ManyValues instances and adds up all their elements together.

Please complete the implementation so that the sum() function starts to operate 
correctly. This may involve giving the classes a common interface, among other things.

*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class ContainsIntegers
{
public:
  virtual int sum()=0;
};

class SingleValue : public ContainsIntegers
{
  int value;
public:
  SingleValue()
  {
    value = 0;
  }


  SingleValue(int value): value(value){}

  int sum() override
  {
    return value;
  }

  friend ostream& operator<<(ostream& os, const SingleValue& singleValue)
  {
    os << "The Value is " << singleValue.value << endl;
    return os;
  } 
};

class ManyValues : public vector<int>, public ContainsIntegers
{

public:
  int sum() override
  {
    return accumulate(this->begin(), this->end(), 0);
  }

  void add(const int value)
  {
    this->push_back(value);
  }

  friend ostream& operator<<(ostream& os, const ManyValues& manyValues)
  {
    for (const auto& vals : manyValues)
    {
      os << vals;
    }
    return os;
  } 
};

int sum(const vector<ContainsIntegers*> items)
{
  int result = 0;
  for (auto& it : items)
  {
    result += it->sum();
  }
  return result;
}

int main()
{
  SingleValue single_value{ 1 };
  ManyValues other_values;
  other_values.add(2);
  other_values.add(3);
  int total_sum = sum({ &single_value, &other_values }); // returns 6 

  cout << "The total sum is: " << total_sum << endl; 
}