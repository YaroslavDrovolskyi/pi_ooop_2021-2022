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

	\todo replace friend class ChessGame by getters, setters and other methods to use
*/
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