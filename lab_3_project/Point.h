#pragma once
#include <string>

struct Point {
	int x;
	int y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}
	std::string getString() const;
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
bool operator==(const Point& a, const Point& b);



struct Move {
	Point from;
	Point dest;

	Move(const Point& from, const Point& dest) : from(from), dest(dest) {}

	bool is_valid() {
		if (from.x == -1 && from.y == -1 && dest.x == -1 && dest.y == -1) {
			return false;
		}
		return true;
	}
};