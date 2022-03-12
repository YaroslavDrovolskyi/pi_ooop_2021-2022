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

