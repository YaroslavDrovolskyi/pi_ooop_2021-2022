/*!
	\file
	\brief Header file for class MovesHistory
*/

#pragma once
#include "Point.h"
#include "Move.h"
#include "Figure.h"
#include "Army.h"
#include "Field.h"

#include <vector>


/*!
	\brief Class that describes list of moves made during the game

	It stores list of moves and list of figures removed while corresponding move.\n

	Also it contains current index - something like read/write head.
*/
class MovesHistory {
private:
	std::vector<Move> moves;
	std::vector<Figure*> removed_figures;

	std::size_t size;
	std::size_t current_index;

public:
	MovesHistory() : size(0), current_index(0) {};
	void insert(const Move& move, Figure* removed_figure = nullptr);
	std::pair<Move, Figure*> undoMove();
	void clear();

	std::size_t getSize() const;

//	bool setCurIndex();
	std::size_t getCurIndex() const;
	bool isEmpty() const;
	void print() const;

	Move getMove(std::size_t index) const;
	bool setRemovedFigure(std::size_t index, Figure* fig = nullptr);

	int writeInFile(const wchar_t* filepath);
	int readFromFile(const wchar_t* filepath);
	
};
