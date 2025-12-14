/*

Visitor Coding Exercise
You are asked to implement a double-dispatch visitor called ExpressionPrinter  
for printing different mathematical expressions. The range of expressions covers 
addition and multiplication - please put round brackets around addition but not around multiplication!
Also, please avoid any blank spaces in output.

Example:

Input: AdditionExpression{Literal{2}, Literal{3}}  -- btw, this is pseudocode, you cannot inline those references unfortunately
Output: (2+3) 
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;


struct ExpressionVisitor
{
  virtual void accept(Value& v) = 0;
  virtual void accept(AdditionExpression& ae) = 0;
  virtual void accept(MultiplicationExpression& me) = 0;

};

struct Expression
{
  virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
  int value;

  Value(int value) : value(value) {}

  void visit(ExpressionVisitor& ev) override
  {
    ev.accept(*this);
  }
};

struct AdditionExpression : Expression
{
  Expression &lhs, &rhs;

  AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor& ev) override
  {
    ev.accept(*this);
  }
};

struct MultiplicationExpression : Expression
{
  Expression &lhs, &rhs;

  MultiplicationExpression(Expression &lhs, Expression &rhs)
    : lhs(lhs), rhs(rhs) {}

  void visit(ExpressionVisitor& ev) override
  {
    ev.accept(*this);
  }
};

struct ExpressionPrinter : ExpressionVisitor
{
  
  void accept(Value& v) override
  {
    oss << v.value;
  }

  void accept(AdditionExpression& ae) override
  {
    oss << "(";
    ae.lhs.visit(*this);
    oss << "+";
    ae.rhs.visit(*this);
    oss << ")";

  }

  void accept(MultiplicationExpression& me) override
  {
    me.lhs.visit(*this);
    oss << "*";
    me.rhs.visit(*this);
  }

  string str() const 
  {
    return oss.str();
  }

private:
  ostringstream oss;
};

int main()
{
  // 2*(5+3)
  Value v2{2};
  Value v3{3};
  Value v5{5};
  AdditionExpression addition{v5, v3};
  auto e = new MultiplicationExpression{v2, addition};

  ExpressionPrinter ep;

  e->visit(ep);

  cout << ep.str() << endl;
  return 0;
}