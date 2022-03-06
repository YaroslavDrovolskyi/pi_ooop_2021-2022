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
	MovesHistory();
	void insert(const Move& move, Figure* removed_figure = nullptr);
	std::pair<Move, Figure*> undoMove();
};
