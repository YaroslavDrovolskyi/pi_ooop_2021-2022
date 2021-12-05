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
	this->marked = false;
	this->possible_fight = false;
	this->selected = false;
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
	/* some tests
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

	sf::RenderWindow window(sf::VideoMode(1600, 950), "Chess", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true); // sync frequency
	window.setPosition({ 150, 25 });
	sf::Image icon;
	icon.loadFromFile("img/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);

	/*
	for (std::size_t i = 0; i < 8; i++) {
		for(std::size_t j = 0; j < 8; j++) {
			std::cout << Point(i,j) << ": " << Point(i, j).getString() << std::endl;
		}
	}
	*/
//	sf::Texture texture;
//	texture.loadFromFile("img/field.jpg");

//	sf::Sprite sprite(texture);
//	sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
//	sprite.setScale(2, 2);

	while (window.isOpen()) {


		if (winner == 0 && cur_player == Player::ai) {
			aiMove(team_b, b_moves_count);
		}
		else {
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

				else if (event.type == sf::Event::MouseButtonPressed) {
					int x = event.mouseButton.x / w;
					int y = event.mouseButton.y / w;
					std::cout << "Mouse pressed: (" << event.mouseButton.x << "; " << event.mouseButton.y << ") " << " =  (" << x << "; " << y << ") " << std::endl;

					if (this->winner == 0) {
						if (cur_player == Player::user) {
							if (x >= 2 && x <= 9 && y >= 1 && y <= 8) {
								handleFieldClick(Point(x - 2, 8 - y));
							}
							else if (x >= 11 && x < 14 && y >= 6 && y < 7) {
								restart();
							}
							else if (x >= 11 && x < 14 && y >= 8 && y < 9) {
								window.close();
							}
						}
					}
					else { // if game is over (winner is -1 or 1)
						if (x >= 11 && x < 14 && y >= 6 && y < 7) {
							restart();
						}
						else if (x >= 11 && x < 14 && y >= 8 && y < 9) {
							window.close();
						}
					}
				}



			}
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
	case FigType::pawn: {return pawn_moves(p, move_number, consider_king); }
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

std::vector<Point> Game::pawn_moves(Point p, int moves_number, bool consider_king) {
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

	if (consider_king) {
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
		
	}
	else { // if we don't consider the king (we make calulations to calculate possible moves of enemy king)
			// diagonal (fight) moves
		Point p1(p.x + 1, p.y + is_white);
		if (isCorrectPoint(p1) && !field.cells[p1.y][p1.x].figure) {
			result.push_back(p1);
		}

		Point p2(p.x - 1, p.y + is_white);
		if (isCorrectPoint(p2) && !field.cells[p2.y][p2.x].figure) {
			result.push_back(p2);
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

	Army& enemy_team = field.cells[p.y][p.x].figure->color == Color::white ? team_b : team_w;
	int enemy_moves_number = enemy_team.color == Color::black ? b_moves_count : w_moves_count;

	std::vector<Move> possible_enemy_moves = allPossibleMoves(enemy_team, enemy_moves_number, false);
//	bool removed = false;
	
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
	if (!best_move.is_valid() || !team.figures[15].is_alive) { // when AI hasn't possible moves or hasn't king
		markAsWinner(getOppositeTeam(team));
		return;
	}

	
	std::string str = team.color == Color::white ? "white: " : "black: ";
	std::cout << str << best_move.from.getString() << " -> " << best_move.dest.getString() << std::endl;
	
	makeMove(best_move.from, best_move.dest);

	moves_number++;

	if (!getOppositeTeam(team).figures[15].is_alive || allPossibleMoves(getOppositeTeam(team), w_moves_count).size() == 0) { // if opposite king isn't alive or opposite hasn't moves
		markAsWinner(team);
		std::cout << "WINNER: " << winner << std::endl;
	}

	cur_player = Player::user;
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
//	displayField(window);
	sf::Font font;
	font.loadFromFile("fonts/calibri.otf");

	if (winner == 0) {
		window.clear(sf::Color(250, 220, 100, 0)); // set background
		displayField(window);


		sf::RectangleShape button_restart(sf::Vector2f(3 * w, w));
		button_restart.setFillColor(sf::Color(10, 103, 163));
		button_restart.setPosition(11 * w, 6 * w);

		sf::Text text_restart("Restart", font, 40);
		text_restart.setPosition(12 * w - w / 10, 6 * w + w / 4);


		sf::RectangleShape button_close(sf::Vector2f(3 * w, w));
		button_close.setFillColor(sf::Color(255, 7, 1));
		button_close.setPosition(11 * w, 8 * w);

		sf::Text text_close("Close", font, 40);
		text_close.setPosition(12 * w + w / 10, 7 * w + 3 * w / 4 + w / 2);


		if (warning1) {
			sf::Text text_warn1("Please, choose white figure", font, 40);
			text_warn1.setFillColor(sf::Color::Red);
			text_warn1.setPosition(10 * w + w / 2, 3 * w / 2);
			window.draw(text_warn1);
		}
		if (warning2) {
			sf::Text text_warn2("Impossible move to this point", font, 40);
			text_warn2.setFillColor(sf::Color::Red);
			text_warn2.setPosition(10*w + w/2, 3*w / 2);
			window.draw(text_warn2);
		}


		window.draw(button_restart);
		window.draw(text_restart);
		window.draw(button_close);
		window.draw(text_close);

	}

	else if (winner != 0) {
		window.clear(sf::Color(250, 220, 100, 0));
		displayField(window);
		sf::Text win_text("", font, 100);
		win_text.setFillColor(sf::Color(248, 1, 20));
		win_text.setPosition(10 * w + w / 2, 3*w);

		if (winner == 1) { // user (white) won
			win_text.setString("YOU WON!");
		}
		else { // ai (black) won
			win_text.setString("AI WINS!");
		}

		
		sf::RectangleShape button_restart(sf::Vector2f(3 * w, w));
		button_restart.setFillColor(sf::Color(10, 103, 163));
		button_restart.setPosition(11 * w, 6 * w);

		sf::Text text_restart("Restart", font, 40);
		text_restart.setPosition(12 * w - w / 10, 6 * w + w / 4);


		sf::RectangleShape button_close(sf::Vector2f(3 * w, w));
		button_close.setFillColor(sf::Color(255, 7, 1));
		button_close.setPosition(11 * w, 8 * w);

		sf::Text text_close("Close", font, 40);
		text_close.setPosition(12 * w + w / 10, 7 * w + 3 * w / 4 + w / 2);
		

		window.draw(win_text);
		window.draw(button_restart);
		window.draw(text_restart);
		window.draw(button_close);
		window.draw(text_close);
		
	}

	window.display();
}

void Game::displayField(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromFile("img/textures.png");
	sf::Sprite cell(texture);

	
	sf::Sprite figure(texture);

	sf::Sprite number_label(texture);
	
	

	for (std::size_t i = 0; i < field.cells.size(); i++) {
		for (std::size_t j = 0; j < field.cells[i].size(); j++) {
			// draw cell
			if ((i + j) % 2 == 0) { // cell is white
				cell.setTextureRect(sf::IntRect(8 * w0, 0, w0, w0));
			}
			else {
				cell.setTextureRect(sf::IntRect(8 * w0, w0, w0, w0));
			}

			cell.setScale((double)w / w0, (double)w / w0);
			cell.setPosition(j * w, (7 - i) * w);
			cell.move(2 * w, w);
			window.draw(cell);

			// draw marks
			if (field.cells[i][j].marked) {
				cell.setTextureRect(sf::IntRect(9 * w0, 0, w0, w0));
			}
			else if (field.cells[i][j].possible_fight) {
				cell.setTextureRect(sf::IntRect(9 * w0, w0, w0, w0));
			}
			else if (field.cells[i][j].selected) {
				cell.setTextureRect(sf::IntRect(10 * w0, 0, w0, w0));
			}
			window.draw(cell);

			// draw figures
			Figure* f = field.cells[i][j].figure;
			if (f) {
				if (f->color == Color::white) {
					switch (f->type) {
					case FigType::pawn: {figure.setTextureRect(sf::IntRect(0, 0, w0, w0)); break; }
					case FigType::horse: {figure.setTextureRect(sf::IntRect(w0, 0, w0, w0)); break; }
					case FigType::bishop: {figure.setTextureRect(sf::IntRect(2 * w0, 0, w0, w0)); break; }
					case FigType::rook: {figure.setTextureRect(sf::IntRect(3 * w0, 0, w0, w0)); break; }
					case FigType::queen: {figure.setTextureRect(sf::IntRect(4 * w0, 0, w0, w0)); break; }
					case FigType::king: {figure.setTextureRect(sf::IntRect(5 * w0, 0, w0, w0)); break; }
					default: {break; }
					}
				}
				else {
					switch (f->type) {
					case FigType::pawn: {figure.setTextureRect(sf::IntRect(0, w0, w0, w0)); break; }
					case FigType::horse: {figure.setTextureRect(sf::IntRect(w0, w0, w0, w0)); break; }
					case FigType::bishop: {figure.setTextureRect(sf::IntRect(2 * w0, w0, w0, w0)); break; }
					case FigType::rook: {figure.setTextureRect(sf::IntRect(3 * w0, w0, w0, w0)); break; }
					case FigType::queen: {figure.setTextureRect(sf::IntRect(4 * w0, w0, w0, w0)); break; }
					case FigType::king: {figure.setTextureRect(sf::IntRect(5 * w0, w0, w0, w0)); break; }
					default: {break; }
					}
				}

				figure.setScale((double)w / w0, (double)w / w0);

				figure.setPosition(j * w, (7 - i) * w);
				figure.move(2*w, w);
				window.draw(figure);
			}
		}
	}

	// draw number labels
	
	
	for (std::size_t i = 0; i < 16; i++) {
		if (i < 4) {
			number_label.setTextureRect(sf::IntRect(6 * w0 + (double)i*w0 / 4, 0, w0 / 4, w0));
			number_label.setPosition((double)7*w/4, w*i + w);
		}
		else if (i < 8) {
			number_label.setTextureRect(sf::IntRect(6 * w0 + (double)(i - 4) * w0 / 4, w0, w0 / 4, w0));
			number_label.setPosition((double)7 * w / 4, w * i + w);

		}
		else if (i < 12) {
			number_label.setTextureRect(sf::IntRect(7 * w0, 0 + (i - 8)*w0/4, w0, w0 / 4));
			number_label.setPosition(2*w + (i-8)*w, 9 * w);
//			number_label.setPosition(0,0);
		}
		else {
			number_label.setTextureRect(sf::IntRect(7 * w0, w0 + (i - 12)*w0/4, w0, w0 / 4));
			number_label.setPosition(2 * w + (i-8) * w, 9 * w);
		}

		number_label.setScale((double)w / w0, (double)w / w0);
		// set position

		window.draw(number_label);
	}

}

std::string Point::getString() const {
	assert(x >= 0 && x < 8);
	assert(y >= 0 && y < 8);

	std::string result;
	result += 'A' + x;
	result += std::to_string(y + 1);
	

	return result;
}



void Game::handleFieldClick(const Point& pos) {
	assert(cur_player == Player::user);

	Figure* figure = field.cells[pos.y][pos.x].figure; // figure in cell, on which user clicked
	if (!selected_figure) {
		if (figure&& figure->color == Color::white) {
			selected_figure = figure;
			field.putMarks(pos, movesFromPoint(pos, w_moves_count));

			warning1 = false;
			warning2 = false;
		}
		else {
			warning1 = true; // WARNING: "Please, choose own (white) figure"
		}
		
	}
	else {
		if (figure && figure->color == Color::white) { // if we selected other own figure
			field.clearMarks();
			selected_figure = figure;
			field.putMarks(pos, movesFromPoint(pos, w_moves_count));

			warning2 = false;
		}
		else {
			if (field.cells[pos.y][pos.x].marked || field.cells[pos.y][pos.x].possible_fight) {  // need to move
				std::cout << "white: " << selected_figure->position.getString() << " -> " << pos.getString() << std::endl;
				Point from = selected_figure->position; // get a value for not to pass position in makeMove() by reference (cause of inctorrect behaviour: no move)
				Figure* removed_figure = makeMove(from, pos);
				selected_figure = nullptr;
				w_moves_count++;
				field.clearMarks();
				cur_player = Player::ai;

				warning2 = false;
			}
			else {
				warning2 = true; // WARNING: "Impossible move to thos point"
			}
		}
		
	}
}


void Field::putMarks(const Point& selected_point, const std::vector<Point>& points) {
	for (const Point& p : points) {
		
		if (this->cells[p.y][p.x].figure) {
			this->cells[p.y][p.x].possible_fight = true;
		}
		else {
			this->cells[p.y][p.x].marked = true;
		}
	}

	this->cells[selected_point.y][selected_point.x].selected = true;

}


void Field::clearMarks() {
	for (std::size_t i = 0; i < this->cells.size(); i++) {
		for (std::size_t j = 0; j < this->cells[i].size(); j++) {
			this->cells[i][j].marked = false;
			this->cells[i][j].possible_fight = false;
			this->cells[i][j].selected = false;
		}
	}
}


void Game::restart() {
	this->team_w = Army(Color::white);
	this->team_b = Army(Color::black);
	this->field = Field(team_w, team_b);

	w_moves_count = 0;
	b_moves_count = 0;
	cur_player = Player::user;
	winner = 0;
	w = w0 = 100;
	selected_figure = nullptr;
	warning1 = warning2 = false;
}
