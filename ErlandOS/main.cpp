#pragma once
#include "publicFunctions.h"
#include <iostream>

HWND hWnd = GetConsoleWindow();
COORD defaultCursorCoord = { 0,0 };

int main() { 
	

	ShowWindow(hWnd, SW_SHOWMAXIMIZED); // Maximize window - needed for some programs to look correctly
	
	std::vector<std::string> choices; //

	bool quit = false;
	while (!quit) { // For loop to run as long as quit has not been pressed
		system("cls"); // Clear the console
		SetConsoleTitle((L"ErlandOS")); // Set the consoles title

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), defaultCursorCoord);
		choices = { "Adress table ", "Multiplication Table ", "Number-Guess ", "Hangman ",  "Battleships ", "Quit " };
		switch (arrowKeyMenu(choices, false, "\n\n\tMove up and down using the arrow keys, and press enter to choose", 0, false))
		{
		case 0: system("cls"); SetConsoleTitle((L"ErlandOS: Adress Table"));		 adressTable();			break; // Run the adress table 
		case 1: system("cls"); SetConsoleTitle((L"ErlandOS: Multiplication Table")); multiplicationTable(); break; // Run the multiplication table
		case 2: system("cls"); SetConsoleTitle((L"ErlandOS: Number-Guess"));		 numberGuess();			break; // Run the number guess game
		case 3: system("cls"); SetConsoleTitle((L"ErlandOS: Hangman"));				 hangman();				break; // Run hangman
		case 4: system("cls"); SetConsoleTitle((L"ErlandOS: Battleships"));			 battleships();			break; // run battleships
		default: quit = true; break; 
		}
		ShowConsoleCursor(false);
	}
	
	return(0);

}