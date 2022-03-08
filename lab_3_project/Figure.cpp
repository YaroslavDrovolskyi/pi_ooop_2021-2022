#include "Figure.h"

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

bool Figure::isAlive() const {
	return this->is_alive;
}

Color Figure::getColor() const {
	return this->color;
}

FigType Figure::getType() const {
	return this->type;
}

Point Figure::getPosition() const {
	return this->position;
}

void Figure::setPosition(const Point& new_pos) {
	this->position = new_pos;
}

void Figure::setIsAlive(bool new_is_alive) {
	this->is_alive = new_is_alive;
}

bool operator==(const Figure& a, const Figure& b) {
	return (a.getColor() == b.getColor() && a.getPosition() == b.getPosition() &&
		a.getType() == b.getType() && a.isAlive() == b.isAlive());
}