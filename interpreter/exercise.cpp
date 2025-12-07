/*
Intepreter design pattern: Used to define and evaluate the grammar of a lenguage or expression 
in a flexible and extensible way.

Interpreter Coding Exercise
You are asked to write an expression processor for simple numeric expressions with the following 
constraints:

Expressions use integral values (e.g., "13" ), single-letter variables defined in variables , 
as well as + and - operators only
There is no need to support braces or any other operations
If a variable is not found in Variables  
(or if we encounter a variable with >1 letter, e.g. ab), 
the evaluator returns 0 (zero)
In case of any parsing failure, evaluator returns 0
Example:

calculate("1+2+3")  should return 6
calculate("1+2+xy")  should return 0
calculate("10-2-x")  when x=3 is in variables should return 5

*/
#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <memory>

using namespace std;

struct Token
{
  enum Type {integer, plus, minus, variable, invalid} type;
  string text;

  Token(Type type, const string& text): type(type), text(text)
  {

  }
}; 


struct Element
{
  virtual int eval() = 0;
};

struct IntegerElement : Element
{
  int value;

  IntegerElement(int value): value(value)
  {

  }

  int eval() override
  {
    return value;
  }
};

struct BinaryOperation : Element
{
  shared_ptr<Element> lhs, rhs;
  enum Operation {addition, substraction} type;

  int eval() override
  {
    if (type == addition)
    {
      if (lhs == nullptr || rhs == nullptr)
        return 0;
      return lhs->eval() + rhs->eval();
    }
    else
    { 
      if (lhs == nullptr || rhs == nullptr)
        return 0;
      return lhs->eval() -  rhs->eval();
    }
  }

};

struct ExpressionProcessor
{
  map<char,int> variables;

  ExpressionProcessor()
  {

  }

  ExpressionProcessor(const map<char, int>& vars): variables(vars)
  {

  }

  vector<Token> lex(const string& expression)
  {
    vector<Token> result;
    for (char ch : expression)
    {
      switch(ch)
      {
        case '+':
          result.push_back(Token{Token::plus, "+"});
          break;
        case '-':
          result.push_back(Token{Token::minus, "-"});
          break;
        default:
          if (isdigit(ch))
          {
            result.push_back(Token{Token::integer, string(1, ch)});
          }
          else if(isalpha(ch))
          {
            result.push_back(Token{Token::variable, string(1, ch)}); 
          }
          else
          {
            result.push_back(Token{Token::invalid, string(1, ch)});
          }
          break;
      }
    }
  
    return result;
  }

  shared_ptr<Element> parse(const vector<Token>& tokens, const map<char, int>& variables)
  {
  
    // Base case: empty token list
    if (tokens.size() == 0)
      return nullptr;
    // Base case, 1 token
    if (tokens.size() == 1)
    {
      if (tokens[0].type == Token::integer)
        return make_shared<IntegerElement>(stoi(tokens[0].text));
      else if(tokens[0].type == Token::variable)
      {
        if (tokens[0].text.size() == 1 && variables.find(tokens[0].text[0]) != variables.end())
          return make_shared<IntegerElement>(variables.at(tokens[0].text[0]));
      }
      return nullptr;
    }
  
    shared_ptr<BinaryOperation> result = make_shared<BinaryOperation>();
    bool have_lhs = false;
    
    for(size_t i=0; i < tokens.size(); ++i)
    {
      auto& token = tokens[i];
      switch (token.type)
      {
        case Token::plus:
          result->type = BinaryOperation::addition;
          break;
        case Token::minus:
          result->type = BinaryOperation::substraction;
          break;
        case Token::invalid:
          return nullptr;
  
        case Token::variable:
          // check if variable is in the variables map
          if (token.text.size() != 1 || variables.find(token.text[0]) == variables.end())
          {
            return nullptr;
          }
          else
          {
            if(!have_lhs)
            {
              result->lhs = make_shared<IntegerElement>(variables.at(token.text[0]));
              have_lhs = true;
            }
            else
            {
              // next element shall be operator not number nor variable
              if (i+1 < tokens.size() && tokens[i+1].type != Token::plus &&
                  tokens[i+1].type != Token::minus)
                  return nullptr;
              vector<Token> rest_tokens(tokens.begin()+i, tokens.end());
              auto element = parse(rest_tokens, variables);
              result->rhs = element;
              return result;
            }
          }
          break;
        case Token::integer:
          if (!have_lhs)
          {
            result->lhs = make_shared<IntegerElement>(stoi(token.text));
            have_lhs = true;
          }
          else
          {
            // next element shall be operator not number nor variable
            if (i+1 < tokens.size() && tokens[i+1].type != Token::plus &&
                tokens[i+1].type != Token::minus)
              return nullptr;
  
            vector<Token> rest_tokens(tokens.begin()+i, tokens.end());
            auto element = parse(rest_tokens, variables);
            result->rhs = element;
            return result;
  
          }
          break;
      }
    }
  
    return result;
  }

  int calculate(const string& expression)
  {
    // Lexing part
    vector<Token> tokens = lex(expression);
    // parsing part
    int result=0;
    auto element = parse(tokens, variables);

    if (element == nullptr)
    {
      return 0;
    }
    else
    {
      result = element->eval();
    }

    return result;
  }
};

int main()
{
  map<char, int> vars{{'x', 4}};
  ExpressionProcessor ep{vars};
    
  cout << ep.calculate("1+2+3") << endl; // should return 6
  cout << ep.calculate("1+2+x") << endl; // should return 7
  cout << ep.calculate("1+2+xy") << endl; // should return 0

  return 0;
}