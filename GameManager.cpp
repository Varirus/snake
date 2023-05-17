#include "GameManager.h"
#include <algorithm>

GameManager::GameManager(DifficultyLevel diff)
    : board(), difficulty(diff)
{
    state = STOPPED;
    init_snake();
    init_gameDifficulty();
    relocateApple();

    // DEBUG
    apple.col = 0;
    apple.row = 20;
}

int GameManager::getSnakeSpeed() { return snakeSpeed; }

std::queue<Position> GameManager::getSnake() { return snake; }

TurnSignal GameManager::getPendingTurn() { return pendingTurn; }

GameState GameManager::getGameState() { return state; }

void GameManager::setPendingTurn(TurnSignal pt) { pendingTurn = pt; }

void GameManager::init_snake()
{
    Position starting;
    starting.col = BoardSizeCol / 2;
    starting.row = BoardSizeRow / 2;
    snake.push(starting);
    facing = EAST;
    pendingTurn = NO_MOVE;
    pendingGrow = 5;
}

void GameManager::init_gameDifficulty()
{
    if (difficulty == EASY)
    {
        snakeSpeed = 300;
        growSize = 1;
    }
    if (difficulty == NORMAL)
    {
        snakeSpeed = 200;
        growSize = 2;
    }
    if (difficulty == HARD)
    {
        snakeSpeed = 100;
        growSize = 3;
    }
}

void GameManager::changeGameDifficulty(DifficultyLevel diff)
{
    difficulty = diff;
    init_gameDifficulty();
}

void GameManager::startGame()
{
    state = RUNNING;
}

Position GameManager::next_head()
{
    int row_update = 0;
    int col_update = 0;
    Position pos;
    if (facing == NORTH)
        row_update = -1;
    if (facing == SOUTH)
        row_update = 1;
    if (facing == WEST)
        col_update = -1;
    if (facing == EAST)
        col_update = 1;
    pos.row = snake.back().row + row_update;
    pos.col = snake.back().col + col_update;
    return pos;
}

bool GameManager::checkIfInSnake(Position ps)
{
    std::queue<Position> snakeCopy = snake;
    Position currentPos;

    while (!snakeCopy.empty())
    {
        currentPos = snakeCopy.front();
        snakeCopy.pop();
        if (currentPos.col == ps.col && currentPos.row == ps.row)
            return true;
    }
    return false;
}

void GameManager::relocateApple()
{
    apple.col = rand() % BoardSizeCol;
    apple.row = rand() % BoardSizeRow;

    if (checkIfInSnake(apple))
        relocateApple();
}

void GameManager::eatApple()
{
    pendingGrow += growSize;
    relocateApple();
}

bool GameManager::checkCollision()
{
    Position nextHead = next_head();

    if (nextHead.col >= BoardSizeCol)
    {
        state = FINISHED_LOSS;
        return true;
    }
    if (nextHead.col < 0)
    {
        state = FINISHED_LOSS;
        return true;
    }
    if (nextHead.row >= BoardSizeRow)
    {
        state = FINISHED_LOSS;
        return true;
    }
    if (nextHead.row < 0)
    {
        state = FINISHED_LOSS;
        return true;
    }
    if (checkIfInSnake(nextHead))
    {
        state = FINISHED_LOSS;
        return true;
    }
    if (nextHead.col == apple.col && nextHead.row == apple.row)
    {
        eatApple();
        return false;
    }
    return false;
}

void GameManager::turn(TurnSignal ts)
{
    pendingTurn = NO_MOVE;
    if (ts == NO_MOVE)
        return;
    if (ts == LEFT)
    {
        if (facing == NORTH)
            facing = WEST;
        else if (facing == WEST)
            facing = SOUTH;
        else if (facing == SOUTH)
            facing = EAST;
        else if (facing == EAST)
            facing = NORTH;
    }
    if (ts == RIGHT)
    {
        if (facing == NORTH)
            facing = EAST;
        else if (facing == EAST)
            facing = SOUTH;
        else if (facing == SOUTH)
            facing = WEST;
        else if (facing == WEST)
            facing = NORTH;
    }
}

void GameManager::update()
{
    if (state == RUNNING)
    {
        if (!checkCollision())
        {
            snake.push(next_head());
            if (pendingGrow == 0)
                snake.pop();
            else
                pendingGrow--;
        }
    }
}

void GameManager::snake_to_table()
{
    std::fill(board, board + (BoardSizeCol * BoardSizeRow), EMPTY);
    std::queue<Position> snakeCopy = snake;

    Position currentPos;

    while (!snakeCopy.empty())
    {
        currentPos = snakeCopy.front();
        snakeCopy.pop();
        board[currentPos.row * BoardSizeCol + currentPos.col] = SNAKE;
    }
    board[currentPos.row * BoardSizeCol + currentPos.col] = SNAKE_HEAD;

    board[apple.row * BoardSizeCol + apple.col] = APPLE;
}

void GameManager::debug_display()
{
    snake_to_table();
    std::cout << "Snake x = " << next_head().col << " ,y = " << next_head().row << std::endl
              << std::endl;
    for (int i = 0; i < BoardSizeRow; i++)
    {
        for (int j = 0; j < BoardSizeCol; j++)
        {
            if (board[i * BoardSizeCol + j] == EMPTY)
                std::cout << "_";
            if (board[i * BoardSizeCol + j] == APPLE)
                std::cout << "A";
            if (board[i * BoardSizeCol + j] == SNAKE)
                std::cout << "S";
            if (board[i * BoardSizeCol + j] == SNAKE_HEAD)
                std::cout << "H";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}