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
    if (!snakeTexture.loadFromFile("../Resources/snake.png"))
        snakeTexture.loadFromFile("Resources/snake.png");
    snakeTexture.setSmooth(true);
    snake.setTexture(snakeTexture);

    if (!snakeHeadTexture.loadFromFile("../Resources/snakeHead.png"))
        snakeHeadTexture.loadFromFile("Resources/snakeHead.png");
    snakeHeadTexture.setSmooth(true);
    snakeHead.setTexture(snakeHeadTexture);
    snakeHead.setOrigin(sf::Vector2f(snakeHead.getLocalBounds().width / 2, snakeHead.getLocalBounds().height / 2));

    if (!appleTexture.loadFromFile("../Resources/apple.png"))
        appleTexture.loadFromFile("Resources/apple.png");
    appleTexture.setSmooth(true);
    snack.setTexture(appleTexture);

    if (!waterTexture.loadFromFile("../Resources/water.png"))
        waterTexture.loadFromFile("Resources/water.png");

    if (!bgGrassTexture.loadFromFile("../Resources/backgroundGrass.png"))
        bgGrassTexture.loadFromFile("Resources/backgroundGrass.png");
    bg.setTexture(bgGrassTexture);
    bg.setPosition(0, 0);

    if (!bgSandTexture.loadFromFile("../Resources/backgroundSand.png"))
        bgSandTexture.loadFromFile("Resources/backgroundSand.png");

    if (!menuTexture.loadFromFile("../Resources/menu.png"))
        menuTexture.loadFromFile("Resources/menu.png");
    menu.setTexture(menuTexture);
    menu.setPosition(0, 0);

    if (menuSandTexture.loadFromFile("../Resources/menuSand.png"))
        menuSandTexture.loadFromFile("Resources/menuSand.png");
}

void View::init_font()
{
    if (!font.loadFromFile("../Resources/pixel_font.ttf"))
        font.loadFromFile("Resources/pixel_font.ttf");
    highscoreText.setFont(font);
    highscoreText.setCharacterSize(30);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setPosition(5, 0);
    highscoreText.setString("0");
    highscoreText.setOutlineThickness(1);
    highscoreText.setOutlineColor(sf::Color::Black);

    text.setFont(font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::Black);
}

void View::change_theme(std::string board)
{
    if (board == "SAND")
    {
        bg.setTexture(bgSandTexture);
        snack.setTexture(waterTexture);
        menu.setTexture(menuSandTexture);
    }

    if (board == "GRASS")
    {
        bg.setTexture(bgGrassTexture);
        snack.setTexture(appleTexture);
        menu.setTexture(menuTexture);
    }
}

void View::draw_snake(sf::RenderWindow &win)
{

    std::queue<Position> snakeCopy = manager.getSnake();
    Position currentPos;

    while (snakeCopy.size() != 1)
    {
        currentPos = snakeCopy.front();
        snakeCopy.pop();

        snake.setPosition(currentPos.col * CellSize, currentPos.row * CellSize);
        win.draw(snake);
    }
    currentPos = snakeCopy.front();
    Direction facing = manager.getFacing();
    if (facing == NORTH)
        snakeHead.setRotation(0);
    if (facing == EAST)
        snakeHead.setRotation(90);
    if (facing == SOUTH)
        snakeHead.setRotation(180);
    if (facing == WEST)
        snakeHead.setRotation(270);
    snakeHead.setPosition(currentPos.col * CellSize + CellSize / 2, currentPos.row * CellSize + CellSize / 2);
    win.draw(snakeHead);
}

void View::display_menu(sf::RenderWindow &win)
{
    win.draw(menu);
}

void View::display_game(sf::RenderWindow &win)
{
    win.draw(bg);
    highscoreText.setString(std::to_string(manager.getHighscore()));
    win.draw(highscoreText);
    draw_snake(win);
    snack.setPosition(manager.getSnackPosition().col * CellSize, manager.getSnackPosition().row * CellSize);
    win.draw(snack);
}

void View::display_scoreboard(sf::RenderWindow &win)
{
    text.setPosition(100, 100);
    text.setString("GAME OVER");
    win.draw(text);
    text.setPosition(100, 175);
    text.setString("Your score: " + std::to_string(manager.getHighscore()));
    win.draw(text);
    text.setPosition(100, 255);
    text.setCharacterSize(30);
    text.setString("Scoreboard: ");

    win.draw(text);
    int j = 0;
    for (std::vector<int>::iterator i = scoreboard.getScoreboardBegin(); i < scoreboard.getScoreboardEnd(); i++)
    {
        std::string points = std::to_string(*i);
        j++;
        std::string score = std::to_string(j) + ". " + points;
        text.setPosition(100, 255 + 35 * j);
        text.setString(score);
        win.draw(text);
    }
    text.setCharacterSize(60);
}

void View::display_pause(sf::RenderWindow &win)
{
    text.setString("PAUSED");
    text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2));
    text.setPosition(400, 400);
    win.draw(text);
    text.setOrigin(sf::Vector2f(0, 0));
}