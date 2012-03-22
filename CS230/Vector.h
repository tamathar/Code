#include "VectorData.h"
using namespace std;


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*									Vector (facade class) -	Declarations										*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

template <class T>
class Vector
{
	public:
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructors/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
						Vector();													//default
						Vector(int n);												//create a zero-filled vector of size n
						Vector(const Vector & other);								//copy constructor
						Vector(T *a,int n);											//create vector of size n from a[]
						~Vector();													//Dec use/dealloc
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	Vector<T> 			addition(const Vector<T> & other) const;					//element-wise addition of zero-extended vectors
	T 					dotMultiply(const Vector<T> & other) const;					//A * B - dot product of two vectors, new vector is size of shortest
	Vector<T>			scalarMultiply(const T & scalar) const;						//A * x - scalar multiplication of vector and a scalar T
	void				print(ostream & os) const {if(data)data->print(os);}		//print vector to ostream
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Required Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	int					size() const {return data ? data->size() : 0;}				//number of elements in the vector
	T					magnitude() const;											//Euclidean norm of the vector
	#ifdef DEBUG
	VectorData<T>&		implementation() {if(!data) data = new VectorData<T>; return *data;}//DEBUG only, returns underlying implementation, see below
 	#endif
	
	const Vector<T> & 	operator=(const Vector<T> other);							//assignment operator
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-In-Class Overloads=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	T &					operator[](int index);
	T 					operator[](int index) const;
	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"Private" Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	void				copyData();													//our function for copy-on-write
	private:
						Vector(const VectorData<T> & source);						//for our purposes	

	
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	VectorData<T> * data;
	static T		fakeval; 														//redundant, but I don't have time to restructure things
};

template <class T>
T Vector<T>::fakeval = 0;
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*									Vector (facade class) -	Overloads											*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-In-Class Overloads=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <class T>
T &	Vector<T>::operator[](int index)
{
	if(data)
	{
		copyData();
		return (*data)[index];
	}
	fakeval=0;
	return fakeval;
}

template <class T>
T Vector<T>::operator[](int index) const
{
	if(data)	
		return (*data)[index];
	return 0;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Global Overloads=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//ADDITION OVERLOADS
template <class T>
Vector<T> operator+(const Vector<T> & left, const Vector<T> & right) {return left.addition(right);}
template <class T>
void operator+=(Vector<T> & left, const Vector<T> & right) {left.copyData(); left = left.addition(right);}

//DOT MULT OVERLOADS
template <class T>
T operator*(const Vector<T> & left, const Vector<T> & right) {return left.dotMultiply(right);}


//SCALAR OVERLOADS
template <class T>
Vector<T> operator*(const T & scalar, const Vector<T> & vector) {return vector.scalarMultiply(scalar);}

template <class T>
Vector<T> operator*(const Vector<T> & vector, const T & scalar) {return vector.scalarMultiply(scalar);}

template <class T>
void operator*=(Vector<T> & vector, const T & scalar) {vector.copyData(); vector = vector.scalarMultiply(scalar);}

//BOOL OVERLOADS
template <class T>
bool operator==(const Vector<T> & left, const Vector<T> & right) 
{
	if(left.size() == right.size())
	{
		for(int i = 0; i < left.size(); i++)
			if(left[i] != right[i])
				return false;
		return true;
	}
	return false;
}

template <class T>
bool operator!=(const Vector<T> & left, const Vector<T> & right) {return !(left == right);}




/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*									Vector (facade class) -	Implementation										*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/	

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructors/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <class T>
Vector<T>::Vector()
	:data(NULL)
{}

template <class T>
Vector<T>::Vector(int n)
{
	data = new VectorData<T>(n);
}

template <class T>
Vector<T>::Vector(const Vector & other)
	:data(other.data)
{
	if(data)
		data->incUse();
}

template <class T>
Vector<T>::Vector(T *a,int n)
{
	data = new VectorData<T>(a, n);
}

template <class T>
Vector<T>::~Vector()
{
	if(data)
	{
		if(data->useCount() > 1)
			data->decUse();
		else
			delete data;
	}
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Required Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <class T>
T Vector<T>::magnitude() const 
{
	if(!data)
		return 0;
		
	T answer = 0;
	for(int i = 0; i < size(); i++)
	{
		answer += (*this)[i] * (*this)[i];
	}
	
	answer = sqrt(answer);
	return answer;
}


template <class T>
const Vector<T> & Vector<T>::operator=(const Vector<T> other)
{
	
	if(data)
	{
		if(data->useCount() == 1)
			delete data;
		else
			data->decUse();
	}
		
	data=other.data;
	
	if(data)
		data->incUse();
		
	return *this;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
Vector<T> Vector<T>::addition (const Vector<T> & other) const
{
	Vector<T> answer;
	if(data)
	{	

		answer.data = (size() > other.size() ? new VectorData<T>(*data) : new VectorData<T>(*(other.data)));
	}

	for(int i = 0; i < answer.size(); i++)
		answer[i] = (*this)[i] + other[i];

	return answer;
}

template <class T>
T Vector<T>::dotMultiply (const Vector<T> & other) const
{
	T answer = 0;
	
	if(data && other.data)
		for(int i = 0; i < size() || i < other.size(); i++)
		{	
			//cout << other[i] << endl;;
			answer +=  (*this)[i] * other[i];
		}

	return answer;
}

template <class T>
Vector<T> Vector<T>::scalarMultiply (const T & scalar) const
{
	Vector<T> answer(*this);
	
	for(int i = 0; i < size(); i++)
		answer[i] *= scalar;
		
	return answer;
}

template <class T>
void Vector<T>::copyData()
{
	if(data && data->useCount() > 1)
	{
		data->decUse();
		data = new VectorData<T>(*data);
	}
}





