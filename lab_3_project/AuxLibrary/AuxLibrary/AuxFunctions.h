/*!
	\file
	\brief Header file for declarations of some useful functions in AuxFunctions library
*/

#pragma once
#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#ifdef AUXLIBRARY_EXPORTS
#define AUXLIBRARY_API __declspec(dllexport)
#else
#define AUXLIBRARY_API __declspec(dllimport)
#endif



#include <vector>
#include <string>

extern "C++" {
	template <typename T>
	AUXLIBRARY_API void print(const std::vector<T>& vector);
}

extern "C++" {
	template <typename T>
	AUXLIBRARY_API std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2);
}

extern "C++" AUXLIBRARY_API std::string getCurrentTimeAsString();



#include "AuxFunctions.inl"

#endif // AUXFUNCTIONS_H




// Guide how to make a library: https://docs.microsoft.com/ru-ru/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170
