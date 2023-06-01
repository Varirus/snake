#include "GameManager.h"
#include <algorithm>

GameManager::GameManager(DifficultyLevel diff, Scoreboard &sb)
    : board(), difficulty(diff), scoreboard(sb)
{
    resetGame();
    init_gameDifficulty();
}

int GameManager::getSnakeSpeed() { return snakeSpeed; }

std::queue<Position> GameManager::getSnake() { return snake; }

TurnSignal GameManager::getPendingTurn() { return pendingTurn; }

Position GameManager::getSnackPosition() { return snack; }

GameState GameManager::getGameState() { return state; }

int GameManager::getHighscore() { return highscore; }

Direction GameManager::getFacing() { return facing; }

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
        snakeSpeed = 160;
        growSize = 1;
    }
    if (difficulty == NORMAL)
    {
        snakeSpeed = 120;
        growSize = 2;
    }
    if (difficulty == HARD)
    {
        snakeSpeed = 80;
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

void GameManager::stop_game()
{
    state = PAUSED;
}

void GameManager::resetGame()
{
    stop_game();
    while (!snake.empty())
        snake.pop();
    highscore = 0;
    init_snake();
    relocate_snack();
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

bool GameManager::intersect_snake(Position ps)
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

void GameManager::relocate_snack()
{
    snack.col = rand() % BoardSizeCol;
    snack.row = rand() % BoardSizeRow;

    if (intersect_snake(snack))
        relocate_snack();
}

void GameManager::eat_snack()
{
    pendingGrow += growSize;
    highscore += growSize;
    relocate_snack();
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
    if (intersect_snake(nextHead))
    {
        state = FINISHED;
        scoreboard.add_new_score(highscore);
        return true;
    }
    if (nextHead.col == snack.col && nextHead.row == snack.row)
    {
        eat_snack();
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

void GameManager::snake_to_array()
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

    board[snack.row * BoardSizeCol + snack.col] = SNACK;
}

void GameManager::debug_display()
{
    snake_to_array();
    std::cout << "Snake x = " << next_head().col << " , y = " << next_head().row << std::endl
              << " , highscore = " << highscore << std::endl;
    for (int i = 0; i < BoardSizeRow; i++)
    {
        for (int j = 0; j < BoardSizeCol; j++)
        {
            if (board[i * BoardSizeCol + j] == EMPTY)
                std::cout << "_";
            if (board[i * BoardSizeCol + j] == SNACK)
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