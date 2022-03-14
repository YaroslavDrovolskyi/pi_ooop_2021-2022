/*!
	\file
	\brief File with implementation of struct Point

*/

#include "Point.h"

#include <cassert>
#include <iostream>



/*!
	Constructor. 

	\param[in] x is x coordinate of point
	\param[in] y is y coordinate of point
*/
Point::Point(int x, int y) : x(x), y(y) {}
/*!
	Converts "math" coordinate (x;y) on chess board into "game" representation (for example: A5, F8)
	\returns "game" representation of (x;y) coordinate
*/
std::string Point::getString() const {
	assert(x >= 0 && x < 8);
	assert(y >= 0 && y < 8);

	std::string result;
	result += 'A' + x;
	result += std::to_string(y + 1);


	return result;
}

/*!
	<< Operator for class Point

	\param[in, out] stream is a left operand
	\param[in] point is a right operand
*/
std::ostream& operator<<(std::ostream& stream, const Point& point) {
	stream << "(" << point.x << "; " << point.y << ")";

	return stream;
}

/*!
	== Operator for class Point

	\param[in] a is a left operand
	\param[in] b is a right operand
*/
bool operator==(const Point& a, const Point& b) {
	if (a.x == b.x && a.y == b.y) {
		return true;
	}
	return false;
}

