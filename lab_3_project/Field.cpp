/*!
	\file
	\brief File with implementation of struct Cell and class Field
*/

#include "Field.h"
#include <iostream>

/*!
	Constructor initialize chess board, put figures on places

	\param[in,out] white is a white team
	\param[in,out] black is a black team
	\param[in] size is a size of board (usually it is 8)
*/
Field::Field(Army& white, Army& black, int size) {
	this->cells.resize(size);
	for (std::size_t i = 0; i < size; i++) {
		this->cells[i].resize(size);
		for (std::size_t j = 0; j < size; j++) {
			if (i == 0) { // black
				switch (j) {
				case 0: this->cells[i][j].figure = white.getFigurePointer(12); break;
				case 1: this->cells[i][j].figure = white.getFigurePointer(8); break;
				case 2: this->cells[i][j].figure = white.getFigurePointer(10); break;
				case 3: this->cells[i][j].figure = white.getFigurePointer(14); break;
				case 4: this->cells[i][j].figure = white.getFigurePointer(15); break;
				case 5: this->cells[i][j].figure = white.getFigurePointer(11); break;
				case 6: this->cells[i][j].figure = white.getFigurePointer(9); break;
				case 7: this->cells[i][j].figure = white.getFigurePointer(13); break;
				default: break;
				}
			}
			else if (i == 1) {
				this->cells[i][j].figure = white.getFigurePointer(j);
			}
			else if (i == 6) { // white
				this->cells[i][j].figure = black.getFigurePointer(j);
			}
			else if (i == 7) {
				switch (j) {
				case 0: this->cells[i][j].figure = black.getFigurePointer(12); break;
				case 1: this->cells[i][j].figure = black.getFigurePointer(8); break;
				case 2: this->cells[i][j].figure = black.getFigurePointer(10); break;
				case 3: this->cells[i][j].figure = black.getFigurePointer(14); break;
				case 4: this->cells[i][j].figure = black.getFigurePointer(15); break;
				case 5: this->cells[i][j].figure = black.getFigurePointer(11); break;
				case 6: this->cells[i][j].figure = black.getFigurePointer(9); break;
				case 7: this->cells[i][j].figure = black.getFigurePointer(13); break;
				default: break;
				}
			}
		}
	}
}

/*!
	Print chess board in console \n
	Figures prints as two letters: 'w' or 'b' - means team, and first letter of figure type name: 'p', 'h', 'b', 'r', 'q', 'k'. For example: "wp", "wb".
*/
void Field::print() {
	std::cout << std::endl << "  ";
	for (std::size_t i = 0; i < 23; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int i = 7; i >= 0; i--) {
		std::cout << i << "|";
		for (std::size_t j = 0; j < 8; j++) {
			std::string str;
			if (!this->cells[i][j].figure) {
				str = "  "; // 00
			}
			else {
				if (this->cells[i][j].figure->getType() == FigType::pawn) {
					str = "p";
				}
				else if (this->cells[i][j].figure->getType() == FigType::horse) {
					str = "h";
				}
				else if (this->cells[i][j].figure->getType() == FigType::bishop) {
					str = "b";
				}
				else if (this->cells[i][j].figure->getType() == FigType::rook) {
					str = "r";
				}
				else if (this->cells[i][j].figure->getType() == FigType::queen) {
					str = "q";
				}
				else if (this->cells[i][j].figure->getType() == FigType::king) {
					str = "k";
				}

				if (this->cells[i][j].figure->getColor() == Color::white) {
					str = "w" + str;
				}
				else {
					str = "b" + str;
				}
			}


			std::cout << str << "|";

		}
		std::cout << std::endl;
		std::cout << "  ";
		for (std::size_t i = 0; i < 23; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	// for print indexes of field
//	std::cout << "  ";
//	for (std::size_t i = 0; i < 23; i++) {
//		std::cout << "-";
//	}
	std::cout << "  ";
	for (std::size_t i = 0; i < 8; i++) {
		std::cout << i << "  ";
	}
}


/*!
	Evaluate the chess board. This method used in minimax algorithm

	\returns current value of board
*/
int Field::evaluate() {
	int result = 0;
	for (std::size_t i = 0; i < 8; i++) {
		for (std::size_t j = 0; j < 8; j++) {
			if (cells[i][j].figure) {
				result += cells[i][j].figure->getValue();
			}
		}
	}

	return result;
}

/*!
	Put logical marks on board cells.\n 
	We can see them, when player chose figure: this marks show player possible cells to move.

	\param[in] selected_point is point selected by player
	\param[in] points is points where user can move
*/
void Field::putMarks(const Point& selected_point, const std::vector<Point>& points) {
	for (const Point& p : points) {

		if (this->cells[p.y][p.x].figure) {
			this->cells[p.y][p.x].possible_fight = true;
		}
		else {
			this->cells[p.y][p.x].marked = true;
		}
	}

	this->cells[selected_point.y][selected_point.x].selected = true;

}

/*!
	Clear all logical marks from board cells.
*/
void Field::clearMarks() {
	for (std::size_t i = 0; i < this->cells.size(); i++) {
		for (std::size_t j = 0; j < this->cells[i].size(); j++) {
			this->cells[i][j].marked = false;
			this->cells[i][j].possible_fight = false;
			this->cells[i][j].selected = false;
		}
	}
}