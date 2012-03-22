// compile using the following command-line, where N=1..10
//
// g++ -Wall -DTEST=N -DDEBUG test.cpp
//
// running the program should produce no run-time errors including assertions

#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;
#include "Vector.h"

template <class T>
void test() {
#ifndef TEST
	#error TEST must be defined (1..10)
#elif TEST==1
	Vector<T> a(5);
	Vector<T> b(a);
    
	assert(a==b);
#elif TEST==2
	Vector<T> a(5);
	Vector<T> b(a);
    
	assert(a[3] == 0);
	assert(a[2] == 0);
	assert(!(a!=b));
	a[3] = 7;
	assert(a!=b);
	assert(a[3] == 7);
	assert(a[2] == 0);
#elif TEST==3
	Vector<T> a(5);
	Vector<T> b(a);
	Vector<T> c(b);
    
	assert(a==b);
	assert(a==c);
	assert(c==b);
	assert(!(a!=b));
	assert(!(a!=c));
	assert(!(b!=c));
	a[3] = 7;
	Vector<T> d(a);
	assert(a!=b);
	assert(a!=c);
	assert(d==a);
	assert(c==b);
	assert(d!=b);
	assert(d!=c);
    
	for (int i=0; i<5; i++) {
assert(b[i] == 0);
    		assert(c[i] == 0);
    		assert(a[i] == (i==3 ? 7 : 0));
	}
#elif TEST==4
	Vector<T> a(5);
	Vector<T> b(a);
	assert(&b.implementation() == &a.implementation());
	Vector<T> c(b);
	assert(&b.implementation() == &c.implementation());
    
	assert(a==b);
	assert(a==c);
	assert(c==b);
	assert(!(a!=b));
	assert(!(a!=c));
	assert(!(b!=c));
	assert(&b.implementation() == &c.implementation());
	a[3] = 7;
	assert(&b.implementation() == &c.implementation());
	assert(&b.implementation() != &a.implementation());
    
	Vector<T> d(a);
	assert(&a.implementation() == &d.implementation());
	assert(a!=b);
	assert(a!=c);
	assert(d==a);
	assert(c==b);
	assert(d!=b);
	assert(d!=c);
    
	assert(&a.implementation() == &d.implementation());
	assert(&b.implementation() == &c.implementation());
    
	assert(a.implementation().useCount() == 2);
	assert(b.implementation().useCount() == 2);
	assert(c.implementation().useCount() == 2);
	assert(d.implementation().useCount() == 2);

	for (int i=0; i<500; i++) {
    		assert(b[i] == 0);
    		assert(c[i] == 0);
    		assert(a[i] == (i==3 ? 7 : 0));
	}

#elif TEST==5
	Vector<T> a(5);
	Vector<T> b(a);
    
	assert(a==b);
	assert(!(a!=b));
	for (int i=-1000; i<5000; i++) {
    		b[i] = 0;
    		a[i] = 0;
	}
	Vector<T> c(b);
	a[3] = 7;
	a[5] = 9;
	assert(a!=b);
	assert(a!=c);
	assert(c==b);  
    
	assert(&a.implementation() != &b.implementation());
	assert(&b.implementation() == &c.implementation());
    
	assert(a.implementation().useCount() == 1);
	assert(b.implementation().useCount() == 2);
	assert(c.implementation().useCount() == 2);

	for (int i=-100; i<500; i++) {
    		assert(b[i] == 0);
    		assert(c[i] == 0);
    		assert(a[i] == (i==3 ? 7 : 0));
	}
#elif TEST==6
	Vector<T> *a[1000];
	a[0] = new Vector<T>(3);
	for (int i=1; i<1000; i++)
    		a[i] = new Vector<T>(*a[i-1]);
	for (int i=1; i<1000; i++)
    		assert(&a[i]->implementation() == &a[i-1]->implementation());
	for (int i=0; i<1000; i++) {
    		assert(a[i]->implementation().useCount() == 1000-i);
    		delete a[i];
	}

	a[0] = new Vector<T>(4);
	for (int i=1; i<1000; i++)
    	a[i] = new Vector<T>(*a[i-1]);
	for (int i=1; i<1000; i++)
    		assert(&a[i]->implementation() == &a[i-1]->implementation());
	Vector<T> b(4);
	for (int i=0; i<1000; i++) {
    		*a[i] = b;
    		assert(b.implementation().useCount() == i+2);
	}
	for (int i=0; i<1000; i++) {
    		assert(a[i]->implementation().useCount() == 1000-i+1);
    		delete a[i];
	}
	assert(b.implementation().useCount() == 1);
#elif TEST==7
	T data[] = {2,3,5,7,11,13,17,19,23};
	Vector<T> a(data,9);
	Vector<T> b(data,3);
	assert(a.size()==9);
	assert(b.size()==3);
	Vector<T> c = a + b;
	assert(a.size()==9);
	assert(b.size()==3);
	assert(c.size()==9);
	for (int i=0; i<9; i++) {
    		assert(a[i] == data[i]);
    		assert(b[i] == (i<3 ? data[i] : 0));
    		assert(c[i] == (i<3 ? data[i]*2 : data[i]));
	}
	assert(a.implementation().useCount()==1);
	assert(b.implementation().useCount()==1);
	assert(c.implementation().useCount()==1);
#elif TEST==8
	T data[] = {2,3,5,7,11,13,17,19,23};
	Vector<T> a(data,9);
	Vector<T> b(data,3);
	Vector<T> c(data,9);
	assert(a.size()==9);
	assert(b.size()==3);
	assert(c.size()==9);
	c = b;
	b = a;
	assert(a.size()==9);
	assert(b.size()==9);
	assert(c.size()==3);
	assert(a.implementation().useCount()==2);
	assert(b.implementation().useCount()==2);
	assert(c.implementation().useCount()==1);

	for (int i=-10; i<90; i++) {
    		assert(((const Vector<T>)a)[i] == (i>=0 && i<9 ? data[i]:0));
    		assert(((const Vector<T>)b)[i] == ((const Vector<T>)a)[i]);
    		assert(((const Vector<T>)c)[i] == (i>=0 && i<3 ? data[i]:0));
	}
	assert(a.implementation().useCount()==2);
	assert(b.implementation().useCount()==2);
	assert(c.implementation().useCount()==1);
#elif TEST==9
	T data[] = {2,3,5,7,11,13,17,19,23};
	Vector<T> a(data,9);
	Vector<T> b(data+1,5);
	assert(a*b == 2*3 + 3*5 + 5*7 + 7*11 + 11*13);
	assert(b*b == 3*3 + 5*5 + 7*7 + 11*11 + 13*13);
	assert(a*a == 2*2 + 3*3 + 5*5 + 7*7 + 11*11 + 13*13 + 17*17 + 19*19 + 23*23);
	//cout << "mag: " <<  a.magnitude() << endl;
	//cout << "other: " << ((T)sqrt(a*a)) << endl << endl;
	assert(abs(a.magnitude() - (T)sqrt(a*a)) < .00001);
#elif TEST==10
	T data[] = {2,3,5,7,11,13,17,19,23};
	Vector<T> a(data,9);
	Vector<T> b = a*(T)3;
	for (int i=0; i<9; i++)
    		assert(b[i] == data[i]*3);
#else
	#error TEST must be defined
#endif
}

int main()
{
	test<int>();
	test<double>();
	test<long>();
}
