/*!
	\file
	\brief File with implementation of class Figure
*/

#include "Figure.h"

/*!
	Getter for figure value

	\returns value of figure
*/
int Figure::getValue() {
	int result;
	if (this->type == FigType::pawn) {
		result = 10;
	}
	else if (this->type == FigType::horse || this->type == FigType::bishop) {
		result = 30;
	}
	else if (this->type == FigType::rook) {
		result = 50;
	}
	else if (this->type == FigType::queen) {
		result = 90;
	}
	else if (this->type == FigType::king) {
		result = 900;
	}

	if (this->color == Color::black) {
		result *= -1;
	}

	return result;
}

/*!
	Show if figure alive or not

	\returns true is figure is alive, and false if not
*/
bool Figure::isAlive() const {
	return this->is_alive;
}

/*!
	Getter for figure color

	\returns color of figure
*/
Color Figure::getColor() const {
	return this->color;
}

/*!
	Getter for figure type

	\returns type of figure
*/
FigType Figure::getType() const {
	return this->type;
}

/*!
	Getter for figure position

	\returns position of figure
*/
Point Figure::getPosition() const {
	return this->position;
}

/*!
	Setter for figure position

	\param[in] new_pos is a new position of figure
*/
void Figure::setPosition(const Point& new_pos) {
	this->position = new_pos;
}

/*!
	Allow to change aliveness of figure

	\param[in] new_is_alive is a new aliveness of figure: true or false
*/
void Figure::setIsAlive(bool new_is_alive) {
	this->is_alive = new_is_alive;
}

/*!
	== Operator for class Figure

	\param[in] a is a left operand
	\param[in] b is a right operand
*/
bool operator==(const Figure& a, const Figure& b) {
	return (a.getColor() == b.getColor() && a.getPosition() == b.getPosition() &&
		a.getType() == b.getType() && a.isAlive() == b.isAlive());
}