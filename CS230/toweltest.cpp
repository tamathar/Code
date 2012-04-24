#include <iostream>
#include "Geometry.h"
#include <sstream>
using namespace std;

int main()
{

	//TOWELL TESTS----------------------------------------------------------------------------
	cout << "Towell TESTS-----------------------------------------------------------------------------------------------------------" << endl;
	
	    double pts[] = {1,1,7,2,3,5,6,8,4,3};
    Geometry * list[100];
    int count = 0;
    list[count++] = new Box(BLUE,0,1,1,0);
    list[count++] = new Box(CYAN,2,3,4,9);
    list[count++] = new Circle(WHITE,5,5,3);
    list[count++] = new Triangle(BLACK,pts);
    list[count++] = new Polygon(GREEN,pts,5);

	//list[3];

    double distance = 0;
    double area = 0;
    stringstream ss;
    for (int i=0; i<count; i++) {
        distance += list[i]->perimeter();
        area += list[i]->area();
        list[i]->draw(ss); 
        ss << "\n";
    }
    for (int i=0; i<count; i++) {
        list[i]->translate(10,10);
        list[i]->draw(ss);
        ss << "\n";
    }
    cout << "distance: " << distance << " area: " << area << "\n";
    cout << "drawing: " << ss.str();
	
	}