#pragma once
#include "Army.h"



struct Cell {
public:
	Figure* figure;
	bool marked; // cell is marked (possible move and not attack)
	bool possible_fight;
	bool selected; // selected own figure

	Cell() : figure(nullptr), marked(false), possible_fight(false), selected(false) {};
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