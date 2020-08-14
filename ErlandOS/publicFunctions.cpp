#include "publicFunctions.h"

#include <iostream>
#include <thread>		// For delay func.
#include <chrono>       // For delay func.


// == Shamelessly stolen from the interwebs ==
void ShowConsoleCursor(bool showFlag) // Function to turn on/off the cursor flag
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = showFlag; // Set the cursor visibility
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

COORD GetConsoleCursorPosition() // Function to get the cursors position
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
// ===========================================



// Function to set the position of the console cursor
void setCursorPos(COORD coord) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set text and background color
void setColor(int textCol, int backgroundCol) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textCol + (backgroundCol * 16));
}

// Functions for the arrow key menu system
#pragma region arrowKeyMenuFunctions 

COORD cursorCoord;
COORD prevCursorCoord = { 0,0 }; 

int selection = 0;

void arrowKeyMenuDraw(int selection, std::vector<std::string> choices, std::string message, int mode) {
	ShowConsoleCursor(false);


	cursorCoord.Y = prevCursorCoord.Y; 

	setCursorPos(cursorCoord); // Set the cursors position

	prevCursorCoord = GetConsoleCursorPosition();  // stores the cursors current position so the menu can be drawn from the same coordinates every time

	setColor(white, black);

	std::cout << "\t" << message << "\n"; // Print the title/message of the menu

	if (mode == 1) { // If mode is 1 (horizontal)
		std::cout << "\t"; // Print a "tab" to move the menu to the right
	}

	for (unsigned int i = 0; i < choices.size(); i++) { // For loop to get every choice in the menu

		if (mode == 0) { // If mode is 0 (vertical)

			if (i == selection) { // If the current choice to be drawn is selected 
				std::cout << "\t> "; // Draw pointer of menu
				if ((choices[i] == "Quit ") || (choices[i] == "Back ")) { setColor(red, black); } // Set color if the current choice is 'Quit' or 'Back'
				std::cout << choices[i] << "\n"; // Draw current choice
			}
			else { // If the current choice to be drawn is NOT selected 
				if ((choices[i] == "Quit ") || (choices[i] == "Back ")) { setColor(red, black); } // Set color if the menu option is 'Quit' or 'Back'
				std::cout << "\t " << choices[i] << "\n"; // Draw current choice
			}
		}
		else if (mode == 1) { // If mode is 1 (horizontal)
			if (i == selection) {  // If the current choice to be drawn is selected 
				std::cout << "[ "; // Draw opening bracket to show selected item
				if ((choices[i] == "Quit") || (choices[i] == "Back")) { setColor(red, black); } // Set color if the menu option is 'Quit' or 'Back'
				std::cout << choices[i]; // Draw selected choice
				setColor(white, black);  // Set color back to white
				std::cout << " ]\t";     // Draw closing bracket to show selected item
			}
			else { // If the current choice to be drawn is NOT selected 
				std::cout << "  " << choices[i] << "  \t"; // Draw choices
			}
		}
		setColor(white, black); // Set color back to white
	}
}

int arrowKeyMenu(std::vector<std::string> choices, bool clear, std::string message, int mode, bool keepSelection) {
	if (!keepSelection) {
	selection = 0;
	}

	if (clear) { system("cls"); } // Clear console


	int numberOfchoices = choices.size();

	bool pressedUp = false;    //
	bool pressedDown = false;  //  Theese bools are in place to make sure the keys has to be released.
	bool pressedEnter = false; //

	prevCursorCoord = GetConsoleCursorPosition(); // Stores the cursor position, where the menu will be drawn from

	arrowKeyMenuDraw(selection, choices, message, mode); // Calling the function to draw the menu, the arguments are (in order): the selected line  ,  the vector of choices  ,  the title/message of the menu , mode of menu (vertical(0)/horizontal(1))



	// == Check keys continously ====
	while (true) {

		// == Check for enter press ==========================
		if ((GetKeyState(VK_RETURN) & 0x8000) && pressedEnter == false) {
			pressedEnter = true;

		}
		if (!(GetKeyState(VK_RETURN) & 0x8000) && pressedEnter == true) {
			pressedEnter = false;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Flushes the buffer
			break;
		}
		// ==============================================

		// == Check for up key ==========================
		if (((GetKeyState(VK_UP) & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000)) && (selection > 0)) {
			if (pressedUp == false) {
				pressedUp = true;
				selection--;
				arrowKeyMenuDraw(selection, choices, message, mode);
			}
		}
		else {
			pressedUp = false;
		}
		// ==============================================

		// == Check for down key ========================
		if (((GetKeyState(VK_DOWN) & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000)) && (selection < numberOfchoices - 1)) {
			if (pressedDown == false) {
				pressedDown = true;
				selection++;
				arrowKeyMenuDraw(selection, choices, message, mode);
			}
		}
		else {
			pressedDown = false;
		}
	}
	// ==============================
	return(selection);
}
#pragma endregion arrowKeyMenuFunctions 

// Function for delay
void delay(int x) { 
	std::this_thread::sleep_for(std::chrono::milliseconds(x)); 
}

// Function to get 'safe' int input
int getIntInput(int start, int end) {  // the arguments start & end are limits you set when calling the function, to make sure you get numbers within a certain range

	while (true) { // This while loop is in place to keep giving a request to enter an int if the previous input was not valid  
		int input;
		std::cout << "\t> "; // 'tabs' to move the cursor to the right, then prints a '>' to visualize where the text will be entered 
		std::cin >> input;   // Get input
		if (!std::cin.good() || (input < start) || (input > end)) {	// cin.good() checks if what has been entered is a valid integer, if it is not execute code below. Or if the input is less than the 'start' argument, or higher than the 'end' argument   
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), darkRed);	// Set text color to red
			std::cout << "\tError: invalid number - Please try again: \n";		// Enter error message
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);	// Set text color to white
			std::cin.clear();								// Clear the cin  <-.
			std::cin.ignore(std::cin.rdbuf()->in_avail());  // Ignore the cin <-'- In short terms theese two makes sure the next time a 'std::cin >>' is ran, it works correctly 
		}
		else { // If the input is valid, return 
			std::cin.sync();
			return(input);  
		}
	} 
}

// Function to get 'safe' char input - Works alomst exactly like the one above for integers, exept its for chars
char getCharInput(char start, char end) { 
	while (true) {
		char input;
		std::cin >> input;
		input = tolower(input); // Here the input is converted to lower capitalization
		if (!std::cin.good() || (input < start) || (input > end)) {
			std::cout << "Error: invalid char - Please try again: \n";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}
		else {
			return(input);
			std::cin.sync();
		}
	}
}








