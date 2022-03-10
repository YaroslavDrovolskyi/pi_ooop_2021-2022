/*!
	\file
	\brief File with implementation of structs Point and Move

*/

#include "Point.h"

#include <cassert>
#include <iostream>

/*!
	Converts "math" coordinate (x;y) on chess board into "game" representation (for example: A5, F8)
	\returns "game representation of (x;y) coordinate"
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

/*!
	Shows if move is valid
	\returns true if move is valid, and false if not
*/
bool Move::isValid() const {
	if (from.x == -1 && from.y == -1 && dest.x == -1 && dest.y == -1) {
		return false;
	}
	return true;
}


/*!
	== Operator for class Move

	\param[in] a is a left operand
	\param[in] b is a right operand
*/
bool operator==(const Move& a, const Move& b) {
	return (a.from == b.from && a.dest == b.dest);
}

/*!
	<< Operator for class Point

	\param[in, out] stream is a left operand
	\param[in] move is a right operand
*/
std::ostream& operator<<(std::ostream& stream, const Move& move) {
	stream << move.from.getString() << " -> " << move.dest.getString();

	return stream;
}

