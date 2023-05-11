#include "GameManager.h"
#include <algorithm>

GameManager::GameManager()
    : board()
{
    init_snake();
}

void GameManager::init_snake()
{
    Position starting;
    starting.col = 19;
    starting.row = 19;
    snake.push(starting);

    facing = EAST;
    pendingGrow = 5;
}

Position GameManager::next_head()
{
    int row_update = 0;
    int col_update = 0;
    Position pos;
    if (facing == NORTH)
        row_update = 1;
    if (facing == SOUTH)
        row_update = -1;
    if (facing == WEST)
        col_update = -1;
    if (facing == EAST)
        col_update = 1;
    pos.row = snake.back().row + row_update;
    pos.col = snake.back().col + col_update;
    return pos;
}

void GameManager::turn(TurnSignal ts)
{
    if(ts == LEFT){
        if(facing == NORTH)
            facing = WEST;
        else if (facing == WEST)
            facing = SOUTH;
        else if(facing == SOUTH)
            facing = EAST;
        else if(facing == EAST)
            facing = NORTH;
    }
    if (ts == RIGHT)
    {
        if (facing == NORTH)
            facing = EAST;
        else if(facing == EAST)
            facing = SOUTH;
        else if(facing == SOUTH)
            facing = WEST;
        else if(facing == WEST)
            facing = NORTH;
    }
}

void GameManager::update()
{
    snake.push(next_head());
    if (pendingGrow == 0)
        snake.pop();
    else
        pendingGrow--;
}

void GameManager::snake_to_table()
{
    std::fill(board, board+1600, EMPTY);
    std::queue<Position> snakeCopy = snake;

    Position currentPos;

    while(!snakeCopy.empty()){
        currentPos = snakeCopy.front();
        snakeCopy.pop();
        board[currentPos.row * 40 + currentPos.col] = SNAKE;
    }
    board[currentPos.row * 40 + currentPos.col] = SNAKE_HEAD;
}

void GameManager::debug_display()
{
    snake_to_table();
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            if(board[i*40+j] == EMPTY)
                std::cout << "_";
            if (board[i * 40 + j] == APPLE)
                std::cout << "A";
            if (board[i * 40 + j] == SNAKE)
                std::cout << "S";
            if (board[i * 40 + j] == SNAKE_HEAD)
                std::cout << "H";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}