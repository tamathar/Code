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
	
	~VectorData();																		//deletes dynamic array

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Core Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	int				size			() const { return length;}						//return length
	int				useCount		() const { return currentUse;}				//return currentUsage
	void			incUse			() { currentUse++;}							//add 1 to currentUsage
	void			decUse			() { currentUse--;}							//subtract 1 from currentUsage 
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Basic Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	void			print			(ostream & os);									//print the array for debugging


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Overloaders=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	const 	VectorData<T> & operator=(const VectorData<T> & other);					//assignment op	
	 T & 	operator[](int index);													//if 0≤i<size refers to ith element, otherwise 0, both l- and r-value


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Data=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	private:

	int length;
	int arraySize;
	int currentUse;
	T * vector;
	static T fakeval;
	
	//private convenience function
	void 			insert			(const T & element);
};

	
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*										Vector Data -	Definitions												*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/	

//init fakeval
template <class T>
T VectorData<T>::fakeval = 0;


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
VectorData<T>::~VectorData()
{
	delete []vector;
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Private Functions=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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




template <class T>
void VectorData<T>::print (ostream & os)
{
	os << "(";
	for(int i = 0; i < length; i++)
		os << (*this)[i] << ",";
	os << ")";
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
T & VectorData<T>::operator[](int index)
{
	fakeval = 0;
	if(index < 0 || index >= size())
		return fakeval;
		
	return vector[index];
}
	
	
	
	
	
	
	
