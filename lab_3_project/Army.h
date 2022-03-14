/*!
	\file
	\brief Header file for class Army
*/

#pragma once
#include "Figure.h"

#include <vector>




/*!
	\brief Class that describes chess team: set of same-colored figures

	It stores list of figures and color of team.
*/
class Army {
private:
	Color color;
	std::vector<Figure> figures;

	int count_value(int val);

public:

	Army(const Color& color);
	void restore();
	Color getColor() const;
	Figure* getFigurePointer(std::size_t index);
	const std::vector<Figure>& getAllFigures() const;
	bool isKingAlive() const;
};