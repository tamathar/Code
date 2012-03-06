//Thomas Scroggins
//CS 356 Assignment 2
//This program calculates left-hand Reimann Sums, and times how long it takes to do so for various ranges.

#include <windows.h>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double start, stop;
	while(true)
	{
		int endpoint;
		cout << "How far to sum: ";
		cin >> endpoint;
		
		double sum = 0;
			
		start = GetTickCount();
			
		for(int k = 0; k < endpoint; k++)
			sum += pow(-1, k+1)*(4/(2*k+1));
				
		stop = GetTickCount();
			
		//cout << sum << endl;
		cout << (double)stop-start << endl;		
	}
}