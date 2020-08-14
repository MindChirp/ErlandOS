#include "hangmanFunctions.h"
#include "publicFunctions.h"

#include <array>
#include <iostream>


void hangman() {
	// == Variables == 
	std::string top = "  ^";
	std::string middle = "";
	std::string bottom = "";

	std::string word;
	std::string input;

	int wordLength;
	int wrongs = 0;
	int wrong = 0;

	int guessesLeft = 3;

	bool chooseWord;
	// ===============


	delay(100);
	system("cls");

	std::vector<std::string> choices;
	bool quit = false; 

	choices = { "Choose word manually ", "Random word ", "Quit " };
	switch (arrowKeyMenu(choices, false, "\n\n\tHow do you want to play? ", 0, false))
	{
	case 0: chooseWord = true; break;
	case 1: chooseWord = false; break;
	default: quit = true;  break;
	}
	ShowConsoleCursor(false);

	if (!quit) {
		
		// == Set word ==
		
		system("cls");

		if (chooseWord) {

			std::cout << "\tPlease enter a word of your choice: \n\t> ";
			ShowConsoleCursor(true);
			
			std::cin >> word;
			
			std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			ShowConsoleCursor(false);
		}
		else {
			word = getRandomWord();
		}

		wordLength = word.length();
		// ==============
	

		// == Setting up vectors ==
		std::vector<char> answerVector(wordLength, '_'); // Creates a vector that will contain the correctly guessed letters, is filled with '_' to visualize the missing letters
		std::vector<char> wrongChars(8, ' '); // Creates a vector that will contain the wrong guessed letters, is only 8 long, since you cant get more wrongs
		// ========================
	

		while (true) { // Game loop
			draw(wrongChars, wrongs, guessesLeft);
			std::cout << "\t";
			for (int i = 0; i < wordLength; i++) {  //Checks words length and writes '_' or the correct letter 
				std::cout << answerVector[i] << " "; // For example "_ _ l l _ " <- (hello)
			}
			std::cout << "\n\n";// << std::endl;

		
			ShowConsoleCursor(true);

			std::cout << "\t> ";
			input = getCharInput('a', 'z');

			ShowConsoleCursor(false);

			std::vector<char> wordVectorBeforeLower(word.begin(), word.end()); //Splitting up the word (a sring) into a char array
			std::vector<char> wordVector(wordVectorBeforeLower.size());

			for (int i = 0; i < wordVectorBeforeLower.size(); i++) {
				wordVector[i] = tolower(wordVectorBeforeLower[i]);
			}

		
			std::vector<char> inputVector(input.begin(), input.end()); //Splitting up the input (a string) into a char array

			int inputLength = inputVector.size(); //Get the length of the input

			if (inputLength == 1) {			//Checks if the input is only one letter
				for (int i = 0; i < wordLength; i++) {			//Selects every position of the word (i is position)

					if (inputVector[0] == tolower(wordVector[i])) {		//Checks if the input corresponds to any of the letters of the word
						answerVector[i] = inputVector[0];		//If so, set the answers char in the correct spot (i) to equal input 
						wrong -= 1;		//Subtracts from wrong
					}
					else {
						wrong += 1;    //Adds to wrong
					}
				}
			}
			else {
				if (input == word) {
					for (int i = 0; i < wordLength; i++) {
						answerVector[i] = inputVector[i];
					}
				}
				else {
					guessesLeft -= 1; //Wrong guess 
				}
			}

			if (wrong == wordLength) { //If wrong is as large as the wordLength the character is not in the word, everytime the for loop above finds a correct character it substracts 1, and everytime it doesnt find it it adds 1   
				wrongChars[wrongs] = inputVector[0];
				wrongs += 1;
			}
			wrong = 0;

			if ((wrongs == 7) || (guessesLeft == 0)) {
				loose(word);
				break;
			}
			if (answerVector == wordVector) {
				win(word);
				break;
			}
		}

		delay(1000);
		system("pause");
		system("cls");
	}
}