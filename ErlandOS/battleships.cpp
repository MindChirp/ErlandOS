#include "publicFunctions.h"

#include <iostream>
#include <array>
#include <stdlib.h>   // Random
#include <time.h> 




// == Variables ==
#pragma region variables

int defaultPrimaryColor = white;

// == Defining the players' boards ==
const int boardSize = 10;

int boardP1[boardSize][boardSize];
int boardP2[boardSize][boardSize];
// ==================================*/


// == Board offset variables ==
int defaultxOffset = 6;
int defaultyOffset = 6;
int distanceBetweenTables = 80;
// ============================*/


// == Bools for where ships can be played ==
bool canPlace;
bool canPlaceLeft;
bool canPlaceRight;
bool canPlaceUp;
bool canPlaceDown;
// =========================================*/


// == Bools for playing against the computer ==
bool againstComp;
bool showCompBoats = false;

const int spriteHeight = 1;
const int spriteWidth = 2;

bool gameWon = false;
int winner = 0;

COORD attackCoord;
COORD lastCompHit = {0,0}; 

bool compHit = false;
int lastCompDirection;
bool compDirectionSuccessfull = false;
// ============================================*/


enum ships { carrier = 1, battleship, cruiser, submarine, destroyer }; // Enum containing the number for each ship, 1-5.

int length[6]{ 0,5,4,3,2,2 }; // Array containing the length of each ship, the ships are 1-5. length[0] is not in use, and is therefore 0. Practically speaking the array starts at 1.
	   // Ship - 1 2 3 4 5

int shipsLeft[2][6]{ // 2D array containing the amount of ships left for each player. shipsLeft[player][ship type]
	{0, 1, 2, 2, 1, 4}, // player 1
	{0, 1, 2, 2, 1, 4}  // player 2
};


// == Sprites =========
#pragma region sprites

// These sprites build up the GUI-boards, the sprites are 1*2, but the arrays are 2*2, the second row contains color information 
// Here the chars that are making up the sprites are blank, but they have a background color, making filled squares

char spriteSea [spriteHeight+1][spriteWidth]{
	{' ',' '}, // Sprite
	{'D','D'}, // { Color, Background Color}
};

char spriteShip[spriteHeight + 1][spriteWidth]{
	{' ',' '}, // Sprite
	{'K','K'}, // { Color, Background Color}
};

char spriteHit [spriteHeight + 1][spriteWidth]{
	{' ',' '}, // Sprite
	{'M','M'}, // { Color, Background Color}
};

char spriteMiss[spriteHeight + 1][spriteWidth]{
	{' ',' '}, // Sprite
	{'I','I'}, // { Color, Background Color
};


#pragma endregion sprites
// ====================*/

#pragma endregion variables
// ===============*/

// == Functions ==
#pragma region functions

// Function to get player input coordinates, both for placement and attack
COORD getCOORDInput(char startChar, char endChar, int startInt, int endInt, std::string msg) {
	// Basically the 'getCharInput' and 'getIntInput' functions in 'publicFunctions' combined
	COORD outputCOORD;
	std::cout << msg;
	while (true) {

		char inputChar;
		std::cout << "  \n> ";
		std::cin >> inputChar;

		if (!std::cin.good() || (tolower(inputChar) < startChar) || (tolower(inputChar) > endChar)) {
			setColor(red, black);
			std::cout << "  Error: invalid Y - Please try again: \n";
			setColor(defaultPrimaryColor, black);
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}
		else {
			outputCOORD.Y = (int(tolower(inputChar)) - 97);

			int inputInt;
			std::cin >> inputInt;
			if (!std::cin.good() || (inputInt < startInt) || (inputInt > endInt)) {
				setColor(red, black);
				std::cout << "  Error: invalid X - Please try again: \n";
				setColor(defaultPrimaryColor, black);
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
			}
			else {
				outputCOORD.X = inputInt;
				return(outputCOORD);
			}
		}
	}
}

COORD compChooseAttackCoord() {
	int attackDirection = 0;
	while (true) {
		attackCoord.X = rand() % boardSize;	// Get a random X coordinate
		attackCoord.Y = rand() % boardSize; // Get a random Y coordinate

			if (compDirectionSuccessfull == true){   // If the last direction the computer went after a hit was successful
				attackDirection = lastCompDirection; // Continue in the same direction

				switch (attackDirection)
				{
				case 0: if (lastCompHit.Y - 1 >= 0)        { attackCoord.X = lastCompHit.X; attackCoord.Y = lastCompHit.Y - 1; } break; // | Adds/subtracts 1 to the desired axis depending on the direction,
				case 1: if (lastCompHit.Y + 1 < boardSize) { attackCoord.X = lastCompHit.X; attackCoord.Y = lastCompHit.Y + 1; } break; // | but only if that location is within the board. 
				case 2: if (lastCompHit.X - 1 >= 0)        { attackCoord.X = lastCompHit.X - 1; attackCoord.Y = lastCompHit.Y; } break; // | If it is outside the board, the attack coordinates will be random 
				case 3: if (lastCompHit.X + 1 < boardSize) { attackCoord.X = lastCompHit.X + 1; attackCoord.Y = lastCompHit.Y; } break; // | as set above.
				default: break;
				}
			}

		if (boardP1[attackCoord.Y][attackCoord.X] < 6) {  break; } // Checks if the coordinate to attack is < 6 ( that means it has not been attacked before ). If so, break the while loop.
		else { compDirectionSuccessfull = false; } // If the location has been hit before, set 'compDirectionSuccessfull' to false, so the computer will have to use a random coordinate
	}
	lastCompDirection = attackDirection;
	return(attackCoord);
}

COORD compChoosePlaceCoord() {
	COORD outputCOORD;
	outputCOORD.Y = rand() % boardSize; // Random Y coordinate
	outputCOORD.X = rand() % boardSize; // Random X coordinate
	return(outputCOORD);
}

int compChoosePlaceDir() {
	bool good; 
	int output;
	while (true) {	
		output = rand() % 4; // Pick a random direction

		switch (output) // The canPlace.. variables are bools, this switch sets the bool 'good' to equal the canPlace.. in the direction randomly chosen above
		{ 
		case 0: good = canPlaceUp;    break; 
		case 1: good = canPlaceDown;  break;  
		case 2: good = canPlaceLeft;  break;  
		case 3: good = canPlaceRight; break;  
		default: good = false;  break; 
		}
		if (good) { // If the canPlace.. corresponding to the direction was true, 'good' will be true, and the while loop will be stopped. If the canPlace.. was false, the while loop will make it try again
			break;
		}
	}
	return(output);
}

int getDirInput() {
	std::cout << "  What direction? ";

	// Only shows the possible directions to place the ship
	if (canPlaceUp) std::cout <<    "U = up, "   ;
	if (canPlaceDown) std::cout <<  "D = down, " ;
	if (canPlaceLeft) std::cout <<  "L = left, " ;
	if (canPlaceRight) std::cout << "R = right, ";

	std::cout << "  \n> "; 

	while (true) {

		char input;
		std::cin >> input; // Get user input
		

		// Checks if user input is invalid, OR if it does not equal any legal letters, OR if the letter corresponding to direction that is not possbile is entered
		if (!std::cin.good() || ((tolower(input) != 'u') && (tolower(input) != 'd') && (tolower(input) != 'l') && (tolower(input) != 'r')) || (tolower(input) == 'u' && !canPlaceUp) || (tolower(input) == 'd' && !canPlaceDown) || (tolower(input == 'l' && !canPlaceLeft) || (input) == 'r' && !canPlaceRight) ) {
			setColor(red, black); // Set color to red for a fancy error message
			std::cout << "Error: invalid direction - Please try again: \n"; // Print error message
			setColor(defaultPrimaryColor, black); // Set color back to the defaultPrimaryColor
			std::cin.clear(); // Clear the cin error flags
			std::cin.ignore(std::cin.rdbuf()->in_avail()); // Clear read buffer
		}
		else { // If the input is good

			int output = 0; 

			switch (tolower(input))  // Using tolower(), so the capitalization of the input is irrelevant, for a better user experience
			{
			case 'u': output = 0;  break; // Set the 'output' int to 0 if 'u' is entered (Up)
			case 'd': output = 1;  break; // Down (1)
			case 'l': output = 2;  break; // Left (2)
			case 'r': output = 3;  break; // Right (3)
			default:  break;
			}
			return(output); // Return the 'output' int ie. the direction
		}
	}
}

void drawShipList(int player) {
	// Draws the list of available ships

	std::cout << "   _____________________________\n";
	std::cout << "  | Ship        | Size | Amount |\n";
	std::cout << "  |             |      |        |\n";
	std::cout << "  | Carrier     | 5    | " << shipsLeft[player-1][carrier]    << "      |\n"; // Draws the amount of ships left of each type, using the 2D arrays defined earlier. it is 'player-1' because the players are identified as 1 and 2, but the array is 0 and 1
	std::cout << "  | Battleship  | 4    | " << shipsLeft[player-1][battleship] << "      |\n"; 
	std::cout << "  | Cruiser     | 3    | " << shipsLeft[player-1][cruiser]    << "      |\n";
	std::cout << "  | Submarine   | 2    | " << shipsLeft[player-1][submarine]  << "      |\n";
	std::cout << "  | Destroyer   | 2    | " << shipsLeft[player-1][destroyer]  << "      |\n";
	std::cout << "  |_____________|______|________|\n";
	std::cout << "\n";

}

void drawSprite(char sprite[spriteHeight + 1][spriteWidth], int x, int y) {

	COORD xy;
		
	int col = int(sprite[spriteHeight][0]) - 65;  // Extract the color and background color from the sprite arrays. They are defined with chars, ('A' - 'P'), the ASCII value for 'A' is 65. If 65 is subtracted from the char, the values will be from 0-15
	int colBG = (int(sprite[spriteHeight][1]) - 65); // ^

	setColor(col, colBG); // Set the color

	for (int j = 0; j < spriteHeight; j++) { // For loop for the sprites height (its currently just 1, so the for loop is not neccesarry, but the sprite sizes can theoretically be changed)
		for (int i = 0; i < spriteWidth; i++) { // For loop for the sprites width (also not completely necessary here, but it is there for expandability)
			xy.Y = y + j;  // Set the X coordinate for drawing, the (the 'x' argument is the origin point of the sprite) 
			xy.X = x + i;  // Set the Y coordinate for drawing, the (the 'y' argument is the origin point of the sprite) 
			setCursorPos(xy); // Set the cursor to the current coordinates for drawing the sprite
			std::cout << sprite[j][i]; // Draw the current part of the sprite on the screen
		}
		std::cout << "\n";
	}
	setColor(defaultPrimaryColor, black); // Set the color back to default
}

void drawInt(int number, int x, int y, int col) {
	// Function to draw an int at a specified position on the screen

	COORD xy; // Define the coordinates

	xy.X = x; // Set the x coordinate
	xy.Y = y; // Set the y coordinate

	setColor(col, black);
	setCursorPos(xy);    // Set the cursors position
	std::cout << number; // Print the number

	setColor(defaultPrimaryColor, black); // Set color back to default
}

void drawChar(char letter, int x, int y, int col) {
	// Function to draw a char at a specified position on the screen

	COORD xy; // Define the coordinates

	xy.X = x; // Set the x coordinate
	xy.Y = y; // Set the y coordinate

	setColor(col, black);
	setCursorPos(xy); // Set the cursors position
	std::cout << letter; // Print the number

	setColor(defaultPrimaryColor, black); // Set color back to default
}


void drawStrNumStr(std::string text1, int number, std::string text2, int x, int y, int col) {
	// Function to draw first a string, then an int, then another string at a specified position on the screen

	COORD xy;// Define the coordinates

	xy.X = x; // Set the x coordinate
	xy.Y = y; // Set the y coordinate

	setColor(col, black);
	setCursorPos(xy); // Set the cursors position
	std::cout << text1 << number << text2; //Prints text

	setColor(defaultPrimaryColor, black); // Set color back to default
}

void drawTable(int player, int xOffset, int yOffset,  bool showShips) {

	drawStrNumStr("Player ", player, "'s board:" , xOffset, yOffset-4, defaultPrimaryColor); // Draw a header for the board, informing the players whoose board it is.


	for (int i = 0; i < boardSize; i++) { // For loop for drawing the X coordinates above the board
		drawInt(i, i * (spriteWidth+2) + xOffset, yOffset - 2, defaultPrimaryColor); // Drawing the X coordinates (numbers)
	}

	for (int j = 0; j < boardSize; j++) { // For loop for the height of the board

		drawChar(char(j) + 65, xOffset - 3, j * (spriteHeight+1) + yOffset, defaultPrimaryColor); // Drawing the Y coordinates (letters) before each row of the board

		for (int i = 0; i < boardSize; i++) { // For loop for the width of the board

			if (player == 1) { // For player 1

				switch (boardP1[i][j]) { // Get value of the current coordinate on the board
				case 0:	 drawSprite(spriteSea,  j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break; // If it is 0 (sea),  run the 'drawSprite' function, with the sea sprite
				case 6:  drawSprite(spriteMiss, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break; // If it is 6 (miss), run the 'drawSprite' function, with the miss sprite
				case 7:  drawSprite(spriteHit,  j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break; // If it is 7 (hit),  run the 'drawSprite' function, with the hit sprite
				default:  if (showShips) { drawSprite(spriteShip, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); } // If showShips is true, run the 'drawSprite' function, with the ship sprite
					     else { drawSprite(spriteSea, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); } // If not, use the sea sprite
					   break;
				}
			}
			else if (player == 2) { // For player 2, the code is identical to that of player 1, apart from what board is used
				switch (boardP2[i][j]) { 
				case 0:	 drawSprite(spriteSea, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break;
				case 6:  drawSprite(spriteMiss, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break;
				case 7:  drawSprite(spriteHit, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); break;
				default:  if (showShips) { drawSprite(spriteShip, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); }
					   else { drawSprite(spriteSea, j * (spriteWidth + 2) + xOffset, i * (spriteHeight + 1) + yOffset); }
					   break;
				}
			}
		}
	}
}

void checkIfPlaceable(int player, COORD coordinates, int length) {

	if (player == 1){ // Check which player

		if (boardP1[coordinates.Y][coordinates.X] == 0) {//Check if place position is empty
			canPlace = true;

			canPlaceUp = true;
			canPlaceDown = true;
			canPlaceLeft = true;
			canPlaceRight = true;

			// Check up
			if (coordinates.Y - length >= 0) {
				for (int i = 0; i < length; i++) {
					if (boardP1[coordinates.Y - i][coordinates.X] != 0) {
						canPlaceUp = false;
					}
				}
			} else canPlaceUp = false;

			// Check down
			if (coordinates.Y + length <= boardSize) {
				for (int i = 0; i < length; i++) {
					if (boardP1[coordinates.Y + i][coordinates.X] != 0) {
						canPlaceDown = false;
					}
				}
			} else canPlaceDown = false;

			// Check left
			if (coordinates.X - length >= 0) {
				for (int i = 0; i < length; i++) {
					if (boardP1[coordinates.Y][coordinates.X - i] != 0) {
						canPlaceLeft = false;
					}
				}
			} else canPlaceLeft = false;

			// Check right
			if (coordinates.X + length <= boardSize) {
				for (int i = 0; i < length; i++) {
					if (boardP1[coordinates.Y][coordinates.X + i] != 0) {
						canPlaceRight = false;
					}
				}
			} else canPlaceRight = false;
		}
		else {
			canPlace = false;
		}

		if (!canPlaceUp && !canPlaceDown && !canPlaceLeft && !canPlaceRight) {
			canPlace = false;
		}

	}
	else if (player == 2) {
		if (boardP2[coordinates.Y][coordinates.X] == 0) {//Check if place position is empty
			canPlace = true;

			canPlaceUp = true;
			canPlaceDown = true;
			canPlaceLeft = true;
			canPlaceRight = true;

			// Check up
			if (coordinates.Y - length >= 0) {
				for (int i = 0; i < length; i++) {
					if (boardP2[coordinates.Y - i][coordinates.X] != 0) {
						canPlaceUp = false;
					}
				}
			} else canPlaceUp = false;

			// Check down
			if (coordinates.Y + length <= boardSize-1) {
				for (int i = 0; i < length; i++) {
					if (boardP2[coordinates.Y + i][coordinates.X] != 0) {
						canPlaceDown = false;
					}
				}
			} else canPlaceDown = false;

			// Check left
			if (coordinates.X - length >= 0) {
				for (int i = 0; i < length; i++) {
					if (boardP2[coordinates.Y][coordinates.X - i] != 0) {
						canPlaceLeft = false;
					}
				}
			} else canPlaceLeft = false;

			// Check right
			if (coordinates.X + length <= boardSize-1) {
				for (int i = 0; i < length; i++) {
					if (boardP2[coordinates.Y][coordinates.X + i] != 0) {
						canPlaceRight = false;
					}
				}
			} else canPlaceRight = false;

		}
		else {
			canPlace = false;
		}
	}
}

void placeShip(int player, int shipType, int shipSize, COORD placeCoords) {

	checkIfPlaceable(player, placeCoords, shipSize); // Run function to check directions the ship can be placed
	int direction;

	if (canPlace) { // If the ship can be placed at the coordinate at all
		shipsLeft[player - 1][shipType] -= 1;  // Subtracting 1 ship of the current ship type, from the current player

		if (player == 1) { // Player 1
			direction = getDirInput();
			boardP1[placeCoords.Y][placeCoords.X] = shipType; // Placing the origin of the ship

			if (direction == 0) { // up
				for (int i = 0; i < shipSize; i++) { // For loop 'going up' in the board array
					boardP1[placeCoords.Y-i][placeCoords.X] = shipType;  // Set current position in the array to the ship type (1 - 5)
				}
			}
			
			if (direction == 1) { // down
				for (int i = 0; i < shipSize; i++) { // For loop 'going down' in the board array
					boardP1[placeCoords.Y + i][placeCoords.X] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}

			if (direction == 2) { // left
				for (int i = 0; i < shipSize; i++) { // For loop 'going left' in the board array
					boardP1[placeCoords.Y][placeCoords.X - i] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}

			if (direction == 3) { // right
				for (int i = 0; i < shipSize; i++) { // For loop 'going right' in the board array
					boardP1[placeCoords.Y][placeCoords.X + i] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}


		}
		else if (player == 2) { //Player 2

			if (!againstComp) { // If not against computer
			direction = getDirInput(); // Get user input for direction
			} else {
			direction = compChoosePlaceDir(); // If playing against computer, run function to let it pick a random possible direction
			}

			boardP2[placeCoords.Y][placeCoords.X] = shipType; // Placing the origin of the ship
			
			if (direction == 0) { // up
				for (int i = 0; i < shipSize; i++) { // For loop 'going up' in the board array
					boardP2[placeCoords.Y - i][placeCoords.X] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}

			if (direction == 1) { // down
				for (int i = 0; i < shipSize; i++) { // For loop 'going down' in the board array
					boardP2[placeCoords.Y + i][placeCoords.X] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}

			if (direction == 2) { // left
				for (int i = 0; i < shipSize; i++) { // For loop 'going left' in the board array
					boardP2[placeCoords.Y][placeCoords.X - i] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}

			if (direction == 3) { // right
				for (int i = 0; i < shipSize; i++) { // For loop 'going right' in the board array
					boardP2[placeCoords.Y][placeCoords.X + i] = shipType; // Set current position in the array to the ship type (1 - 5)
				}
			}
		}
	} // If the ship could not be placed, the number of ships will not be subtracted, so the while loops in 'placeShips' will automatically ask for it to be placed again


	if (!againstComp || player == 1) {  // If not playing against the computer, OR if its player 1's turn
		system("cls");  // Clear console
		drawTable(player, defaultxOffset, defaultyOffset, true); // Draw the table to update it
		std::cout << "\n"; 
		drawShipList(player); // Draw the list of ships to update it
	}
}

void placeShips(int player) {

	COORD chooseCoord;

	// Place Carrier
	while (shipsLeft[player - 1][carrier]) { // As long as there are ships left of this type, run code below
		
		if (againstComp && player == 2) { // If against computer, and it is the computers turn
			chooseCoord = compChoosePlaceCoord(); // Run function to let it choose coordinate to place ship on
		}
		else { // If not against computer, or if it is player 1's turn
			std::cout << "  Place a Carrier:\n"; // Announce the ship type to place
			chooseCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize - 1, "  What coordinates? examples:\"A0\" or \"B3\". "); // Get user input for the coordinate to place ship.
		}
		placeShip(player, carrier, length[carrier], chooseCoord); // Run function to place the current ship on chosen coordinates
	}

	// Code below is the same as above, but with different ships

	// Place Battleship
	while (shipsLeft[player - 1][battleship]) {
	
		if (againstComp && player == 2) {
			chooseCoord = compChoosePlaceCoord();
		}
		else {
			std::cout << "  Place a Battleship:\n";
			chooseCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize - 1, "  What coordinates? examples:\"A0\" or \"B3\". ");
		}
		placeShip(player, battleship, length[battleship], chooseCoord);
	}

	// Place Cruisers
	while (shipsLeft[player - 1][cruiser]) {
	
		if (againstComp && player == 2) {
			chooseCoord = compChoosePlaceCoord();
		}
		else {
			std::cout << "  Place a Cruiser:\n";
			chooseCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize - 1, "  What coordinates? examples:\"A0\" or \"B3\". ");
		}
		placeShip(player, cruiser, length[cruiser], chooseCoord);
	}

	// Place Submarines
	while (shipsLeft[player - 1][submarine]) {
	
		if (againstComp && player == 2) {
			chooseCoord = compChoosePlaceCoord();
		}
		else {
			std::cout << "  Place a Submarine:\n";
			chooseCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize - 1, "  What coordinates? examples:\"A0\" or \"B3\". ");
		}
		placeShip(player, submarine, length[submarine], chooseCoord);
	} 

	// Place Destroyers
	while (shipsLeft[player - 1][destroyer]) {
	
		if (againstComp && player == 2) {
			chooseCoord = compChoosePlaceCoord();
		}
		else {
			std::cout << "  Place a Destroyer:\n";
			chooseCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize - 1, "  What coordinates? examples:\"A0\" or \"B3\". ");
		}
		placeShip(player, destroyer, length[destroyer], chooseCoord);
	}

}

void setup() {
	// == Board setup ======

	std::cout << " --Setup --\n\n";
	std::cout << " Player 1's board:\n\n";

	system("pause");
	system("cls");

	drawTable(1, defaultxOffset, defaultyOffset,true); // Draw player 1s board
	std::cout << "\n"; 
	drawShipList(1); // Draw the list showing all available ships 
	placeShips(1); // Run the function to place ships 

	system("pause");
	system("cls");

	if (!againstComp) { // If not playing against computer, let player 2 set up their board

	std::cout << " -- Setup --\n\n";
	std::cout << " Player 2's board:\n\n";
	system("pause");

	system("cls");
	
	drawTable(2, defaultxOffset, defaultyOffset, true); // Draw player 2s board
	std::cout << "\n";
	drawShipList(2);// Draw the list showing all available ships 
	}
	placeShips(2);// Run the function to place ships 

	if (!againstComp) { // Pause if not playing against computer
		system("pause");
	}
	// =====================*/
}

bool checkForWin(int board) {
	bool win = true; // win is set to true
		for (int i = 0; i < boardSize; i++) { // For loop for going through the y axis of the board
			for (int j = 0; j < boardSize; j++) { // For loop for going through the x axis of the board
				if (board == 1) { // Get board
					if ((boardP1[i][j] < 6) && (boardP1[i][j] > 0)) { // checks if there are any boats left on player 1s board
						win = false; // if so, make win false
					}
				} else if (board == 2) { // Get board
					if ((boardP2[i][j] < 6) && (boardP2[i][j] > 0)) { // checks if there are any boats left on player 2s board
						win = false; // if so, make win false
					}
				}
			}
		}		
	return(win);
}

void attack(int player) {

	int playerToAttack = 3 - player; // If player is 1, player to attack is 2. if player is 2, playyer to attack is 1. 3-1 and 3-2

	std::cout << "\n";

	if (!againstComp) {  // If not against computer

		// Print message between turns, so the players can "swap places"
		system("cls");
		std::cout << "\n\t-- Player " << player << "'s turn to attack --\n\n";
		system("pause");
		system("cls");

		
		std::cout << "-- Player " << player << "'s attack --";
		drawTable(playerToAttack, defaultxOffset, defaultyOffset, false); // Draw opponents board 
		drawTable(player, defaultxOffset + distanceBetweenTables, defaultyOffset, true); // Draw current players board

		attackCoord = getCOORDInput('a',char(97 +boardSize),0,boardSize,"\n\n Where to attack?\n"); // Get player input for coordinates to attack
	}
	else { // If playing against computer
		if (player == 2) { // If it is the computers turn
			attackCoord = compChooseAttackCoord(); // Run funtion for the computer to choose attack coordinate 
		} 
		else {
			system("cls");
			std::cout << "-- Player 1's attack --";
			drawTable(playerToAttack, defaultxOffset, defaultyOffset, false); // Draw the computers board 
			drawTable(player, defaultxOffset + distanceBetweenTables, defaultyOffset, true); // Draw current players board
			
			if (showCompBoats) { // If the setting for showing computers boats is enabled
			drawTable(playerToAttack, defaultxOffset + distanceBetweenTables * 2, defaultyOffset, true); // Draw the computers board INCLUDING the ships
			}
			attackCoord = getCOORDInput('a', char(97 + boardSize), 0, boardSize, "\n\n Where to attack?\n"); // Get player input for coordinates to attack
		}
	}


	if (player == 1) { // If it is player 1's turn
		if ((boardP2[attackCoord.Y][attackCoord.X] > 0)&&(boardP2[attackCoord.Y][attackCoord.X] < 6)) { // Checks if the chosen coordinate contains a number between 1 and 5 (ships)
			boardP2[attackCoord.Y][attackCoord.X] = 7; // If so, set the board value of the chosen coordinate to 7, 7 represents a hit.
			system("cls"); // Clear the screen;
			std::cout << "-- Player " << player << "'s attack --";
			drawTable(playerToAttack, defaultxOffset, defaultyOffset, false); // Draw opponents board
			drawTable(player, defaultxOffset+ distanceBetweenTables, defaultyOffset, true); // Draw current players' board

			std::cout << "\n Hit!\n"; // Announce a hit

		} else if (boardP2[attackCoord.Y][attackCoord.X] == 0) { // Checks if the chosen coordinate contains a 0, 0 represents water.
			boardP2[attackCoord.Y][attackCoord.X] = 6; // Set the board value of the chosen coordinate to 6, 6 represents a hit.
			system("cls"); // Clear the screen;
			std::cout << "-- Player " << player << "'s attack --";
			drawTable(playerToAttack, defaultxOffset, defaultyOffset, false); // Draw opponents board
			drawTable(player, defaultxOffset+ distanceBetweenTables, defaultyOffset, true); // Draw current players' board
	
			std::cout << "\n Miss!\n"; // Announce a miss
		}
		else  { // This will return true if the coordinate contains a 6 or 7, hit or miss
			std::cout << "\n You already guessed that...\nThats on you...\n\n";  // Announce that this coordinate have been chosen before
		}

		if (checkForWin(2)) { // Runs function to check if player 1 has won (the argument is 2 representing player 2's board)
			std::cout << "\n Player 1 won!\n"; // If so, announce it
			gameWon = true; // Set gameWon to true to end the game afterwards
			winner = 1; // Set the winner to be player 1
		}
		delay(800);
	}
	else if ((player == 2) && !againstComp) {  // If it is player 2's turn - And only if playing 2 player mode
		// Same code as above, just with the players swapped, this could definitely be made more compact, sharing more code, but i did not have time for that 
		if ((boardP1[attackCoord.Y][attackCoord.X] > 0) && (boardP1[attackCoord.Y][attackCoord.X] < 6)) {
			boardP1[attackCoord.Y][attackCoord.X] = 7; 
			system("cls");
			std::cout << "-- Player " << player << "'s attack --";
			drawTable(playerToAttack, defaultxOffset, defaultyOffset, false);
			drawTable(player, defaultxOffset+ distanceBetweenTables, defaultyOffset, true);
			std::cout << "\n Hit!\n";
		}
		else if (boardP1[attackCoord.Y][attackCoord.X] == 0) {
			boardP1[attackCoord.Y][attackCoord.X] = 6; 
			system("cls");
			std::cout << "-- Player " << player << "'s attack --";
			drawTable(playerToAttack, defaultxOffset, defaultyOffset,false);
			drawTable(player, defaultxOffset+ distanceBetweenTables, defaultyOffset, true);
			std::cout << "\n Miss!\n";
		} else  {
			std::cout << "\n You already guessed that...\nThats on you...\n\n";
		}

		if (checkForWin(1)) {
			std::cout << "\n Player 2 won!\n";
			gameWon = true;
			winner = 2;
		}
		delay(800);
	}

	else if (againstComp) { // Checks if playing against computer
		delay(500);
		// Very similar to the blocks above
		if ((boardP1[attackCoord.Y][attackCoord.X] > 0) && (boardP1[attackCoord.Y][attackCoord.X] < 6)) {
			boardP1[attackCoord.Y][attackCoord.X] = 7; // 7 = hit
			std::cout << "\n The computer hit!\n"; 
			drawTable(2, defaultxOffset, defaultyOffset, false);
			drawTable(1, defaultxOffset + distanceBetweenTables, defaultyOffset, true);
			lastCompHit = attackCoord; // Stores the location of the hit    
			compDirectionSuccessfull = true; // This makes the computer aware that it hit, and can use that the next round
		}
		else if (boardP1[attackCoord.Y][attackCoord.X] == 0) {
			boardP1[attackCoord.Y][attackCoord.X] = 6; // 6 = miss
			std::cout << "\n The computer missed!\n";
			drawTable(2, defaultxOffset, defaultyOffset, false);
			drawTable(1, defaultxOffset + distanceBetweenTables, defaultyOffset, true);
			compDirectionSuccessfull = false;

		}

		if (checkForWin(1)) {
			system("cls");
			std::cout << "\n The computer won!\n";
			drawTable(2, defaultxOffset, defaultyOffset, false);
			drawTable(1, defaultxOffset + distanceBetweenTables, defaultyOffset, true);
			gameWon = true;
			winner = 2;
		}
		delay(800);
	}
}


// I have not commented on the settings menus since they were not really required, and i did not have time
void infoScreenBattleships() {
	system("cls");
	std::cout << "\n\n\tProtip:\tIn the settings menu, you can enable seeing the opponents boats when playing against the computer.\n\t\tVery practical for debugging, and for testing, for example if a teacher wanted to test the program. :)";
	std::cout << "\n\n\tPS: There is one known bug, when you play against the computer, it can get stuck placing the ships. This is however fairly rare, and i did not have time to fix it. If this happens, a restart is required.";
	std::cout << "\n\n\tThere are also settings for the colors, because i wanted the challenge. The program looks terrible if using anything else than white...  \n\n\t";
	system("pause");

}

void settingsVisibleShips() {
	std::vector<std::string> choices;
	choices = { "On ", "Off " };
	std::cout << "\n\n\tShow opponents ships in 1-player mode?\n\tCurrently ";
	if (showCompBoats) { std::cout << "on\n\n"; }
	else { std::cout << "off\n\n"; }
	switch (arrowKeyMenu(choices, false, "\n", 0, false))
	{
	case 0: showCompBoats = true; break;
	case 1: showCompBoats = false; break;
	default: break;
	}
}

void settingsColors() {
	std::vector<std::string> choices;
	choices = { "Dark Blue ", "Dark Green ", "Cyan ", "Dark Red ", "Dark Purple ", "Dark Yellow ", "Gray ", "Dark Gray ", "Blue ", "Green ", "Light Blue ", "Red ", "Purple ", "Yellow ", "White " };
	defaultPrimaryColor= arrowKeyMenu(choices, false, "\n\tSet primary program color", 0, false)+1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultPrimaryColor);
}

void settingsBattleships() {
	std::vector<std::string> choices;
	bool continued = false;
	while (!continued) {
		system("cls");
		choices = { "Show opponents ships in 1-player mode ", "Set primary program color ","Back " };
		switch (arrowKeyMenu(choices, false, "\n\n\tSettings", 0, false))
		{
		case 0: settingsVisibleShips(); break;
		case 1: settingsColors(); break;
		default: continued = true; break;
		}
		ShowConsoleCursor(false);
	}
}

#pragma endregion functions
// ===============*/

void battleships() {

	// Fill the boards with 0
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			boardP1[i][j] = 0;
			boardP2[i][j] = 0;
		}
	}

	std::vector<std::string> choices; // Create vector for choices in arrow key menus

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultPrimaryColor); // Setting the color

	srand((unsigned int)time(NULL)); // Creating a seed for making psuedorandom numbers

	// == Main menu ==
	bool continued = false;
	bool quit = false;

	while (!continued) {
		system("cls"); // Clear screen
		choices = { "Before you play ", "Settings ", "Play game ", "Quit "}; // Menu choices

		switch (arrowKeyMenu(choices, false, "\n\n\t",0, false)) // Switch based on return from the menu
		{
		case 0: infoScreenBattleships(); break;
		case 1: settingsBattleships(); break;
		case 2: continued = true;  break;
		default: continued = true; quit = true; break;
		}
		ShowConsoleCursor(false);
	}
	// ===============*/
	
	if (!quit) {
	// == Play mode menu ==
	choices = { "1 Player ","2 Player " };
	switch (arrowKeyMenu(choices, false, "\n\n\tChoose mode:\n", 0, false))
	{
	case 0: system("cls"); againstComp = true; break;
	case 1: system("cls"); againstComp = false; break;
	default: break;
	}
	// ====================*/

	setup(); // Run the setup function (placing ships)
	while (!gameWon) { // Game loop - Runs as long as the game has not been won 
		if (!gameWon) { attack(1); } // Player 1's turn to attack
		if (!gameWon) { attack(2); } // Player 2's turn to attack
	}
	}
}