#ifndef __player_h_
#define __player_h_
#include <string>
#include <vector>

class Player{
public:
    //Constructor
    Player(const std::string& player_name, const std::string& team);

    //Accessors
    std::string get_name() const;
    std::string get_team() const;
    int get_goals() const;
    int get_assists() const;
    int get_penalties() const;

    //Modifiers
    void add_goal();
    void add_assist();
    void add_penaltie();

private:
    std::string name;
    std::string team;
    int goals;
    int assists;
    int penalties;
};

bool sort_player(const Player& player1, const Player& player2);

#endif