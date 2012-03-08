/**
  * \file test2testharness.cpp
  * \author Thomas Scroggins
  * \date 3-7-2012
  * \brief This is Google test code for the TComplex class. I don't have gtest installed so I apologize for simple typos
  */

#include "test2.h"
#include "gtest/gtest.h"
#include <sstream>
using namespace std;
using namespace Complex;

//Tests the constructors
//Asserts because if they don't work right the other tests will not either
TEST(TComplex, Constructors) {
	
	TComplex c1;
	ASSERT_EQ( 0, c1.r());
	ASSERT_EQ( 0, c1.i());
	
	TComplex c2(3, 4.5);
	ASSERT_EQ( 3, c1.r());
	ASSERT_EQ( 4.5, c1.i());
	
	TComplex c3(c2);  
	ASSERT_EQ( 3, c1.r());
	ASSERT_EQ( 4.5, c1.i());
}

//Tests the assignment operator
//Asserts because if assignment doesn't work right the other tests will not either
TEST(TComplex, Assignment) {
	
	TComplex c1;
	TComplex c2(3, 4.5);
	
	c1 = c2;
	ASSERT_EQ(c1.r(), c2.r());
	ASSERT_EQ(c1.i(), c2.i());
}

//Tests addition
TEST(TComplex, Addition) {
	
	TComplex c1(3, 4.5);
	TComplex c2(3, 4.5);
	TComplex c3(-3, -4.5);
	TComplex c4(6, 9);
	TComplex c5(0, 0);
	
	EXPECT_EQ(c4, (c1+c2));
	EXPECT_EQ(c5, (c1+c3));
}	

//Tests subtract
TEST(TComplex, Subtraction) {
	
	TComplex c1(3, 4.5);
	TComplex c2(3, 4.5);
	TComplex c3(-3, -4.5);
	TComplex c4(6, 9);
	TComplex c5(0, 0);
	
	EXPECT_EQ(c5, (c1-c2));
	EXPECT_EQ(c4, (c1-c3));
}

//Tests division
TEST(TComplex, Division) {
	
	TComplex c1(3, 4.5);
	TComplex c2(3, 4.5);
	TComplex c3(-3, -4.5);
	TComplex c4(-1, 0);
	TComplex c5(1, 0);
	
	EXPECT_EQ(c4, (c1/c3));
	EXPECT_EQ(c5, (c1/c2));
}

//Tests multiplication
TEST(TComplex, Multiplication) {
	
	TComplex c1(3, 4);
	TComplex c2(3, 4);
	TComplex c3(-3, -4);
	TComplex c4(-7, 24);
	TComplex c5(7, -24);
	
	EXPECT_EQ(c5, (c1*c3));
	EXPECT_EQ(c4, (c1*c2));
	
	TComplex c6(6, 8);
	TComplex c7(0, 0);
	
	EXPECT_EQ(c6, (c1*2));
	EXPECT_EQ(c7, (c1*0));	
}

//Tests equality
TEST(TComplex, Multiplication) {
	
	TComplex c1(3, 4);
	TComplex c2(3, 4);
	TComplex c3(-3, -4);
	
	EXPECT_TRUE(c1==c2);
	EXPECT_FALSE(c1!=c2);
	EXPECT_TRUE(c1!=c3);
	EXPECT_FALSE(c1==c2);
}

//Test <<
TEST(TComplex, Print) {
	
	stringstream ss;
	string output;
	TComplex c1(3,4);
	TComplex c2(0,0);
	
	ss << c1;
	ss >> output;
	EXPECT_EQ( "(3 + 4i)", output);
	
	ss << c2;
	ss >> output
	EXPECT_EQ("(0 0i)", output);
}

int main()
{
	RUN_ALL_TESTS();
}

