#include "team.h"
#include <string>
#include <cmath>

Team::Team(const std::string& theName){
    name = theName;
    wins = 0;
    losses = 0;
    ties = 0;
    goals = 0;
    penalties = 0;
    win_perc = 0.0;

    games_won_home = 0;
    games_won_away = 0;
    percent_diff = 0;
}
std::string Team::get_name() const{
    return name;
}
int Team::get_wins() const{
    return wins;
}
int Team::get_losses() const{
    return losses;
}
int Team::get_goals() const{
    return goals;
}
int Team::get_ties() const{
    return ties;
}
int Team::get_penalties() const{
    return penalties;
}
float Team::get_winperc() const{
    return win_perc;
}
int Team::get_homewins() const{
    return games_won_home;
}
int Team::get_awaywins() const{
    return games_won_away;
}
float Team::get_percentdiff() const{
    return percent_diff;
}
void Team::add_goal(){
    goals += 1;
}
void Team::add_penal(){
    penalties += 1;
}
void Team::add_win(){
    wins += 1;
}
void Team::add_loss(){
    losses += 1;
}
void Team::add_tie(){
    ties += 1;
}
void Team::calc_winperc(){
    win_perc = (wins+(0.5*ties))/(wins+losses+ties);
}
void Team::add_homewin(){
    games_won_home += 1;
}
void Team::add_awaywin(){
    games_won_away += 1;
}
//Calculate percent diff
void Team::calc_percentdiff(){
    int filler = games_won_home - games_won_away;
    if (games_won_away == 0){
        percent_diff = 100;
    } else {
        percent_diff = (((filler)/(float(games_won_away+games_won_home)/2))) * 100;
    }
}       
//Team sorting function
bool sort_team(const Team& team1, const Team& team2){

    if (team1.get_winperc() == team2.get_winperc() && team1.get_goals() == team2.get_goals()){
        if (team1.get_name() < team2.get_name()){
            return true;
        } else {
            return false;
        }
    } else if (team1.get_winperc() == team2.get_winperc()){
        if (team1.get_goals() < team2.get_goals()){
            return false;
        } else {
            return true;
        }
    } else {
        if (team1.get_winperc() < team2.get_winperc()){
            return false;
        } else {
            return true;
        }
    }
}

