#include <iostream>
#include "Set.h"
using namespace std;

int main()
{
    double odds[] = {1,3,5,7,9,11,13,15,17,19};
    int primes[] = {2,3,5,7,11,13,17,19};

	Set<int>grr;
	Set<int>arg;
	
	arg = grr & 3;
	
    Set<double> s;
    Set<int> p(primes,8);
    Set<int> n(p);

    Set<double> a[10];
    for (int i=0; i<10; i++)
        for (int j=0; j<i; j++)
            a[i].insert(j);

    s = a[9];
    a[7] = (Set<double>() | 3.5) | 2.7;
    a[8] &= (Set<double>(odds,10) | s);
	cout << a[8] << endl;
    Set<double> b[8] = {s,a[1],a[3],Set<double>(odds,8)};
    cout << s << " " << n << endl;
    cout << p << " " << n << endl;
    
    if (a[3] < s) cout << "a[3] is a subset of s\n";
    if (3.5 < a[7]) cout << "3.5 is an element of s\n";
}