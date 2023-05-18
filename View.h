#ifndef VIEW_H
#define VIEW_H
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class View
{

    GameManager &manager;         // GameManager
    Scoreboard &scoreboard;               // Scoreboard

        sf::RectangleShape snake; // Snake Tail
    sf::RectangleShape snakeHead; // Snake Head
    sf::Sprite apple;             // Apple
    sf::Texture appleTexture;     // Apple Texture
    sf::Sprite bg;                // Background
    sf::Texture bgTexture;        // Background Texture
    sf::Text highscoreText;       // Highscore Text
    sf::Text finishedText;        // Victory/Defeat Text
    sf::Font font;                // Font

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
};

#endif