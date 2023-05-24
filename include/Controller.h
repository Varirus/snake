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
        @param diff desired difficulty

     */
    bool isInStartButton(int mouseX, int mouseY, DifficultyLevel diff);

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