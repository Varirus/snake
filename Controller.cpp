#include "Controller.h"

Controller::Controller(sf::RenderWindow &w, GameManager &m, View &v)
    : window(w), manager(m), view(v)
{

}

void Controller::play()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        sf::Clock clock;
        while (true)
        {
            if (clock.getElapsedTime().asMilliseconds() >= 1000)
            {
                clock.restart();
            }
        }

        window.clear(sf::Color::Black);
        //view.display(window);

        window.display();
    }
}