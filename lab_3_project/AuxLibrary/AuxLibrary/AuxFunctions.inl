/*!
	\file
	\brief File with implementation of template functions declarated in file AuxFunctions.h
*/

#ifndef AUXFUNCTIONS_INL
#define AUXFUNCTIONS_INL


#include "pch.h"
#include <iostream>
#include "AuxFunctions.h"




/*!
	Function that prints all elements of vector \n
	\warning Operator << must be overloaded for vector items

	\param[in] vector is vector to print

*/
template <typename T>
void print(const std::vector<T>& vector) {
	if (vector.size() == 0) { return; }
	for (const T& t : vector) {
		std::cout << t << " ";
	}
	std::cout << std::endl;
}


/*!
	Function that concatinate two vectors \n

	\param[in] vec1 is first vector
	\param[in] vec2 is second vector

	\returns new vector = concatinate vec1 and vec2

*/
template <typename T>
std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2) {
	std::vector<T> result;

	for (const T& i : vec1) {
		result.push_back(i);
	}

	for (const T& i : vec2) {
		result.push_back(i);
	}

	return result;
}



#endif // AUXFUNCTIONS_INL