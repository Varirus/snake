#include "GameManager.h"
#include <algorithm>

GameManager::GameManager(DifficultyLevel diff, Scoreboard &sb)
    : board(), difficulty(diff), scoreboard(sb)
{
    state = STOPPED;
    highscore = 0;
    init_snake();
    init_gameDifficulty();
    relocate_apple();
}

int GameManager::getSnakeSpeed() { return snakeSpeed; }

std::queue<Position> GameManager::getSnake() { return snake; }

TurnSignal GameManager::getPendingTurn() { return pendingTurn; }

Position GameManager::getApplePosition() { return apple; }

GameState GameManager::getGameState() { return state; }

int GameManager::getHighscore() { return highscore; }

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
        snakeSpeed = 120;
        growSize = 1;
    }
    if (difficulty == NORMAL)
    {
        snakeSpeed = 100;
        growSize = 2;
    }
    if (difficulty == HARD)
    {
        snakeSpeed = 70;
        growSize = 3;
    }
}

void GameManager::change_gameDifficulty(DifficultyLevel diff)
{
    difficulty = diff;
    init_gameDifficulty();
}

void GameManager::start_game()
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

bool GameManager::check_if_in_snake(Position ps)
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

void GameManager::relocate_apple()
{
    apple.col = rand() % BoardSizeCol;
    apple.row = rand() % BoardSizeRow;

    if (check_if_in_snake(apple))
        relocate_apple();
}

void GameManager::eat_apple()
{
    pendingGrow += growSize;
    highscore += growSize;
    relocate_apple();
}

bool GameManager::check_collision()
{
    Position nextHead = next_head();

    if (nextHead.col >= BoardSizeCol)
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (nextHead.col < 0)
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (nextHead.row >= BoardSizeRow)
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (nextHead.row < 0)
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (check_if_in_snake(nextHead))
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (nextHead.col == apple.col && nextHead.row == apple.row)
    {
        eat_apple();
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
        if (!check_collision())
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
    std::cout << "Snake x = " << next_head().col << " , y = " << next_head().row << std::endl
              << " , highscore = " << highscore << std::endl;
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