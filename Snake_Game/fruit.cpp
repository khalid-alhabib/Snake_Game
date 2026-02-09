#include "game.hpp"

// initializes a random coord
Fruit::Fruit(){
    randomizeCoord(); // randomizes the coords
}

// randomizes the coords of the fruit;
void Fruit::randomizeCoord(){
    int row = std::rand() % 18 + 1; // range from index 1 to 18
    int column = std::rand() % 28 + 1; // range from index 1 to 28
    coord = {row, column};
}

std::vector<int> Fruit::getFruit(){
    return coord;
}
