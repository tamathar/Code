#include <iostream>
#include "ScatterData.h"
using namespace std;

int main()
{
    	ScatterData<double> a("[(1,2),(3,4),(5,6)]");
    	typename ScatterData<double>::Point p(7,8);
    	ScatterData<double> c;
   
    	c = p+a;
	c += p;
}
