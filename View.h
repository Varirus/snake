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
           @brief Draws game on the window

     */
    void display(sf::RenderWindow &win);
};

#endif