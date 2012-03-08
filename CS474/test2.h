/**
  * \file test2.h
  * \author Rob Byrd (edited by Thomas Scroggins)
  * \date 3-7-2012
  * \class TComplex [test2.h] [TComplex]	
  * \brief This is the header for a class that makes a datatype for complex numbers and overloads several operators to accept them. Function documentation in implementation.
  */

 
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Glossary=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * TComplex - The class name. It can be thought of as simply being a comlex number
 * real - The part of the complex number that is not the coefficient of i.
 * imaginary - The part of the complex number that is the coefficient of i. 
 * oper - RHS parameter of  an overloaded operator that does mathematical calculations (where the value is an operand of the function)
 * rvalue - RHS parameter of an overloaded operator that uses it for only its value (such as = or ==)
 * result - The variable that will eventually be the return value of the method. The answer of the function executed by the method.
 * sum - The result of adding 2 complex numbers according to standard mathematical rules.
 * product - The result of multiplying 2 complex numbers according to standard mathematical rules.
 * quotient - The result of dividing one complex number by another according to standard mathematical rules.
 * difference - The result of subtracting one complex number from another according to standard mathematical rules.
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
  
  
#include <cmath>
#include <iostream>
using namespace std;

// specification file ----------------------------------
namespace Complex {

class TComplex
{
  public:
  TComplex();
  TComplex(double r, double i);
  TComplex(const TComplex &);  
  TComplex operator+(const TComplex &) const;
  TComplex operator-(const TComplex &) const;
  TComplex operator=(const TComplex &);
  TComplex operator*(const TComplex &) const;
  TComplex operator/(const TComplex &) const;
  TComplex operator*(float ) const;
  TComplex operator~() const;
  bool operator!=(const TComplex &) const;
  bool operator==(const TComplex &) const;
  double r() const;
  double i() const;

 
  private:
  double real, imaginary;
};

ostream &operator<<(ostream &, const TComplex &);

}
