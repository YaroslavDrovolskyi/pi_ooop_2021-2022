/*!
	\file
	\brief File with implementation of class ChessGame

*/

#include "Game.h"

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


#include <ctime>
#include <windows.h>
#include <WinUser.h>





ChessGame::ChessGame() : 
	team_w(Color::white),
	team_b(Color::black), 
	field(team_w, team_b),
	main_window(sf::VideoMode(1600, 950), "Chess", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize),
	w_moves_count(0),
	b_moves_count(0),
	cur_player(Player::user),
	winner(0),
	selected_figure(nullptr),
	ui(main_window, field, winner)
{

}

/*!
	\brief The main function in class ChessGame.\n
	It manage the program and handle all situations via auxiliary methods.
*/
void ChessGame::exec() {
//	loadMovesHistory();
	/*
	int msgboxID = MessageBox(
		NULL,
		L"temp.txt already exists.\nDo you want to replace it?",
		L"Confirm Save As",
		MB_ICONEXCLAMATION | MB_YESNO
	);
	*/


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

//	sf::RenderWindow main_window(sf::VideoMode(1600, 950), "Chess", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	/* ============================== initWindow()   =================================
	main_window.setVerticalSyncEnabled(true); // sync frequency
	main_window.setPosition({ 150, 25 });
	sf::Image icon;
	icon.loadFromFile("img/icon.png");
	main_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	*/

//	ui.init(&main_window, &field);
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


	while (main_window.isOpen()) {


		if (winner == 0 && cur_player == Player::ai) {
			aiMove(team_b, b_moves_count);
		}
		else {
			sf::Event event;
			if (main_window.waitEvent(event)) { // while and pollEvent
				if (event.type == sf::Event::Closed) {
					handleClose();
				//	main_window.close();
				}

				else if (event.type == sf::Event::Resized) {
					ui.resizeWindow();
				}


				else if (event.type == sf::Event::MouseButtonPressed) {
					Point field_point;
					Ui::Place clicked_place = ui.getClickedPlace(event, field_point);


					// check places, where reaction doesn't depend on is there a winner or not
					if (clicked_place == Ui::Place::button_save) {
						saveMovesHistory();
					}
					else if (clicked_place == Ui::Place::button_load) {
						loadMovesHistory();
					}
					else if (clicked_place == Ui::Place::button_restart) {
						restart();
					}
					else if (clicked_place == Ui::Place::button_close) {
						handleClose();
					}



					if (this->winner == 0) {
						if (cur_player == Player::user) {
							if (clicked_place == Ui::Place::field) {
								handleFieldClick(field_point);
							}	
						}
					}
					else { // if game is over (winner is -1 or 1)
						// nothing to check anymore
					}
				}
			}
		}
		ui.displayWindow();
	}
}






std::vector<Point> ChessGame::movesFromPoint(Point p, int move_number, bool consider_king) {
	if (!field.cells[p.y][p.x].figure) { return std::vector<Point>(); }

	switch (field.cells[p.y][p.x].figure->getType()) {
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

std::vector<Point> ChessGame::pawn_moves(Point p, int moves_number, bool consider_king) {
	std::vector<Point> result;

	int is_white = 1;
	if (field.cells[p.y][p.x].figure) {
		if (field.cells[p.y][p.x].figure->getColor() == Color::black) {
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
			&& field.cells[p.y][p.x].figure->getColor() != field.cells[p1.y][p1.x].figure->getColor()) {
			result.push_back(p1);
		}

		Point p2(p.x - 1, p.y + is_white);
		if (isCorrectPoint(p2) && field.cells[p2.y][p2.x].figure
			&& field.cells[p.y][p.x].figure->getColor() != field.cells[p2.y][p2.x].figure->getColor()) {
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



	eraseIncorrectMoves(p, result);

	return result;
}


std::vector<Point> ChessGame::rook_moves(Point p) {
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

	eraseIncorrectMoves(p, result);

	return result;

}


std::vector<Point> ChessGame::horse_moves(Point p) {
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

	eraseIncorrectMoves(p, result);

	return result;
}


std::vector<Point> ChessGame::bishop_moves(Point p) {
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

	eraseIncorrectMoves(p, result);

	return result;

}

std::vector<Point> ChessGame::queen_moves(Point p) {
	return concatinate(rook_moves(p), bishop_moves(p)); // queen ways is (bishop + rook) ways
}


std::vector<Point> ChessGame::king_moves(Point p, int moves_number) {
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

	Army& enemy_team = field.cells[p.y][p.x].figure->getColor() == Color::white ? team_b : team_w;
	int enemy_moves_number = enemy_team.getColor() == Color::black ? b_moves_count : w_moves_count;

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

	eraseIncorrectMoves(p, result);

	return result;
}

bool ChessGame::isCorrectPoint(const Point& p) {
	if (p.x > 7 || p.y > 7) {
		return false;
	}
	if (p.x < 0 || p.y < 0) {
		return false;
	}

	return true;
}

void ChessGame::eraseIncorrectMoves(Point from, std::vector<Point>& destinations) {
	for (std::size_t i = 0; i < destinations.size(); ) {
		Point dest = destinations[i];
		if (!isCorrectPoint(destinations[i])) {
			destinations.erase(destinations.begin() + i);
		}
		else if (field.cells[dest.y][dest.x].figure && field.cells[dest.y][dest.x].figure->getColor() == field.cells[from.y][from.x].figure->getColor()) { // if figures with same colors fight
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
Figure* ChessGame::makeMove(const Point& from_p, const Point& dest_p) { // assuming coordinates are correct
	assert(isCorrectPoint(from_p));
	assert(isCorrectPoint(dest_p));

	Figure* figure = field.cells[from_p.y][from_p.x].figure;
	Figure* dest_figure = field.cells[dest_p.y][dest_p.x].figure;

	figure->setPosition(dest_p);

	if (dest_figure) {
		dest_figure->setIsAlive(false);
		dest_figure->setPosition(Point(-1, -1));
	}

	//	field.makeMove(from_p, dest_p);

	field.cells[dest_p.y][dest_p.x].figure = field.cells[from_p.y][from_p.x].figure;
	field.cells[from_p.y][from_p.x].figure = nullptr;

	return dest_figure; // return removed figure
}



std::vector<Move> ChessGame::allPossibleMoves(const Army& team, int move_number, bool consider_king) {
	std::vector<Move> result;
	for (const Figure& figure : team.figures) {
		if (figure.isAlive()) {
			Point pos(figure.getPosition());
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

// return best move for team (according to minimax)
// or invalid move if there are any possible moves
Move ChessGame::calculateBestMove(const Army& team, int move_number) {
	std::vector<Move> all_possible_moves = allPossibleMoves(team, move_number);

	if (all_possible_moves.size() == 0) {
		return Move(Point(-1, -1), Point(-1, -1)); //// need to Reimplement
	}

	unsigned int t1 = clock();
	int i_best = minimax(0, 2, team, move_number, -10000, 10000);
	std::cout << "minimax time: " << (double)(clock() - t1) / 1000 << "s" << std::endl;

	//	std::cout << "Best move: from " << all_possible_moves[i_best].from << " to " << all_possible_moves[i_best].dest << std::endl;

	assert(i_best >= 0);
	return all_possible_moves[i_best];
}


int ChessGame::minimax(int cur_depth, int max_depth, const Army& team, int move_number, int alpha, int beta) {
	if (cur_depth == max_depth) {
		return field.evaluate();
	}

	std::vector<Move> possible_moves = allPossibleMoves(team, move_number);

	int best_move_value = 0;
	int best_move_index = -1;

	if (team.getColor() == Color::white) {
		best_move_value = -10000;
		for (std::size_t i = 0; i < possible_moves.size(); i++) {
			Move cur_move = possible_moves[i];
			Figure* removed_figure = makeMove(cur_move.from, cur_move.dest);
			int next_field_value = minimax(cur_depth + 1, max_depth, team_b, move_number + 1, alpha, beta);
			undoMove(cur_move.from, cur_move.dest, removed_figure);

			if (next_field_value > best_move_value) { // find max
				best_move_value = next_field_value;
				best_move_index = i;
			}

			alpha = std::max(alpha, best_move_value);
			if (beta <= alpha) { break; }
		}
	}
	else {
		best_move_value = 10000;
		for (std::size_t i = 0; i < possible_moves.size(); i++) {
			Move cur_move = possible_moves[i];
			Figure* removed_figure = makeMove(cur_move.from, cur_move.dest);
			int next_field_value = minimax(cur_depth + 1, max_depth, team_w, move_number + 1, alpha, beta);
			undoMove(cur_move.from, cur_move.dest, removed_figure);

			if (next_field_value < best_move_value) { // find min
				best_move_value = next_field_value;
				best_move_index = i;
			}

			beta = std::min(beta, best_move_value);
			if (beta <= alpha) { break; }
		}
	}


	if (cur_depth == 0) {
		return best_move_index;
	}
	else {
		return best_move_value;
	}

}


void ChessGame::undoMove(const Point& from, const Point& dest, Figure* removed_figure) {
	makeMove(dest, from);
	if (removed_figure) {
		removed_figure->setPosition(dest);
		removed_figure->setIsAlive(true);
		field.cells[dest.y][dest.x].figure = removed_figure;
	}
}

void ChessGame::aiMove(const Army& team, int& moves_number) {
	Move best_move = calculateBestMove(team, moves_number);
	if (!best_move.isValid() || !team.isKingAlive()) { // when AI hasn't possible moves or hasn't king
		markAsWinner(getOppositeTeam(team));
		return;
	}


	std::string str = team.getColor() == Color::white ? "white: " : "black: ";
	std::cout << str << best_move.from.getString() << " -> " << best_move.dest.getString() << std::endl << std::endl;

	Figure* removed_figure = makeMove(best_move.from, best_move.dest);
	moves_list.insert(best_move, removed_figure);

	moves_number++;

	if (!getOppositeTeam(team).isKingAlive() || allPossibleMoves(getOppositeTeam(team), w_moves_count).size() == 0) { // if opposite king isn't alive or opposite hasn't moves
		markAsWinner(team);
	}

	cur_player = Player::user;
}

void ChessGame::userMove(const Army& team, int& moves_number) {
	auto possible_moves = allPossibleMoves(team, moves_number);
	if (possible_moves.size() == 0) {
		markAsWinner(getOppositeTeam(team));
		return;
	}
	Move best_move = possible_moves[rand() % possible_moves.size()];


	std::string str = team.getColor() == Color::white ? "white: " : "black: ";
	std::cout << str << best_move.from << " -> " << best_move.dest << std::endl;

	makeMove(best_move.from, best_move.dest);

	moves_number++;

	if (!getOppositeTeam(team).isKingAlive()) { // if opposite king isn't alive
		markAsWinner(team);
	}
}



Army& ChessGame::getOppositeTeam(const Army& team) {
	if (team.getColor() == Color::black) {
		return team_w;
	}
	return team_b;
}


void ChessGame::markAsWinner(const Army& team) {
	if (team.getColor() == Color::black) {
		winner = -1;
	}
	else {
		winner = 1;
	}
	std::cout << "WINNER: " << winner << std::endl << std::endl;
}



void ChessGame::handleFieldClick(const Point& pos) {
	assert(cur_player == Player::user);

	Figure* figure = field.cells[pos.y][pos.x].figure; // figure in cell, on which user clicked
	if (!selected_figure) {
		if (figure && figure->getColor() == Color::white) {
			selected_figure = figure;
			field.putMarks(pos, movesFromPoint(pos, w_moves_count));
		}
		else if (figure && figure->getColor() == Color::black) {
			ui.displayMessageBox(L"Please, choose own (white) figure");
		}

	}
	else {
		if (figure && figure->getColor() == Color::white) { // if we selected other own figure
			field.clearMarks();
			selected_figure = figure;
			field.putMarks(pos, movesFromPoint(pos, w_moves_count));
		}
		else {
			if (field.cells[pos.y][pos.x].marked || field.cells[pos.y][pos.x].possible_fight) {  // need to move
				std::cout << "white: " << selected_figure->getPosition().getString() << " -> " << pos.getString() << std::endl;
				Point from = selected_figure->getPosition(); // get a value for not to pass position in makeMove() by reference (cause of inctorrect behaviour: no move)
				Figure* removed_figure = makeMove(from, pos);
				moves_list.insert(Move{from, pos}, removed_figure); // add move to the list
				selected_figure = nullptr;
				w_moves_count++;
				field.clearMarks();
				cur_player = Player::ai;
			}
			else {
				ui.displayMessageBox(L"Impossible move to this cell");
			}
		}

	}
}





void ChessGame::saveMovesHistory() {
	wchar_t filepath[260];

	if (ui.getSavePath(filepath, sizeof(filepath)) == TRUE) {
		moves_list.writeInFile(filepath);
		std::wcout << L"Game saved in file: " << filepath << std::endl;
	}
}


void ChessGame::loadMovesHistory() {
	wchar_t filepath[260];

	if (ui.getLoadPath(filepath, sizeof(filepath)) == TRUE) {
		restart(); // because sequense of moves we'll apply started from new game
		moves_list.readFromFile(filepath);
		std::wcout << L"Game loaded from file: " << filepath << std::endl;
		
		applyMoves(moves_list); // apply moves

		moves_list.print();
	}
}




// function to apply moves when we got them from file. Also upgrade moves with &removed_figure for each move
void ChessGame::applyMoves(MovesHistory& moves) {
	for (std::size_t i = 0; i < moves.getSize(); i++) {
		Move move = moves.getMove(i);
		Figure* fig = makeMove(move.from, move.dest);

		moves.setRemovedFigure(i, fig);
	}

	field.clearMarks();

	// Change current player according to even/odd of size of MovesHistory
	// if white is winner, black is current
	// else if black is winner, white is current
	
	if (moves.getSize() % 2 == 0) {
		cur_player = Player::user;
	}
	else {
		cur_player = Player::ai;
	}

	// update b_move_count and w_moves_count assuming game started from white move
	w_moves_count = moves.getSize() / 2;
	b_moves_count = moves.getSize() - w_moves_count;

	// if it is a winner
	winner = checkForWinner();

	selected_figure = nullptr;
}

// check who is winner and return: -1 - black, 0 - nobody, 1 - white
int ChessGame::checkForWinner() {
	if (!team_w.isKingAlive() || allPossibleMoves(team_w, w_moves_count).size() == 0) { // if white king isn't alive or team hasn't moves
		return -1;
	}
	if (!team_b.isKingAlive() || allPossibleMoves(team_b, b_moves_count).size() == 0) { // if black king isn't alive or team hasn't moves
		return 1;
	}
	return 0;
}
	



void ChessGame::restart() {
//	moves_list.print();

	team_w.restore();
	team_b.restore();
	field.restore(team_w, team_b);
	moves_list.clear();

	w_moves_count = 0;
	b_moves_count = 0;
	cur_player = Player::user;
	winner = 0;
	selected_figure = nullptr;

	std::cout << "RESTART" << std::endl << std::endl << std::endl;

}

// returns true if window is closed, and false if player want to continue
bool ChessGame::handleClose() {
	int close = ui.displayQuestionBox(L"Do you want to exit?", L"Exit?");
	if (close == IDYES) { 
		if (ui.displayQuestionBox(L"Do you want to save game?", L"Save?") == IDYES) { // save & exit
			saveMovesHistory();
		}
		main_window.close();
		return true;
	}
	else { // continue game
		return false;
	}
}