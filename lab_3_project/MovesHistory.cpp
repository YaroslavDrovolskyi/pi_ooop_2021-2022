#include "MovesHistory.h"
#include <cassert>
#include <iostream>
#include <fstream>


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

void MovesHistory::clear() {
	this->current_index = 0;
	this->size = 0;

	this->moves.resize(size);
	this->removed_figures.resize(size);
}

void MovesHistory::print() const {
	std::cout << "Moves History:" << std::endl;
	if (size == 0) {
		std::cout << "Empty";
	}

	for (std::size_t i = 0; i < size; i++) {
		std::cout << moves[i] << " " << removed_figures[i];
		if (i == current_index) {
			std::cout << " [current index]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

int MovesHistory::writeInFile(const wchar_t* filepath) {
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open()) {
		return -1;
	}

	for (const Move& move : moves) {
		file.write((char*)&move, sizeof(Move));
	}

	file.close();

	return 0;
}

int MovesHistory::readFromFile(const wchar_t* filepath) {
	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open()) {
		return -1;
	}

	clear();

	Move move; // create buffer
	while (file.read((char*)&move, sizeof(Move))) {
		insert(move);
	}

	file.close(); 

	return 0;
}

Move MovesHistory::getMove(std::size_t index) const {
	assert(index < size);

	return moves[index];
}

bool MovesHistory::setRemovedFigure(std::size_t index, Figure* fig) {
	if (index < size) {
		removed_figures[index] = fig;
		return true;
	}

	return false;
}