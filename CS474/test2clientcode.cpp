/**
  * \file test2clientcode.h
  * \author Thomas Scroggins
  * \date 3-7-2012
  * \brief This is sample client code for the TComplex class. It loops around doing simple calculations using the class overloaded operators.
  */

#include "test2.h"
#include <cctype>
using namespace std;
using namespace Complex;

string makeUpper(string input)
{
	for(int i = 0; i < (int)input.length(); i++)
	{
		input[i] = toupper( input[i]);
	}
	return input;
}

int main()
{
	
	cout << "This programs runs mathematical operations on complex numbers.\n";
	
	while(true)
	{
		cout << "Please enter one of the following commands: add, subtract, multiply, divide, scalarMultiply, tilde, or quit.\n";
		string input;
		cin >> input;
		
		if(makeUpper(input) == "QUIT")
		{
			break;
		}
		
		double r, i;
		cout << "Enter real part of first number: ";
		cin >> r;
		cout << "Enter imaginary part of first number: ";
		cin >> i;
		TComplex num1(r, i);
		
		if(makeUpper(input) == "TILDE")
		{
			cout << "~" << num1 << " = " << ~num1 << endl;
		}
		else if(makeUpper(input) == "SCALARMULTIPLY")
		{
			cout << "Enter scalar number: ";
			cin >> r;
			cout << num1 << " * " << r << " = " << num1*r << endl;
		}
		else
		{
		
			cout << "Enter real part of second number: ";
			cin >> r;
			cout << "Enter imaginary part of second number: ";
			cin >> i;
			TComplex num2(r, i);			
		
			if(makeUpper(input) == "ADD")
			{
				cout << num1 << " + " << num2 << " = " << num1+num2 << endl;
			}
			else if(makeUpper(input) == "SUBTRACT")
			{
				cout << num1 << " - " << num2 << " = " << num1-num2 << endl;			
			}
			else if(makeUpper(input) == "MULTIPLY")
			{
				cout << num1 << " * " << num2 << " = " << num1*num2 << endl;			
			}
			else if(makeUpper(input) == "DIVIDE")
			{
				cout << num1 << " / " << num2 << " = " << num1/num2 << endl;					
			}
			else
			{
				cout << "Error: Invalid Command\n";
			}
		}
	}
	
}