/*!
	\file
	\brief File with implementation of class Army
*/

#include "Army.h"

#include <cassert>

/*!
	\brief Constructor
	Create and init all figures

	\param[in] color of chess team
*/
Army::Army(const Color& color) : color(color) {
	this->figures.resize(16);

	int pawns_row_index = color == Color::white ? 1 : 6;
	int others_row_index = color == Color::white ? 0 : 7;

	for (std::size_t i = 0; i < 16; i++) {
		if (i < 8) { // pawns
			Point p(i, pawns_row_index);
			this->figures[i] = Figure(color, FigType::pawn, p);
		}
		else if (i < 10) { // horses
			int j = (i == 8 ? 1 : 6);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::horse, p);
		}
		else if (i < 12) { // bishop
			int j = (i == 10 ? 2 : 5);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::bishop, p);
		}
		else if (i < 14) { // rook
			int j = (i == 12 ? 0 : 7);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::rook, p);
		}
		else if (i == 14) { // queen
			Point p(3, others_row_index);
			this->figures[i] = Figure(color, FigType::queen, p);
		}
		else if (i == 15) { // king
			Point p(4, others_row_index);
			this->figures[i] = Figure(color, FigType::king, p);
		}
	}
}

/*!
	Method that restore position and aliveness of all figures in a team \n
	This method is using for restarting the game
*/
void Army::restore() {
	int pawns_row_index = color == Color::white ? 1 : 6;
	int others_row_index = color == Color::white ? 0 : 7;

	for (std::size_t i = 0; i < 16; i++) {
		figures[i].setIsAlive(true);
		if (i < 8) { // pawns
			figures[i].setPosition(Point(i, pawns_row_index));
		}
		else if (i < 10) { // horses
			int j = (i == 8 ? 1 : 6);
			figures[i].setPosition(Point(j, others_row_index));
		}
		else if (i < 12) { // bishop
			int j = (i == 10 ? 2 : 5);
			figures[i].setPosition(Point(j, others_row_index));
		}
		else if (i < 14) { // rook
			int j = (i == 12 ? 0 : 7);
			figures[i].setPosition(Point(j, others_row_index));
		}
		else if (i == 14) { // queen
			figures[i].setPosition(Point(3, others_row_index));
		}
		else if (i == 15) { // king
			figures[i].setPosition(Point(4, others_row_index));
		}
	}
}

/*!
	Getter for color of army

	\returns color of army
*/
Color Army::getColor() const {
	return this->color;
}


/*!
	Getter for figure by index

	\param[in] index correct index of figure that we need

	\returns pointer on figure, that we need
*/
Figure* Army::getFigurePointer(std::size_t index) {
	return &this->figures[index];
}

/*!
	Shows if king is alive or not

	\returns true if king is alive, and false otherwise
*/
bool Army::isKingAlive() const {
	return this->figures[15].isAlive();
}


int Army::count_value(int val) {
	assert(val > 0);
	return this->color == Color::black ? (-1) * val : val;
}