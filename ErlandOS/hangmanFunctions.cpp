#pragma once

#include "hangmanFunctions.h"

#include <iostream>
#include <array>
#include <fstream>
#include <stdlib.h>   // Random
#include <time.h> 


std::string getRandomWord() {
	srand((unsigned int)time(NULL));

	// === Read from file & write to vector ========
	std::string line;
	std::ifstream readFromFile;
	std::vector<std::string> lines;
	std::string output;

	readFromFile.open("words.txt"); // Open the file containing the words

	if (readFromFile.fail()) {  // If reading fails, file does not exist
		std::cout << "File doesnt exist\n";
	}
	else {
		int lineNumb = 0;
		while (!readFromFile.eof()) // To get you all the lines.
		{
			getline(readFromFile, line); // Read the current line
			lines.push_back(line); // Add the line (the word) to the end of the 'lines' array
		}
		int randomNum = rand() % lines.size(); // Generate a random number
		output = lines[randomNum]; // Choose a word from the 'lines' array based on the random number  
	}
	return(output); // Return the word
	// ===============================================
}

void draw(std::vector<char> chars, int wrongs, int guessesLeft) {


	// Sprite bases for the man
	std::string top = "  ^";
	std::string middle = "    ";
	std::string bottom = "    ";


	switch (wrongs) { // Choosing sprites for the man depending on the number of wrong guesses
		case 1: top = "  O"; break;
		case 2: top = "  O"; middle = "  | ";  break;
		case 3: top = "  O"; middle = " /| ";  break;
		case 4: top = "  O"; middle = " /|\\"; break;
		case 5: top = "  O"; middle = " /|\\"; bottom = " /  ";  break;
		case 6: top = "  O"; middle = " /|\\"; bottom = " / \\"; break;
		default: break;
	}



	system("cls"); // Drawing the table
	std::cout << "\n\n\t ____________________________  \n";
	std::cout << "\t| - Hangman 2 - |            | \n";
	std::cout << "\t|_______________|            | \n";
	std::cout << "\t|                            | \n";
	std::cout << "\t|               ______       | \n";
	std::cout << "\t|              |/     |      | \n";
	std::cout << "\t|              |    " << top << "      |\n";
	std::cout << "\t|              |    " << middle << "     |\n";
	std::cout << "\t|              |    " << bottom << "     |\n";
	std::cout << "\t|_____________/|_            | \n";
	std::cout << "\t|                |           | \n";
	std::cout << "\t|                |~~~~~~~~~~~| \n";
	std::cout << "\t|________________|___________| \n";
	std::cout << "\t| Word guesses left: " << guessesLeft << "       |\n";
	std::cout << "\t|----------------------------| \n";
	std::cout << "\t| Wrong letters:             | \n";
	std::cout << "\t| ";

	for (int i = 0; i < 6; i++) { // For loop for drawing the wrong letters
		std::cout << chars[i] << " "; // Drawing the wrong letters, with a space between
	}

	std::cout << "               |\n";
	std::cout << "\t|____________________________| \n";
	std::cout << "\n" << std::endl;
}

void loose(std::string i) {
	// Drawing the loose screen

	system("cls"); // Clear the console
	std::cout << "\n\n\tThe correct word was \"" << i << "\"\n\n"; // Print out what the correct word was
		
	  std::cout << "\t                                    $$\\                                         $$\\  \n"
				<< "\t                                    $$ |                                        $$ | \n"
				<< "\t$$\\   $$\\  $$$$$$\\  $$\\   $$\\       $$ | $$$$$$\\   $$$$$$\\   $$$$$$$\\  $$$$$$\\  $$ | \n"
				<< "\t$$ |  $$ |$$  __$$\\ $$ |  $$ |      $$ |$$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ $$ | \n"
				<< "\t$$ |  $$ |$$ /  $$ |$$ |  $$ |      $$ |$$ /  $$ |$$ /  $$ |\\$$$$$$\\  $$$$$$$$ |\\__| \n"
				<< "\t$$ |  $$ |$$ |  $$ |$$ |  $$ |      $$ |$$ |  $$ |$$ |  $$ | \\____$$\\ $$   ____|     \n"
				<< "\t\\$$$$$$$ |\\$$$$$$  |\\$$$$$$  |      $$ |\\$$$$$$  |\\$$$$$$  |$$$$$$$  |\\$$$$$$$\\ $$\\  \n"
				<< "\t \\____$$ | \\______/  \\______/       \\__| \\______/  \\______/ \\_______/  \\_______|\\__|  \n"
				<< "\t$$\\   $$ |                                                                           \n"      
				<< "\t\\$$$$$$  |                                                                           \n"
				<< "\t \\______/                                                                             \n";
	  std::cout << "\t\n\n\n\n";
}

void win(std::string i) {
	// Drawing the win screen

	system("cls"); // Clear the console

	std::cout	<< "\n\n\tThe word was, as you guessed \"" << i << "\"\n\n"; // Print out the word 

	std::cout	<< "\t                                                  $$\\           $$\\  \n"
				<< "\t                                                  \\__|          $$ | \n"
				<< "\t$$\\   $$\\  $$$$$$\\  $$\\   $$\\       $$\\  $$\\  $$\\ $$\\ $$$$$$$\\  $$ | \n"
				<< "\t$$ |  $$ |$$  __$$\\ $$ |  $$ |      $$ | $$ | $$ |$$ |$$  __$$\\ $$ | \n"
				<< "\t$$ |  $$ |$$ /  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |\\__| \n"
				<< "\t\\$$$$$$$ |\\$$$$$$  |\\$$$$$$  |      \\$$$$$\\$$$$  |$$ |$$ |  $$ |$$\\  \n"
				<< "\t \\____$$ | \\______/  \\______/        \\_____\\____/ \\__|\\__|  \\__|\\__| \n"
				<< "\t$$\\   $$ |                                                           \n"
				<< "\t\\$$$$$$  |                                                           \n"
				<< "\t \\______/                                                            \n";

	std::cout	<< "\n\n\n\n";
}