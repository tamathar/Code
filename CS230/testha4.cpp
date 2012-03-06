//Thomas Scroggins
//Test harness for Set.h

#include <cassert>
#include <iostream>
#include "Set.h"
using namespace std;

int main()
{

	int numbers[10] = {1,2,3,4,5,6,7,8,9,0};
	Set<int> a;
	Set<int> b(a);
	Set<int> c(numbers, 10);
	
	b = a;
	assert(b==a);
	
	a = b & c;
	assert(a.empty());
	
	a = b & 3;
	assert(a.empty());
	
	a = 3 & b;
	assert(a.empty());
	
	b &= a;
	assert(b.empty());
	
	b &= 3;
	assert(b.empty());
	
	b = a | c;
	assert(b == c);
	
	b = a | 3;
	assert(b.size() == 1);
	
	b = 3 | a;
	assert(b.size() == 1);
	
	a |= b;
	assert(a.size() == 1);
	
	a |= 3;
	assert(a.size() == 1 && a.contains(3));
	

	assert(!(a != b));
	
	assert(a< c);
	
	assert(3 < c);
	c > a;
	c > 3;
	a <= c;
	c >= a;
	a.contains(3);
	a.empty();
	a.size();
	a.insert(99);
	cout << a << endl << c;
	a.remove(99);
	
}