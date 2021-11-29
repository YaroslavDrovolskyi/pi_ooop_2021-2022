#pragma once
#include <vector>
#include <cassert>

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

struct Point {
	int x;
	int y;

	Point(int x, int y) : x(x), y(y){}
};



class Figure {
public:
	Color color;
	FigType type;
	int value;
	bool is_alive;
//	Point position;

public:
	Figure() {}
	Figure(Color color, FigType type) : color(color), type(type), is_alive(true), value(get_figure_value()) {}

	void set_pos(const Point& position) {
//		this->position = position;
	}

	int get_figure_value();
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
	std::vector<Point> get_possible_ways(Point p, int move_number);
	std::vector<Point> pawn_ways(Point p, int move_number);
	std::vector<Point> rook_ways(Point p);
	void getCorrectWays(Point from, std::vector<Point>& dest); // put away incorrect destination points

	bool isCorrectPoint(const Point& p);
};

std::ofstream& operator<<(std::ofstream& stream, const Point& point);

class Game {
private:
	Field field;
	Army team_w;
	Army team_b;

public:
	Game() : team_w(Color::white), team_b(Color::black) {
		this->field = Field(team_w, team_b);
	}
	void exec();

};


template <typename T>
void print(const std::vector<T>& vector);