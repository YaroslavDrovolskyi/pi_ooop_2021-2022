#include "Game.h"
#include <vector>
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
			this->figures[i] = Figure(count_value(10));
		}
		else if (i < 10) { // horses
			this->figures[i] = Figure(count_value(30));
		}
		else if (i < 12) { // bishop
			this->figures[i] = Figure(count_value(30));
		}
		else if (i < 14) { // rook
			this->figures[i] = Figure(count_value(50));
		}
		else if (i == 14) { // queen
			this->figures[i] = Figure(count_value(90));
		}
		else if (i == 15) { // king
			this->figures[i] = Figure(count_value(900));
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
			else if (i == 6) {
				this->cells[i][j].figure = &black.figures[j];
			}
			else if (i == 7) {
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
		}
	}
}




void Game::exec() {
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