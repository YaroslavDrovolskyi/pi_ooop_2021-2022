#include "Ui.h"

#include <windows.h>
#include <WinUser.h>


/*!
	Method that allow to display exclamation Message Box using a WinAPI \n
	It is a "wrapper" of MessageBox function

	\param[in] message is a message to display
	\param[in] title is a title of a message box

	\returns the code of user respond
*/
int Ui::displayMessageBox(const wchar_t* message, const wchar_t* title) {
	int respond = MessageBox(
		window->getSystemHandle(),
		message,
		title,
		MB_ICONEXCLAMATION | MB_OK
	);

	return respond;
}

Ui::Ui() {
	window = nullptr;
	field = nullptr;
}

void Ui::init(sf::RenderWindow* window, Field* field) {
	if (window) {
		this->window = window;
	}
	this->field = field;
}


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
	ofn.hwndOwner = this->window->getSystemHandle();
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
	ofn.hwndOwner = this->window->getSystemHandle();
	ofn.hwndOwner = NULL;
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