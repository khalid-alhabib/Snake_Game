#include "game.hpp"

// default constructor
Grid::Grid(){
   clearGrid(); // makes a 20x30 vector 
}

std::vector<std::vector<std::string>>& Grid::getGrid(){
    return grid;
}

// printGrid prints the grid
void Grid::printGrid(){
    int lastColumn = 30;
    if (WIN){
        int lastColumn = 31;
    }
    for (size_t row = 0; row < 20; ++row){
        for (size_t column = 0; column < lastColumn; ++column){
            std::cout << grid[row][column];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

// draws the snake in the screen using the elements of the body index inside snake and draws the fruit
void Grid::drawSnake(const Snake& snake){
    // body = [[10,13], [10,14], [10,15]]
    const std::vector<std::vector<int>> body = snake.getBody(); // this is constant.
    const std::vector<int> head = snake.getHead();
    grid[head[0]][head[1]] = "O";
    for (const std::vector<int>& coord : body){
        int x = coord[0];
        int y = coord[1];
        grid[x][y] = "*"; // represent each body part by "*"
    }
    // draws the fruit
    // I don't want to draw a fruit for the winning animation
    if (!WIN){
        std::vector<int> fruitCoords = Fruit::getFruit();
        grid[fruitCoords[0]][fruitCoords[1]] = "K";
    }
        
}

void Grid::drawFruit(Fruit& fruit){
    if (fruitEaten){
        fruit.randomizeCoord();
    }
    std::vector<int> fruitCoord = fruit.getFruit();
    grid[fruitCoord[0]][fruitCoord[1]] = "K";
    fruitEaten = false;
}  

void Grid::clearGrid(){
    // 20 x 30 grid
    grid.clear();
    grid.resize(20, std::vector<std::string>(30, " "));
    // we are filling the far sided columns
    for (size_t row = 0; row < 20; ++row){
        grid[row][0] = "#";
        grid[row][29] = "#";
    }
    // the upper and bottom row
    for (size_t column = 0; column < 30; ++column){
                grid[0][column] = "#";
                grid[19][column] = "#";
    }

    // for the winning animation
    if (WIN){
        grid[5].resize(31, " ");
        grid[5][29] = " "; 
        grid[5][0] = "#";
    }
    
}

GAMEOVER::GAMEOVER(): std::runtime_error("GameOver :(") {}

// What is the largest inscribed square I can put inside of a 18(row) x 28(column) rectangle
// CALCULUS
void Grid::printGameOver(){
    clearGrid();
    // first diagonal
    int column = 6;
    for (int row = 1; row < 19; ++row){
        grid[row][column] = "X";
        grid[19-row][column] = "X";
        ++column;
    }
    printGrid();
}

void Grid::winnerAnimation(){
    Snake winner;
    int counter = 0;
    while (counter < 5){
        system("clear");
        winner.move('u');
        drawSnake(winner);
        printGrid();
        clearGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // a clock to make everything run smoother
        ++counter;
    }
    bool firstTime = true;
    std::cout << "A GATE HAS OPENED SNAKE. YOU ARE FREE...." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // a clock to make everything run smoother
    counter = 0;
    system("afplay snake_game_recording.wav &"); // run the command and don't wait for it to finish
    while (counter < 17){
        system("clear");
        winner.move('r');
        drawSnake(winner);
        printGrid();
        clearGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // a clock to make everything run smoother
        ++counter;
    }
    std::cout << "The snake has been fighting for its freedom all along..." << std::endl;
    std::cout << "But aren't we all?" << std::endl;
}