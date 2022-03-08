#pragma once
#include "Point.h"
#include "Figure.h"
#include "Army.h"
#include "Field.h"

#include <vector>

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
	std::size_t getCurIndex() const;
	bool isEmpty() const;
	void print() const;

	int writeInFile(const std::string& filename);
	int readFromFile(const std::string& filename);
	
};
