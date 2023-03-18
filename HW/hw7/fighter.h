#ifndef __fighter_h_
#define __fighter_h_
#include <string>
#include <map>

using std::string; using std::map;

class Fighter{
public:
    Fighter(string charName) {name = charName;}

    int getMoveTime(string moveName) const {return moves[moveName];}

    void setMove(string moveName, int frameCount) {moves[moveName] = frameCount;}

private:
    string name;
    map<string,int> moves;


};
#endif