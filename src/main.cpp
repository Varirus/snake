#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "View.h"
#include "Controller.h"
#include "Scoreboard.h"
#include <time.h>

int main()
{
    //no elo
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Scoreboard scoreboard("scoreboard.txt");
    GameManager manager(NORMAL, scoreboard);
    View view(manager, scoreboard);
    Controller controller(window, manager, view);

    while (window.isOpen())
    {
        controller.show_menu();
        controller.play(false);
    }

    return 0;
}