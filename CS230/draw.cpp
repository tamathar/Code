#include <iostream>
#include <fstream>
#include <sstream>
#include "Geometry.h"
using namespace std;

void createShape(istream & is, Geometry ** input, int & count)
{
	//variables we all will need
	string colorChoices[8] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE" };
	char temp;
	Color color;	
		
	is >> temp; 								//grab our op
	
	if(temp == 'B') 						//is it a Box?
	{
		double L,T,R,B;
		
		for(int i = 0; i < 3; i++)
			is >> temp;						//Burn the "ox("

				
													//grab our color
		string colorstr;
		is >> temp;		
		while(temp != ',')
		{
			colorstr += temp;
			is >> temp;						//The last time through, this disposes of the comma
		}
		
		for(int i = 0; i < 8; i ++)		//assign our color
			if(colorstr == colorChoices[i])
				color = (Color)i;
				
		
		is >> L;								//grab edges while burning commas
		is >> temp;
		is >> T;
		is >> temp;
		is >> R;
		is >> temp;
		is >> B;
		is >> temp;
		
		input[count++] = new Box(color, L, T, R, B);
			
	}
	else if(temp == 'C')		//how about a Circle?
	{
		double r, x, y;
		
		for(int i = 0; i < 6; i++)
			is >> temp;						//Burn the "ircle("
			
													
		string colorstr;						//grab our color
		is >> temp;		
		while(temp != ',')
		{
			colorstr += temp;
			is >> temp;						//The last time through, this disposes of the comma
		}
		
		for(int i = 0; i < 8; i ++)		//assign our color
			if(colorstr == colorChoices[i])
				color = (Color)i;
				
		is >> x;								//get our dimensions
		is >> temp;
		is >> y;
		is >> temp;
		is >> r;
		is >> temp;
		
		input[count++] = new Circle(color, x, y, r);
	}
	else if(temp == 'T')		//a Triangle?
	{
		double point[6];
		
		for(int i = 0; i < 8; i++)
			is >> temp;						//Burn the "riangle("
			
		string colorstr;						//grab our color
		is >> temp;		
		while(temp != ',')
		{
			colorstr += temp;
			is >> temp;						//The last time through, this disposes of the comma
		}
		
		for(int i = 0; i < 8; i ++)		//assign our color
			if(colorstr == colorChoices[i])
				color = (Color)i;
				
		for(int i = 0; i < 6; i++)		//get points
		{
			is >> point[i];
			is >> temp;
		}
		
		input[count++] = new Triangle(color, point);		
	}
	else if(temp == 'P')		//or a Polygon?
	{
		double *point;
		int size;
		
		for(int i = 0; i < 7; i++)
			is >> temp;						//Burn the "olygon("
			
		string colorstr;						//grab our color
		is >> temp;		
		while(temp != ',')
		{
			colorstr += temp;
			is >> temp;						//The last time through, this disposes of the comma
		}
		
		for(int i = 0; i < 8; i ++)		//assign our color
			if(colorstr == colorChoices[i])
				color = (Color)i;
				
		is >> size; 							//grab our size
		is >> temp;							//discard the comma
		
		point = new double[size*2];
		
		for(int i = 0; i  < size*2; i++)	//get points
		{
			is >> point[i];
			is >> temp;
		}
		
		input[count++] = new Polygon(color, point, size);
		
		delete []point;
	}
	else								//Must be a group
	{
		Geometry ** objects;
		int size;
		
		for(int i = 0; i < 5; i++)
			is >> temp;						//Burn the "roup("
			
		string colorstr;						//grab our color
		is >> temp;		
		while(temp != ',')
		{
			colorstr += temp;
			is >> temp;						//The last time through, this disposes of the comma
		}
		
		for(int i = 0; i < 8; i ++)		//assign our color
			if(colorstr == colorChoices[i])
				color = (Color)i;
				
		is >> size; 							//grab our size
		is >> temp;							//discard the comma
		
		objects = new Geometry*[size];
		
		int tracker = 0;
		for(int i = 0; i < size; i ++)	//recursively make our shapes
		{
			createShape(is, objects, tracker);
			is >> temp;
		}
		
		input[count++] = new Group(color, size, objects);
		
		delete []objects;
	}
}

int main(int argc, char * argv[])
{
	string myColors[8] = { "BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE" };

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
		int count =  0;
	
			
		fstream fs(argv[1]);		
		stringstream ss;
		string fileBuffer;
		
		while(fs >> fileBuffer)
		{
			ss << fileBuffer;			
			createShape(ss, shapes, count);			
		}
	
	
		if((string)argv[2] == "count")
		{
			int tally[8] = {0,0};
			
			for(int i = 0; i < count; i++)
				tally[(shapes[i]->getColor())] += shapes[i]->realCount(); //returns 1 for all but group			
				
			for(int i = 0; i < 8; i++)
				cout << tally[i] << " " << myColors[i] << endl;
		}
		else if((string)argv[2] == "perimeter")
		{
			double perim = 0;
			
			for(int i = 0; i < count; i++)
				perim += shapes[i]->perimeter();
				
			cout << perim << endl;
		}
		else if((string)argv[2] == "area")
		{
			double areas[8] = {0,0};
			
			for(int i = 0; i < count; i++)
			{
				areas[(shapes[i]->getColor())] += shapes[i]->area();
			}
				
			for(int i = 0; i < 8; i++)
				cout << areas[i] << " " << myColors[i] << endl;
		}
		else if((string)argv[2] == "bounds")
		{
			double bounds[4] = {999999, -999999, -999999, 999999};
			
			for(int i = 0; i < count; i++)
			{	
				shapes[i]->bounds(bounds);
			}	
			for(int i = 0; i < 4; i++)
			{
				cout << bounds[i];
				if(i < 3)
					cout << ", ";
			}
			cout << endl;
		}
		else if((string)argv[2] == "move")
		{
			double dx, dy;
			stringstream ss(argv[3]);
			ss >> dx;
			stringstream ss2(argv[4]);
			ss2 >> dy;
			cout << dx << " " << dy << endl;
			for(int i = 0; i < count; i++)
				shapes[i]->translate(dx, dy);

			for(int i = 0; i < count; i++)
			{
				shapes[i]->draw(cout);
				cout << endl;
			}
		}
		else //cycle
		{
			for(int i = 0; i < count; i ++)
				shapes[i]->setColor((Color)((shapes[i]->getColor() +1)%8));
				
			for(int i = 0; i < count; i++)
			{
				shapes[i]->draw(cout);
				cout << endl;
			}
		}
	

	}
}
