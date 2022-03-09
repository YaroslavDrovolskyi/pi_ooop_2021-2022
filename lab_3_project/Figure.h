/*!
	\file
	\brief Header file for enum Color, enum FigType and class Figure
*/

#pragma once
#include "Point.h"


/*!
	\enum Color
	\brief Enum that describes color of chess figure
*/
enum class Color {
	black, white
};

/*!
	\enum FigType
	\brief Enum that describes type of chess figure
*/
enum class FigType {
	pawn, // 10
	horse, // 30
	bishop, // 30, goes through diagonales
	rook, // 50, goes through lines
	queen, // 90
	king // 900
};

/*!
	\brief Class that describes chess figure

	It contains color, type, value and position of figure. \n
	== operator is overloaded fro this class
*/
class Figure {
private:
	Color color;
	FigType type;
	int value;
	bool is_alive;
	Point position;


public:
	Figure() {}
	Figure(Color color, FigType type, const Point& pos) : color(color), type(type), is_alive(true), position(pos), value(getValue()) {}

	Color getColor() const;
	FigType getType() const;
	Point getPosition() const;
	int getValue();
	bool isAlive() const;

	void setPosition(const Point& new_pos);
	void setIsAlive(bool new_is_alive);
};

bool operator==(const Figure& a, const Figure& b);