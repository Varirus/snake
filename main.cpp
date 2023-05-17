#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "View.h"
#include "Controller.h"
#include <time.h>

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(BoardSizeRow * 20, BoardSizeCol * 20), "Snake", sf::Style::Close);
    window.setFramerateLimit(30);

    GameManager manager(HARD);
    View view(manager);
    Controller controller(window, manager, view);

    controller.play();

    // sf::Clock clock;
    // sf::Clock clock_turn;
    // while (true)
    // {
    //     if (clock_turn.getElapsedTime().asMilliseconds() >= 5500)
    //     {
    //         manager.turn(LEFT);
    //         clock_turn.restart();
    //     }
    //     if (clock.getElapsedTime().asMilliseconds() >= manager.getSnakeSpeed())
    //     {
    //         manager.update();
    //         manager.debug_display();
    //         clock.restart();
    //     }
    // }
    return 0;
}