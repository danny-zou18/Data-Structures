#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
#include "team.h"
#include "player.h"

using std::cout; using std::endl; using std::left; using std::right; using std::setw; 

//Function that checks if a string is in a vector
bool in_vector(const std::string& str, const std::vector<std::string>& vec){
    for (unsigned int i = 0; i < vec.size(); i++){
        if (str == vec[i]){
            return true;
        } 
    }
    return false;
}
bool in_vector_players(const std::string& player_name, const std::string& team_name, std::vector<std::vector<std::string> >& double_vec){
    for (unsigned int i = 0; i < double_vec.size(); i++){
        if (double_vec[i][0] == player_name && double_vec[i][1] == team_name){
            return true;
        } 
    }
    return false;
}
//Function that formats team stats and outputs it to file
void team_stats(std::vector<Team>& teams, const unsigned int max_team_length, std::ofstream& out_str){

    sort(teams.begin(),teams.end(),sort_team); //Sorts teams based on given conditions, biggest to smallest

    //Setting the correct widths for formatting
    out_str << left << setw(max_team_length) << "Team Name"
    << right << setw(2) << "W" << setw(4) << "L" << setw(4) << "T" << setw(7) << "Win%"
    << setw(7) << "Goals" << setw(11) << "Penalties" << "\n";
    //Goes through the sorted teams vector, formats it, then outputs it correspondingly
    for (unsigned int i = 0; i < teams.size(); i++){           
        out_str << left << setw(max_team_length) << teams[i].get_name() 
        << right << setw(2) << teams[i].get_wins() << setw(4) << teams[i].get_losses() << setw(4) 
        << teams[i].get_ties() << setw(7) << std::setprecision(2) << std::fixed <<teams[i].get_winperc() << setw(7) 
        << teams[i].get_goals() << setw(11) << teams[i].get_penalties() << "\n";
    }
}
//Function that formats player stats and outputs it to file
void player_stats(std::vector<Player>& players, const unsigned int max_player_length,
    const unsigned int max_team_length, std::ofstream& out_str){
    
    stable_sort(players.begin(),players.end(),sort_player); //Sorts players based on given conditions, from biggest to smallest

    //Setting the correct widths for formatting
    out_str << left << setw(max_player_length) << "Player Name" << left << setw(max_team_length) << "Team" 
    << right << setw(5) << "Goals" << setw(9) << "Assists" << setw(11) << "Penalties" << "\n";
    //Goes through the sorted players vector, formats it, then outputs it correspondingly
    for (unsigned int i = 0; i < players.size(); i++){
        out_str << left << setw(max_player_length) << players[i].get_name() << left << setw(max_team_length) << players[i].get_team()
        << right << setw(5) << players[i].get_goals() << setw(9) << players[i].get_assists()
        << setw(11) << players[i].get_penalties() << "\n";
    }
}
//Function that formats custom stats and outputs it to file
void custom_stats(std::vector<Team>& teams, const unsigned int max_team_length, std::ofstream& out_str, char* input_name){
    sort(teams.begin(),teams.end(),sort_team);

    //Settings the correct widths for formatting
    out_str << left << setw(max_team_length) << "Team Name" << right << setw(12) << "Home Wins" << setw(11) << "Away Wins"
    << setw(20) << "Percent Difference" << "\n";
    //Goes through the sorted teams vector, formats it, then outputs it correspondingly
    for (unsigned int i = 0; i < teams.size(); i++){
        out_str << left << setw(max_team_length) << teams[i].get_name() << right << setw(12) << teams[i].get_homewins()
        << setw(11) << teams[i].get_awaywins() << setw(19) << std::setprecision(2) << std::fixed << teams[i].get_percentdiff()
         << "%" << "\n";
    }

    //Calculates the average percent difference of all the teams
    float total_average = 0;
    for (unsigned int i = 0; i < teams.size(); i++){
        total_average += teams[i].get_percentdiff();
    }
    float average_change = total_average / float(teams.size());
    out_str << endl;
    out_str << "On average, Teams in " << input_name << " win " << std::setprecision(2) << std::fixed << average_change << "% more when playing on home field.";
}

int main(int argc, char* argv[]){
    if (argc != 4){             //ERROR CHECKING !!
        std::cerr << "Not enough arguments." << endl;
        exit(1);
    }
    std::ifstream in_str(argv[1]); 
    if (!in_str.good()){        //ERROR CHECKING !!
        std::cerr << "Can not open " << argv[1] << " to read!" << endl;
        exit(1);                                                           
    }
    std::ofstream out_str(argv[2]);
    if (!out_str.good()){       //ERROR CHECKING !!
        std::cerr << "Can not open " << argv[2] << " to write!" << endl;
        exit(1);
    }                   
    if (strcmp(argv[3], "--team_stats") != 0 && strcmp( argv[3], "--player_stats") != 0 && strcmp( argv[3], "--custom_stats") != 0){
        std::cerr << argv[3] << " is not a valid command." << endl;         //ERROR CHECKING !!
        exit(1); 
    }
    std::vector<std::string> all; //vector that stores all the iuputted strings

    std::string x; 
    while (in_str >> x){ //inputs string into all vector
        all.push_back(x);
    }

    std::vector<Team> teams; //Vector containing every single team as a class object
    std::vector<Team> current_teams; //Vector containing just the teams for the a single game, used to calculate which team wins
    std::vector<std::string> team_names; 

    //A 2-D vector that stores vectors containing seperate players and their correspondingly teams. 
    //For checking if two players have the same name but different teams.
    std::vector<std::vector<std::string> > players_and_teams; 

    std::vector<Player> players; //Vector containing every single player as a class object

    std::vector<std::string> assist_players;  //Stores every player that scores a assist
    std::vector<std::string> assist_teams;  
    std::vector<std::string> goal_players;  //Stores every player that scores a goal
    std::vector<std::string> goal_teams;
    std::vector<std::string> penal_players;  // stores every player that get a penaltie
    std::vector<std::string> penal_teams;

    std::string team_name;
    std::string player_name;
    std::string goal_penal;

    //main loop that goes through every single string in "all" vector
    unsigned int i = 0;
    while (i < all.size()){

        /* If the string is "at" or "vs.", than we know that the away team is before it and
        the home team is after it. Once we have set the teams as their respected variables, we check if
        the team is already a object member in the teams vector, if it is not we make it one and add it. */
        if (all[i] == "at" || all[i] == "vs."){
            std::string home_team = all[i+1];
            std::string away_team = all[i-1];
            if (!in_vector(home_team,team_names)){
                Team team(home_team);
                teams.push_back(team);
                team_names.push_back(team.get_name());
                current_teams.push_back(team);
            } else {
                Team team(home_team);
                current_teams.push_back(team);
            }
            if (!in_vector(away_team,team_names)){
                Team team(away_team);
                teams.push_back(team);
                team_names.push_back(team.get_name());
                current_teams.push_back(team);
            } else {
                Team team(away_team);
                current_teams.push_back(team);
            }
        }
        /* Checks if the string is a time, if it is, we'll know that the next string is going to be a team,
        the next next string is going to be either a penalty or a goal and that the next next next string
        is going to be a player name. If the next next string is a goal, then we'll also know where the assist players
        are. */
        if (all[i][1] == ':' || all[i][2] == ':'){
            if (in_vector(all[i+1], team_names)){
                team_name = all[i+1];
                goal_penal = all[i+2];
                if (goal_penal == "goal"){
                    int c = 0;
                    //Loop that looks for every assist player and checks if they are already a player member, if they are not 
                    //then make them into one and store it in "players" vector
                    while (all[(i+5)+c] != ")"){ 
                        if (!in_vector_players(all[(i+5)+c], team_name, players_and_teams)){
                            Player player(all[(i+5)+c], team_name);
                            players.push_back(player);
                            std::vector<std::string> filler;
                            filler.push_back(all[(i+5)+c]);
                            filler.push_back(team_name);
                            players_and_teams.push_back(filler);
                            assist_players.push_back(all[(i+5)+c]);
                            assist_teams.push_back(team_name);
                            c++;
                        } else {
                            assist_players.push_back(all[(i+5)+c]);
                            assist_teams.push_back(team_name);
                            c++;
                        }
                    }
                }
    
                if (all[i+3] == "BENCH"){ //Checks if a team receives a BENCH penalty, if not there is a player in that spot
                    for (unsigned int i = 0; i < teams.size();i++){
                        if (team_name == teams[i].get_name()){
                            if (goal_penal == "penalty"){
                                teams[i].add_penal();
                            }
                        }
                    }
                    i++;
                    continue;
                } else {
                    player_name = all[i+3];
                }
                /* Checks if player is already a object member in "players" vector, if they are not make them into one
                and add it. */
                if (!in_vector_players(player_name, team_name, players_and_teams)){
                    Player player(player_name, team_name);
                    players.push_back(player);
                    std::vector<std::string> filler; 
                    filler.push_back(player_name);
                    filler.push_back(team_name);
                    players_and_teams.push_back(filler);
                    if (goal_penal == "goal"){
                        goal_players.push_back(player_name);
                        goal_teams.push_back(team_name);
                    } else if (goal_penal == "penalty" && all[i+3] != "BENCH"){
                        penal_players.push_back(player_name);
                        penal_teams.push_back(team_name);
                    }
                } else {
                    if (goal_penal == "goal"){
                        goal_players.push_back(player_name);
                        goal_teams.push_back(team_name);
                    } else if (goal_penal == "penalty" && all[i+3] != "BENCH"){
                        penal_players.push_back(player_name);
                        penal_teams.push_back(team_name);
                    }
                }
                //Goes through the teams and gives them goals or penalities
                for (unsigned int i = 0; i < teams.size();i++){
                    if (team_name == teams[i].get_name()){
                        if (goal_penal == "goal"){
                            teams[i].add_goal();
                        } else if (goal_penal == "penalty"){
                            teams[i].add_penal();
                        }
                    break;
                    }
                }
                //Calculates the current games score so we can determine which team wins
                for (unsigned int i = 0; i < 2; i++){
                    if (team_name == current_teams[i].get_name()){
                        if (goal_penal == "goal"){
                            current_teams[i].add_goal();
                        }    
                    }
                }
            }
        }
        /*If the string is "FINAL" we know that the game is coming to an end, we determine which team wins by comparing
        their goals. If they have the same number of goals, then they both get a tie, otherwise, they get their corresponding
        losses or wins. */
        if (all[i] == "FINAL"){
            if (current_teams[0].get_goals() > current_teams[1].get_goals()){
                for (unsigned int i = 0; i < teams.size(); i++){
                    if (current_teams[0].get_name() == teams[i].get_name()){
                        teams[i].add_win();
                        teams[i].add_homewin();
                    }
                    if (current_teams[1].get_name() == teams[i].get_name()){
                        teams[i].add_loss();
                    }
                }
            } else if (current_teams[0].get_goals() < current_teams[1].get_goals()){
                for (unsigned int i = 0; i < teams.size(); i++){
                    if (current_teams[1].get_name() == teams[i].get_name()){
                        teams[i].add_win();
                        teams[i].add_awaywin();
                    }
                    if (current_teams[0].get_name() == teams[i].get_name()){
                        teams[i].add_loss();
                    }
                }
            } else {
                for (unsigned int i = 0; i < teams.size(); i++){
                    if (current_teams[1].get_name() == teams[i].get_name()){
                        teams[i].add_tie();
                    }
                    if (current_teams[0].get_name() == teams[i].get_name()){
                        teams[i].add_tie();
                    }
                }
            }
            //Clears the current teams so the next game can begin
            current_teams.clear();
        }
        i++;
    }    
    //Goes through all the goals players have scored and adds them to their corresponding player
    for (unsigned int x = 0; x < goal_players.size(); x++){
        for (unsigned int i = 0; i < players.size(); i++){
            if (goal_players[x] == players[i].get_name()){
                if (players[i].get_team() == goal_teams[x]){
                    players[i].add_goal();
                }
            }
        }
    }
    //Goes through all the penalties players have gotten and adds them to their corresponding player
    for (unsigned int x = 0; x < penal_players.size(); x++){
        for (unsigned int i = 0; i < players.size(); i++){
            if (penal_players[x] == players[i].get_name()){
                if (players[i].get_team() == penal_teams[x]){
                    players[i].add_penaltie();
                }
            }
        }
    }
    //Goes through all the assist players have scored and adds them to their corresponding player
    for (unsigned int x = 0; x < assist_players.size(); x++){
        for (unsigned int i = 0; i < players.size(); i++){
            if (assist_players[x] == players[i].get_name()){
                if (players[i].get_team() == assist_teams[x]){
                    players[i].add_assist();
                }
            }
        }
    }
    //Goes through all the teams and calculates their win percentage and percentage difference
    for (unsigned int i = 0; i < teams.size(); i++){
        teams[i].calc_winperc();
        teams[i].calc_percentdiff();
    }
    //Finds the maximum player length for formatting
    unsigned int max_player_length = 0;
    for (unsigned int i = 0; i < players.size(); i++){
        unsigned int temp_length = players[i].get_name().size();
        max_player_length = std::max(max_player_length,temp_length);
    }
    max_player_length += 2;
    //Finds the maximum team length for formatting
    unsigned int max_team_length = 0;
    for (unsigned int i = 0; i < teams.size(); i++){
        unsigned int temp_length = teams[i].get_name().size();
        max_team_length = std::max(max_team_length,temp_length);
    }
    max_team_length += 3;
    
    if (strcmp(argv[3],"--team_stats") == 0){
        team_stats(teams,max_team_length, out_str);
    } else if (strcmp(argv[3],"--player_stats") == 0){
        player_stats(players,max_player_length, max_team_length, out_str);
    } else if (strcmp(argv[3],"--custom_stats") == 0){
        custom_stats(teams, max_team_length, out_str, argv[1]);
    }
    
    out_str.close();
    return 0;
}
    

    sdiofdoisfiodsjfodsifoijds