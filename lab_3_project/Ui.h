#pragma once
#include <SFML/Graphics.hpp>

#include "Field.h"



/*!
	\brief Class that describes UI of the game
*/
class Ui {
public:
	class Button {

	};
private:
	int& w; // native width of one square of netting
	int& w0; // width of one texture in image files
	sf::RenderWindow& main_window;
	sf::View window_view;
	Field& field;


	std::string getCurrentTimeAsString();
	void initWindow();
public:
	Ui(sf::RenderWindow& main_window, Field& field, int& w, int& w0) : main_window{ main_window }, field{ field }, w(w), w0(w0) {
		initWindow();
		window_view = main_window.getDefaultView();
	};
//	void init(sf::RenderWindow* window, Field* field);

	
	int displayMessageBox(const wchar_t* message, const wchar_t* title = L"Warning");
	int displayQuestionBox(const wchar_t* question, const wchar_t* title);
	bool getSavePath(wchar_t* filePath, std::size_t buffer_size);
	bool getLoadPath(wchar_t* filePath, std::size_t buffer_size);
	void resizeWindow();


};

