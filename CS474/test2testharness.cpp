#include "test2.h"
using namespace std;
using namespace Complex;

int main()
{
	TComplex c1;
	TComplex c2(3, 4.5);
	TComplex c3(c2);  
	
	cout << c1 << endl << c2 << endl << c3 << endl;
	
	c1 = c2 + c3;
	cout << c1 << endl;
	
	TComplex c4(c1);
	cout << c4 << endl;
	
	c4 = c4 - c1;
	cout << c4 << endl;
	
	cout << (c1/c2) << endl;
	
	cout << (c1*c2) << endl;
	
	cout << (c1*3) << endl;
	
	cout << (~c1) << endl;
	
	cout << (c2==c1) << endl;
	cout << (c2!=c1) << endl;
	cout << (c2==c3) << endl;
	cout << (c2!=c3) << endl;
	
	cout << c2.r() << ", " << c2.i() << endl;
	

}

