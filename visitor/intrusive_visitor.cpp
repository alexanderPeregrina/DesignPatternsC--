
/*
Intrusive visitor design pattern: Component that allows to traverse the entire hierarchy to add a new feature.
Downside, you have to implement the new functionality in every class of the hierarchy.

*/
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Expression
{
  virtual ~Expression() =  default;
  virtual void print(ostringstream& oss) = 0; // <---- Intrusive visitor
};

struct DoubleExpression : public Expression
{
  double value;
  DoubleExpression(double value): value(value)
  {

  }

  void print(ostringstream& oss) override
  {
    oss << value;
  }
};

struct AdditionExpression : public Expression
{
  Expression *left, *right;
  AdditionExpression(Expression* left, Expression* right):
  left(left), right(right)
  {

  }

  void print(ostringstream& oss)
  {
    oss << "(";
    left->print(oss);
    oss << " + ";
    right->print(oss);
    oss << ")";
  }

  ~AdditionExpression()
  {
    delete left, right;
  }
};

int main()
{
  AdditionExpression *p_addition = new AdditionExpression{new DoubleExpression{1}, 
                                                          new AdditionExpression{new DoubleExpression{2},
                                                          new DoubleExpression{3}}};

  ostringstream oss;                                                          
  p_addition->print(oss);

  cout << oss.str() << endl; 
  return 0;
}