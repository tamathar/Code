/**
  * \file test2.cpp
  * \author Rob Byrd (edited by Thomas Scroggins)
  * \date 3-7-2012
  * \class TComplex [test2.h] [TComplex]	
  * \brief This is the implementation a class that makes a datatype for complex numbers and overloads several operators to accept them.
  */

#include "test2.h"
using namespace std;


// implementation file-----------------------------

namespace Complex {

/**
  * \brief Standard Copy Constructor
  */
TComplex::TComplex()
	:real(0),
	 imaginary(0)
{}

/**
  * \brief  Constructor that takes 2 doubles.
  * \param[in] r The real part of the complex number.
  * \param[in] i The imaginary part of the complex number.
  */
TComplex::TComplex(double r, double i)
	:real(r),
	 imaginary(i)
{}

/**
  * \brief  Standard Copy Constructor
  * \param[in] otherComplex The complex number to be copied into the new one.
  */
TComplex::TComplex(const TComplex & otherComplex)
	:real(otherComplex.real),
	 imaginary(otherComplex.real)
{}

/**
  * \brief  Adds two values of type TComplex.
  * \param[in] oper The TComplex object on the right side of the operand.
  * \param[out] result The sum of *this and oper.
  */
TComplex TComplex::operator+(const TComplex & oper) const
{
    TComplex result;
    result.real  = real + oper.real;
    result.imaginary = imaginary + oper.imaginary;
    return result;
}

/**
  * \brief  Subtract the TComplex value on the right from the TComplex on the left of the operand.
  * \param[in] oper The TComplex object on the right side of the operand that will be subtracted from the other.
  * \param[out] result The difference of *this and oper.
  */
TComplex TComplex::operator-(const TComplex & oper) const
{
    TComplex result;
    result.real  = real - oper.real;
    result.imaginary = imaginary - oper.imaginary;
    return result;
}

/**
  * \brief  Multiplies two values of type TComplex.
  * \param[in] oper The TComplex object on the right side of the operand.
  * \param[out] result The product of *this and oper.
  */
TComplex TComplex::operator*(const TComplex & oper) const
{
    TComplex result;
    result.real  = real * oper.real - imaginary * oper.imaginary;
    result.imaginary = real * oper.imaginary + imaginary * oper.real;
    return result;
}

/**
  * \brief  Multiplies a TComplex number by a float/real number.
  * \param[in] oper The float number we are multiplying the TComplex by.
  * \param[out] result The product of *this and oper.
  */
TComplex TComplex::operator*(float oper) const
{
    TComplex result;
    result.real  = real * oper;
    result.imaginary = imaginary * oper;
    return result;
}

/**
  * \brief  Divides the TComplex on the left by the one on the right.
  * \param[in] oper The divisor this is of type TComplex.
  * \param[out] result The quotient of *this and oper.
  */
TComplex TComplex::operator/(const TComplex & oper) const
{   double temp;
    TComplex result;
    temp = oper.real * oper.real + oper.imaginary * oper.imaginary;
    result.real  = (real * oper.real + imaginary * oper.imaginary)/temp;
    result.imaginary = (imaginary * oper.real - real * oper.imaginary)/temp;
    return result;
}

/**
  * \brief  Finds the complement of a TComplex
  * \param[out] result The compliment of *this
  */
TComplex TComplex::operator~() const
{   double temp;
    TComplex result;
    temp = real * real + imaginary * imaginary;
    result.real  = real/temp;
    result.imaginary = -imaginary/temp;
    return result;
}

/**
  * \brief  Assigns the value of the TComplex number on the right to the TComplex on the left.
  * \param[in] rvalue The values we are assigning to the TComplex on the left.
  * \param[out] *this Return *this which now has the same values as rvalue.
  */
TComplex TComplex::operator=(const TComplex & rvalue)
{
    real = rvalue.real;
    imaginary = rvalue.imaginary;
    return *this;
}

/**
  * \brief  Checks to see if 2 TComplex numbers are equal.
  * \param[in] rvalue The right side value we are comparing.
  * \param[out] result A boolean value: true if the 2 are equal, false if they are not.
  */
bool TComplex::operator==(const TComplex & rvalue) const
{   if ((fabs(rvalue.real - real < .001))
     && (fabs(rvalue.imaginary - imaginary) < .001 ))
    return true;
    else
    return false;
}

/**
  * \brief  Checks to see if 2 TComplex numbers are not equal.
  * \param[in] rvalue The right side value we are comparing.
  * \param[out] result A boolean value: false if the 2 are equal, true if they are not.
  */
bool TComplex::operator!=(const TComplex & rvalue) const
{   if (float(rvalue.real - real)
     == float(rvalue.imaginary - imaginary))
    return false;
    else
    return true;
}

/**
  * \brief Prints out a TComplex value to the specified outstream.
  * \param[in] s A reference to the outstream to print to.
  * \param[in] oper The TComplex value to be printed.
  * \param[out] s A reference to the outstream for cascade printing.
  */
ostream & operator<<(ostream & s, const TComplex & oper)
{
  	if ( oper.i() > 0)
  	  s << "(" << oper.r() << " + " << oper.i() << "i)";
  	else
  	  s << "(" << oper.r() << " " << oper.i() << "i)";
  	return s;

}

/**
  * \brief Returns the real part of a TComplex value.
  * \param[out] real A double containing the real portion of the TComplex value.
  */
double TComplex::r() const
{
 	return real;
}

/**
  * \brief Returns the imaginary part of a TComplex value.
  * \param[out] imaginary A double containing the imaginary portion of the TComplex value.
  */
double TComplex::i() const
{
 	return imaginary;
}

}
