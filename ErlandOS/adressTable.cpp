#include "publicFunctions.h"

#include <iostream>

#include <conio.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds





#pragma region infoFunctions 

void drawInfo(std::vector<std::string> text, COORD drawCoord) {

	setColor(cyan, black);

	drawCoord.X += 18;
	drawCoord.Y += 1;
	setCursorPos(drawCoord);
	COORD currentDrawCord;
	COORD startDrawCord;
	std::cout << "\n";
	currentDrawCord = GetConsoleCursorPosition();
	startDrawCord = GetConsoleCursorPosition();
	drawCoord.Y = currentDrawCord.Y;
	setCursorPos(drawCoord);

	std::vector<std::string> empty{
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	"                                                        \n",
	};

	for (int i = 0; i < empty.size(); i++) {
		currentDrawCord = GetConsoleCursorPosition();
		drawCoord.Y = currentDrawCord.Y;
		setCursorPos(drawCoord);

		std::cout << empty[i];
	}

	setCursorPos(startDrawCord);
	for (int i = 0; i < text.size(); i++) {

		currentDrawCord = GetConsoleCursorPosition();
		drawCoord.Y = currentDrawCord.Y;
		setCursorPos(drawCoord);

		std::cout << "|" << text[i];
	}

}

#pragma region types 

void infoBool(COORD drawCoord) {
	std::vector<std::string> boolInfo {
		" Bool               \n",
		"------------------------------------------------------  \n",
		" A bool (short for boolean) is a data type that has two \n",
		" possible values, true and false, or 1 and 0.           \n",
		"______________________________________________________  \n",
	};

	drawInfo(boolInfo, drawCoord);
}


void infoInt(COORD drawCoord) {
	std::vector<std::string> intInfo{
		" Int               \n",
		"------------------------------------------------------ \n",
		" An int (short for integer) is a data type containing  \n",
		" whole numbers.                                        \n",
		" An integer can either be \"signed\" or \"unsigned\".  \n",
		" A signed integer can contain both negative and        \n",
		" positive values. An unsigned int however can not.     \n",
		" An unsigned integer has twice the max size than       \n",
		" that of a signed integer.                             \n",
		"______________________________________________________ \n"
	};

	drawInfo(intInfo, drawCoord);
}

void infoFloat(COORD drawCoord) {
	std::vector<std::string> floatInfo{
		" Float               \n",
		"------------------------------------------------------ \n",
		" A float is in short terms a data type containing      \n",
		" decimal numbers.                                      \n",
		"                                                       \n",
		" A float has 7 digits of precision, and can, like the  \n",
		" int data type be both signed and unsigned.            \n",
		"______________________________________________________ \n",
	};

	drawInfo(floatInfo, drawCoord);
}

void infoDouble(COORD drawCoord) {
	std::vector<std::string> doubleInfo{
		" Double               \n",
		"------------------------------------------------------ \n",
		" A double is a much like the float data type,          \n",
		" containing decimal numbers, but as the name might     \n",
		" suggest, it has double the decimal precision. It      \n",
		" actually has 15 digits, instead of seven.             \n",
		" It can also be signed/unsigned.                       \n",
		"______________________________________________________ \n",
	
	};

	drawInfo(doubleInfo, drawCoord);
}

void infoChar(COORD drawCoord) {
	std::vector<std::string> charInfo{
		" Char               \n",
		"------------------------------------------------------ \n",
		" A char is a data type containing a letter.            \n",
		"______________________________________________________ \n",

		
	};

	drawInfo(charInfo, drawCoord);
}

void infoString(COORD drawCoord) {
	std::vector<std::string> stringInfo{
		" String               \n",
		"------------------------------------------------------ \n",
		" A string is a data type containing text, where a char \n",
		" contains one and one letter, a string can contain     \n",
		" whole words or sentences.                             \n",
		"______________________________________________________ \n",

		
	};

	drawInfo(stringInfo, drawCoord);
}

void infoArray(COORD drawCoord) {
	std::vector<std::string> arrayInfo{
		" Array                \n",
		"------------------------------------------------------ \n",
		" An array is a data type that acts as a \"list of data\", \n",
		" it can contain different data types, for example an   \n",
		" int or a char.                                        \n",
		" An array needs a defined size, and type, and can then \n",
		" be filled with data.                                  \n",
		" You find data in the array by specifying the location \n",
		" in it.                                                \n",
		"______________________________________________________ \n "
	};

	drawInfo(arrayInfo, drawCoord);
}

void infoVector(COORD drawCoord) {
	std::vector<std::string> vectorInfo{
		" Vector               \n",
		"------------------------------------------------------ \n",
		" A vector is very similar to an array. They both       \n",
		" contain \"lists\" of data. The difference between     \n",
		" them is that the vector is much more diverse, more    \n",
		" manipulatable.                                        \n",
		" Where an array needs a defined size, a vector does    \n",
		" not. The vector can be resized at any time.           \n",
		"______________________________________________________ \n",
		
	};

	drawInfo(vectorInfo, drawCoord);
}

#pragma endregion types 
#pragma endregion infoFunctions


int delayTime = 50;


void title() {
	setColor(white, black);
	std::cout << "             _                     _        _     _      \n";
	std::cout << "    /\\      | |                   | |      | |   | |     \n";
	std::cout << "   /  \\   __| |_ __ ___  ___ ___  | |_ __ _| |__ | | ___ \n";
	std::cout << "  / /\\ \\ / _` | '__/ _ \\/ __/ __| | __/ _` | '_ \\| |/ _ \\\n";
	std::cout << " / ____ \\ (_| | | |  __/\\__ \\__ \\ | || (_| | |_) | |  __/\n";
	std::cout << "/_/    \\_\\__,_|_|  \\___||___/___/  \\__\\__,_|_.__/|_|\\___|\n";
	setColor(cyan, black);
	std::cout << "=========================================================\n\n";
}


void adressTable() {
	std::vector<std::string> choices;

	system("cls");
	ShowConsoleCursor(false); // Hide cursor
	title(); // Run function to draw the title
	std::cout << "\n";

	#pragma region drawTable 
	// == Variable table =====================

	// == Variables ==
	bool bool0 = false;
	bool bool1 = true;

	int int0 = 56;
	int int1 = INT_MAX;
	int hello = 1;
	int world = 2;

	float flo0 = 3.141592;
	float flo1 = 1.1;

	double doub0 = 1.7976931348623158e+308;
	double doub1 = 5000000000000000000;

	char chr0 = 'A';
	char chr1 = 'B';

	std::string str0 = "Hello World";
	std::string str1 = "sample text";

	int arr0[9] = { 3,1,7,6 };
	char arr1[3] = { 'a','b','c' };

	std::vector<std::string> vec0{"s1","s2","s3",};
	std::vector<char> vec1{'x','y'};

	// ============== 


	// == Header ====
	setColor(white,black);
	std::cout << " Adress          Name            Value           Type      \n";
	std::cout << "--------------  --------------  --------------  ---------------\n";
	// ==============
	delay(delayTime);

	// == Bools =====
	setColor(white, black); // Set color
	std::cout << &bool0 << "\t" << "bool0" << "\t\t" << bool0 << "\t\t" << "bool" << "\n"; // Print out the adress, name, value and type of variable
	delay(delayTime); // A little delay for a scrolling-text effect
	
	std::cout << &bool1 << "\t" << "bool1" << "\t\t" << bool1 << "\t\t" << "bool" << "\n"; // The same as above, but for the second bool
	delay(delayTime); 
	// ==============

	// Most of the variable types below are printed exactly the same way, exept for the arrays and vectors

	// == Ints ======
	setColor(cyan, black);
	std::cout << &int0  << "\t" << "int0 " << "\t\t" << int0  << "\t\t" << "int" << "\n";
	delay(delayTime);
	
	std::cout << &int1  << "\t" << "int1 " << "\t\t" << int1  << "\t"   << "int" << "\n";
	delay(delayTime);
	// ==============
	

	// == Float =====
	setColor(white,black);
	std::cout << &flo0 << "\t" << "flo0 " << "\t\t" << flo0 << "\t\t" << "float" << "\n";
	delay(delayTime);
	
	std::cout << &flo1 << "\t" << "flo1 " << "\t\t" << flo1 << "\t\t" << "float" << "\n";
	delay(delayTime);
	// ==============

	// == Doubles ===
	setColor(cyan, black);
	std::cout << &doub0 << "\t" << "doub0" << "\t\t" << doub0 << "\t" << "double" << "\n";
	delay(delayTime);
	
	std::cout << &doub1 << "\t" << "doub1" << "\t\t" << doub1 << "\t\t" << "double" << "\n";
	delay(delayTime);
	// ==============

	// == Chars =====
	setColor(white, black);
	std::cout << (void*)&chr0 << "\t" << "chr0" << "\t\t" << chr0 << "\t\t" << "char" << "\n";
	delay(delayTime);
	
	std::cout << (void*)&chr1 << "\t" << "chr1" << "\t\t" << chr1 << "\t\t" << "char" << "\n";
	delay(delayTime);
	// ==============


	// == Strings ===
	setColor(cyan, black);
	std::cout << &str0 << "\t" << "str0" << "\t\t" << str0 << "\t" << "string" << "\n";
	delay(delayTime);
	
	std::cout << (void*)&str1 << "\t" << "str1" << "\t\t" << str1 << "\t" << "string" << "\n";
	delay(delayTime);
	// ==============


	// == Arrays ====
	setColor(white, black); // Setting the color 



	std::cout << &arr0 << "\t" << "arr0" << "\t\t"; // First printing out the adress and then name
	for (int i = 0; i < 4; i++) {		// For loop for going through the whole array
		std::cout << arr0[i] << ",";	// Prints the value of the current location in the array, then a comma as a seperator
	}
	std::cout << "\t" << "array" << "\n"; //  Prints the type of variable last
	delay(delayTime);




	std::cout << &arr1 << "\t" << "arr1" << "\t\t"; // First printing out the adress and then name
	for (int i = 0; i < 3; i++) {		// For loop for going through the whole array
		std::cout << arr1[i] << ",";	// Prints the value of the current location in the array, then a comma as a seperator
	}
	std::cout << "\t\t" << "array" << "\n"; //  Prints the type of variable last
	delay(delayTime);
	

	// ==============

	// == Vectors ===
	setColor(cyan, black);
	std::cout << &vec0 << "\t" << "vec0" << "\t\t"; // First printing out the adress and then name
	for (int i = 0; i < vec0.size(); i++) {		// For loop for going through the whole vector
		std::cout << vec0[i] << ",";	// Prints the value of the current location in the vector, then a comma as a seperator
	}
	std::cout << "\t" << "vector" << "\n"; //  Prints the type of variable last
	delay(delayTime);
	
	setColor(cyan, black);
	std::cout << &vec1 << "\t" << "vec1" << "\t\t"; // First printing out the adress and then name
	for (int i = 0; i < vec1.size(); i++) {		// For loop for going through the whole vector
		std::cout << vec1[i] << ",";	// Prints the value of the current location in the vector, then a comma as a seperator
	}
	std::cout << "\t\t" << "vector" << "\n"; //  Prints the type of variable last
	delay(delayTime);
	// ==============


	setColor(cyan, black);
	std::cout << "--------------  --------------  --------------  ---------------\n\n\n"; // Printing the bottom of the table.
	

	// =======================================
	
#pragma endregion drawTable
	
	delay(500); 


	// == Info menu ==========================
	COORD cursorCordBeforeTable = GetConsoleCursorPosition(); // Getting the current location of the cursor

	// Drawing an arrow-key menu, where you can pick any variable to read about.
	bool quit = false;
	while (!quit) { // While loop, so you can continue to look at different menues
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorCordBeforeTable); // Setting the location of the cursor, so the menu will be drawn in the correct location. If this was not here, the menu would get duplicated downwards. This is why the coordinates are set above the while loop, they will not change
		choices = { "Bool ","Int ","Float ","Double ","Char ","String ","Array ","Vector ","Quit "}; // Choices for the menu
		switch (arrowKeyMenu(choices, false, "Choose a variable type with the arrow keys and press enter to see information about them:\n\t-----------------------------------------------------------------------------------------",0,true)) // Switch that calls the menu function, which returns with the selected item in the menu
		{ // Runs a function based on the item selected in the menu
		case 0: infoBool(cursorCordBeforeTable); break; 
		case 1: infoInt(cursorCordBeforeTable); break;
		case 2: infoFloat(cursorCordBeforeTable); break;
		case 3: infoDouble(cursorCordBeforeTable); break;
		case 4: infoChar(cursorCordBeforeTable);  break;
		case 5: infoString(cursorCordBeforeTable); break;
		case 6: infoArray(cursorCordBeforeTable); break;
		case 7: infoVector(cursorCordBeforeTable); break;
		case 8: quit = true; setColor(white, black); break; // If quit is selected, the while loop will not continue, and the program will end
		default: break;
		}
		ShowConsoleCursor(false);
	}

	system("cls");

	// ======================================= */
	

}