#include "Controller.h"

Controller::Controller(sf::RenderWindow &w, GameManager &m, View &v)
    : window(w), manager(m), view(v)
{
}

void Controller::show_menu()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        view.display_menu(window);

        window.display();
    }
}

void Controller::play()
{
    manager.start_game();
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    manager.setPendingTurn(LEFT);
                }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    manager.setPendingTurn(RIGHT);
                }
            }
        }
        if (manager.getGameState() == RUNNING)
        {
            if (clock.getElapsedTime().asMilliseconds() >= manager.getSnakeSpeed())
            {
                manager.turn(manager.getPendingTurn());
                manager.update();

                //manager.debug_display();

                clock.restart();
            }
        }

        window.clear(sf::Color::Black);

        view.display_game(window);

        if (manager.getGameState() == FINISHED)
        {
            view.display_scoreboard(window);
        }

        window.display();
    }
}