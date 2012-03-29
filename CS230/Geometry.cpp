#include <iostream>
#include <math.h>
#include "Geometry.h"
using namespace std;



//FOR PRINTING OUR STRINGS FOR COLORS
string colorList[8] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE" };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///********************************************************************************************************************************///
///*													Class Definitions														  *///
///********************************************************************************************************************************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/********************************************************************************************************************************/
/*												Box (Derived Class) - Definitions												*/
/********************************************************************************************************************************/

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Box::Box(Color c,double l, double t, double r, double b)
	:Geometry(c), left(l), top(t), right(r), bottom(b) {}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

double Box::area() const
{
	return (right - left) * (top - bottom);
}

double Box::perimeter() const
{
	return (2 * (right-left) + 2 * (top - bottom));
}

void Box::translate(double dx,double dy)
{
	left += dx;
	right += dx;
	
	top += dy;
	bottom += dy;
}

void Box::draw(ostream &os) const
{
	os << "Box(" << colorList[getColor()] << "," << left << "," << top << "," << right << "," << bottom << ")";
}
	


/********************************************************************************************************************************/
/*											Circle (Derived Class) - Definitions												*/
/********************************************************************************************************************************/


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Circle::Circle(Color c,double centerX,double centerY, double rad)
	:Geometry(c), X(centerX), Y(centerY), radius(rad) {}
	

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

double Circle::area() const
{
	double const pi=4*atan(1);
	
	return pi*radius*radius;
}

double Circle::perimeter() const
{
	double const pi=4*atan(1);

	return pi*2*radius;
}

void Circle::translate(double dx,double dy)
{
	X += dx;
	Y += dy;
}

void Circle::draw(ostream &os) const
{
	os << "Circle(" << colorList[getColor()] << ","  << X << "," << Y << "," << radius << ")";
}
	


/********************************************************************************************************************************/
/*											Triangle (Derived Class) - Definitions												*/
/********************************************************************************************************************************/


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Triangle::Triangle(Color c,double pts[])
	:Geometry(c)
{
	for(int i = 0; i < 6; i++)
		points[i] = pts[i];
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

double Triangle::area() const
{
	double area = 0;
	
	for(int i = 0; i < 3; i++)
		area += (points[2*i]*points[(2*(i+1)+1)%6] - points[(2*i)+1]*points[(2*(i+1))%6]);
	
	
	return area/2;
}

double Triangle::perimeter() const
{
	double perim = 0;
	
	for(int i = 0; i < 3; i++)
		perim += sqrt(pow(points[2*i]-points[(2*(i+1))%6], 2) + pow(points[2*i+1]-points[(2*(i+1)+1)%6], 2));
	
	
	return perim;
}

void Triangle::translate(double dx,double dy)
{
	for(int i = 0; i < 3; i++)
	{
		points[2*i] += dx;
		points[2*i+1] += dy;
	}
}

void Triangle::draw(ostream &os) const
{
	os << "Triangle(" << colorList[getColor()] << ",";
	
	for(int i = 0; i < 6; i++)
	{
		os << points[i];
		if(i < 5)
			os << ",";
	}
	
	os << ")";
}
	

/********************************************************************************************************************************/
/*											Polygon (Derived Class) - Definitions												*/
/********************************************************************************************************************************/

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Polygon::Polygon(Color c,double pts[],int n)
	:Geometry(c)
{	
	pointCount = n*2;
	points = new double[pointCount];
	
	for(int i = 0; i < pointCount; i++)
		points[i] = pts[i];
}
	
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void Polygon::setVertexes(double pts[],int n)
{
	delete []points;
	
	pointCount = n*2;
	points = new double[pointCount];
	
	for(int i = 0; i < pointCount; i++)
		points[i] = pts[i];
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

double Polygon::area() const
{
	double area = 0;
	
	for(int i = 0; i < pointCount/2; i++)
		area += (points[2*i]*points[(2*(i+1)+1)%pointCount] - points[(2*i)+1]*points[(2*(i+1))%pointCount]);
	
	
	return area/2;
}

double Polygon::perimeter() const
{
	double perim = 0;
	
	for(int i = 0; i < pointCount/2; i++)
		perim += sqrt(pow(points[2*i]-points[(2*(i+1))%pointCount], 2) + pow(points[2*i+1]-points[(2*(i+1)+1)%pointCount], 2));
	
	
	return perim;
}

void Polygon::translate(double dx,double dy)
{
	for(int i = 0; i < pointCount/2; i++)
	{
		points[2*i] += dx;
		points[2*i+1] += dy;
	}
}

void Polygon::draw(ostream &os) const
{
	os << "Polygon(" << colorList[getColor()] << ",";
	
	for(int i = 0; i < pointCount; i++)
	{
		os << points[i];
		if(i < pointCount-1)
			os << ",";
	}
	
	os << ")";
}


























