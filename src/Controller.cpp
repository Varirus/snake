#include "Controller.h"

Controller::Controller(sf::RenderWindow &w, GameManager &m, View &v)
    : window(w), manager(m), view(v)
{
}

bool Controller::button_click(int mouseX, int mouseY, std::string button)
{
    if (mouseY >= 586 && mouseY <= 650)
    {
        if (button == "GRASS")
        {
            if (mouseX >= 608 && mouseX <= 671)
            {
                return true;
            }
        }
        if (button == "SAND")
        {
            if (mouseX >= 691 && mouseX <= 755)
            {
                return true;
            }
        }
    }
    if (mouseY < 448 || mouseY > 564)
    {
        return false;
    }
    if (button == "EASY")
    {
        if (mouseX >= 35 && mouseX <= 260)
        {
            return true;
        }
    }
    if (button == "NORMAL")
    {
        if (mouseX >= 291 && mouseX <= 516)
        {
            return true;
        }
    }
    if (button == "HARD")
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
                    if (button_click(event.mouseButton.x, event.mouseButton.y, "EASY"))
                    {
                        manager.change_gameDifficulty(EASY);
                        return;
                    }
                    if (button_click(event.mouseButton.x, event.mouseButton.y, "NORMAL"))
                    {
                        manager.change_gameDifficulty(NORMAL);
                        return;
                    }
                    if (button_click(event.mouseButton.x, event.mouseButton.y, "HARD"))
                    {
                        manager.change_gameDifficulty(HARD);
                        return;
                    }
                    if (button_click(event.mouseButton.x, event.mouseButton.y, "GRASS"))
                    {
                        view.change_theme("GRASS");
                    }
                    if (button_click(event.mouseButton.x, event.mouseButton.y, "SAND"))
                    {
                        view.change_theme("SAND");
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        view.display_menu(window);

        window.display();
    }
}

void Controller::play(bool debug)
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
                // Movement
                if (manager.getGameState() == RUNNING)
                {
                    Direction facing = manager.getFacing();
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                    {
                        if (facing == EAST)
                            manager.setPendingTurn(LEFT);
                        if (facing == WEST)
                            manager.setPendingTurn(RIGHT);
                    }
                    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                    {
                        if (facing == NORTH)
                            manager.setPendingTurn(LEFT);
                        if (facing == SOUTH)
                            manager.setPendingTurn(RIGHT);
                    }
                    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    {
                        if (facing == EAST)
                            manager.setPendingTurn(RIGHT);
                        if (facing == WEST)
                            manager.setPendingTurn(LEFT);
                    }
                    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    {
                        if (facing == NORTH)
                            manager.setPendingTurn(RIGHT);
                        if (facing == SOUTH)
                            manager.setPendingTurn(LEFT);
                    }
                }
                // Pause
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
                if(debug)
                    manager.debug_display();

                clock.restart();
            }
        }

        window.clear(sf::Color::Black);

        // Game Display
        view.display_game(window);

        // Pause Display
        if (manager.getGameState() == PAUSED)
            view.display_pause(window);

        // Game Over Display
        if (manager.getGameState() == FINISHED)
        {
            view.display_scoreboard(window);
            if (clock.getElapsedTime().asSeconds() >= 5)
            {
                manager.resetGame();
                return;
            }
        }

        window.display();
    }
}