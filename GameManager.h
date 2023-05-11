#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <queue>

enum DifficultyLevel
{
    DEBUG,
    EASY,
    NORMAL,
    HARD
};

enum GameState
{
    RUNNING,
    FINISHED_WIN,
    FINISHED_LOSS
};

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum Title
{
    EMPTY,
    SNAKE,
    SNAKE_HEAD,
    APPLE
};

enum TurnSignal
{
    LEFT,
    RIGHT
};

struct Position
{
    int row; // Row Number (y)
    int col; // Column number (x)
};

class GameManager
{
    std::queue<Position> snake;
    Title board[1600];

    int snakeSpeed;
    int pendingGrow;

    Direction facing; // Snakes facing direction
    Position apple;

public:
    /**
        @brief Construct a new GameManager object.

     */
    GameManager();
    /**
        @brief Initializes snake

     */
    void init_snake();

    /**
        @brief Calculates next Head Position

     */
    Position next_head();

    /**
        @brief Updates snake position

     */
    void turn(TurnSignal ts);

    /**
        @brief Updates snake position

     */
    void update();

    /**
        @brief Transmition snake to board table
        
     */
    void snake_to_table();

    /**
        @brief Prints debug diplay in terminal

     */
    void debug_display();
};

#endif