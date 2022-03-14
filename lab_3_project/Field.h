/*!
	\file
	\brief Header file for struct Cell and class Field
*/


#pragma once
#include "Army.h"


/*!
	\brief Struct that describes cell on chess board

	It contains address of figure, that stay on it, and some visual flags, that used in displaying cell
*/
struct Cell {
public:
	Figure* figure;
	bool marked; ///< cell is marked (possible move and not attack)
	bool possible_fight;
	bool selected; ///< selected own figure

	Cell();
	void clean();
};



/*!
	\brief Class that describes chess board

	As for structure: it is a matrix size x size (usually 8x8) of struct Cell
*/
class Field {
private:
	void putFiguresOnField(Army& white, Army& black);
	std::size_t size;
	std::vector <std::vector <Cell>> cells; ///<implementation of matrix
public:

	Field() {}
	Field(Army& white, Army& black, std::size_t size = 8);
	void restore(Army& white, Army& black);
	void putMarks(const Point& from, const std::vector<Point>& points);
	void clearMarks();
	void print() const;
	int evaluate();
	std::size_t getSize() const;
	Cell& getCell(const Point& point);
	Cell& getCell(int x, int y);

};