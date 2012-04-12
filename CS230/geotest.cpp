#include <iostream>
#include "Geometry.h"
using namespace std;

int main()
{
	double pts[6] = {0,0,2,0,2,2};
	double pts2[8] = {0,0,2,0,2,2,3,3};
	
	Box box(BLUE,0,4,5,0);
	
	Circle circle(WHITE, 0, 2, 5);
	
	Triangle triangle(BLACK, pts);
	
	Polygon polygon(RED, pts, 3);
	
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

	//Triangle TESTS-----------------------------------------------------------------------------------------------------------
	cout << "Triangle TESTS-----------------------------------------------------------------------------------------------------------" << endl;
	
	for(int i = 0; i < 3; i++)
		cout << "(" << triangle.getCornerX(i)  <<  "," << triangle.getCornerY( i) << ")\n";
	
	cout << triangle.area() << endl ;
	cout << triangle.perimeter() << endl;
	
	triangle.translate(3,4);
	triangle.draw(cout);
	cout << endl;
	
	triangle.setCorner(2, 2, 4.5);
	triangle.draw(cout);
	cout << endl << endl;	
	
	//Polygon TESTS-----------------------------------------------------------------------------------------------------------
	cout << "Polygon TESTS-----------------------------------------------------------------------------------------------------------" << endl;

	int index = polygon.getVertexCount();

	for(int i = 0; i < index; i++)
		cout << polygon.getVertexX(i) << "," << polygon.getVertexY(i) << endl;
	
	cout << polygon.area() << endl;								
	cout << polygon.perimeter()<< endl ;									
	polygon.translate(3,4);								
	polygon.draw(cout) ;
	cout << endl;
	
	polygon.setVertexes(pts2, 4); 				
	polygon.draw(cout) ;
	cout << endl << endl;
	

	//Group TESTS-----------------------------------------------------------------------------------------------------------
	cout << "Group TESTS-----------------------------------------------------------------------------------------------------------" << endl;
    Geometry * list[5];
   	Geometry * list2[5];
    int count = 0;
    list[count++] = new Box(BLUE,0,1,1,0);
    list[count++] = new Box(BLUE,2,3,4,9);
    list[count++] = new Circle(BLUE,5,5,3);
    list[count++] = new Triangle(BLUE,pts);
    list[count++] = new Polygon(BLUE,pts2,4);

	list2[4] = new Group(BLUE, count, list);
	
	list2[4]->draw(cout);
	cout << endl;
	
	list2[4]->translate(3,4);
	list2[4]->draw(cout);
	cout << endl;
	
	//list2[4]->getObject(0)->draw(cout);
	//cout << endl << list2[4]->getObjectCount() << endl;
	
	cout << list2[4]->area() << endl;
	cout << list2[4]->perimeter() << endl;
	

	list2[0] = new Box(BLUE,0,1,1,0);
    list2[1] = new Box(BLUE,2,3,4,9);
    list2[2] = new Circle(BLUE,5,5,3);
    list2[3] = new Triangle(BLUE,pts);
    
    Group group2(BLUE, count, list2);
    
    group2.draw(cout);
    cout << endl;
    
    cout << group2.area() << endl << group2.perimeter() << endl;
    
    Group group3(BLUE, 0, list);
    
    group3.draw(cout);
    cout << endl;
    
    cout << group3.area() << endl << group3.perimeter() << endl;
}
