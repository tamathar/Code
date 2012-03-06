//Thomas Scroggins
// Class for containing a set of integers (not templatized)

#include <iostream>
using namespace std;




template <class T>
class Set{

	public:
		//constructors/destructor
		Set();
		Set(T numbers[], int size);
		Set(const Set<T> &other);
		~Set();
		
		const Set<T> & operator= (const Set<T> & other);
	
		//INTERSECTION
		const Set<T> & operator& (const Set<T> & other);		
		const Set<T> & operator& ( T other);
		//global for a & A
		
		const Set<T> & operator&=(const Set<T> & other);
		const Set<T> & operator&=(T other);
		
		//UNION
		const Set<T> & operator| (const Set<T> & other);
		const Set<T> & operator| (T other);
		//global for a | A
		
		const Set<T> & operator|=(const Set<T> & other);
		const Set<T> * operator|=(T other);
		
		//OTHER
		bool operator== (const Set<T> & other);
		bool operator!= (const Set<T> & other);
		
		//SUBSET
			//PROPER
		bool operator< (const Set<T> & other);
		//global for a < A
		
		bool operator> (const Set<T> & other);
		bool operator> (T other);
		
			//NON-PROPER
		bool operator<= (const Set<T> & other);
		bool operator>= (const Set<T> & other);
		
		
		

		bool contains(T n);
		bool empty();
		int size();
		
		void insert(T n);
		void print(ostream *os);
		void remove(T n);
	

		
		
	private:
		int arraysize;
		T *array;
		int length;
};

// << overload
template <class T>
ostream & operator<< (ostream &os, Set<T> &item);

template <class T>
const Set<T> & operator& (T item, Set<T> A);

template <class T>
const Set<T> & operator| (T item, Set<T> A);

template <class T>
const Set<T> & operator< (T item, Set<T> A);





