#include "player.h"
#include <string>

Player::Player(const std::string& player_name, const std::string& team_name){
    name = player_name;
    team = team_name;
    goals = 0;
    assists = 0;
    penalties = 0;
}

std::string Player::get_name() const {
    return name;
}
std::string Player::get_team() const {
    return team;
}
int Player::get_goals() const {
    return goals;
}
int Player::get_assists() const {
    return assists;
}
int Player::get_penalties() const {
    return penalties;
}
void Player::add_goal() {
    goals += 1;
}
void Player::add_assist() {
    assists += 1;
}
void Player::add_penaltie() {
    penalties += 1;
}
//sort function for players
bool sort_player(const Player& player1, const Player& player2){
    int total1 = player1.get_goals() + player1.get_assists();
    int total2 = player2.get_goals() + player2.get_assists();
    if (total1 == total2 && player1.get_penalties() == player2.get_penalties()){
        if (player1.get_name() < player2.get_name()){
            return true;
        } else {
            return false;
        }
    } else if (total1 == total2){
        if (player1.get_penalties() > player2.get_penalties()){
            return false;
        } else {
            return true;
        }
    } else {
        if (total1 < total2){
            return false;
        } else {
            return true;
        }
    }
}