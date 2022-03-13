/*!
	\file
	\brief Header file for declarations of some useful functions
*/

#pragma once
#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include <vector>
#include <string>


template <typename T>
void print(const std::vector<T>& vector);

template <typename T>
std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2);

std::string getCurrentTimeAsString();

#include "AuxFunctions.inl"

#endif // AUXFUNCTIONS_H
