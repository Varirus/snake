#include "Scoreboard.h"

Scoreboard::Scoreboard(std::string name)
    : fileName(name)
{
    scoreboard.reserve(10);
    load_from_file();
}

std::vector<int>::iterator Scoreboard::getScoreboardBegin() { return scoreboard.begin(); }

std::vector<int>::iterator Scoreboard::getScoreboardEnd() { return scoreboard.end(); }

void Scoreboard::load_from_file()
{
    std::ifstream in(fileName);
    if (!in)
        return;

    std::string str;

    while ((std::getline(in, str)))
    {
        scoreboard.push_back(std::stoi(str));
    }
    in.close();
    while (scoreboard.size() != 10)
    {
        scoreboard.push_back(0);
    }
}

void Scoreboard::save_to_file()
{
    std::ofstream out(fileName);
    if (!out)
        return;

    std::string str;
    for (std::vector<int>::iterator i = scoreboard.begin(); i < scoreboard.end(); i++)
    {
        out << *i << std::endl;
    }
    out.close();
}

void Scoreboard::add_new_score(int score)
{
    if (scoreboard.begin() == scoreboard.end())
    {
        scoreboard.emplace_back(score);
        save_to_file();
        return;
    }
    for (std::vector<int>::iterator i = scoreboard.begin(); i < scoreboard.end(); i++)
    {
        if (*i < score)
        {
            scoreboard.pop_back();
            scoreboard.emplace(i, score);
            save_to_file();
            return;
        }
    }
}

void Scoreboard::show()
{
    int j = 0;
    for (std::vector<int>::iterator i = scoreboard.begin(); i < scoreboard.end(); i++)
    {
        // int score = *i.base();
        std::cout << (j + 1) << ". " << *i << std::endl;
        j++;
    }
}