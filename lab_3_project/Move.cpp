/*!
	\file
	\brief File with implementation of struct Move

*/

#include "Move.h"
#include <iostream>

/*!
	Default constructor, that initialize move as invalid
*/
Move::Move() :
	from{ Point{ -1,-1 } },
	dest{ Point{ -1,-1 } }
{

}


/*!
	Constructor for move

	\param[in] from is move departure point on the chess board
	\param[in] dest is move destination point on the chess board

*/
Move::Move(const Point& from, const Point& dest) :
	from(from),
	dest(dest)
{

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