#include <iostream>
#include <fstream>
#include <sstream>
#include "Geometry.h"
using namespace std;

void createShape(istream & is, Geometry ** input)
{
	char temp;
	
	is >> temp;
	
	if(temp == 'B') 		//is it a Box?
	{
	
	}
	else if(temp == 'C')	//how about a Circle?
	{
	
	}
	else if(temp == 'T')	//a Triangle?
	{
	
	}
	else if(temp == 'P')	//or a Polygon?
	{
	
	}
	else					//Must be a group
	{
	
	}
}

int main(int argc, char * argv[])
{
	if(argc < 3)
	{
		cout << "usage: draw <in-file> <operation>\n";
		cout << "where: <in-file> is the name of a text file containing geometry objects\n";
		cout << "and <operation> is one of the following, or assumed to be info if missing.\n";
		cout << "\tcount\t\tdisplay: count of objects by color\n";
		cout << "\tperimeter\tdisplay: total perimeter of all objects\n";
		cout << "\tarea\t\tdisplay: total area of objects by color\n";
		cout << "\tbounds\t\tdisplay: bounds of objects\n";
		cout << "\tmove dx dy\twrite translated objects to standard output\n";
		cout << "\tcycle\t\twrite color-cycled objects to standard output\n";
	}
	else
	{
		Geometry * shapes[1000];
	
		fstream fs(argv[1]);		
		stringstream ss;
		
		while(fs >> ss)
		{
			createShape(
		}
	
	
	}
}
