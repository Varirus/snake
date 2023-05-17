#ifndef VIEW_H
#define VIEW_H
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class View
{

    GameManager &manager; // GameManager

    sf::RectangleShape snake;     // Snake Tail
    sf::RectangleShape snakeHead; // Snake Head
    sf::RectangleShape apple;     // Apple

public:
    /**
        @brief Construct a new View object.

        @param mgr GameManager

     */
    View(GameManager &mgr);

    /**
           @brief Initialize shapes

     */
    void initShapes();

    /**
           @brief Draws Snake

           @param win RenderWindow

     */
    void drawSnake(sf::RenderWindow &win);

    /**
           @brief Draws game on the window
           
           @param win RenderWindow

     */
    void display(sf::RenderWindow &win);
};

#endif