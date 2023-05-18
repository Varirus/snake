#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "View.h"
#include "Controller.h"
#include "Scoreboard.h"
#include <time.h>

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(BoardSizeRow * 40, BoardSizeCol * 40), "Snake", sf::Style::Close);
    window.setFramerateLimit(60);

    Scoreboard scoreboard("scoreboard.txt");
    GameManager manager(NORMAL, scoreboard);
    View view(manager, scoreboard);
    Controller controller(window, manager, view);

    controller.play();
    return 0;
}