/**
  * \file test2.cpp
  * \author Rob Byrd (edited by Thomas Scroggins)
  * \date 3-7-2012
  * \class TComplex [test2.h] [TComplex]	
  * \brief This is the header for a class that makes a datatype for complex numbers and overloads several operators to accept them.
  */

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
