//
//  game.cpp
//  Snake_Game
//
//  Created by Khalid Alhabib on 6/19/25.
//  This is a game.cpp file; it will include all the defintions
#include "game.hpp"

// game default constructor
Game::Game(){
    Game::run(); // runs the game
}

void Game::run(){
    try{
        while (true){
            system("clear"); // clears the terminal output for each frame
            std::cout << "SCORE: " << score << std::endl; // print score
            if (score == winningScore){
                WIN = true;
                grid.winnerAnimation();
                break;
            }
            if (fruitEaten)
                grid.drawFruit(fruit); // draws the newly fruit for the snake class
            userInput(snake); // takes user input and changes the global variable currentDirection
            snake.move(currentDirection);
            grid.drawSnake(snake); // draws the snake to the grid
            grid.printGrid(); // prints the grid
            grid.clearGrid(); // resets the grid for the next frame
            std::this_thread::sleep_for(std::chrono::milliseconds(100-speed)); // a clock to make everything run smoother
            // if the delay is less then the game is faster
            
        }
    }
    catch (const GAMEOVER& ge){
       std::cout << ge.what() << std::endl;
       grid.printGameOver();
       std::string userInput;
       if (score > highScore)
            highScore = score;
       std::cout << "Highscore: " << highScore << std::endl;
       std::cout << "(r) to retry or (q) to quit: ";
       std::cin >> userInput;
       while (userInput != "q" && userInput != "r"){
            std::cout << "Invalid response :( Try Again: ";
            std::cin >> userInput;
       }
       if (userInput == "q"){
            system("clear");
            std::cout << "Goodbye!" << std::endl;
       }
       else{ // r
            reset();
       }
    }
    
}

// Reads a single character from the keyboard without blocking the game loop.
// Returns 0 if no input is available.
// Disables canonical mode (so input is processed immediately) and echo (so characters are not shown on screen).
char getch_nonblocking() {
    struct termios oldt, newt;  // Structures to hold terminal I/O settings
    char ch = 0;                // Variable to store the input character
    int oldf;                   // Variable to store original file status flags for stdin

    // Get the current terminal attributes and store them in 'oldt'
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;  // Make a copy so we can modify and restore later

    // Turn off canonical mode and echo:
    // - ICANON: disables line buffering (input is available immediately)
    // - ECHO: disables character echoing to the terminal
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply the modified terminal settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Save current file descriptor flags (to restore later)
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    // Set the file descriptor to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Try to read a character from stdin
    // If no character is available, read() will return -1 and 'ch' stays 0
    if (read(STDIN_FILENO, &ch, 1) < 0) {
        ch = 0;  // No input was available
    }

    // Restore the original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Restore original file descriptor flags (turn off non-blocking)
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;  // Return the character read, or 0 if no input
}


void Game::userInput(Snake& snake){ // takes the user input and moves the snake accordingly
    // (Arrow up) for moving the head up, (Arrow down) for down, etc. And q for quit
    char input = getch_nonblocking();
    switch (input){
        case('d'): // right
            if (currentDirection != 'l') // cannot move right if curr direction is left
                currentDirection = 'r';
            break;

        case('a'): // left 
            if (currentDirection != 'r') // cannot move left if curr direction is right
                currentDirection = 'l';
            break;
        
        case('w'): // up
            if (currentDirection != 'd') // cannot move up if curr direction is down
                currentDirection = 'u';
            break;

        case('s'): // down
            if (currentDirection != 'u') // cannot move down if current direction is up
                currentDirection = 'd';
            break;

        case('q'):
            throw GAMEOVER();
            break;
    }
}

void Game::reset(){
    currentDirection = 'r'; // Right(r), Left(l), Up(u), Down(d)
    fruitEaten = true;
    speed = 1;
    score = 0;
    WIN = false;
    Game game;
}