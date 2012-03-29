#include <iostream>
#include "Geometry.h"
using namespace std;

int main()
{
	double pts[6] = {0,0,2,0,2,2};
	
	Box box(BLUE,0,4,5,0);
	
	Circle circle(WHITE, 0, 2, 5);
	
	Triangle triangle(BLACK, pts);
	
	//Polygon polygon(RED, pts, 3);
	
	//BOX TESTS-----------------------------------------------------------------------------------------------------------
	cout << "BOX TESTS-----------------------------------------------------------------------------------------------------------" << endl;
	cout << box.getLeft() << endl;
	cout << box.getTop() << endl;
	cout << box.getRight() << endl;
	cout << box.getBottom() << endl;
	cout << endl;
	
	cout << box.area() << endl;
	cout << box.perimeter() << endl;//compute the perimeter of the shape
	box.translate(4,3);
	box.draw(cout);
	cout << endl << endl;									//print a description to os (see below)	
	
	box.setLeft(0);
	box.setTop(4);
	box.setRight(4);
	box.setBottom(0);
	
	box.draw(cout);
	cout << endl << endl;		
	
	//Circle TESTS-----------------------------------------------------------------------------------------------------------
	cout << "Circle TESTS-----------------------------------------------------------------------------------------------------------" << endl;
	
	cout << circle.getCenterX() << endl;
	cout << circle.getCenterY() << endl;
	cout << circle.getRadius() << endl << endl;
	
	cout << circle.area() << endl;												//compute the area of the shape
	cout << circle.perimeter() << endl;											//compute the perimeter of the shape
	circle.translate(5,4.5);								//move the shape
	circle.draw(cout);
	cout << endl;
		
	circle.setCenter(0,0);
	circle.setRadius(6.5);
	circle.draw(cout);
	cout << endl << endl;




	
}
