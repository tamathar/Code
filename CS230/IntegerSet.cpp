//Author: Thomas Scroggins
//Program: CS 230 Assignment 1 Class Definitions

#include "IntegerSet.h"
#include <iostream>
using namespace std;





//Constructors
//_______________________________________________________________________________________

template <class T>
Set<T>::Set()
{
	arraysize = 1;
	array = new T[arraysize];
	length = 0;
}

template <class T>
Set<T>::Set(T numbers[], int size)
{
	arraysize = size +10; //so we have room to grow
	length = size;
	array = new T[arraysize];
	
	for(int i = 0; i < length; i ++)
		array[i] = numbers[i];
}

template <class T>
Set<T>::Set(const Set<T> & other)
{
	arraysize = other.arraysize;
	length = other.length;
	array = new T[arraysize];
	
	for(int i = 0; i < length; i++)
		array[i] = other.array[i];
}

//__________________________________________________________________________________________

template <class T>
Set<T>::~Set()
{
	delete []array;
}

template <class T>
const Set<T> & Set<T>::operator= (const Set<T> & other)
{
	arraysize = other.arraysize;
	length = other.length;
	
	delete []array;
	array = new T[arraysize];
	
	for(int i = 0; i < length; i++)
		array[i] = other.array[i];
	

	return *this;
}

//INTERSECTION
template <class T>
const Set<T> & Set<T>::operator& (const Set<T> & other)
{
	Set<T> answer;
	
	for(int i = 0; i < length; i++)
		for(int j = 0; j < other.length; j++)
			if(array[i] == other.array[j])
				answer.insert(array[i]);
	
	return answer;
}

template <class T>	
const Set<T> & Set<T>::operator& ( T other)
{
	Set<T> temp(other, 1);
	
	return (*this & temp);
}
//global for a & A

template <class T>
const Set<T> & Set<T>::operator&=(const Set<T> & other)
{
	*this = (*this & other);
	return *this;
}

template <class T>
const Set<T> & Set<T>::operator&=(T other)
{
	Set<T> temp(other, 1);
	
	*this = (*this & temp);
	return *this;
}


//UNION
template <class T>
const Set<T> & Set<T>::operator| (const Set<T> & other)
{
	Set<T> answer;
	
	for(int i = 0; i < length; i++)
		answer.insert(array[i]);
		
	for(int j = 0; j < other.length; j++)
		answer.insert(other.array[j]);
	
	return answer;
}

template <class T>
const Set<T> & Set<T>::operator| (T other)
{
	Set<T> temp(other, 1);
	
	return (*this | temp);
}

//global for a | A

template <class T>
const Set<T> & Set<T>::operator|=(const Set<T> & other)
{
	*this = (*this | other);
	
	return *this;
}

template <class T>
const Set<T> * Set<T>::operator|=(T other)
{
	Set<T> temp(other, 1);
	
	*this = (*this | temp);
	return *this;
}


//OTHER
template <class T>
bool Set<T>::operator== (const Set<T> & other)
{
	Set<T> answer;
	
	answer = (*this & other);
	
	if(answer.length == this->length && answer.length == other.length)
		return true;
		
	return false;
}

template <class T>
bool Set<T>::operator!= (const Set<T> & other)
{
	bool answer = (*this == other);
	
	return !answer;
}


//SUBSET
	//PROPER
template <class T>
bool Set<T>::operator< (const Set<T> & other)
{
	Set<T> answer = (*this & other);
	
	if(this->length == answer.length && other.length > answer.length);
		return true;
	return false;
}

//global for a < A

template <class T>
bool Set<T>::operator> (const Set<T> & other)
{
	Set<T> answer = (*this & other);
	
	if(this->length > answer.length && other.length == answer.length);
		return true;
	return false;
}

template <class T>
bool Set<T>::operator> (T other)
{
	Set<T> temp(other, 1);
	
	return (*this > temp);

}


	//NON-PROPER
template <class T>
bool Set<T>::operator<= (const Set<T> & other)
{
	Set<T> answer = (*this & other);
	
	if(this->length == answer.length && other.length >= answer.length);
		return true;
	return false;
}

template <class T>
bool Set<T>::operator>= (const Set<T> & other)
{
	Set<T> answer = (*this & other);
	
	if(this->length >= answer.length && other.length == answer.length);
		return true;
	return false;
}




template <class T>
bool Set<T>::contains(T n)
{
	for(int i = 0; i < length; i++)
		if(array[i] == n)
			return true;
			
	return false;
}

template <class T>
bool Set<T>::empty()
{
	if(length <= 0)
		return true;
	
	return false;
}

template <class T>
int Set<T>::size()
{
	return length;
}

template <class T>
void Set<T>::insert(T n)
{
	if(!contains(n))
	{
		if(length == arraysize)
		{
			arraysize *= 2;
			T *temp = new T[arraysize];
			for(int i = 0; i < arraysize; i++)
				temp[i] = array[i];
			
			delete []array;
			array = temp;			
		}
		
		array[length++] = n;
		
	}		
}

template <class T>
void Set<T>::print(ostream *os)
{
	*os << "{";
	
	for(int i = 0; i < length; i ++)
	{
		*os << array[i];
		if(i < length-1)
			*os << ", ";
	}
	
	*os << "}";
	
}

template <class T>
void Set<T>::remove(T n)
{
	if(!empty() && contains(n))
	{
		for(int i = 0; i < length; i++)
			if(array[i] == n)
			{
				array[i] = array[--length];
				return;
			}
	}
}






//overloaded ops
template <class T>
ostream & operator<< (ostream &os, Set<T> &item)
{
	item.print(&os);
	return os;
}

template <class T>
const Set<T> & operator& (T item, Set<T> A)
{
	Set<T> temp(item, 1);
	
	return (A & temp);
}

template <class T>
const Set<T> & operator| (T item, Set<T> A)
{
	Set<T> temp(item, 1);
	
	return (A | temp);
}

template <class T>
const Set<T> & operator< (T array, Set<T> A)
{
	Set<T> temp(item, 1);
	
	return (temp < A);
}