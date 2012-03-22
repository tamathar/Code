#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int data2[11] = {0,1,2,3,4,5,6,7,8,9,99};

	
	cout << "--------------------------------Construction---------------------------------------\n";

	Vector<int> v1;
	Vector<int> v2(10);
	Vector<int> v4(data2, 11);
	Vector<int> v3(v4);	
	
	v1.print(cout); cout << endl;
	v2.print(cout); cout << endl;
	v3.print(cout); cout << endl;
	v4.print(cout); cout << endl;
	
	cout << "--------------------------------Addition-------------------------------------------\n";
	
	(v1.addition(v2)).print(cout); cout << endl;
	(v2.addition(v2)).print(cout); cout << endl;
	(v3.addition(v2)).print(cout); cout << endl;

	cout << "-------------------------------Dot Mult--------------------------------------------\n";
	
	cout <<(v1.dotMultiply(v2)); cout << endl;
	cout <<(v3.dotMultiply(v2)); cout << endl;
	cout <<(v3.dotMultiply(v4)); cout << endl;

	cout << "-------------------------------Scalar Mult-----------------------------------------\n";
	
	(v1.scalarMultiply(2)).print(cout); cout << endl;
	(v2.scalarMultiply(2)).print(cout); cout << endl;
	(v3.scalarMultiply(2)).print(cout); cout << endl;

	cout << "-------------------------------Size------------------------------------------------\n";	
	
	cout << v1.size() << endl;
	cout << v2.size() << endl;
	cout << v3.size() << endl;
	cout << v4.size() << endl;
	
	cout << "-------------------------------Magnitude-------------------------------------------\n";	
	cout << v1.magnitude() << endl;
	cout << v2.magnitude() << endl;
	cout << v3.magnitude() << endl;
	cout << v4.magnitude() << endl;
	
	cout << "-------------------------------Assignment------------------------------------------\n";
	v1.print(cout); cout << "before\n";
	v1 = v2;
	v1.print(cout); cout << "after\n";
	v1.print(cout); cout << "before\n";
	v1 = v3;
	v1.print(cout); cout << "after\n";
	v1.print(cout); cout << "before\n";
	v1 = v2;
	v1.print(cout); cout << "after\n";
	
	cout << "-------------------------------\"+\" overload-------------------------------------\n";
	Vector<int> v5;
	
	(v1+v2).print(cout); cout << endl;
	(v2+v2).print(cout); cout << endl;
	(v5+v2).print(cout); cout << endl;
	(v3+v4).print(cout); cout << endl;
	
	cout << "-------------------------------\"+=\" overload-------------------------------------\n";

	v1+=v2;
	v1.print(cout); cout << endl;
	v5+=v2;
	v5.print(cout); cout << endl;
	v4+=v3;
	v4.print(cout); cout << endl;

	cout << "-------------------------------\"*(dot)\" overload-------------------------------------\n";

	cout << (v1*v2); cout << endl;
	cout << (v2*v2); cout << endl;
	cout << (v5*v2); cout << endl;
	cout << (v3*v4); cout << endl;

	cout << "-------------------------------\"*(scalar)\" overload-------------------------------------\n";

	(v1*2).print(cout); cout << endl;
	(v2*2).print(cout); cout << endl;
	(v5*2).print(cout); cout << endl;
	(v3*4).print(cout); cout << endl;

	(2*v1).print(cout); cout << endl;
	(2*v2).print(cout); cout << endl;
	(2*v5).print(cout); cout << endl;
	(4*v3).print(cout); cout << endl;

	cout << "-------------------------------bool overloads-----------------------------------------\n";

	cout << (v1 == v1) << endl;
	cout << (v5 == v2) << endl;
	cout << (v5 == v5) << endl;
	cout << (v4 == v4) << endl;
	cout << endl;
	cout << (v1 != v1) << endl;
	cout << (v5 != v2) << endl;
	cout << (v5 != v5) << endl;
	cout << (v4 != v4) << endl;
	
	
	#ifdef DEBUG
	cout << "-------------------------------Use Count Check-----------------------------------------\n";


	cout << endl;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	//cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v5 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v4 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v3 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v2 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v1 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v1[1] = v1[1];
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v5 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v4 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v3 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v2 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	v1 = v1;
	cout << v1.implementation()->useCount() << endl;
	cout << v2.implementation()->useCount() << endl;
	cout << v3.implementation()->useCount() << endl;
	cout << v4.implementation()->useCount() << endl;
	cout << v5.implementation()->useCount() << endl;
	cout << endl;
	#endif
}
