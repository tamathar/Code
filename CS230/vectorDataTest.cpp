#include <iostream>
#include "vectorData.h"
using namespace std;

int main()
{
	int data[10] = {0,1,2,3,4,5,6,7,8,9};

	VectorData<int> vd1;
	VectorData<int> vd3(5);
	VectorData<int> vd4(data, 10);
	VectorData<int> vd2(vd4);
	
	cout << vd2[0];

	vd1.print(cout);
	cout << endl;
	vd2.print(cout);
	cout << endl;
	vd3.print(cout);
	cout << endl;
	vd4.print(cout);
	cout << endl;
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Core Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	cout << vd2.size() << endl << vd4.size() << endl;

	vd2.insert(99);
	vd2.print(cout);
	cout << endl << vd2.size() << endl;
	
	cout << vd2.getUsage() << endl;
	vd2.incUse();
	cout << vd2.getUsage() << endl;	
	vd2.decUse();
	cout << vd2.getUsage() << endl;	
	
	vd1 = vd2;
	vd1.print(cout);
	cout << endl;
	vd2.print(cout);
	cout << endl;
	
	VectorData<int> vd5 = vd2.addition(vd4);
	vd5.print(cout);
	cout << endl;
	vd2.print(cout);
	cout << endl;
	vd4.print(cout);
	cout << endl;

	int result = vd5.dotMultiply(vd3);
	vd5.print(cout);
	cout << " dot ";
	vd3.print(cout);
	cout << " = " << result << endl;
	
	/*
	VectorData<T>	scalarMultiply	(const T & scalar) const; 						//A * x - scalar multiplication of vector and a scalar T


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	 T & 	operator[](int index) const;		*/
}
