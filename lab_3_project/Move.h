/*!
	\file
	\brief header file for struct Move
*/

#pragma once
#include "Point.h"



/*!
	\brief Struct that describes move on the chess board.\n

	Operators << and == are overloaded for this struct.
*/
struct Move {
	Point from;
	Point dest;

	Move(); // initialize move as invalid
	Move(const Point& from, const Point& dest);

	bool isValid() const;
};

bool operator==(const Move& a, const Move& b);
std::ostream& operator<<(std::ostream& stream, const Move& point);