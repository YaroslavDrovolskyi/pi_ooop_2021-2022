#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

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
		while (window.pollEvent(event)) {
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