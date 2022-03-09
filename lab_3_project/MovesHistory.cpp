/*!
	\file
	\brief File with implementation of class MovesHistory
*/

#include "MovesHistory.h"
#include <cassert>
#include <iostream>
#include <fstream>

/*!
	Insert move and corresponding removed figure after current index (moves after current index will be removed)

	\param[in] move move to insert
	\param[in] removed_figure removed figure to insert
*/
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

/*!
	Give you and remove current move, removed figure; (Moves after current index also will be removed)

	\returns move and corresponding removed figure
*/
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

/*!
	Getter for size

	\returns size of it (number of stored items)
*/
std::size_t MovesHistory::getSize() const {
	return this->size;
}

/*!
	Getter for current index

	\returns current index
*/
std::size_t MovesHistory::getCurIndex() const {
	return this->current_index;
}


/*!
	Shows if it is empty or not

	\returns true if it is empty, and false otherwise
*/
bool MovesHistory::isEmpty() const {
	return (size == 0);
}

/*!
	Remove all stored items\n
	Also reset size and current index
*/
void MovesHistory::clear() {
	this->current_index = 0;
	this->size = 0;

	this->moves.resize(size);
	this->removed_figures.resize(size);
}


/*!
	Prints a list of stored items in format:\n
	[move.from] -> [move.destination] [address of removed figure]\n
	Also it marks item that lies below current index
*/
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


/*!
	Write all moves in the file (file will be overwritten) \n
	It don't write removed figures, because that addresses are valid only during one game session (they are useless during loading the saved game) 

	\param[in] filepath full or relative correct path to file (non-existent file is possible, it we'll be created)
	\returns 0 if all are OK, and -1 if something wrong with opening a file
*/
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

/*!
	Read all items from the file

	\param[in] filepath : full or relative path to file (file must exist)
	\returns 0 if all are OK, and -1 if something wrong with opening a file
*/
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

/*!
	Getter for move

	\param[in] index : correct index of move that we need

	\returns move, that we need
*/
Move MovesHistory::getMove(std::size_t index) const {
	assert(index < size);

	return moves[index];
}


/*!
	Setter for removed figure

	\param[in] index correct index where we need to place fig
	\param[in] fig pointer of removed figure

	\returns true if all are OK, and false if index is incorrect

*/
bool MovesHistory::setRemovedFigure(std::size_t index, Figure* fig) {
	if (index < size) {
		removed_figures[index] = fig;
		return true;
	}

	return false;
}