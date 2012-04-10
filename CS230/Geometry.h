#include <iostream>
using namespace std;

enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///********************************************************************************************************************************///
///*													Class Declarations														  *///
///********************************************************************************************************************************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/********************************************************************************************************************************/
/*											Geometry (Base Class) - Declarations												*/
/********************************************************************************************************************************/


class Geometry
{
	public:
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Geometry(Color c) :color(c) {}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		


	virtual double		area() const = 0;											//compute the area of the shape
	virtual double		perimeter() const = 0;										//compute the perimeter of the shape
	virtual void		translate(double dx,double dy) = 0;							//move the shape
	virtual void		draw(ostream &os) const = 0;								//print a description to os (see below)



	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Non-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	void				setColor(Color newColor)	{color = newColor;}				//set the color of the shape
	Color				getColor()	 const 			{return color;}					//get the color of the shape	
	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Protected Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	protected:
	static string colorList[8];
	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	private:
	Color color;
	
};	

/********************************************************************************************************************************/
/*												Box (Derived Class) - Declarations												*/
/********************************************************************************************************************************/

class Box : public Geometry
{
	public:
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Box(Color c,double left, double top, double right, double bottom);
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	double 				getLeft() const 			{return left;}
	double 				getTop() const 				{return top;}
	double 				getRight() const 			{return right;}
	double 				getBottom() const 			{return bottom;}
	
	void 				setLeft(double newl)		{left = newl;}
	void 				setTop(double newt)			{top = newt;}
	void 				setRight(double newr)		{right = newr;}
	void 				setBottom(double newb)		{bottom = newb;}
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	double				area() const;												//compute the area of the shape
	double				perimeter() const;											//compute the perimeter of the shape
	void				translate(double dx,double dy);								//move the shape
	void				draw(ostream &os) const;									//print a description to os (see below)
		
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-	
	private:
	double left, top, right, bottom;
};

/********************************************************************************************************************************/
/*											Circle (Derived Class) - Declarations												*/
/********************************************************************************************************************************/

class Circle : public Geometry
{
	public:	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	Circle(Color c,double centerX,double centerY, double radius);
		
		
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	double 				getCenterX() const 			{return X;}
	double 				getCenterY() const 			{return Y;}
	double				getRadius() const 			{return radius;}
	
	void 				setCenter(double centerX,double centerY) {X=centerX; Y=centerY;}
	void				setRadius(double rad)		{radius = rad;}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	double				area() const;												//compute the area of the shape
	double				perimeter() const;											//compute the perimeter of the shape
	void				translate(double dx,double dy);								//move the shape
	void				draw(ostream &os) const;									//print a description to os (see below)
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-	
	private:
	double X, Y, radius;
};


/********************************************************************************************************************************/
/*											Triangle (Derived Class) - Declarations												*/
/********************************************************************************************************************************/

class Triangle : public Geometry
{
	public:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	Triangle(Color c,double pts[]); 											// pts[] contains 3 pairs (x,y)
	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	double				getCornerX(int i) const					{return points[2*i];}	
	double				getCornerY(int i) const					{return points[2*i+1];}	
	
	void				setCorner(int n,double x,double y)		{points[2*n]=x; points[2*n+1]=y;}
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	double				area() const;												//compute the area of the shape
	double				perimeter() const;											//compute the perimeter of the shape
	void				translate(double dx,double dy);								//move the shape
	void				draw(ostream &os) const;									//print a description to os (see below)
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	private:
	double points[6];
};

/********************************************************************************************************************************/
/*											Polygon (Derived Class) - Declarations												*/
/********************************************************************************************************************************/

class Polygon : public Geometry
{
	public:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	Polygon(Color c,double pts[],int n); 										// pts[] contains n pairs (x,y)
	~Polygon() 													{delete []points;}
		
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	int					getVertexCount() const					{return pointCount/2;}
	double				getVertexX(int i) const					{return points[2*i];}
	double				getVertexY(int i) const					{return points[2*i+1];}
	
	void				setVertexes(double pts[],int n); 				

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	double				area() const;												//compute the area of the shape
	double				perimeter() const;											//compute the perimeter of the shape
	void				translate(double dx,double dy);								//move the shape
	void				draw(ostream &os) const;									//print a description to os (see below)
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-	
	private:
	double *points;
	int pointCount;
};

/********************************************************************************************************************************/
/*											Group (Derived Meta Class) - Declarations											*/
/********************************************************************************************************************************/

class Group : public Geometry
{
	public:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructor/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	Group(Color c,int n,Geometry **list);											//Array of Geometry*
	~Group();																		//gonna have a dynamic array
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Public Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	int					getObjectCount() const				{return count;}
	Geometry *			getObject(int i) 					{return shapes[i];}
	void 				setObjects(int n,Geometry **list);
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Virtual Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	double				area() const;												//compute the area of the shape
	double				perimeter() const;											//compute the perimeter of the shape
	void				translate(double dx,double dy);								//move the shape
	void				draw(ostream &os) const;									//print a description to os (see below)
	
	private:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-	
	Geometry** shapes;
	int count;
};





















