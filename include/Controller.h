#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "GameManager.h"
#include "View.h"
#include <SFML/Graphics.hpp>

class Controller
{
    sf::RenderWindow &window; // Window
    GameManager &manager;     // GameManager
    View &view;               // View

public:
    /**
        @brief Construct a new Controller object.

        @param w window
        @param m GameManager
        @param v View
     */
    Controller(sf::RenderWindow &w, GameManager &m, View &v);

    /**
        @brief Checks if mouse click was in one of play buttons

        @param mouseX mouse X coordinate
        @param mouseY mouse Y coordinate
        @param button desired button

        @return \b true - if click is in desired button
        @return \b false - if click is not in desired button
     */
    bool button_click(int mouseX, int mouseY, std::string button);

    /**
        @brief Shows menu

     */
    void show_menu();

    /**
        @brief Starts the game

     */
    void play();
};

#endif