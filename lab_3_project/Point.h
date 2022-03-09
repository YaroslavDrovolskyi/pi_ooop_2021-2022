/*!
	\file
	\brief header file for structs Point and Move
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

	Point(int x = 0, int y = 0) : x(x), y(y) {}
	std::string getString() const;
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
bool operator==(const Point& a, const Point& b);


/*!
	\brief Struct that describes move on the chess board.\n

	Operators << and == are overloaded for this struct.
*/
struct Move {
	Point from;
	Point dest;

	Move() : from{Point{ -1,-1 }}, dest{Point{ -1,-1 }} {} ///< constructor, that initialize object as invalid
	Move(const Point& from, const Point& dest) : from(from), dest(dest) {}

	bool isValid() const;
};

bool operator==(const Move& a, const Move& b);
std::ostream& operator<<(std::ostream& stream, const Move& point);