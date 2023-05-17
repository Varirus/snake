#include "View.h"

View::View(GameManager &mgr)
    : manager(mgr)
{
    initShapes();
}

void View::initShapes()
{
    snake = sf::RectangleShape(sf::Vector2f(20, 20));
    snake.setFillColor(sf::Color(60, 250, 80));
    // snake.setOutlineColor(sf::Color(50, 50, 50));
    snake.setOutlineThickness(2);

    apple = sf::RectangleShape(sf::Vector2f(20, 20));
    apple.setFillColor(sf::Color(245, 60, 90));
    // apple.setOutlineColor(sf::Color(30, 30, 30));
    apple.setOutlineThickness(2);
}

void View::display(sf::RenderWindow &win)
{
}