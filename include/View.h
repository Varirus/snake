#ifndef VIEW_H
#define VIEW_H
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class View
{

    GameManager &manager;   // GameManager
    Scoreboard &scoreboard; // Scoreboard

    sf::Sprite snake;             // Snake
    sf::Texture snakeTexture;     // Snake Texture
    sf::Sprite snakeHead;         // Snake Head
    sf::Texture snakeHeadTexture; // Snake Head Texture
    sf::Sprite snack;             // Snack
    sf::Texture appleTexture;     // Apple Texture
    sf::Texture waterTexture;     // Water Texture
    sf::Sprite bg;                // Background
    sf::Texture bgGrassTexture;   // Background Grass Texture
    sf::Texture bgSandTexture;    // Background Sand Texture
    sf::Sprite menu;              // Menu
    sf::Texture menuTexture;      // Menu Texture
    sf::Text highscoreText;       // Highscore Text
    sf::Text text;                // Information Text
    sf::Font font;                // Font

    const int CellSize = 40; // Defined CellSize

public:
    /**
        @brief Construct a new View object.

        @param mgr GameManager

     */
    View(GameManager &mgr, Scoreboard &sb);

    /**
           @brief Initializes sprites

     */
    void init_sprites();

    /**
           @brief Initializes font and text settings

     */
    void init_font();

    /**
           @brief Change Game Theme

           @param board desired board

     */
    void change_theme(std::string board);

    /**
           @brief Draws Snake

           @param win RenderWindow

     */
    void draw_snake(sf::RenderWindow &win);

    /**
           @brief Draws menu on the window

           @param win RenderWindow

     */
    void display_menu(sf::RenderWindow &win);

    /**
           @brief Draws game on the window

           @param win RenderWindow

     */
    void display_game(sf::RenderWindow &win);

    /**
           @brief Draws victory/defeat text and scoreboard

           @param win RenderWindow

     */
    void display_scoreboard(sf::RenderWindow &win);

    /**
           @brief Draws pause text

           @param win RenderWindow

     */
    void display_pause(sf::RenderWindow &win);
};

#endif