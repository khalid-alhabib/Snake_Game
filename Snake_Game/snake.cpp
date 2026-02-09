#include "game.hpp"

// Default constructor for the class Snake
Snake::Snake(){
    body = {{10,13},{10,14}}; // each element (row x column) format
    head = {10,15};
}

const std::vector<std::vector<int>>& Snake::getBody() const{
    return body;
}
const std::vector<int> Snake::getHead() const{
    return head;
}

void Snake::move(const char direction){
    std::vector<int> prev;
    std::vector<int> temp;
    std::vector<int> fruitCoords = Fruit::getFruit();
    switch (direction){
        case 'r': // right
            if (head[1] + 1 < 29){ // check if we hit boundaries
                // collision detection
                // if the snake hit the fruit
                if (head[0] == fruitCoords[0] && head[1]+1 == fruitCoords[1]){
                    body.push_back(head);
                    head[1] += 1; // increment the column of head
                    fruitEaten = true;
                    speed += 5;
                    ++score;
                }
                prev = head; // save the location of the current head
                head[1] += 1; // increment the column of head
                for (int index = body.size()-1; index >= 0; --index){
                    // change each body element to be the next one
                    temp = body[index];
                    body[index] = prev;
                    prev = temp;
                }
            }
            else{ // else throw an error, if not won.
                if (!WIN)
                    throw GAMEOVER();
                else{
                    // For the winning animation
                    prev = head; // save the location of the current head
                    head[1] += 1; // increment the column of head
                    for (int index = body.size()-1; index >= 0; --index){
                        // change each body element to be the next one
                        temp = body[index];
                        body[index] = prev;
                        prev = temp;
                }
                }
            }
            break;

        case 'l': // left
            if (head[1] - 1 > 0){ // check if we hit boundaries
                // collision detection
                // if the snake hit the fruit
                if (head[0] == fruitCoords[0] && head[1]-1 == fruitCoords[1]){
                    body.push_back(head);
                    head[1] -= 1; // decrement the column of head
                    fruitEaten = true;
                    speed += 5;
                    ++score;
                }
                prev = head; 
                head[1] -= 1;
                for (int index = body.size()-1; index >= 0; --index){
                    // change each body element to be the next one
                    temp = body[index];
                    body[index] = prev;
                    prev = temp;
                }
            }
            else{ // else throw an error
                throw GAMEOVER(); 
            }
            break;

        case 'u': // up
            if (head[0] - 1 > 0){ // check if we hit boundaries
                // collision detection
                // if the snake hit the fruit
                if (head[0]-1 == fruitCoords[0] && head[1] == fruitCoords[1]){
                    body.push_back(head);
                    head[0] -= 1; // decrement the column of head
                    fruitEaten = true;
                    speed += 5;
                    ++score;
                }
                prev = head;
                head[0] -= 1;
                for (int index = body.size()-1; index >= 0; --index){
                    // change each body element to be the next one
                    temp = body[index];
                    body[index] = prev;
                    prev = temp;
                }
            }
            else{ // else throw an error
                throw GAMEOVER();
            }   
            break;

        case 'd': // down
            if (head[0] + 1 < 19){ // check if we hit boundaries
                // collision detection
                // if the snake hit the fruit
                if (head[0]+1 == fruitCoords[0] && head[1] == fruitCoords[1]){
                    body.push_back(head);
                    head[0] += 1; // decrement the column of head
                    fruitEaten = true;
                    speed+= 5;
                    ++score;
                }
                prev = head;
                head[0] += 1;
                for (int index = body.size()-1; index >= 0; --index){
                    // change each body element to be the next one
                    temp = body[index];
                    body[index] = prev;
                    prev = temp;
                }
            }
            else{ // else throw an error
                throw GAMEOVER();
            }
            break;
    }
    // collision detection
    // detects if we hit the snake
    for (const std::vector<int> elem : body){
        if (head[0] == elem[0] && head[1] == elem[1])
            throw GAMEOVER();
    }
}
