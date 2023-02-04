#ifndef __team_h_
#define __team_h_
#include <string>
#include <vector>

class Team{
public:
    //Constructor
    Team(const std::string& theName);

    //Accessors
    std::string get_name() const;
    int get_wins() const;
    int get_losses() const;
    int get_ties() const;
    int get_goals() const;
    int get_penalties() const;
    float get_winperc() const;

    int get_homewins() const;
    int get_awaywins() const;
    float get_percentdiff() const;

    //Modifiers
    void add_goal();
    void add_penal();
    void add_win();
    void add_loss();
    void add_tie();
    void calc_winperc();

    void add_homewin();
    void add_awaywin();
    void calc_percentdiff();
    void has_homeadv();

private:
    std::string name;
    int wins;
    int losses;
    int ties;
    int goals;
    int penalties;
    float win_perc;

    int games_won_home;
    int games_won_away;
    float percent_diff;
    

};

bool sort_team(const Team& team1, const Team& team2);
#endif