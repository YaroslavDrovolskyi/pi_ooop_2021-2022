/*!
	\file
	\brief header file for struct Point
*/

#pragma once
#include <string>

/*!
	\brief Struct that describes cell position on the chess board

	Counting starts from left bottom corner. It starts from (0,0).\n

	Operators << and == are overloaded for this struct.
*/
struct Point {
	int x;
	int y;

	Point(int x = 0, int y = 0);
	std::string getString() const;
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
bool operator==(const Point& a, const Point& b);
