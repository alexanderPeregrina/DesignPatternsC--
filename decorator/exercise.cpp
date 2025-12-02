/*
Roses can be red, blue or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower and 
BlueFlower that would print the following:

*/
#include <iostream>
#include <string>

using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  Rose()
  {

  }
  string str() override {
    return "A rose";
  }
};

struct RedFlower : Flower
{
  Flower& flower;
  RedFlower(Flower& flower): flower(flower)
  {

  }
  string str() override
  {
    string base_str = flower.str();
    if ((base_str.find("blue") != string::npos) && (base_str.find("red") != string::npos))
      return "A rose that is red and blue";
    else if (base_str.find("blue") != string::npos)
      return flower.str() + " and red";
    else
      return flower.str() + " that is red";
  }
};

struct BlueFlower : Flower
{
  Flower& flower;
  BlueFlower(Flower& flower): flower(flower)
  {

  }
  string str() override
  {
    string base_str = flower.str();
    if ((base_str.find("blue") != string::npos) && (base_str.find("red") != string::npos))
      return " A rose that is red and blue";
    else if (base_str.find("red") != string::npos)
      return flower.str() + " and blue";
    else
      return flower.str() + " that is blue";
  }
};

int main()
{
  Rose rose;
  RedFlower red_rose{rose};
  RedFlower red_red_rose{red_rose};
  BlueFlower blue_red_rose{red_rose};
  cout << rose.str() << endl;          // "A rose"
  cout << red_rose.str() << endl;      // "A rose that is red"
  cout << red_red_rose.str() << endl;  // "A rose that is red"
  cout << blue_red_rose.str() << endl; // "A rose that is red and blue"

  return 0;
}