#pragma once

#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>

#include "Point.h"
#include "Figure.h"
#include "Army.h"
#include "Field.h"
#include "MovesHistory.h"



class ChessGame {
private:

	Army team_w;
	Army team_b;
	Field field;
	MovesHistory moves_list;

	int w_moves_count;
	int b_moves_count;

	enum class Player { user, ai };
	Player cur_player;
	int winner; // -1 - black, 1 - white, 0 - nobody

//	enum class Mode{game, end};

	Figure* selected_figure;

	int w; // native width of one square of netting
	int w0; // width of one texture in image files

	bool warning1; // please, choose white (your) figures
	bool warning2; // impossible move to this point

public:
	ChessGame();
	void exec();


private:

	void aiMove(const Army& team, int& moves_number);
	void userMove(const Army& team, int& moves_number);

	Figure* makeMove(const Point& from, const Point& dest);
	void undoMove(const Point& from, const Point& dest, Figure* removed_figure = nullptr); // undo move only after making it (don't work with multuply moves)


	Move calculateBestMove(const Army& team, int move_number);
	int minimax(int depth, int max_depth, const Army& team, int move_number, int alpha, int beta);
	std::vector<Move> allPossibleMoves(const Army& team, int move_number, bool consider_king = true);

	std::vector<Point> movesFromPoint(Point p, int move_number, bool consider_king = true);
	std::vector<Point> pawn_moves(Point p, int move_number, bool consider_king = true);
	std::vector<Point> rook_moves(Point p);
	std::vector<Point> horse_moves(Point p);
	std::vector<Point> bishop_moves(Point p);
	std::vector<Point> queen_moves(Point p);
	std::vector<Point> king_moves(Point p, int moves_number);

	void eraseIncorrectMoves(Point from, std::vector<Point>& dest); // put away incorrect destination points
	bool isCorrectPoint(const Point& p);
	Army& getOppositeTeam(const Army& team);
	void markAsWinner(const Army& team);

	void displayField(sf::RenderWindow& window);

	void handleFieldClick(const Point& pos);

	void update(sf::RenderWindow& window); // display window
	void restart();
};


template <typename T>
void print(const std::vector<T>& vector);

template <typename T>
std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2);

