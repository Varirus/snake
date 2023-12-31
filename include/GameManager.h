#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <queue>
#include "Scoreboard.h"

enum DifficultyLevel
{
    EASY,
    NORMAL,
    HARD
};

enum GameState
{
    PAUSED,
    RUNNING,
    FINISHED,
};

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum Tile
{
    EMPTY,
    SNAKE,
    SNAKE_HEAD,
    SNACK
};

enum TurnSignal
{
    LEFT,
    RIGHT,
    NO_MOVE
};

struct Position
{
    int row; // Row Number (y)
    int col; // Column number (x)
};

class GameManager
{
    std::queue<Position> snake;
    Tile board[1600];           // Board for Terminal/Debug display
    int snakeSpeed;             // Snake's Speed
    int pendingGrow;            // Pending grow size
    int growSize;               // How many titles will snake grow upon eating snack
    int highscore;              // Player's highscore
    Direction facing;           // Snake's facing direction
    Position snack;             // snack's position
    TurnSignal pendingTurn;     // Pedning Turn Signal
    GameState state;            // GameState (PAUSED|RUNNING|FINISHED)
    DifficultyLevel difficulty; // DifficultyLevel (EASY|NORMAL|HARD)
    Scoreboard &scoreboard;     // Scoreboard Controller

    const int BoardSizeCol = 20; // Defined number of columns
    const int BoardSizeRow = 20; // Defined number of rows

public:
    /**
        @brief Construct a new GameManager object.

        @param diff game difficulty level
        @param sb Scoreboard

     */
    GameManager(DifficultyLevel diff, Scoreboard &sb);

    /**
        @brief Returns snake's speed

        @return snake's speed
     */
    int getSnakeSpeed();

    /**
        @brief Returns snake queue

        @return snake
     */
    std::queue<Position> getSnake();

    /**
        @brief Returns pendingTurn

        @return pendingTurn
     */
    TurnSignal getPendingTurn();

    /**
        @brief Returns snack position

        @return snack position

     */
    Position getSnackPosition();

    /**
        @brief Returns game state

        @return game state (FINISHED|RUNNING|PAUSED)
     */
    GameState getGameState();

    /**
        @brief Returns player's highscore

        @return player's highscore
     */
    int getHighscore();

    /**
        @brief Returns snake's facing

        @return snake's facing
     */
    Direction getFacing();

    /**
        @brief Sets pendingTurn to desired TurnSignal

        @param pt pendingTurn
     */
    void setPendingTurn(TurnSignal pt);

    /**
        @brief Initializes snake

     */
    void init_snake();

    /**
        @brief Initializes game difficulty

     */
    void init_gameDifficulty();

    /**
           @brief Changes Game Difficulty to desired one

           @param diff game difficulty

        */
    void change_gameDifficulty(DifficultyLevel diff);

    /**
        @brief Starts Game

     */
    void start_game();

    /**
        @brief Stops Game

     */
    void stop_game();

    /**
        @brief Resets game

     */
    void resetGame();

    /**
        @brief Calculates next Head Position

        @return next head position

     */
    Position next_head();

    /**
        @brief Checks if given position intersects snake

        @param ps position

        @return \b true - if given position is in snake
        @return \b false - if given position is not in snake

     */
    bool intersect_snake(Position ps);

    /**
        @brief Relocates snack position

     */
    void relocate_snack();

    /**
        @brief Relocates snack, makes snake bigger

     */
    void eat_snack();

    /**
        @brief Checks if snake hit itself, is out of board or ate snack

        @return \b true - if snake collision loses game
        @return \b false - if snake collision doesn't affect game
     */
    bool check_collision();

    /**
        @brief Changes Snake Direction

        @param ts (LEFT|RIGHT|NO_MOVE)

     */
    void turn(TurnSignal ts);

    /**
        @brief Updates snake position

     */
    void update();

    /**
        @brief Transmition snake to board array

     */
    void snake_to_array();

    /**
        @brief Prints debug diplay in terminal

     */
    void debug_display();
};

#endif