#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "View.h"
#include "Controller.h"
#include <time.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake", sf::Style::Close);
    window.setFramerateLimit(30);

    GameManager manager;
    View view;
    Controller controller(window, manager, view);

    sf::Clock clock;
    sf::Clock clock_turn;
    while (true)
    {
        if (clock_turn.getElapsedTime().asMilliseconds() >= 2500)
        {
            manager.turn(LEFT);
            clock_turn.restart();
        }
        if (clock.getElapsedTime().asMilliseconds() >= 500)
        {
            manager.update();
            manager.debug_display();
            clock.restart();
        }
        
    }
    // for (int i = 0; i < 15; i++)
    // {
    //     manager.update();
    //     manager.debug_display();
    //     manager.update();
    //     manager.debug_display();
    //     manager.update();
    //     manager.debug_display();
    //     manager.update();
    //     manager.debug_display();
    //     manager.update();
    //     manager.turn(LEFT);
    //     manager.debug_display();
    // }
    
    
    // manager.debug_display();
    //controller.play();
    return 0;
}