#include <iostream>
#include <math.h>
using namespace std;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*										Vector Data -	Declarations												*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

template <class T>
class VectorData
{

	public:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructors/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	VectorData();																	//Default
	VectorData(int n);																//create a zero-filled vector of size n
	VectorData(T *a,int n);															//create vector of size n from a[]
	
	~Vector();																		//deletes dynamic array

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	int size();																		//number of elements in the vector
	double magnitude();																	//Euclidean norm of the vector
	#ifdef DEBUG
	const VectorData<T> & implementation();											//DEBUG only, returns underlying implementation, see below
	#endif	
	int useCount();																	//number of "co-owners"


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	const VectorData<T> & operator=(const VectorData<T> & other);					//assignment op

	      VectorData<T>   operator+(const VectorData<T> & other) const;
	const VectorData<T> & operator+=(const VectorData<T> & other);					//element-wise addition of zero-extended vectors, new vector is size of longest operand

	      VectorData<T>   operator*(const VectorData<T> & other) const;				//dot product of two vectors, new vector is size of shortest

		  VectorData<T>   operator*(int scalar) const;
	const VectorData<T> & operator*=(int scalar);									//scalar multiplication of vector and a scalar T

	bool operator==(const VectorData<T> & other) const;								//A exactly equals B
	bool operator!=(const VectorData<T> & other) const;								//A does not equal B
	
	 T & operator[](int index) const;											//if 0≤i<size refers to ith element, otherwise 0, both l- and r-value


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	private:

	int length;
	int arraySize;
	int currentUse;
	T * vector;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Global Handler=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
VectorData<T> operator*(int scalar, const VectorData<T> vector) {return vector*scalar;}
	
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*										Vector Data -	Definitions												*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/	
	
template <class T>	
VectorData<T>::VectorData()
	:length(0),
	 arraySize(1),
	 currentUse(1)
{
	vector = new T[arraySize];
}

template <class T>
VectorData<T>::VectorData(int n)
	:length(n),
	 arraySize(n),
	 currentUse(1)
{
	vector = new T[arraySize];
	for(int i = 0; i < length; i++)
		vector[i] = 0;
}

template <class T>
VectorData<T>::VectorData(T *a,int n)
	:length(n),
	 arraySize(n),
	 currentUse(1)
{
	vector = new T[arraySize];
	for(int i = 0; i < length; i++)
		vector[i] = a[i];
}

template <class T>
VectorData<T>::~Vector()
{
	delete []vector;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
int VectorData<T>::size()
{
	return length;
}

template <class T>
double VectorData<T>::magnitude()
{
	T temp = 0;
	for(int i = 0; i < length; i++)
		temp += pow(this[i], 2);
	
	return sqrt(temp);
}

#ifdef DEBUG
template <class T>
VectorData<T> & VectorData<T>::implementation()
{
	return *this;	
}
#endif	

template <class T>
int VectorData<T>::useCount()
{
	return currentUse;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
const VectorData<T> & VectorData<T>::operator=(const VectorData<T> & other)
{
	if(this == &other) return *this;					//suicide not allowed
	
	arraySize = other.arraySize;
	length = other.length;
	
	delete []vector;
}

template <class T>
      VectorData<T>   VectorData<T>::operator+(const VectorData<T> & other) const;

template <class T>
const VectorData<T> & VectorData<T>::operator+=(const VectorData<T> & other);					//element-wise addition of zero-extended vectors, new vector is size of longest operand

template <class T>
      VectorData<T>   VectorData<T>::operator*(const VectorData<T> & other) const;				//dot product of two vectors, new vector is size of shortest

template <class T>
	  VectorData<T>   VectorData<T>::operator*(int scalar) const;

template <class T>
const VectorData<T> & VectorData<T>::operator*=(int scalar);									//scalar multiplication of vector and a scalar T

template <class T>
bool VectorData<T>::operator==(const VectorData<T> & other) const;								//A exactly equals B

template <class T>
bool VectorData<T>::operator!=(const VectorData<T> & other) const;								//A does not equal B

template <class T>
T & VectorData<T>::operator[](int index) const;		
	
	
	
	
	
	
	
