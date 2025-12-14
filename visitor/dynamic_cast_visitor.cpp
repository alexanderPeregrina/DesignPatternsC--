
/*
Dynamic cast visitor design pattern: Component that allows to traverse the entire hierarchy to add a new feature.
Downside, you have to cast and check all classes that will have this new functionality.

*/
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Expression
{
  virtual ~Expression() =  default;
};

struct DoubleExpression : public Expression
{
  double value;
  DoubleExpression(double value): value(value)
  {

  }
};

struct AdditionExpression : public Expression
{
  Expression *left, *right;
  AdditionExpression(Expression* left, Expression* right):
  left(left), right(right)
  {

  }

  ~AdditionExpression()
  {
    delete left, right;
  }
};

struct ExpressionPrinter
{
  ostringstream oss;
  string str() const
  {
    return oss.str();
  }

  void print(Expression* expression)
  {
    if (auto de = dynamic_cast<DoubleExpression*>(expression))
    {
      oss << de->value;
    }
    else if (auto ae = dynamic_cast<AdditionExpression*>(expression))
    {
      oss << "(";
      print(ae->left);
      oss <<" + ";
      print(ae->right);
      oss << ")";

    }
  }
};

int main()
{
  AdditionExpression *p_addition = new AdditionExpression{new DoubleExpression{1}, 
                                                          new AdditionExpression{new DoubleExpression{2},
                                                          new DoubleExpression{3}}};

  ExpressionPrinter ex_printer;

  ex_printer.print(p_addition);

  cout << ex_printer.str() << endl; 
  return 0;
}