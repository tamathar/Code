#include <iostream>
#include "IntegerSet.h"
using namespace std;

int main()
{
    IntegerSet s;
    s.empty() ? cout << "s is empty":cout <<"s is not empty" ;
	cout << endl;
    s.insert(3);
    s.insert(4);
	s.remove(2);
    s.remove(3);
    cout << "|s| = " << s.size() << endl;
    s.contains(4) ? cout << "s contains 4":cout <<"s does not contain 4";
	cout << endl;
    s.contains(3) ? cout << "s contains 3":cout << "s does not contain 3";
	cout << endl;
}