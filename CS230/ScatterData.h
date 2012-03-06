#include <iostream>
#include <sstream>

using namespace std;



/************************************************************************************************************************/
/*						Declarations								*/
/************************************************************************************************************************/

template <class T>
class ScatterData
{
	public:

		struct Point
		{
			Point() : x(0), y(0) {}
			Point(T a,T b) : x(a),y(b) {}
			bool operator==(const Point &other) {return (x == other.x && y == other.y);}
			T x,y;
		};

		
		//=-=-=-=-=-=-=-====-=--=-=-=-=-=-=-=-=-=-=-=-=-=Constructor/Destructor==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		ScatterData();						//default, empty data set
		ScatterData(const ScatterData<T> &other);		//copy constructor
		ScatterData(T *x,T *y,int n);				//create data set from x[] and y[]
		ScatterData(Point *p,int n);				//create data set from p[]
		ScatterData(istream &istream);				//read a text description from the input stream
		ScatterData(const string &s);				//read a text description from the input stream

		~ScatterData();						//bc we have a dynamic array (allocated memory)

		



		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=

		void  insert(const T & x,const T &y);					//concatenate the point (x,y) to the data set
		void  insert(const Point &p);					//concatenate the point p to the data set
		void  remove(const T &x,const T &y);					//remove all points (x,y) from the data set
		void  remove(const Point &p);					//remove all points p from the data set
		int   count() const;					//number of points in the data set
		int   count(const T &x, const T &y) const;				//number of occurrences of the point (x,y) in the data set
		int   count(const Point &p) const;				//number of occurrences of the point p in the data set
		Point topLeft() const;					//top-left corner of bounding box
		Point bottomRight() const;				//botom-right corner of bounding box



		//=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		const ScatterData<T> &operator=(const ScatterData<T> &other);
		
		const ScatterData<T>::Point &operator[](int index) const;	

		ScatterData<T> operator+(const ScatterData<T> &other) const;
		ScatterData<T> operator+(const Point &a) const;
		

		void operator+=(const ScatterData<T> &other);
		void operator+=(const Point & a);

		bool operator==(const ScatterData<T> &other) const;
		bool operator!=(const ScatterData<T> &other) const;


		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Global Receivers=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		void print(ostream &os) const;
		void input(istream &os);	

	private:

		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Implementation Variables=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		int numElements;
		int arraySize;
		Point *data;
};


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Global Handlers=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=

	//call internal function
	template <class T>
	ostream & operator<<(ostream &os, const ScatterData<T> &printed)
	{
		printed.print(os);
		return os;
	}

	//call internal function
	template <class T>
	istream &operator>>(istream &is, ScatterData<T> &inputted)
	{
		inputted.input(is);
		return is;
	}

	//just switch order and call appropriate function
	template <class T>
	ScatterData<T> operator+(const typename ScatterData<T>::Point &p, const ScatterData<T> &data)
	{
		return data + p;
	}



/****************************************************************************************************/
/*																						Definitions																				  			   */
/****************************************************************************************************/

//=-=-=-=-=-=-=-====-=--=-=-=-=-=-=-=-=-=-=-=-=-=Constructors/Destructor==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class T>
ScatterData<T>::ScatterData()
	:numElements(0),
	 arraySize(10)
{
	data = new Point[arraySize];	
}

template <class T>
ScatterData<T>::ScatterData(const ScatterData<T> &other)
	:numElements(other.numElements),
	 arraySize(other.arraySize)
{
	data = new Point[arraySize];
	for(int i = 0; i < numElements; i++)
	{
		data[i].x = other.data[i].x;
		data[i].y = other.data[i].y;
	}	
}

template <class T>
ScatterData<T>::ScatterData(T *x,T *y,int n)
	:numElements(n),
	 arraySize(n)
{
	data = new Point[arraySize];
	for(int i = 0; i < numElements; i++)
	{
		data[i].x = x[i];
		data[i].y = y[i];
	}
}

template <class T>
ScatterData<T>::ScatterData(Point *p,int n)
	:numElements(n),
	 arraySize(n)
{
	data = new Point[arraySize];
	for(int i = 0; i < numElements; i++)
	{
		data[i].x = p[i].x;
		data[i].y = p[i].y;
	}
}

//passes work to istream function
template <class T>
ScatterData<T>::ScatterData(istream &istream)
{
	data = new Point[1]; //idk if you can delete what doesn't exist, but this line avoids the issue
	istream >> *this;
}

//passes work to istream function
template <class T>
ScatterData<T>::ScatterData(const string &s)
{
	data = new Point[1]; //same comment as prev function
	stringstream ss(s);
	ss >> *this;
}


//simple
template <class T>
ScatterData<T>::~ScatterData()
{
	delete []data;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=

//passing work to next function
template <class T>
void ScatterData<T>::insert(const T & x,const T & y)
{
	Point temp(x,y);	//transform
	insert(temp);		//delegate work
}

//inserts a point, resizing array if needed
template <class T>
void ScatterData<T>::insert(const Point &p)
{
	if(arraySize == numElements)							//make bigger...
	{
		arraySize *= 2;
		Point *temp = new Point[arraySize];
		for(int i = 0; i < numElements; i++)
			temp[i] = data[i];
		
		delete []data;
		data = temp;				
	}
	
	data[numElements++] = p;							//and store it
}

//passing work to next function
template <class T>
void ScatterData<T>::remove(const T &x, const T &y)
{
	Point temp(x, y);		//transform
	remove(temp);		//delegate work
}

//remove ALL the points p
template <class T>
void ScatterData<T>::remove(const Point &p)
{
	for(int i = 0; i < numElements; i++)
		if(data[i] == p)								//if its equal, kill it
		{
			numElements--;
			data[i] = data[numElements];		
			i --;												//we have to recheck the value we put there, though this would generally be bad
		}	
}

//just a getter for numElements basically
template <class T>
int ScatterData<T>::count() const
{
	return numElements;
}

//passes to next function
template <class T>
int ScatterData<T>::count(const T &x,const T &y) const
{
	Point temp(x,y);				//transform
	return count(temp);		//delegate work
}

//count instances of a point
template <class T>
int ScatterData<T>::count(const Point &p) const
{
	int counter = 0;
	for(int i = 0; i < numElements; i++)		//simply cycle and inc
		if(data[i] == p)
			counter++;
			
	return counter;
}

//return min x, max y
template <class T>
typename ScatterData<T>::Point ScatterData<T>::topLeft() const
{
	T maxy = data[0].y;
	T minx = data[0].x;
	
	for(int i = 0; i < numElements; i++)			//go through as simeoultaneously find min x and max y
	{
		if(data[i].y > maxy)
			maxy = data[i].y;
			
		if(data[i].x < minx)
			minx = data[i].x;
	}
	
	return ScatterData<T>::Point(minx, maxy);	//return as a point
}

//return max x, min y
template <class T>
typename ScatterData<T>::Point ScatterData<T>::bottomRight() const										
{
	T miny = data[0].y;
	T maxx = data[0].x;
	
	for(int i = 0; i < numElements; i++)		//go through as simeoultaneously find max x and min y
	{
		if(data[i].y < miny)
			miny = data[i].y;
			
		if(data[i].x > maxx)
			maxx = data[i].x;
	}
	
	return ScatterData<T>::Point(maxx, miny);	//return them as a point
}


//=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//standard assignment operator
template<class T>
const ScatterData<T> &ScatterData<T>::operator=(const ScatterData<T> &other)
{
	if(this == &other)										//We don't want to be suicidal now
		return *this;
		
	arraySize = other.arraySize;							//overwrite old dimensions so we're identical
	numElements = other.numElements;
	
	delete []data;
	data = new Point[arraySize];
	for(int i = 0; i < numElements; i ++)					//remake the data in the image of other
	{
		data[i].x = other.data[i].x;
		data[i].y = other.data[i].y;
	}
	
	return *this;
}

//return the point at the index spot in the data array
template<class T>
const typename ScatterData<T>::Point &ScatterData<T>::operator[](int index) const
{
	return data[index];
}


//combines two ScatterDatas
template<class T>
ScatterData<T> ScatterData<T>::operator+(const ScatterData<T> &other) const
{
	ScatterData<T> answer(*this);							//Just construct the answer with the first set inside
	for(int i = 0; i < other.numElements; i++)
		answer.insert(other.data[i]);						//add the other item by item
		
	return answer;
}

//We transform the Point into a ScatterData and pass it to the above function
template<class T>
ScatterData<T> ScatterData<T>::operator+(const Point &a) const
{
	ScatterData<T> temp;
	temp.insert(a);					//easiest way to trasform
	return (*this + temp);			//pass to the work function
}

//This function just glues the corresponding operator= to the corresponding operator+
template<class T>
void ScatterData<T>::operator+=(const ScatterData<T> &other)
{
	*this = *this + other;
}

//This function just glues the corresponding operator= to the corresponding operator+
template<class T>
void ScatterData<T>::operator+=(const Point &a)
{
	this->insert(a);
}

//We know the two are equal if they are the same length and they have the same count of each point for each point in the first array
template<class T>
bool ScatterData<T>::operator==(const ScatterData<T> &other) const
{
	if(numElements != other.numElements) 				//if they aren't the same size we have no hope
		return false;
		
	for(int i = 0; i < numElements; i ++)				//make sure all the data is symmetric
		if(count(data[i]) != other.count(data[i]))
			return false;
	
	return true;
}

//We just negate == for !=
template<class T>
bool ScatterData<T>::operator!=(const ScatterData<T> &other) const
{
	return !(*this == other);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Global Receivers=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//This does the work for the << operator prints out to the given ostream
template <class T>
void ScatterData<T>::print(ostream &os) const
{
	os << "[";
	for(int i = 0; i < numElements; i++)
	{
		os << "(" << data[i].x << "," << data[i].y << ")";
		if(i < numElements-1)
			os << ",";
	}
	os << "]";
}

//This is the work function for the >> operator as well as the istream and string constructors
template <class T>
void ScatterData<T>::input(istream &is)	
{
	//We need to reset whats there
	delete []data;
	arraySize = 1;
	numElements = 0;
	data = new Point[arraySize];
	
	
	//From here on we're parsing and entering
	char prev = ' ';
	bool number = false;
	bool isy = false;
	
	T x;
	T y;
	
	while(true)
	{
		if(!number)
		{
			char character;
			is >> character;
			if(character == ']')
				break;
			else if(character == '[' || character == ')' || (character == ',' && prev == ')'))
			{
				prev = character;
				number = false;
			}
			else if(character == '(')
			{
				prev = character;
				number = true;
			}
			else if(character == ',' && prev != ')')
			{
				prev = character;
				number = true;
				isy = true;
			}
		}
		else if(number)
		{
			if(isy)
			{
				is >> y;
				insert(x,y);
				number = false;
				isy = false;
			}
			else
			{
				is >> x;
				number = false;
				isy = true;
			}
		}
	}
}
