//
//  game.hpp
//  Snake_Game
//
//  Created by Khalid Alhabib on 6/19/25.
//

#ifndef GAMES_HPP
#define GAMES_HPP

#include "game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "termios.h"
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <ctime>

// Global Variables
// the extern keyword tells the compiler to not allocate any memory and take my 
// word that the variable definition exists in another file
// I should put these into a struct
extern char currentDirection; // Global variable holds direction of the snake:
                       //  Right(r), Left(l), Up(u), Down(d)
extern bool fruitEaten; // is the fruit eaten??
extern int speed; // speed of the snake(or diffculty)
extern int score;
extern bool WIN;
extern int winningScore;
extern int highScore;

class Snake{
public:
    Snake(); // Defaulted to 3 segments; 1 head 1 tail 1 body part in the middle of the screen (i.e (10,15)) for the head. Defaulted to the right direction.
    void move(const char direction); // Will move the snake in four directions.
    const std::vector<std::vector<int>>& getBody() const; // returns the current body of the snake
    const std::vector<int> getHead() const;
private:
    std::vector<std::vector<int>> body; // A vector of vectors that will hold the coordinate of each part of the snake except the head. A vector of (row, column) format.
    std::vector<int> head;
};

class Fruit{
public:
    Fruit(); // default constructor
    void randomizeCoord();
    static std::vector<int> getFruit(); // returns the fruit.
private:
    // this is a private static member variable, meaning it belongs to the class, 
    // not the object and cannot be accessed unless from friends or withing the class itself
    static std::vector<int> coord; // will hold (x, y) coord of fruit
};

class Grid{
    friend void move(const char direction); // need to access the grid to modify coords
public:
    Grid(); // default constructor to a 20 x 30 grid (row x columns)
    std::vector<std::vector<std::string>>& getGrid();
    void printGrid(); // will print the grid whenever we want to
    void drawSnake(const Snake& snake);  // draws the snake to the screen
    void drawFruit(Fruit& fruit); // draws the fruit to the screen. Cannot pass it as a constant since we are changing the coords each time
    void clearGrid(); // clears the grid each frame (used in Default Constructor)
    void printGameOver(); // draws X's on the screen diagonally and prints to the screen
    void winnerAnimation(); // prints the screen of a winner

private:
    std::vector<std::vector<std::string>> grid;
};

class GAMEOVER : public std::runtime_error{
public:
    GAMEOVER();
};

class Game{
public:
    static void reset();
    Game();
    void userInput(Snake& snake);
    void run();
private:
    Snake snake;
    Grid grid;
    Fruit fruit;
};

#endif