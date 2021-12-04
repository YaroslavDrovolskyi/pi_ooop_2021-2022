#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


std::ostream& operator<<(std::ostream& stream, const Point& point) {
	stream << "(" << point.x << "; " << point.y << ")";

	return stream;
}

bool operator==(const Point& a, const Point& b) {
	if (a.x == b.x && a.y == b.y) {
		return true;
	}
	return false;
}

Cell::Cell() {
	this->figure = nullptr;
	this->is_marked = false;
}



Army::Army(Color color) {
	this->color = color;
	this->figures.resize(16);
	
	int pawns_row_index = color == Color::white ? 1 : 6;
	int others_row_index = color == Color::white ? 0 : 7;

	for (std::size_t i = 0; i < 16; i++) {
		if (i < 8) { // pawns
			Point p(i, pawns_row_index);
			this->figures[i] = Figure(color, FigType::pawn, p);
		}
		else if (i < 10) { // horses
			int j = (i == 8 ? 1 : 6);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::horse, p);
		}
		else if (i < 12) { // bishop
			int j = (i == 10 ? 2 : 5);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::bishop, p);
		}
		else if (i < 14) { // rook
			int j = (i == 12 ? 0 : 7);
			Point p(j, others_row_index);
			this->figures[i] = Figure(color, FigType::rook, p);
		}
		else if (i == 14) { // queen
			Point p(3, others_row_index);
			this->figures[i] = Figure(color, FigType::queen, p);
		}
		else if (i == 15) { // king
			Point p(4, others_row_index);
			this->figures[i] = Figure(color, FigType::king, p);
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
	/*
	this->field.print();

	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for pawn in" << Point(0, 0) << ": " << std::endl;
	print(pawn_moves(Point(1, 1), 1));


	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for rook in" << Point(7, 0) << ": " << std::endl;
	print(rook_moves(Point(4, 6)));

	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for Horse in" << Point(3, 1) << ": " << std::endl;
	print(horse_moves(Point(7, 0)));
	
	std::cout << std::endl << std::endl;
	std::cout << "Possible ways for Queen in" << Point(7, 0) << ": " << std::endl;
	print(queen_moves(Point(7, 0)));

	std::cout << std::endl << std::endl;
	std::cout << "Possible ways from" << Point(6, 1) << ": " << std::endl;
	print(movesFromPoint(Point(6, 1), 0));

	

	
	Point from(0, 1);
	Point dest(0, 6);
	std::cout << std::endl << std::endl;
	std::cout << "Move from" << from << " to " << dest << std::endl;
	makeMove(from, dest);
	field.print();


	calculateBestMove(team_b, 1);
	std::cout << std::endl;
	field.print();
	*/


	/* game between AI and random-moving AI
	while (winner == 0) {
		userMove(team_w, this->w_moves_count);
		aiMove(team_b, this->b_moves_count);
	}
	std::cout << "winner = " << winner << std::endl;
	
	field.print();
	*/

	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true); // sync frequency
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

			/*
			if (event.type == sf::Event::Resized) {
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;

				int new_width = event.size.width;
				int new_height = event.size.height;

				w = std::min(new_width / 16, new_height / 9);
				std::cout << "w = " << w << std::endl << std::endl;
			}
			*/
		}

		update(window);
	}
}


void Field::print() {
	std::cout << std::endl << "  ";
	for (std::size_t i = 0; i < 23; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int i = 7; i >= 0; i--) {
		std::cout << i << "|";
		for (std::size_t j = 0; j < 8; j++) {
			std::string str;
			if (!this->cells[i][j].figure) {
				str = "  "; // 00
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
			

			std::cout << str << "|";
			
		}
		std::cout << std::endl;
		std::cout << "  ";
		for (std::size_t i = 0; i < 23; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	// for print indexes of field
//	std::cout << "  ";
//	for (std::size_t i = 0; i < 23; i++) {
//		std::cout << "-";
//	}
	std::cout << "  ";
	for (std::size_t i = 0; i < 8; i++) {
		std::cout << i << "  ";
	}
}



std::vector<Point> Game::movesFromPoint(Point p, int move_number, bool consider_king) {
	if (!field.cells[p.y][p.x].figure) { return std::vector<Point>(); }

	switch (field.cells[p.y][p.x].figure->type) {
	case FigType::pawn: {return pawn_moves(p, move_number); }
	case FigType::horse: {return horse_moves(p); }
	case FigType::bishop: {return bishop_moves(p); }
	case FigType::rook: {return rook_moves(p); }
	case FigType::queen: {return queen_moves(p); }
	case FigType::king: {
		if (!consider_king) { return std::vector<Point>(); }
		return king_moves(p, move_number); 
	}
	default: {return std::vector<Point>(); }
	}
}

std::vector<Point> Game::pawn_moves(Point p, int moves_number) {
	std::vector<Point> result;

	int is_white = 1;
	if (field.cells[p.y][p.x].figure) {
		if (field.cells[p.y][p.x].figure->color == Color::black) {
			is_white = -1;
		}
	}
	else {
		return result;
	}

	// diagonal (fight) moves
	Point p1(p.x + 1, p.y + is_white);
	if (isCorrectPoint(p1) && field.cells[p1.y][p1.x].figure
		&& field.cells[p.y][p.x].figure->color != field.cells[p1.y][p1.x].figure->color) {
		result.push_back(p1);
	}

	Point p2(p.x - 1, p.y + is_white);
	if (isCorrectPoint(p2) && field.cells[p2.y][p2.x].figure
		&& field.cells[p.y][p.x].figure->color != field.cells[p2.y][p2.x].figure->color) {
		result.push_back(p2);
	}

	// vertical (ususal) moves
	Point p3(p.x, p.y + is_white);
	if (isCorrectPoint(p3) && !field.cells[p3.y][p3.x].figure) { // pawns ususal moves and fight moves are different
		result.push_back(p3);
	}

	if (moves_number == 0) { // first move for pawn allow this
		Point p4(p.x, p.y + 2 * is_white);
		if (isCorrectPoint(p4) && !field.cells[p4.y][p4.x].figure) { // pawns ususal moves and fight moves are different
			result.push_back(p4);
		}
	}
	
	getCorrectWays(p, result);
	
	return result;
}


std::vector<Point> Game::rook_moves(Point p) {
	std::vector<Point> result;

	if (!field.cells[p.y][p.x].figure) { return result; }

	// go to right
	Point i1(p.x + 1, p.y);
	while (isCorrectPoint(i1) && !field.cells[i1.y][i1.x].figure) {
		result.push_back(i1);
		i1.x++;
	}
	result.push_back(i1);

	// go to left
	Point i2(p.x - 1, p.y);
	while (isCorrectPoint(i2) && !field.cells[i2.y][i2.x].figure) {
		result.push_back(i2);
		i2.x--;
	}
	result.push_back(i2);

	// go to top
	Point i3(p.x, p.y + 1);
	while (isCorrectPoint(i3) && !field.cells[i3.y][i3.x].figure) {
		result.push_back(i3);
		i3.y++;
	}
	result.push_back(i3);

	// go to bottom
	Point i4(p.x, p.y - 1);
	while (isCorrectPoint(i4) && !field.cells[i4.y][i4.x].figure) {
		result.push_back(i4);
		i4.y--;
	}
	result.push_back(i4);

	getCorrectWays(p, result);

	return result;

}


std::vector<Point> Game::horse_moves(Point p) {
	std::vector<Point> result;

	if (!field.cells[p.y][p.x].figure) { return result; }

	result.push_back(Point(p.x - 1, p.y + 2));
	result.push_back(Point(p.x - 2, p.y + 1));

	result.push_back(Point(p.x + 1, p.y + 2));
	result.push_back(Point(p.x + 2, p.y + 1));

	result.push_back(Point(p.x - 1, p.y - 2));
	result.push_back(Point(p.x - 2, p.y - 1));

	result.push_back(Point(p.x + 2, p.y - 1));
	result.push_back(Point(p.x + 1, p.y - 2));

	getCorrectWays(p, result);

	return result;
}


std::vector<Point> Game::bishop_moves(Point p) {
	std::vector<Point> result;

	if (!field.cells[p.y][p.x].figure) { return result; }

	// go to right top
	Point i1(p.x + 1, p.y + 1);
	while (isCorrectPoint(i1) && !field.cells[i1.y][i1.x].figure) {
		result.push_back(i1);
		i1.x++;
		i1.y++;
	}
	result.push_back(i1);

	// go to left top
	Point i2(p.x - 1, p.y + 1);
	while (isCorrectPoint(i2) && !field.cells[i2.y][i2.x].figure) {
		result.push_back(i2);
		i2.x--;
		i2.y++;
	}
	result.push_back(i2);
	
	// go to left bottom
	Point i3(p.x - 1, p.y - 1);
	while (isCorrectPoint(i3) && !field.cells[i3.y][i3.x].figure) {
		result.push_back(i3);
		i3.x--;
		i3.y--;
	}
	result.push_back(i3);


	// go to right bottom
	Point i4(p.x + 1, p.y - 1);
	while (isCorrectPoint(i4) && !field.cells[i4.y][i4.x].figure) {
		result.push_back(i4);
		i4.x++;
		i4.y--;
	}
	result.push_back(i4);

	getCorrectWays(p, result);

	return result;

}

std::vector<Point> Game::queen_moves(Point p) {
	return concatinate(rook_moves(p), bishop_moves(p)); // queen ways is (bishop + rook) ways
}


std::vector<Point> Game::king_moves(Point p, int moves_number) {
	std::vector<Point> result;
	if (!field.cells[p.y][p.x].figure) { return result; }

	result.push_back(Point(p.x, p.y + 1));
	result.push_back(Point(p.x + 1, p.y + 1));
	result.push_back(Point(p.x + 1, p.y));
	result.push_back(Point(p.x + 1, p.y - 1));
	result.push_back(Point(p.x, p.y - 1));
	result.push_back(Point(p.x - 1, p.y - 1));
	result.push_back(Point(p.x - 1, p.y));
	result.push_back(Point(p.x - 1, p.y + 1));

	Army& team = field.cells[p.y][p.x].figure->color == Color::white ? team_b : team_w;
	std::vector<Move> possible_enemy_moves = allPossibleMoves(team, moves_number, false);
	bool removed = false;
	
	for (std::size_t i = 0; i < possible_enemy_moves.size(); i++) {
		for (std::size_t j = 0; j < result.size();) {
			if (result[j] == possible_enemy_moves[i].dest) {
				result.erase(result.begin() + j);
			}
			else {
				j++;
			}
		}
	}

	

	getCorrectWays(p, result);

	return result;
}

bool Game::isCorrectPoint(const Point& p) {
	if (p.x > 7 || p.y > 7) {
		return false;
	}
	if (p.x < 0 || p.y < 0) {
		return false;
	}

	return true;
}

void Game::getCorrectWays(Point from, std::vector<Point>& destinations) {
	for (std::size_t i = 0; i < destinations.size(); ) {
		Point dest = destinations[i];
		if (!isCorrectPoint(destinations[i])) {
			destinations.erase(destinations.begin() + i);
		}
		else if (field.cells[dest.y][dest.x].figure && field.cells[dest.y][dest.x].figure->color == field.cells[from.y][from.x].figure->color) { // if figures with same colors fight
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

template <typename T>
std::vector<T> concatinate(const std::vector<T>& vec1, const std::vector<T>& vec2) {
	std::vector<T> result;

	for (const T& i : vec1) {
		result.push_back(i);
	}

	for (const T& i : vec2) {
		result.push_back(i);
	}

	return result;
}

// return removed figure
Figure* Game::makeMove(const Point& from_p, const Point& dest_p) { // assuming coordinates are correct
	assert(isCorrectPoint(from_p));
	assert(isCorrectPoint(dest_p));

	Figure* figure = field.cells[from_p.y][from_p.x].figure;
	Figure* dest_figure = field.cells[dest_p.y][dest_p.x].figure;

	figure->position = dest_p;

	if (dest_figure) {
		dest_figure->is_alive = false;
		dest_figure->position = Point(-1, -1);
	}

//	field.makeMove(from_p, dest_p);

	field.cells[dest_p.y][dest_p.x].figure = field.cells[from_p.y][from_p.x].figure;
	field.cells[from_p.y][from_p.x].figure = nullptr;

	return dest_figure; // return removed figure
}


/*
void Field::makeMove(const Point& from, const Point& dest) {
	assert(isCorrectPoint(from));
	assert(isCorrectPoint(dest));

	cells[dest.y][dest.x].figure = cells[from.y][from.x].figure;
	cells[from.y][from.x].figure = nullptr;
}
*/

int Field::evaluate() {
	int result = 0;
	for (std::size_t i = 0; i < 8; i++) {
		for (std::size_t j = 0; j < 8; j++) {
			if (cells[i][j].figure) {
				result += cells[i][j].figure->value;
			}
		}
	}

	return result;
}


std::vector<Move> Game::allPossibleMoves(const Army& team, int move_number, bool consider_king) {
	std::vector<Move> result;
	for (const Figure& figure : team.figures) {
		if (figure.is_alive) {
			Point pos(figure.position);
			auto possible_moves = movesFromPoint(pos, move_number, consider_king);
			if (possible_moves.size() > 0) {
				for (const Point& j : possible_moves) {
					result.push_back(Move(pos, j));
				}
			}
		}
	}

	return result;
}


Move Game::calculateBestMove(const Army& team, int move_number) {
	std::vector<Move> all_possible_moves = allPossibleMoves(team, move_number);
	
	if (all_possible_moves.size() == 0) {
		return Move(Point(-1, -1), Point(-1, -1)); //// need to Reimplement
	}

	int i_best = minimax(2, team, move_number);

//	std::cout << "Best move: from " << all_possible_moves[i_best].from << " to " << all_possible_moves[i_best].dest << std::endl;

	assert(i_best >= 0);
	return all_possible_moves[i_best];
}


int Game::minimax(int depth, const Army& team, int move_number) {
	if (depth == 0) {
		return field.evaluate();
	}

	std::vector<Move> possible_moves = allPossibleMoves(team, move_number);

	int best_move_value = 0;
	int best_move_index = -1;

	if (team.color == Color::white) {
		best_move_value = -10000;
		for (std::size_t i = 0; i < possible_moves.size(); i++) {
			Move cur_move = possible_moves[i];
			Figure* removed_figure = makeMove(cur_move.from, cur_move.dest);
			int next_field_value = minimax(depth - 1, team_b, move_number + 1);
			undoMove(cur_move.from, cur_move.dest, removed_figure);

			if (next_field_value > best_move_value) { // find max
				best_move_value = next_field_value;
				best_move_index = i;
			}

		}
	}
	else {
		best_move_value = 10000;
		for (std::size_t i = 0; i < possible_moves.size(); i++) {
			Move cur_move = possible_moves[i];
			Figure* removed_figure = makeMove(cur_move.from, cur_move.dest);
			int next_field_value = minimax(depth - 1, team_w, move_number + 1);
			undoMove(cur_move.from, cur_move.dest, removed_figure);

			if (next_field_value < best_move_value) { // find min
				best_move_value = next_field_value;
				best_move_index = i;
			}

		}
	}


	if (depth == 2) {
		return best_move_index;
	}
	else {
		return best_move_value;
	}
	
}


void Game::undoMove(const Point& from, const Point& dest, Figure* removed_figure) {
	makeMove(dest, from);
	if (removed_figure) {
		removed_figure->position = dest;
		removed_figure->is_alive = true;
		field.cells[dest.y][dest.x].figure = removed_figure;
	}
}

void Game::aiMove(const Army& team, int& moves_number) {
	Move best_move = calculateBestMove(team, moves_number);
	if (!best_move.is_valid()) {
		markAsWinner(getOppositeTeam(team));
		return;
	}

	
	std::string str = team.color == Color::white ? "white: " : "black: ";
	std::cout << str << best_move.from << " -> " << best_move.dest << std::endl;
	
	makeMove(best_move.from, best_move.dest);

	moves_number++;

	if (!getOppositeTeam(team).figures[15].is_alive) { // if opposite king isn't alive
		markAsWinner(team);
	}
}

void Game::userMove(const Army& team, int& moves_number) {
	auto possible_moves = allPossibleMoves(team, moves_number);
	if (possible_moves.size() == 0) {
		markAsWinner(getOppositeTeam(team));
		return;
	}
	Move best_move = possible_moves[rand() % possible_moves.size()];

	
	std::string str = team.color == Color::white ? "white: " : "black: ";
	std::cout << str << best_move.from << " -> " << best_move.dest << std::endl;
	
	makeMove(best_move.from, best_move.dest);

	moves_number++;

	if (!getOppositeTeam(team).figures[15].is_alive) { // if opposite king isn't alive
		markAsWinner(team);
	}
}



Army& Game::getOppositeTeam(const Army& team) {
	if (team.color == Color::black) {
		return team_w;
	}
	return team_b;
}


void Game::markAsWinner(const Army& team) {
	if (team.color == Color::black) {
		winner = -1;
	}
	else {
		winner = 1;
	}
}

void Game::update(sf::RenderWindow& window) {
	displayField(window);
	window.clear(sf::Color(250, 220, 100, 0)); // set background
	displayField(window);
	window.display();
}

void Game::displayField(sf::RenderWindow& window) {
	sf::Texture w_cell_t, b_cell_t;
	w_cell_t.loadFromFile("img/white_cell.png");
	b_cell_t.loadFromFile("img/black_cell.png");
	sf::Sprite white_cell(w_cell_t);
	sf::Sprite black_cell(b_cell_t);

	white_cell.setScale((double) 2 * w / w0, (double)2 * w / w0); ///////////////////////////
	black_cell.setScale((double) 2 * w / w0, (double)2 * w / w0); ///////////////////////////// isn't need 2

	for (std::size_t i = 0; i < field.cells.size(); i++) {
		for (std::size_t j = 0; j < field.cells[i].size(); j++) {
			if ((i + j) % 2 == 0) {
				white_cell.setPosition(i * w, j * w);
				white_cell.move(w, w);
				window.draw(white_cell);
			}
			else {
				black_cell.setPosition(i * w, j * w);
				black_cell.move(w, w);
				window.draw(black_cell);
			}
		}
	}
}