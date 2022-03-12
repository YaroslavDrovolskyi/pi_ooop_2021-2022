#include "Ui.h"

#include <windows.h>
#include <WinUser.h>

#include <iostream>







void Ui::initWindow() {
	main_window.setVerticalSyncEnabled(true); // sync frequency
	main_window.setPosition({ 150, 25 });
	sf::Image icon;
	icon.loadFromFile("img/icon.png");
	main_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}







/*!
	Method that allow to display exclamation Message Box using a WinAPI \n
	It is a "wrapper" of MessageBox() function

	\param[in] message is a message to display
	\param[in] title is a title of a message box

	\returns the code of user respond
*/
int Ui::displayMessageBox(const wchar_t* message, const wchar_t* title) {
	int respond = MessageBox(
		main_window.getSystemHandle(),
		message,
		title,
		MB_ICONEXCLAMATION | MB_OK
	);

	return respond;
}


/*!
	Method that allow to display question Message Box using a WinAPI \n
	It is a "wrapper" of MessageBox() function

	\param[in] question is a question to display
	\param[in] title is a title of a message box

	\returns the code of user respond
*/
int Ui::displayQuestionBox(const wchar_t* question, const wchar_t* title) {
	int respond = MessageBox(
		main_window.getSystemHandle(),
		question,
		title,
		MB_ICONQUESTION | MB_YESNO
	);

	return respond;
}

// MessageBox() documentation: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox


/*!
	Method that allow to get current date and time as string

	\returns string in a format: "dd-mm-yyyy_hh-mm-ss"
*/
std::string Ui::getCurrentTimeAsString() {
	time_t time = std::time(nullptr);
	tm local_time;
	localtime_s(&local_time, &time);
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &local_time);

	return std::string(buffer);
}


/*!
	Method that asks user for path to save game history. \n
	It is implemented using the WinAPI GetSaveFileName() function.

	\param[in, out] filePath is initial filename to save \n
	Also it is a directory to save file

	\returns true if user chose directory, and false if not

*/
bool Ui::getSavePath(wchar_t* filePath, std::size_t buffer_size) {
	std::string name = "game_" + getCurrentTimeAsString() + ".txt";
	std::wstring w_name{ name.begin(), name.end() }; // convertation init filename from std::string into std::wstring


	OPENFILENAME ofn;
	std:copy(w_name.begin(), w_name.end(), filePath); // convertation init filename from std::wstring into char*
	filePath[w_name.length()] = '\0';

	ZeroMemory(&ofn, sizeof(ofn)); // set memory to 0
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = this->main_window.getSystemHandle();
	ofn.lpstrFile = filePath; // file path
//	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = buffer_size;
	ofn.lpstrFilter = L"Text files (*.txt)\0*.txt\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL; // file title (name + file extension)
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = L"Select a file to save game";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	return GetSaveFileName(&ofn);
}



/*!
	Method that asks user for path to load game history. \n
	It is implemented using the WinAPI GetOpenFileName() function.

	\param[out] filePath is a directory to load file

	\returns true if user chose directory, and false if not

*/
bool Ui::getLoadPath(wchar_t* filePath, std::size_t buffer_size) {
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn)); // set memory to 0 
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = this->main_window.getSystemHandle();
//	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath; // file path
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = buffer_size;
	ofn.lpstrFilter = L"Text files (*.txt)\0*.txt\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL; // file title (name + file extension)
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = L"Select a file to load game";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	bool result = GetOpenFileName(&ofn);

//	auto problem = CommDlgExtendedError(); // in taht way we can get info about problem (if exists)

	return result;
}

// GetOpenFileName() example from: https://www.cyberforum.ru/win-api/thread2439941.html
// Explanations of OPENFILENAME attribures: http://www.vsokovikov.narod.ru/New_MSDN_API/Com_dlg_lib/str_openfilename.htm
// About ZeroMemory: https://stackoverflow.com/questions/16210598/null-vs-zeromemory


void Ui::resizeWindow() {
	int new_width = main_window.getSize().x;
	int new_height = main_window.getSize().y;

	if (new_width < 500) {
		main_window.setSize({ 500, main_window.getSize().y });
		new_width = 500;
	}

	if (new_height < 300) {
		main_window.setSize({ main_window.getSize().x, 300 });
		new_height = 300;
	}


	w = std::min(new_width / 16, new_height / 9); // change size of netting square
	std::cout << "w = " << w << std::endl << std::endl;

	window_view.setSize(new_width, new_height);
	window_view.setCenter(8 * w, 5 * w);

	main_window.setView(window_view); // apply wiev for window

//	std::cout << "new width: " << new_width << std::endl
//		<< "new height:" << new_height << std::endl;
}


void Ui::displayWindow() {

	sf::Font font;
	font.loadFromFile("fonts/calibri.otf");

	main_window.clear(sf::Color(250, 220, 100, 0)); // set background
	displayField(); ///////////////////////////

	if (winner != 0) {
		sf::Text win_text("", font, w);
		win_text.setFillColor(sf::Color(248, 1, 20));
		win_text.setPosition(10.5 * w, 1 * w);

		if (winner == 1) { // user (white) won
			win_text.setString("YOU WON!");
		}
		else { // ai (black) won
			win_text.setString("AI WINS!");
		}

		main_window.draw(win_text);
	}

	// button_save
	sf::RectangleShape button_save(sf::Vector2f(3 * w, w));
	button_save.setFillColor(sf::Color(10, 103, 163));
	button_save.setPosition(11 * w, 3.5 * w);
	main_window.draw(button_save);

	sf::Text text_save("Save game", font, 0.4 * w);
	text_save.setPosition(11.7 * w, 3.75 * w);
	main_window.draw(text_save);

	// button_load
	sf::RectangleShape button_load(sf::Vector2f(3 * w, w));
	button_load.setFillColor(sf::Color(10, 103, 163));
	button_load.setPosition(11 * w, 5 * w);
	main_window.draw(button_load);

	sf::Text text_load("Load game", font, 0.4 * w);
	text_load.setPosition(11.7 * w, 5.25 * w);
	main_window.draw(text_load);


	// button_restart
	sf::RectangleShape button_restart(sf::Vector2f(3 * w, w));
	button_restart.setFillColor(sf::Color(10, 103, 163));
	button_restart.setPosition(11 * w, 6.5 * w);
	main_window.draw(button_restart);

	sf::Text text_restart("Restart", font, 0.4 * w);
	text_restart.setPosition(11.9 * w, 6.75 * w);
	main_window.draw(text_restart);


	// button_close
	sf::RectangleShape button_close(sf::Vector2f(3 * w, w));
	button_close.setFillColor(sf::Color(255, 7, 1));
	button_close.setPosition(11 * w, 8 * w);
	main_window.draw(button_close);

	sf::Text text_close("Close", font, 0.4 * w);
	text_close.setPosition(12.1 * w, 8.25 * w);
	main_window.draw(text_close);






	main_window.display();
	
}


void Ui::displayField() {
	
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
			main_window.draw(cell);

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
			main_window.draw(cell);

			// draw figures
			Figure* f = field.cells[i][j].figure;
			if (f) {
				if (f->getColor() == Color::white) {
					switch (f->getType()) {
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
					switch (f->getType()) {
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
				figure.move(2 * w, w);
				main_window.draw(figure);
			}
		}
	}

	// draw number labels


	for (std::size_t i = 0; i < 16; i++) {
		if (i < 4) {
			number_label.setTextureRect(sf::IntRect(6 * w0 + (double)i * w0 / 4, 0, w0 / 4, w0));
			number_label.setPosition((double)7 * w / 4, w * i + w);
		}
		else if (i < 8) {
			number_label.setTextureRect(sf::IntRect(6 * w0 + (double)(i - 4) * w0 / 4, w0, w0 / 4, w0));
			number_label.setPosition((double)7 * w / 4, w * i + w);

		}
		else if (i < 12) {
			number_label.setTextureRect(sf::IntRect(7 * w0, 0 + (i - 8) * w0 / 4, w0, w0 / 4));
			number_label.setPosition(2 * w + (i - 8) * w, 9 * w);
			//			number_label.setPosition(0,0);
		}
		else {
			number_label.setTextureRect(sf::IntRect(7 * w0, w0 + (i - 12) * w0 / 4, w0, w0 / 4));
			number_label.setPosition(2 * w + (i - 8) * w, 9 * w);
		}

		number_label.setScale((double)w / w0, (double)w / w0);
		// set position

		main_window.draw(number_label);
	}

	
}



/* Tried to implement better way to call Message Box */
/*
	Method that allow to display Question Task Dialog using a WinAPI \n
	It is a "wrapper" of TaskDialogIndirect() function

	\param[in] title is a title of a message box
	\param[in] question is a question to display
	\param[in] text_btn1 is a text for button1
	\param[in] text_btn2 is a text for button2
	\param[in] text_btn3 is a text for button3

	\returns -1 if something is wrong, else the number of button user pressed: 1 if 1st button and so on
*/

/*
int Ui::displayQuestionBox(const wchar_t* title, const wchar_t* question, const wchar_t* text_btn1,
							const wchar_t* text_btn2, const wchar_t* text_btn3) {
	int nButtonPressed = 0;
	TASKDIALOGCONFIG config = { 0 };
	const TASKDIALOG_BUTTON buttons[] = {
											{ IDOK, L"Save & exit" }, // define button with custom text, but ID can't be custom
											{ IDYES, L"Exit" },
											{ IDNO, L"Continue" }
	};
	config.cbSize = sizeof(config);
	config.hwndParent = main_window.getSystemHandle();
	config.hInstance = NULL;
	config.dwCommonButtons = NULL;
	config.pszWindowTitle = title;
	config.pszMainIcon = TD_SHIELD_ICON;
	config.pszMainInstruction = question;
//	config.pszContent = L"Remember your changed password.";
	config.pButtons = buttons;
	config.cButtons = ARRAYSIZE(buttons);

	int result = TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL);
	if (result == S_OK) {
		switch (nButtonPressed){
		case IDOK:
			return 1; break;
		case IDYES:
			return 2; break;
		case IDNO:
			return 3; break;
		default:
			return -1; // should never happen
			break;
		}
	}
	else {
		return -1;
	}
}

// about function TaskDialogIndirect(): https://docs.microsoft.com/uk-ua/windows/win32/api/commctrl/nf-commctrl-taskdialogindirect?redirectedfrom=MSDN
// about TASKDIALOGCONFIG: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-taskdialogconfig
*/

