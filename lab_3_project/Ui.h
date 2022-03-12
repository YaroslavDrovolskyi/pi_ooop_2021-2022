/*!
	\file
	\brief Header file for class Ui

*/

#pragma once
#include <SFML/Graphics.hpp>

#include "Field.h"



/*!
	\brief Class that describes UI of the game
*/
class Ui {
public:
	class Button;
	enum class Place;
private:
	int w; // native width of one square of netting
	int w0; // width of one texture in image files
	const int& winner;
	sf::RenderWindow& main_window;
	sf::View window_view;
	Field& field;


	std::string getCurrentTimeAsString();
	void initWindow();
	void displayField();
public:
	Ui(sf::RenderWindow& main_window, Field& field, const int& winner);

	
	int displayMessageBox(const wchar_t* message, const wchar_t* title = L"Warning");
	int displayQuestionBox(const wchar_t* question, const wchar_t* title);
	bool getSavePath(wchar_t* filePath, std::size_t buffer_size);
	bool getLoadPath(wchar_t* filePath, std::size_t buffer_size);
	void resizeWindow();
	void displayWindow();
	Place getClickedPlace(const sf::Event& event, Point& field_point);

};

class Ui::Button {

};

/*!
	\enum Place
	\brief Enum that describes place on main window
*/
enum class Ui::Place {
	field,
	button_save,
	button_load,
	button_restart,
	button_close,
	nowhere
};

