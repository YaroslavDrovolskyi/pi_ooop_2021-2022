/*!
	\file
	\brief Header file for class Ui

*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Field.h"



/*!
	\brief Class that describes UI of the game
*/
class Ui {
public:
	struct Button;
	enum class Place; ///< \brief Enum that describes place on main window
private:
	int w; // native width of one square of netting
	int w0; // width of one texture in image files
	const int& winner;
	sf::RenderWindow& main_window;
	sf::View window_view;
	Field& field;

	std::vector<Button> buttons;


	
	void initWindow();
	void displayField();
	void displayButtons(const sf::Font& font);
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



/*!
	\brief Struct that logically describes button - element of UI

	All positions, size have unit of measurement: it is a size of netting square
*/
struct Ui::Button {
	Ui::Place id;
	std::string label;
	sf::Color color;
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Vector2f label_pos;

	Button(const Ui::Place& id, const std::string& label, const sf::Color& color, const sf::Vector2f& size,
		const sf::Vector2f& position, const sf::Vector2f& label_pos);
	bool isContains(double x, double y) const;
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

