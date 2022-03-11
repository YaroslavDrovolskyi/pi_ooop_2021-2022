#pragma once
#include <SFML/Graphics.hpp>

#include "Field.h"



/*!
	\brief Class that describes UI of the game
*/
class Ui {
private:
	sf::RenderWindow* window;
	Field* field;


	std::string getCurrentTimeAsString();
public:
	Ui();
	//	Ui(sf::RenderWindow& window, Field& field) : window{ window }, field{ field } {};
	void init(sf::RenderWindow* window, Field* field);

	int displayMessageBox(const wchar_t* message, const wchar_t* title = L"Warning");
	bool getSavePath(wchar_t* filePath, std::size_t buffer_size);
	bool getLoadPath(wchar_t* filePath, std::size_t buffer_size);


};

