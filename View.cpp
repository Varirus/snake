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
    //snake.setOutlineThickness(2);

    apple = sf::RectangleShape(sf::Vector2f(20, 20));
    apple.setFillColor(sf::Color(245, 60, 90));
    // apple.setOutlineColor(sf::Color(30, 30, 30));
    //apple.setOutlineThickness(2);
}

void View::drawSnake(sf::RenderWindow &win)
{

    std::queue<Position> snakeCopy = manager.getSnake();
    Position currentPos;

    while (!snakeCopy.empty())
    {
        currentPos = snakeCopy.front();
        snakeCopy.pop();
        snake.setPosition(currentPos.col * 20, currentPos.row * 20);
        win.draw(snake);
    }
    //board[currentPos.row * BoardSizeCol + currentPos.col] = SNAKE_HEAD;
}

void View::display(sf::RenderWindow &win)
{
    // TODO oddzielna metoda na pozycje i rysowanie, snake na ekranie, sprite, menu jako jedna grafika, bo easieeeer
    drawSnake(win);
    apple.setPosition(manager.getApplePosition().col * 20, manager.getApplePosition().row * 20);
    win.draw(apple);
}