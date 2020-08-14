#include "publicFunctions.h"

#include <iostream>

#include <stdlib.h>		// srand, rand
#include <time.h>       // time 


// == Define variables ===== 

int difficulty;
int scoreBase;
int scoreTotal;
int numberToGuess;
int range;
int guess = 0;
int differenceColor;
int numberOfGuesses;
int difference;
int lastDifference;
bool playing = true;
bool closerFurtherFeedback = true;
bool colorFeedback = true;
std::vector<std::string> choices;

COORD replaceCOORD;
// ========================= */


// == Functions ============ 

void infoScreen() {
	system("cls");
	std::cout << "\n\n\tVery Very Quick Tutorial:\n\tEnter a random integer (whole number) inside the range corresponding to the difficulty.\n\tThere are colors indicating how close you are to the correct number:\n\tWhite is > 40, Light Blue is < 40, Blue is < 30, Purple is < 20, Red is < 10";
	std::cout << "\n\n\tYou can enable/disable the color feedback in the settings, and also enable/disable\n\tfeedback telling you whether you are closer of further away than the prevoiuus guess\n\n";
	system("pause");

}

void settingsCloserFurther() {
	choices = { "On ", "Off " };
	std::cout << "\n\nGive closer/further feedback?\n\tCurrently ";
	if (closerFurtherFeedback) { std::cout << "on\n"; }
	else { std::cout << "off\n"; }

	switch (arrowKeyMenu(choices, false, "\n", 0, false))
	{
	case 0: closerFurtherFeedback = true; break;
	case 1: closerFurtherFeedback = false; break;
	default: break;
	}
}

void settingsColorFeedback() {
	choices = { "On ", "Off " };
	std::cout << "\n\nGive color feedback?\n\tCurrently ";
	if (colorFeedback) { std::cout << "on\n"; }
	else { std::cout << "off\n"; }

	switch (arrowKeyMenu(choices, false, "\n", 0, false))
	{
	case 0: colorFeedback = true; break;
	case 1: colorFeedback = false; break;
	default: break;
	}
}

void settings() {
	bool continued = false;
	while (!continued) {
		system("cls");
		choices = { "Closer/Further feedback ", "Color feedback " , "Back " };
		switch (arrowKeyMenu(choices, false, "\n\n\tSettings", 0, false))
		{
		case 0: settingsCloserFurther();  break;
		case 1: settingsColorFeedback();  break;
		default: continued = true; break;
		}
		ShowConsoleCursor(false);
	}
}

// ========================= */



void numberGuess() {
	playing = true;

	while (playing) { // Point to return to if playing again


		// == Set variables ======================
		difficulty = 0;
		scoreBase = 10000;
		numberOfGuesses = 0;
		difference = 0;
		scoreTotal = 0;
		range = 100;
		// ======================================= */ 


		// == Start menu ======================
		bool continued = false;

		while (!continued) {
			system("cls");
			choices = { "Before you play ", "Settings ", "Play game ", "Quit "};
			switch (arrowKeyMenu(choices, false, "\n\n\t", 0, false))
			{
			case 0: infoScreen(); break;
			case 1: settings(); break;
			case 2: continued = true;  break;
			default: continued = true; playing = false; break;
			}
			ShowConsoleCursor(false);
		}
		// ======================================= */ 

		if (!playing) {
			break;
		}

		// == Difficulty Selection ================
		choices = { "Easy","Medium","Hard","Quit" };

		switch (arrowKeyMenu(choices, true, " \n\n\t --< Choose difficulty >-----------------------------", 1, false))
		{
		case 0: difficulty = 0; system("cls"); std::cout << "\n\tEasy difficulty selected. A number between 1 and 100 will be generated\n\n"; range = 100;  break;
		case 1: difficulty = 1; system("cls"); std::cout << "\n\tMedium difficulty selected. A number between 1 and 1000 will be generated\n\n"; range = 1000;  break;
		case 2: difficulty = 2; system("cls"); std::cout << "\n\tHard difficulty selected. A number between 1 and 10000 will be generated\n\n"; range = 10000;  break;
		case 3:  playing = false; break;
		default:   break;
		}

		if (!playing) {
			break;
		}

		system("pause");
		// ======================================= */ 


		// == Generate random number =============	
		srand((unsigned)time(NULL)); // Set seed 

		numberToGuess = rand() % range + 1; //Generate random number
		// ======================================= */


		// == Get input ==========================	
		system("cls");
		std::cout << "\n\n\tGuess the number! (Between 1 and " << range << ")" << "\n";

		while (true) {

			ShowConsoleCursor(true);
			replaceCOORD = GetConsoleCursorPosition(); // Set coord to current position
			
			guess = getIntInput(0, range); // Get user input
			// ======================================= */



			// == Replace input ======================
			replaceCOORD.X += 10; // Change coordinates to fit the replacement of the number (the number will be replaced to give color feedback on it)
			replaceCOORD.X -= 2;  // 

			setCursorPos(replaceCOORD);  // Set the cursor pos to the previously set coordinates

			std::string differenceMessage;

			lastDifference = difference;
			numberOfGuesses++;

			// Response message saying if you were too high, too low, or correct
			if (guess > numberToGuess) { difference = guess - numberToGuess; differenceMessage = "-Too high"; }  
			else if (guess < numberToGuess) { difference = numberToGuess - guess; differenceMessage = "-Too low"; }
			else if (guess == numberToGuess) { difference = 0; differenceMessage = "-Correct!"; }

			// Set what color text should be based on how close to the original number you were
			if (colorFeedback) { // If color feedback is enabled
				if (difference == 0) { differenceColor = green; }
				else if (difference < 10) { differenceColor = red; }
				else if (difference < 20) { differenceColor = purple; }
				else if (difference < 30) { differenceColor = blue; }
				else if (difference < 40) { differenceColor = cyan; }
				else { differenceColor = white; }
			}
			else { // If color feedback is disabled
				differenceColor = white;
			}

			setColor(differenceColor, black);
			std::cout << "  " << guess;

			setColor(white, black);

			std::cout << "\t" << differenceMessage << "\t";

			// Feedback saying whether current guess was closer or further away than the prev. guess
			if ((closerFurtherFeedback) && (lastDifference != 0) && (difference != 0)) {
				if (difference < lastDifference) {
					std::cout << "Closer than the previous";
				}
				else if (difference > lastDifference) {
					std::cout << "Further away than the previous";
				}
			}


			std::cout << "\n";

			if (difference == 0) { // If difference is 0 ie. the correct number was guessed, break the program
				break;
			}
			// ======================================= 
		}

		// Score
		if (scoreBase > numberOfGuesses * 350) { // This if satement makes sure that subtracting 'numberOfGuesses' * 350 from the score base, does not go below zero  
			scoreTotal = scoreBase - numberOfGuesses * 350; // The final score is set by taking the score base (currently set to 10000) and subtracting a value * the amount of guesses 
		}
		else { // If above would result in something less than 0, it will set it to 0 automatically
			scoreTotal = 0; 
		}

		ShowConsoleCursor(false); // Hide cursor

		std::cout << "\n\t" << "Attempts: " << numberOfGuesses << "\n"; // Show number of guesses
		std::cout << "\n\t" << "Score: " << scoreTotal << "\n\n"; // Show total score


		// == Quit or restart ====================
		delay(500);
		choices = { "Yes","No" };
		switch (arrowKeyMenu(choices, false, "Play again?\n", 1, false))
		{
		case 0: system("cls"); delay(500); break;
		case 1: system("cls"); playing = false; break;
		default: break;
		}

		// ======================================= */ 

		{
			system("cls");
			if (!playing) { break; }
		}
	}
}

