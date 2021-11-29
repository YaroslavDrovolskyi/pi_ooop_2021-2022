#pragma once
#include <vector>
#include <cassert>

enum class Color {
	black, white
};

struct Point {
	int x;
	int y;

	Point(int x, int y) : x(x), y(y){}
};



class Figure {
public:
	int value;
	bool is_alive;
//	Point position;

public:
	Figure(int value = 1) : is_alive(true), value(value) {}

	void set_pos(const Point& position) {
//		this->position = position;
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

	Field(Army& white, Army& black, int size = 8);
};



class Game {
private:
	Field field;
	Army team_w;
	Army team_b;

public:
	Game() : team_w(Color::white), team_b(Color::black), field(team_w, team_w) {}
	void exec();

};

