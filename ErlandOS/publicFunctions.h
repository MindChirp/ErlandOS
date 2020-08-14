#pragma once
#include <Windows.h>
#include <string>
#include <vector>




void adressTable();
void hangman();
void battleships();
void numberGuess();
void multiplicationTable();


// Color values
enum color { black = 0, darkBlue, darkGreen, cyan, darkRed, darkPurple, darkYellow, gray, darkGray, blue, green, lightBlue, red, purple, yellow, white };
//			 A			B		 C			 D	   E		F			G			H	  I			J	  K		 L			M	 N		 O		 P	 <- using ASCII ('letter'-65) = 0-15 (Used for sprites in battleships)



void ShowConsoleCursor(bool showFlag);

COORD GetConsoleCursorPosition();


void arrowKeyMenuDraw(int selection, std::vector<std::string> choices, std::string message, int mode);

int arrowKeyMenu(std::vector<std::string> choices, bool clear, std::string message, int mode, bool keepSelection);


void delay(int x);

int getIntInput(int start, int end);

char getCharInput(char start, char end);

void setCursorPos(COORD coord);

void setColor(int textCol, int backgroundCol);