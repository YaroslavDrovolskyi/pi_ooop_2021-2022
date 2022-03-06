#pragma once
#include "Figure.h"

#include <vector>


class Army {
private:
	Color color;
	std::vector<Figure> figures;

	int count_value(int val);

	friend class ChessGame; /////////////////////////
public:

	Army(Color color);
	Color getColor() const;
	Figure* getFigurePointer(std::size_t index);
	bool isKingAlive() const;
};