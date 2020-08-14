#pragma once
#include <string>
#include <vector>

std::string getRandomWord();
void draw(std::vector<char> chars, int wrongs, int guessesLeft);
void loose(std::string i);
void win(std::string i);

