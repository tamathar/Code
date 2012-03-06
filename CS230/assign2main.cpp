#include <iostream>
#include "IntegerSet.h"
using namespace std;



IntegerSet unionize(IntegerSet a,IntegerSet b)
{
    IntegerSet result = a;
    for (int i=0; i<1000000; i++)
        if (b.contains(i))
            result.insert(i);
    return result;
} 

void print(IntegerSet *a,int n);

int main()
{
    int odds[] = {1,3,5,7,9,11,13,15,17,19};
    int primes[] = {2,3,5,7,11,13,17,19};

    IntegerSet s;
    IntegerSet p(primes,8);
    IntegerSet n(p);  // same as IntegerSet n = p;

    IntegerSet a[10];
    for (int i=0; i<10; i++)
        for (int j=0; j<i; j++)
            a[i].insert(j);

    s = a[9];
    a[7] = IntegerSet();
    a[8] = IntegerSet(odds,10);
    IntegerSet b[8] = {s,p,a[1],a[3],IntegerSet(odds,8)};
    cout << s << " " << n << endl;
    cout << p << " " << n << endl;
    print(a,10);
	print(b,8);
}

void print(IntegerSet *a, int n)
{
	for(int i = 0; i < n; i++)
		cout << a[i] << endl;
	cout << endl;
}