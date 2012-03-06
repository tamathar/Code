#include <iostream>
#include "ScatterData.h"
using namespace std;

int main()
{
	int x[10] = {2,2,2,2,2,2,2,2,2,2};
	int y[10] = {2,2,2,2,2,2,2,2,2,2};
	
	
	//Test init.
	ScatterData<int>::Point p1(2,2);
	ScatterData<int>::Point p2(2,2);
	ScatterData<int>::Point p3(2,2);
	ScatterData<int>::Point p4(2,2);
	ScatterData<int>::Point points[4] = {p1,p2,p3,p4};
	
	ScatterData<int> sd1;
	ScatterData<int> sd2(x, y, 10);
	ScatterData<int> sd3(points, 4);
	ScatterData<int> sd4(sd3);
	
	//Test insert/remove
	sd1.insert(1,1);
	sd1.insert(p1);
	sd1.remove(2,2);
	sd1.remove(ScatterData<int>::Point(1,1));
	
	//Test counts
	cout << sd1.count() << endl << sd2.count() << endl << sd3.count() << endl << sd4.count() << endl;	
	cout << sd1.count(1,1) << endl << sd2.count(p1) << endl;	
	sd1.insert(3,3);
	cout << sd1.count(3,3) << endl << sd1.count(ScatterData<int>::Point(3,3)) << endl;
	
	//Test topleft, bottomright
	sd1.insert(1,1);
	ScatterData<int>::Point topleft(sd1.topLeft());
	ScatterData<int>::Point bottomright(sd1.bottomRight());
	cout << topleft.x << "," << topleft.y << endl;
	cout << bottomright.x << "," << bottomright.y << endl;
	
	ScatterData<int> news;
	topleft = news.topLeft();
	bottomright = news.bottomRight();
	cout << topleft.x << "," << topleft.y << endl;
	cout << bottomright.x << "," << bottomright.y << endl;
	
	//Test = and []
	news = sd1;
	news = news;
	cout << sd1[0].x << "," << sd1[0].y << endl;
	cout << sd1[1].x << "," << sd1[1].y << endl;
	
	//Test A + B and A + a
	ScatterData<int> t1(x, y, 10);
	ScatterData<int> t2;
	news = t1 + t2;
	cout << news.count() << endl;
	news = t1 + p1;
	cout << news.count() << endl;
	news = p1 + t1;
	cout << news.count() << endl;
	
	//Testing the +=
	t2 += t1;
	cout << t2.count() << endl;
	t2 += p1;
	cout << t2.count() << endl;
	
	//testing == and !=
	cout << (t2 == t1) << endl << (t2 == t2) << endl;
	cout << (t2 != t1) << endl << (t2 != t2) << endl;
	
	//testing cout
	cout << t2 << endl;
	ScatterData<int> empty;
	cout << empty << endl;
	
	//testing cin; gl
	cin >> t2;
	cout << t2 << endl;
	
	//testing istream/string constructors
	ScatterData<int> in(cin);
	ScatterData<int> strings("[(2,2),(3,3)]");
	cout << in << endl;
	cout << strings << endl;
	
	
	//Dr. Towell's code
	ScatterData<int> xx("[ (1,2),(2,3), (4,5) ]");
    cout << xx << endl;

    stringstream ss("[(1.0,2.5),(2.2,3),(4.5,9.5)]");
    ScatterData<double> yy(ss);
    cout << yy << endl;
    cin >> yy;

    ScatterData<int>::Point p(1,2);
    xx.insert(p);
    cout << xx.count(p) << endl;
    cout << yy.count(1.0,2.5) << endl;

}