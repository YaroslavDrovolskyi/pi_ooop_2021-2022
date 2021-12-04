#pragma once
#include <vector>
#include <cassert>

#include "Figures.h"

struct Point {
	int x;
	int y;

	Point(int x = 0, int y = 0) : x(x), y(y){}
};

enum class Color {
	black, white
};

enum class FigType {
	pawn, // 10
	horse, // 30
	bishop, // 30, goes through diagonales
	rook, // 50, goes through lines
	queen, // 90
	king // 900
};




class Figure {
public:
	Color color;
	FigType type;
	int value;
	bool is_alive;
	Point position;

public:
	Figure() {}
	Figure(Color color, FigType type, const Point& pos) : color(color), type(type), is_alive(true), position(pos), value(get_figure_value()) {}

	void set_pos(const Point& position) {
		//		this->position = position;
	}

	int get_figure_value();
};

struct Move {
	Point from;
	Point dest;

	Move(const Point& from, const Point& dest) : from(from), dest(dest) {

	}
};


struct Cell {
public:
	Figure* figure;
	bool is_marked;

	Cell();
};


class Army {
public:
	Color color;
	std::vector<Figure> figures;

	Army(Color color);


private:
	int count_value(int val) {
		assert(val > 0);
		return this->color == Color::black ? (-1) * val : val;
	}
};

class Field {
public:
	std::vector <std::vector <Cell>> cells;

	Field() {}
	Field(Army& white, Army& black, int size = 8);
	void print();
	/*
	std::vector<Point> get_possible_moves(Point p, int move_number, bool consider_king = true);
	std::vector<Point> pawn_moves(Point p, int move_number);
	std::vector<Point> rook_moves(Point p);
	std::vector<Point> horse_moves(Point p);
	std::vector<Point> bishop_moves(Point p);
	std::vector<Point> queen_moves(Point p);
	std::vector<Point> king_moves(Point p);
	void getCorrectWays(Point from, std::vector<Point>& dest); // put away incorrect destination points

	bool isCorrectPoint(const Point& p);
	*/
	void makeMove(const Point& from, const Point& dest);
	int evaluate();
};

std::ofstream& operator<<(std::ofstream& stream, const Point& point);
bool operator==(const Point& a, const Point& b);

class Game {
private:
	Field field;
	Army team_w;
	Army team_b;

	int w_moves_count;
	int b_moves_count;

public:
	Game() : team_w(Color::white), team_b(Color::black) {
		this->field = Field(team_w, team_b);
	}
	void exec();
	Figure* makeMove(const Point& from, const Point& dest);
	void undoMove(const Point& from, const Point& dest, Figure* removed_figure = nullptr); // undo move only after making it (don't work with multuply moves)
	std::vector<Move> allPossibleMoves(const Army& team, int move_number, bool consider_king = true);
	Move calculateBestMove(const Army& team, int move_number);

	int minimax(int depth, const Army& team, int move_number);



private:
	std::vector<Point> get_possible_moves(Point p, int move_number, bool consider_king = true);
	std::vector<Point> pawn_moves(Point p, int move_number);
	std::vector<Point> rook_moves(Point p);
	std::vector<Point> horse_moves(Point p);
	std::vector<Point> bishop_moves(Point p);
	std::vector<Point> queen_moves(Point p);
	std::vector<Point> king_moves(Point p, int moves_number);
	void getCorrectWays(Point from, std::vector<Point>& dest); // put away incorrect destination points

	bool isCorrectPoint(const Point& p);
};


template <typename T>
void print(const std::vector<T>& vector);

template <typename T>
std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2);