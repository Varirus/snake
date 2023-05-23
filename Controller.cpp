#include "Controller.h"

Controller::Controller(sf::RenderWindow &w, GameManager &m, View &v)
    : window(w), manager(m), view(v)
{
}

bool Controller::isInStartButton(int mouseX, int mouseY, DifficultyLevel diff)
{
    if(mouseY < 448 || mouseY > 564){
        return false;
    }
    if(diff == EASY){
        if (mouseX >= 35 && mouseX <= 260){
            return true;
        }
    }
    if (diff == NORMAL)
    {
        if (mouseX >= 291 && mouseX <= 516)
        {
            return true;
        }
    }
    if (diff == HARD)
    {
        if (mouseX >= 542 && mouseX <= 767)
        {
            return true;
        }
    }
    return false;
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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isInStartButton(event.mouseButton.x, event.mouseButton.y, EASY))
                    {
                        manager.change_gameDifficulty(EASY);
                        play();
                    }
                    if (isInStartButton(event.mouseButton.x, event.mouseButton.y, NORMAL))
                    {
                        manager.change_gameDifficulty(NORMAL);
                        play();
                    }
                    if (isInStartButton(event.mouseButton.x, event.mouseButton.y, HARD))
                    {
                        manager.change_gameDifficulty(HARD);
                        play();
                    }
                }
            }
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
                    if (manager.getGameState() == RUNNING)
                        manager.setPendingTurn(LEFT);
                }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    if (manager.getGameState() == RUNNING)
                        manager.setPendingTurn(RIGHT);
                }
                if (event.key.code == sf::Keyboard::Escape)
                {

                    if (manager.getGameState() == RUNNING)
                        manager.stop_game();

                    else if (manager.getGameState() == PAUSED)
                        manager.start_game();
                }
            }
        }
        if (manager.getGameState() == RUNNING)
        {
            if (clock.getElapsedTime().asMilliseconds() >= manager.getSnakeSpeed())
            {
                manager.turn(manager.getPendingTurn());
                manager.update();

                // manager.debug_display();

                clock.restart();
            }
        }

        window.clear(sf::Color::Black);

        view.display_game(window);

        if (manager.getGameState() == PAUSED)
        {
            view.display_pause(window);
        }

        if (manager.getGameState() == FINISHED)
        {
            view.display_scoreboard(window);
        }

        window.display();
    }
}