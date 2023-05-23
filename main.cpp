#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "View.h"
#include "Controller.h"
#include "Scoreboard.h"
#include <time.h>

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    Scoreboard scoreboard("scoreboard.txt");
    GameManager manager(NORMAL, scoreboard);
    View view(manager, scoreboard);
    Controller controller(window, manager, view);

    controller.show_menu();
    return 0;
}