#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


std::ostream& operator<<(std::ostream& stream, const Point& point) {
	stream << "(" << point.x << "; " << point.y << ")";

	return stream;
}

Cell::Cell() {
	this->figure = nullptr;
	this->is_marked = false;
}



Army::Army(Color color) {
	this->color = color;
	this->figures.resize(16);
	for (std::size_t i = 0; i < 16; i++) {
		if (i < 8) { // pawns
			this->figures[i] = Figure(color, FigType::pawn);
		}
		else if (i < 10) { // horses
			this->figures[i] = Figure(color, FigType::horse);
		}
		else if (i < 12) { // bishop
			this->figures[i] = Figure(color, FigType::bishop);
		}
		else if (i < 14) { // rook
			this->figures[i] = Figure(color, FigType::rook);
		}
		else if (i == 14) { // queen
			this->figures[i] = Figure(color, FigType::queen);
		}
		else if (i == 15) { // king
			this->figures[i] = Figure(color, FigType::king);
		}
	}
}


Field::Field(Army& white, Army& black, int size) {
	this->cells.resize(size);
	for (std::size_t i = 0; i < size; i++) {
		this->cells[i].resize(size);
		for (std::size_t j = 0; j < size; j++) {
			if (i == 0) { // black
				switch (j) {
				case 0: this->cells[i][j].figure = &white.figures[12]; break;
				case 1: this->cells[i][j].figure = &white.figures[8]; break;
				case 2: this->cells[i][j].figure = &white.figures[10]; break;
				case 3: this->cells[i][j].figure = &white.figures[14]; break;
				case 4: this->cells[i][j].figure = &white.figures[15]; break;
				case 5: this->cells[i][j].figure = &white.figures[11]; break;
				case 6: this->cells[i][j].figure = &white.figures[9]; break;
				case 7: this->cells[i][j].figure = &white.figures[13]; break;
				default: break;
				}
			}
			else if (i == 1) {
				this->cells[i][j].figure = &white.figures[j];
			}
			else if (i == 6) { // white
				this->cells[i][j].figure = &black.figures[j];
			}
			else if (i == 7) {
				switch (j) {
				case 0: this->cells[i][j].figure = &black.figures[12]; break;
				case 1: this->cells[i][j].figure = &black.figures[8]; break;
				case 2: this->cells[i][j].figure = &black.figures[10]; break;
				case 3: this->cells[i][j].figure = &black.figures[14]; break;
				case 4: this->cells[i][j].figure = &black.figures[15]; break;
				case 5: this->cells[i][j].figure = &black.figures[11]; break;
				case 6: this->cells[i][j].figure = &black.figures[9]; break;
				case 7: this->cells[i][j].figure = &black.figures[13]; break;
				default: break;
				}
			}
		}
	}
}


int Figure::get_figure_value() {
	int result;
	if (this->type == FigType::pawn) {
		result = 10;
	}
	else if (this->type == FigType::horse || this->type == FigType::bishop) {
		result = 30;
	}
	else if (this->type == FigType::rook) {
		result = 50;
	}
	else if (this->type == FigType::queen) {
		result = 90;
	}
	else if (this->type == FigType::king) {
		result = 900;
	}

	if (this->color == Color::black) {
		result *= -1;
	}

	return result;
}

void Game::exec() {

	this->field.print();

	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for pawn in" << Point(0, 0) << ": " << std::endl;
	print(this->field.pawn_ways(Point(1, 1), 1));


	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for rook in" << Point(7, 0) << ": " << std::endl;
	print(this->field.rook_ways(Point(4, 6)));


	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);



	sf::Texture texture;
	texture.loadFromFile("img/field.jpg");

	sf::Sprite sprite(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	sprite.setScale(2, 2);

	while (window.isOpen()) {
		sf::Event event;
		if (window.waitEvent(event)) { // while and pollEvent
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}

		window.clear();
		window.draw(shape);
		window.draw(sprite);
		window.display();
	}
}


void Field::print() {
	for (int i = 7; i >= 0; i--) {
		for (std::size_t j = 0; j < 8; j++) {
			std::string str;
			if (!this->cells[i][j].figure) {
				str = "00";
			}
			else {
				if (this->cells[i][j].figure->type == FigType::pawn) {
					str = "p";
				}
				else if (this->cells[i][j].figure->type == FigType::horse) {
					str = "h";
				}
				else if (this->cells[i][j].figure->type == FigType::bishop) {
					str = "b";
				}
				else if (this->cells[i][j].figure->type == FigType::rook) {
					str = "r";
				}
				else if (this->cells[i][j].figure->type == FigType::queen) {
					str = "q";
				}
				else if (this->cells[i][j].figure->type == FigType::king) {
					str = "k";
				}

				if (this->cells[i][j].figure->color == Color::white) {
					str = "w" + str;
				}
				else {
					str = "b" + str;
				}
			}
			

			std::cout << str << " ";
		}
		std::cout << std::endl;
	}
}



std::vector<Point> Field::get_possible_ways(Point p, int move_number) {
	std::vector<Point> result;
	if (!this->cells[p.x][p.y].figure) { return result; }

	if (this->cells[p.x][p.y].figure->type == FigType::pawn) {

	}
}

std::vector<Point> Field::pawn_ways(Point p, int move_number) {
	std::vector<Point> result;

	int is_white = 1;
	if (this->cells[p.y][p.x].figure) {
		if (this->cells[p.y][p.x].figure->color == Color::black) {
			is_white = -1;
		}
	}
	else {
		return result;
	}

	result.push_back(Point(p.x - is_white, p.y + is_white));
	result.push_back(Point(p.x, p.y + is_white));
	result.push_back(Point(p.x + is_white, p.y + is_white));
	if (move_number == 0) { // first move for pawn allow this
		result.push_back(Point(p.x, p.y + 2 * is_white));
	}
	
	getCorrectWays(p, result);
	
	return result;
}


std::vector<Point> Field::rook_ways(Point p) {
	std::vector<Point> result;

	if (!this->cells[p.y][p.x].figure) { return result; }

	// go to right 
	int x = p.x + 1;
	while (isCorrectPoint(Point(x, p.y)) && !this->cells[p.y][x].figure && x > 0 && x < 7) {
		result.push_back(Point(x, p.y));
		x++;
	}
	result.push_back(Point(x, p.y));

	// go to left
	x = p.x - 1;
	while (isCorrectPoint(Point(x, p.y)) && !this->cells[p.y][x].figure && x > 0 && x < 7) {
		result.push_back(Point(x, p.y));
		x--;
	}
	result.push_back(Point(x, p.y));

	// go to top 
	int y = p.y + 1;
	while (isCorrectPoint(Point(p.x, y)) && !this->cells[y][p.x].figure && y > 0 && y < 7) {
		result.push_back(Point(p.x, y));
		y++;
	}
	result.push_back(Point(p.x, y));

	// go to bottom 
	y = p.y - 1;
	while (isCorrectPoint(Point(p.x, y)) && !this->cells[y][p.x].figure && y > 0 && y < 7) {
		result.push_back(Point(p.x, y));
		y--;
	}
	result.push_back(Point(p.x, y));

	getCorrectWays(p, result);

	return result;

}

bool Field::isCorrectPoint(const Point& p) {
	if (p.x > 7 || p.y > 7) {
		return false;
	}
	if (p.x < 0 || p.y < 0) {
		return false;
	}

	return true;
}

void Field::getCorrectWays(Point from, std::vector<Point>& destinations) {
	for (std::size_t i = 0; i < destinations.size(); ) {
		Point dest = destinations[i];
		if (!isCorrectPoint(destinations[i])) {
			destinations.erase(destinations.begin() + i);
		}
		else if (this->cells[dest.y][dest.x].figure && this->cells[dest.y][dest.x].figure->color == this->cells[from.y][from.x].figure->color) { // if figures with same colors fight
			destinations.erase(destinations.begin() + i);
		}
		else {
			i++;
		}
	}
}

template <typename T>
void print(const std::vector<T>& vector) {
	if (vector.size() == 0) { return; }
	for (const T& t : vector) {
		std::cout << t << " ";
	}
	std::cout << std::endl;
}