#include "game.hpp"
#include <vector>

char currentDirection = 'r'; // Right(r), Left(l), Up(u), Down(d)
bool fruitEaten = true;
std::vector<int> Fruit::coord;
int speed = 1;
int score = 0;
bool WIN = false;
int winningScore = 10;
int highScore = 0; // will change after resetting
