#include "MovesHistory.h"
#include <cassert>


void MovesHistory::insert(const Move& move, Figure* removed_figure) {
	if (size > 1) { // leave only items, that situated before current index and item with index == current_index
		size = current_index + 1;
		this->moves.resize(size); // resize is when we decide to continue record moves from current move
		this->removed_figures.resize(size);
	}
	
	// push back new item
	this->moves.push_back(move);
	this->removed_figures.push_back(removed_figure);

	if (size > 0) {
		this->current_index++;
	}
	// else current_index is already == 0

	this->size = this->current_index + 1;
}

std::pair<Move, Figure*> MovesHistory::undoMove() {
	assert(size > 0 && current_index >= 0);
	std::pair<Move, Figure*> result = std::make_pair(this->moves[current_index], this->removed_figures[current_index]);

	if (current_index > 0) {
		current_index--;
		size = current_index + 1;
	}
	else { // current_index is already = 0
		size = 0;
	}

	this->moves.resize(size);
	this->removed_figures.resize(size);

	return result;
}

std::size_t MovesHistory::getSize() const {
	return this->size;
}

std::size_t MovesHistory::getCurIndex() const {
	return this->current_index;
}

bool MovesHistory::isEmpty() const {
	return (size == 0);
}