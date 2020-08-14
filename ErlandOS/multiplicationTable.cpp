#include "publicFunctions.h"
#include <iostream>

// Function for drawing the title 
void drawIntro() { 
	std::cout << "\n\n";
	std::cout << " __   __  __   __  ___      _______  ___   _______  ___      ___   _______  _______  _______  ___   _______  __    _        _______  _______  _______  ___      _______  "<<"\n";
	std::cout << "|  |_|  ||  | |  ||   |    |       ||   | |       ||   |    |   | |       ||   _   ||       ||   | |       ||  |  | |      |       ||   _   ||  _    ||   |    |       | "<<"\n";
	std::cout << "|       ||  | |  ||   |    |_     _||   | |    _  ||   |    |   | |       ||  |_|  ||_     _||   | |   _   ||   |_| |      |_     _||  |_|  || |_|   ||   |    |    ___| "<<"\n";
	std::cout << "|       ||  |_|  ||   |      |   |  |   | |   |_| ||   |    |   | |       ||       |  |   |  |   | |  | |  ||       |        |   |  |       ||       ||   |    |   |___  "<<"\n";
	std::cout << "|       ||       ||   |___   |   |  |   | |    ___||   |___ |   | |      _||       |  |   |  |   | |  |_|  ||  _    |        |   |  |       ||  _   | |   |___ |    ___| "<<"\n";
	std::cout << "| ||_|| ||       ||       |  |   |  |   | |   |    |       ||   | |     |_ |   _   |  |   |  |   | |       || | |   |        |   |  |   _   || |_|   ||       ||   |___    _"<<"\n";
	std::cout << "|_|   |_||_______||_______|  |___|  |___| |___|    |_______||___| |_______||__| |__|  |___|  |___| |_______||_|  |__|        |___|  |__| |__||_______||_______||_______|  |_|"<<"\n";
	std::cout << "\n\n\n\n";
}


void multiplicationTable() {
	
	system("cls"); // Clearing the screen
	setColor(red, black); // Setting color to red, with a black background
	drawIntro(); // Drawing title
		
	// Variables defining the size of the table
	int columns;
	int rows;  


	// === User input ================================
	setColor(red,black); // Setting the color, using a function in 'publicFunctions'
	std::cout << "Enter number of columns in table:\n"; // Ask for user input
	setColor(cyan, black); 
	columns = getIntInput(1,14); // Get a safe int input, function in 'publicFunctions'
	
	setColor(red, black); // Setting the color, using a function in 'publicFunctions'
	std::cout << "\nEnter number of rows in table:\n"; // Ask for user input
	setColor(cyan, black);
	rows = getIntInput(1,14); // Get a safe int input, function in 'publicFunctions'
	
	setColor(red, black);
	std::cout << "\n\n\n"; // line spacing
	// ===============================================


	// === Drawing the table =========================
	std::cout << "\t\t"; // Line spacing

	for (int i = 1; i < columns+1; i++) {  // for-loop for printing the numbers indicating columns, above the main table (starts at 1, and ends at 'columns' + 1, because the mult. table starts at 1)
		std::cout << i << "\t";
	}

	std::cout <<  "\n\n"; // Line spacing

	setColor(cyan, black);

	for (int j = 1; j < rows+1; j++) { // For loop for each row (again, starts at 1)

		setColor(red, black); 
		std::cout << "\t"  << j << "\t";  // Prints out the numbers indicating each row
		setColor(cyan, black);

		for (int i = 1; i < columns+1; i++) { // For loop for each column 
			std::cout << i * j << "\t"; // Prints out the product of the current column and row, creating the multiplication table
		}
		std::cout << "\n\n"; // Line spacing
	} 
	std::cout << "\n\n"; // Line spacing

	// ===============================================

	system("pause");
	system("cls");
}