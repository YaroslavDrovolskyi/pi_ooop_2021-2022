#pragma once
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>

struct Point {
	int x;
	int y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}
	std::string getString() const;
};

std::ostream& operator<<(std::ostream& stream, const Point& point);
bool operator==(const Point& a, const Point& b);

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
private:
	Color color;
	FigType type;
	int value;
	bool is_alive;
	Point position;

	friend class Field;
	friend class ChessGame;
public:
	Figure() {}
	Figure(Color color, FigType type, const Point& pos) : color(color), type(type), is_alive(true), position(pos), value(get_figure_value()) {}

	int get_figure_value();
};

struct Move {
	Point from;
	Point dest;

	Move(const Point& from, const Point& dest) : from(from), dest(dest) {}

	bool is_valid() {
		if (from.x == -1 && from.y == -1 && dest.x == -1 && dest.y == -1) {
			return false;
		}
		return true;
	}
};


struct Cell {
public:
	Figure* figure;
	bool marked; // cell is marked (possible move and not attack)
	bool possible_fight;
	bool selected; // selected own figure
	Cell();
};


class Army {
private:
	Color color;
	std::vector<Figure> figures;

	int count_value(int val) {
		assert(val > 0);
		return this->color == Color::black ? (-1) * val : val;
	}

	friend class Field;
	friend class ChessGame;
public:

	Army(Color color);

};

class Field {
public:
	std::vector <std::vector <Cell>> cells;

	Field() {}
	Field(Army& white, Army& black, int size = 8);
	void putMarks(const Point& from, const std::vector<Point>& points);
	void clearMarks();
	void print();
	int evaluate();
};



class ChessGame {
private:

	Army team_w;
	Army team_b;
	Field field;

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

