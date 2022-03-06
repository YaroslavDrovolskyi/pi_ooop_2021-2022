#include "Point.h"

#include <cassert>

std::string Point::getString() const {
	assert(x >= 0 && x < 8);
	assert(y >= 0 && y < 8);

	std::string result;
	result += 'A' + x;
	result += std::to_string(y + 1);


	return result;
}


std::ostream& operator<<(std::ostream& stream, const Point& point) {
	stream << "(" << point.x << "; " << point.y << ")";

	return stream;
}

bool operator==(const Point& a, const Point& b) {
	if (a.x == b.x && a.y == b.y) {
		return true;
	}
	return false;
}