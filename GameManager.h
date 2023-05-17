#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <queue>

#define BoardSizeCol 40
#define BoardSizeRow 40

enum DifficultyLevel
{
    EASY,
    NORMAL,
    HARD
};

enum GameState
{
    STOPPED,
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
    Title board[BoardSizeCol * BoardSizeRow]; // Board for Terminal/Debug display
    int snakeSpeed;                           // Snake's Speed
    int pendingGrow;                          // Pending grow size
    int growSize;                             // How many titles will snake grow upon eating apple
    Direction facing;                         // Snake's facing direction
    Position apple;                           // Apple's position
    TurnSignal pendingTurn;                   // Pedning Turn Signal
    GameState state;                          // GameState (EASY|NORMAL|HARD)
    DifficultyLevel difficulty;               // GameState (RUNNING|FINISHED_LOSS|FINISHED_WIN)

public:
    /**
        @brief Construct a new GameManager object.

     */
    GameManager(DifficultyLevel diff);

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
        @brief Returns game state

        @return game state (FINISHED_WIN|FINISHED_LOSS|RUNNING)
     */
    GameState getGameState();

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
    void changeGameDifficulty(DifficultyLevel diff);

    /**
        @brief Starts Game

     */
    void startGame();

    /**
        @brief Calculates next Head Position

     */
    Position next_head();

    /**
        @brief Check if given position is snake

        @param ps position

        @return \b true - if given position is in snake
        @return \b false - if given position is not in snake

     */
    bool checkIfInSnake(Position ps);

    /**
        @brief Relocates apple position

     */
    void relocateApple();

    /**
        @brief Relocates Apple, makes snake bigger

     */
    void eatApple();

    /**
        @brief Checks if snake hit itself, is out of board or ate apple

        @return \b true - if snake collision loses game
        @return \b false - if snake collision doesn't affect game
     */
    bool checkCollision();

    /**
        @brief Changes Snake Direction

        @param ts (LEFT|RIGHT)

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