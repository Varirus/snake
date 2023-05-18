#include "View.h"
#include <cstring>

View::View(GameManager &mgr, Scoreboard &sb)
    : manager(mgr), scoreboard(sb)
{
    init_sprites();
    init_font();
}

void View::init_sprites()
{
    snake = sf::RectangleShape(sf::Vector2f(40, 40));
    snake.setFillColor(sf::Color(60, 250, 80));

    snakeHead = sf::RectangleShape(sf::Vector2f(40, 40));
    snakeHead.setFillColor(sf::Color(80, 00, 240));

    if (!appleTexture.loadFromFile("../apple.png"))
        appleTexture.loadFromFile("apple.png");
    appleTexture.setSmooth(true);
    apple.setTexture(appleTexture);

    if (!bgTexture.loadFromFile("../background.png"))
        bgTexture.loadFromFile("background.png");
    bg.setTexture(bgTexture);
    bg.setPosition(0, 0);
}

void View::init_font()
{
    if (!font.loadFromFile("../pixel_font.ttf"))
        font.loadFromFile("pixel_font.ttf");
    highscoreText.setFont(font);
    highscoreText.setCharacterSize(30);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setPosition(5, 0);
    highscoreText.setString("0");
    highscoreText.setOutlineThickness(1);
    highscoreText.setOutlineColor(sf::Color::Black);

    finishedText.setFont(font);
    finishedText.setCharacterSize(60);
    finishedText.setFillColor(sf::Color::White);
    finishedText.setOutlineThickness(2);
    finishedText.setOutlineColor(sf::Color::Black);
}

void View::draw_snake(sf::RenderWindow &win)
{

    std::queue<Position> snakeCopy = manager.getSnake();
    Position currentPos;

    while (!snakeCopy.empty())
    {
        currentPos = snakeCopy.front();
        snakeCopy.pop();
        snake.setPosition(currentPos.col * 40, currentPos.row * 40);
        win.draw(snake);
    }

    snakeHead.setPosition(currentPos.col * 40, currentPos.row * 40);
    win.draw(snakeHead);
}

void View::display_menu(sf::RenderWindow &win)
{
}

void View::display_game(sf::RenderWindow &win)
{
    // TODO sprite, menu, scoreboard
    win.draw(bg);
    highscoreText.setString(std::to_string(manager.getHighscore()));
    win.draw(highscoreText);
    draw_snake(win);
    apple.setPosition(manager.getApplePosition().col * 40, manager.getApplePosition().row * 40);
    win.draw(apple);
}

void View::display_scoreboard(sf::RenderWindow &win)
{
    finishedText.setPosition(100, 100);
    finishedText.setString("GAME OVER");
    win.draw(finishedText);
    finishedText.setPosition(100, 175);
    finishedText.setString("Your score: " + std::to_string(manager.getHighscore()));
    win.draw(finishedText);
    finishedText.setPosition(100, 255);
    finishedText.setCharacterSize(30);
    finishedText.setString("Scoreboard: ");
    win.draw(finishedText);
    int j = 0;
    for (std::vector<int>::iterator i = scoreboard.getScoreboardBegin(); i < scoreboard.getScoreboardEnd(); i++)
    {
        std::string points = std::to_string(*i);
        j++;
        std::string score = std::to_string(j) + ". " + points;
        finishedText.setPosition(100, 255 + 35 * j);
        finishedText.setString(score);
        win.draw(finishedText);
    }
    finishedText.setCharacterSize(60);
}