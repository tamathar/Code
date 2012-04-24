#include <iostream>
#include <math.h>
#include "Geometry.h"
using namespace std;


string Geometry::colorList[8] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE" };


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
	
void Box::bounds(double bounds[]) const
{
	if(left < bounds[0])
		bounds[0] = left;
	if(top > bounds[1])
		bounds[1] = top;
	if(right > bounds[2])
		bounds[2] = right;
	if(bottom < bounds[3])
		bounds[3] = bottom;
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
	
void Circle::bounds(double bounds[]) const
{
	if(X-radius < bounds[0])
		bounds[0] = X-radius;
	if(Y+radius > bounds[1])
		bounds[1] = Y+radius;
	if(X+radius > bounds[2])
		bounds[2] = X+radius;
	if(Y-radius < bounds[3])
		bounds[3] = Y-radius;
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
	
	area /= 2;
	
	if(area < 0)
		area *= -1;
		
	return area;
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
	
void Triangle::bounds(double bounds[]) const
{
	for(int i = 0; i < 3; i++)
	{
		if(points[i*2] < bounds[0])
			bounds[0] = points[i*2];
		
		if(points[i*2] > bounds[2])
			bounds[2] = points[i*2];
			
		if(points[i*2 + 1] < bounds[3])
			bounds[3] = points[i*2+1];
			
		if(points[i*2 + 1] > bounds[1])
			bounds[1] = points[i*2+1];
	}
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
	
	area /= 2;
	
	if(area < 0)
		return area*-1;
	
	return area;
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
	os << "Polygon(" << colorList[getColor()] << "," << pointCount/2 << ",";
	
	for(int i = 0; i < pointCount; i++)
	{
		os << points[i];
		if(i < pointCount-1)
			os << ",";
	}
	
	os << ")";
}

void	Polygon::bounds(double bounds[]) const
{
	for(int i = 0; i < pointCount/2; i++)
	{
		if(points[i*2] < bounds[0])
			bounds[0] = points[i*2];
		
		if(points[i*2] > bounds[2])
			bounds[2] = points[i*2];
			
		if(points[i*2 + 1] < bounds[3])
			bounds[3] = points[i*2+1];
			
		if(points[i*2 + 1] > bounds[1])
			bounds[1] = points[i*2+1];
	}
}

/********************************************************************************************************************************/
/*											Group (Derived Meta Class) - Definitions											*/
/********************************************************************************************************************************/


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//Takes over ownership of the elements of list
	Group::Group(Color c,int n,Geometry **list)
		: Geometry(c), count(n)
	{
		shapes = new Geometry*[count];
		
		for(int i = 0; i < count; i++)
			shapes[i] = list[i];
	}
	
	Group::~Group()
	{
		for(int i = 0; i < count; i++)
			delete shapes[i];
		
		delete []shapes;
	}
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-	
	//Takes over ownership of the elements of list
	void Group::setObjects(int n,Geometry **list)
	{
		for(int i = 0; i < count; i++)
			delete shapes[i];
		
		delete []shapes;
		
		shapes = new Geometry*[count];
		
		for(int i = 0; i < count; i++)
			shapes[i] = list[i];
	}
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	double Group::area() const
	{
		double area = 0;
		
		for(int i = 0; i < count; i++)
			area += shapes[i]->area();
			
		return area;
	}
	
	double Group::perimeter() const
	{
		double perimeter = 0;
		
		for(int i = 0; i < count; i++)
			perimeter += shapes[i]->perimeter();	
			
		return perimeter;
	}
	
	void Group::translate(double dx,double dy)
	{
		for(int i = 0; i < count; i++)
			shapes[i]->translate(dx, dy);
	}
	
	void Group::draw(ostream &os) const
	{
		os << "Group(" << colorList[getColor()] << "," << count;
		
		for(int i = 0; i < count; i++)
		{
			os << ",";
			shapes[i]->draw(os);
		}
		
		os << ")";
	}
	
	void Group::bounds(double bounds[]) const
	{
		for(int i = 0; i < count; i++)
			shapes[i]->bounds(bounds);
	}
	
	void Group::setColor(Color newColor)
	{
		Geometry::setColor(newColor);
		
		for(int i = 0; i < count; i++)
			shapes[i]->setColor(newColor);
	}

	int Group::realCount() const
	{
		int total = 0;
		
		for(int i = 0; i < count; i ++)
			total += shapes[i]->realCount();
			
		return total;
	}
























