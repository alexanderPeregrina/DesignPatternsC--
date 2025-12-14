
/*
Dynamic cast visitor design pattern: Component that allows to traverse the entire hierarchy to add a new feature.
Downside, you have to cast and check all classes that will have this new functionality.

*/
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor
{
  virtual void visit(DoubleExpression* de) = 0;
  virtual void visit(AdditionExpression* ae) = 0;
  virtual void visit(SubstractionExpression* se) = 0;

};

struct Expression
{
  virtual ~Expression() =  default;
  virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : public Expression
{
  double value;
  DoubleExpression(double value): value(value)
  {

  }

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }
};

struct AdditionExpression : public Expression
{
  Expression *left, *right;
  AdditionExpression(Expression* left, Expression* right):
  left(left), right(right)
  {

  }

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }

  ~AdditionExpression()
  {
    delete left;
    delete right;
  }
};


struct SubstractionExpression : public Expression
{
  Expression *left, *right;
  SubstractionExpression(Expression* left, Expression* right):
  left(left), right(right)
  {

  }

  void accept(ExpressionVisitor* visitor) override
  {
    visitor->visit(this);
  }

  ~SubstractionExpression()
  {
    delete left;
    delete right;
  }
};

struct ExpressionPrinter: ExpressionVisitor
{
  ostringstream oss;
  string str() const 
  {
    return oss.str();
  }

  void visit(DoubleExpression* de) override
  {
    oss << de->value;
  }

  void visit(AdditionExpression* ae) override
  {

    // check if braces are required, if right not double we need braces
    auto isa_double = dynamic_cast<DoubleExpression*>(ae->right);

    ae->left->accept(this);
    oss << " + ";
    if(!isa_double)
      oss << "(";
    ae->right->accept(this);
    if(!isa_double)
      oss << ")";
  }

  void visit(SubstractionExpression* se) override
  {
    // check if braces are required, if right not double we need braces
    auto isa_double = dynamic_cast<DoubleExpression*>(se->right);

    se->left->accept(this);
    oss << " - ";
    if(!isa_double)
      oss << "(";
    se->right->accept(this);
    if(!isa_double)
      oss << ")";

  }
};

struct ExpressionEvaluator : ExpressionVisitor
{
  double result;
  void visit(DoubleExpression* de) override
  {
    result = de->value;
  }

  void visit(AdditionExpression* ae) override
  {
    ae->left->accept(this);
    double temp = result;
    ae->right->accept(this);

    result += temp;
  }

  void visit(SubstractionExpression* se) override
  {
    se->left->accept(this);
    double temp = result;
    se->right->accept(this);
    result = temp - result;
  }

};

int main()
{
  // 1 + (2 - 3)
  AdditionExpression *p_addition = new AdditionExpression{new DoubleExpression{1}, 
                                                          new SubstractionExpression{new DoubleExpression{2},
                                                          new DoubleExpression{3}}};


  ExpressionPrinter ep;

  ExpressionEvaluator ee;

  p_addition->accept(&ep);
  p_addition->accept(&ee);

  cout << ep.str() <<" = "<< ee.result << endl; 

  return 0;

}