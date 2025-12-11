/*
Strategy Coding Exercise
Consider the quadratic equation and its canonical solution:

x1, x2 = (-b +- sqrt(b^2-4ac))/2a

The part b^2-4*a*c is called the discriminant. 
Suppose we want to provide an API with two different strategies for calculating the discriminant:

In OrdinaryDiscriminantStrategy , If the discriminant is negative, we return it as-is. 
This is OK, since our main API returns std::complex  numbers anyway.

In RealDiscriminantStrategy , if the discriminant is negative, the return value is NaN (not a number). 
NaN propagates throughout the calculation, so the equation solver gives two NaN values.
Please implement both of these strategies as well as the equation solver itself.

With regards to plus-minus in the formula, please return the + result as the first element and - as the second.

*/
#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>

using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
  double calculate_discriminant(double a, double b, double c) override
  {
    return (b * b) - (4*a*c);  
  }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
  double calculate_discriminant(double a, double b, double c) override
  {
    double discriminant = (b * b) - (4*a*c);  
    if (discriminant < 0)
      return NAN;
    else
      return discriminant;
  }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
      tuple<complex<double>, complex<double>> result;
      double discriminant = strategy.calculate_discriminant(a, b, c);
      complex<double> complex_disc{discriminant, 0};
      complex<double> temp = sqrt(complex_disc);

      get<0>(result) = 0.5 * (1/a) * (-b + temp); 
      get<1>(result) = 0.5 * (1/a) * (-b - temp); 

      return result;
    }
};

int main()
{
  // Using real discriminant
  RealDiscriminantStrategy real_strategy;
  QuadraticEquationSolver solver1{real_strategy};
  tuple<complex<double>, complex<double>> result1 = solver1.solve(1, 6, 9);
  cout << "Result (x1, x2): " << get<0>(result1) << endl;
  cout << "Result for x2: " << get<1>(result1) << endl;

  // negative discriminant case:
  result1 = solver1.solve(1, 1, 1);
  cout << "Result for x1: " << get<0>(result1) << endl;
  cout << "Result for x2: " << get<1>(result1) << endl;

// Using complex discriminant
  OrdinaryDiscriminantStrategy ordinary_strategy;
  QuadraticEquationSolver solver2{ordinary_strategy};
  tuple<complex<double>, complex<double>> result2 = solver2.solve(1, 6, 9);
  cout << "Result for x1: " << get<0>(result2) << endl;
  cout << "Result for x2: " << get<1>(result2) << endl;

  // negative discriminant case:
  result2 = solver2.solve(1, 1, 1);
  cout << "Result for x1: " << get<0>(result2) << endl;
  cout << "Result for x2: " << get<1>(result2) << endl;

  return 0;
}