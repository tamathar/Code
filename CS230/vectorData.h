#include <iostream>
#include <math.h>
using namespace std;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*										Vector Data -	Declarations											*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

template <class T>
class VectorData
{

	public:
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructors/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	VectorData();																	//Default
	VectorData(const VectorData & other);											//Copy constructor
	VectorData(int n);																//create a zero-filled vector of size n
	VectorData(T *a,int n);															//create vector of size n from a[]
	
	~Vector();																		//deletes dynamic array

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Core Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	int				size			() const { return length;}						//return length
	void			insert			(const T & element);							//insert element
	void			remove			(const T & element);							//remove element
	int				getUsage		() const { return currentUsage;}				//return currentUsage
	void			incUse			() { currentUsage++;}							//add 1 to currentUsage
	void			decUse			() { currentUsage--;}							//subtract 1 from currentUsage 
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	VectorData<T> 	addition		(const VectorData<T> & other) const;			//element-wise addition of zero-extended vectors
	T 				dotMultiply		(const VectorData<T> & other) const;			//A * B - dot product of two vectors, new vector is size of shortest
	VectorData<T>	scalarMultiply	(const T & scalar) const; 						//A * x - scalar multiplication of vector and a scalar T


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	const 	VectorData<T> & operator=(const VectorData<T> & other);					//assignment op	
	 T & 	operator[](int index) const;											//if 0≤i<size refers to ith element, otherwise 0, both l- and r-value


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	private:

	int length;
	int arraySize;
	int currentUse;
	T * vector;
}

	
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*										Vector Data -	Definitions												*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/	


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Constructors/Destructor=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
template <class T>	
VectorData<T>::VectorData()
	:length(0),
	 arraySize(1),
	 currentUse(1)
{
	vector = new T[arraySize];
}

template <class T>
VectorData<T>::VectorData(const VectorData<T> & other)
	:length(other.length),
	 arraySize(other.arraySize),
	 currentUse(1)
{
	vector = new T[arraySize];
	for(int i = 0; i < length; i++)
		vector[i] = other.vector[i];
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


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Core Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
void VectorData<T>::insert(const T & element)
{
	if(length == arraySize)
	{
		arraySize *= 2;
		T *temp = new T[arraySize];
		for(int i = 0; i < length; i++)
			temp[i] = vector[i];
		
		delete []vector;
		vector = temp;
	}
	
	vector[length++] = element;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
VectorData<T> VectorData<T>::addition (const VectorData<T> & other) const
{
	int tempLength;
	
	if(size() > other.size())
		tempLength = size();
	else
		tempLength = other.size();
		
	VectorData<T> temp();
	
	for(int i = 0; i < tempLength; i++)
		temp.insert(vector[i] + other.vector[i]);

	return temp;
}

template <class T>
T VectorData<T>::dotMultiply (const VectorData<T> & other) const
{
	T answer = 0;
	
	for(int i = 0; i < size() || i < other.size(); i++)
		answer += vector[i] * other.vector[i];

	return answer;
}

template <class T>
VectorData<T> VectorData<T>::scalarMultiply (const T & scalar) const
{
	VectorData<T> temp(*this);
	
	for(int i = 0; i < size(); i++)
		temp.vector[i] *= scalar;
		
	return temp;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <class T>
const VectorData<T> & VectorData<T>::operator=(const VectorData<T> & other)
{
	if(this == &other)										//Say no to suicide
		return *this;
		
	arraySize = other.arraySize;							//overwrite old dimensions so we're identical
	length = other.length;
	
	delete []vector;
	vector = new T[arraySize];
	for(int i = 0; i < length; i ++)					//remake the data in the image of other
		vector[i] = other.vector[i];
	
	return *this;
}

template <class T>
T & VectorData<T>::operator[](int index) const
{
	if(index < 0 || index > size())
		return 0;
	
	return vector[index];
}
	
	
	
	
	
	
	
