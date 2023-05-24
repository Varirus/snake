#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <iostream>
#include <vector>
#include <fstream>

class Scoreboard
{
    std::string fileName;
    std::vector<int> scoreboard;

public:
    /**
        @brief Construct a new Scoreboard object.

        @param name file name

     */
    Scoreboard(std::string name);

    /**
        @brief Returns scoreboard vector begin

        @return scoreboard vector begin
     */
    std::vector<int>::iterator getScoreboardBegin();

    /**
        @brief Returns scoreboard vector end

        @return scoreboard vector end
     */
    std::vector<int>::iterator getScoreboardEnd();

    /**
        @brief Loads scoreboard from file

     */
    void load_from_file();

    /**
        @brief Saves scoreboard to file

     */
    void save_to_file();

    /**
        @brief Adds score to scoreboard at correct place

        @param score score
     */
    void add_new_score(int score);

    /**
        @brief Show scoreboard in terminal

     */
    void show();
};

#endif