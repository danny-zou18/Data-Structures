#include "fighter.h"

Fighter::Fighter(const string& charName){
    name = charName;
}
//Fighter function that takes in a moveName and returns the frame time for that move
int Fighter::getMoveTime(const string& moveName) const {
    map<string,int>::const_iterator it = moves.find(moveName);
    if (it != moves.end()){
        return it->second;
    } else {
        return -1;
    }
}
//Fighter function that takes a outfile as reference and then writes out all the characters moves
//based on move name
void Fighter::printSortedMoves(std::ostream& out) const {
    for (set<map<string, int> >::const_iterator it = sortedMoves.begin(); it != sortedMoves.end(); it++){
        for (map<string, int>::const_iterator it1 = (*it).begin(); it1 != (*it).end(); it1++){
            out << name << " " << it1->first << ": " << it1->second << endl;
        }
    }
}
//Fighter function that checks if the character has the specific frametime for the particular move
bool Fighter::hasMoveFrame(const string& moveName, int frameTime) const {
    if ((moves.find(moveName)->second) == frameTime){
        return true;
    } 
    return false;
}
//Fighter function that sorts the moves based on move name
void Fighter::sortMoves(){
    for (map<string, int>::const_iterator it = moves.begin(); it != moves.end(); it++){
        map<string, int> tempMap;
        tempMap.insert(pair<string,int>(it->first, it->second));
        sortedMoves.insert(tempMap);
    }
}
//Fighter function that initializes the moves in the allCharMoves map
void Fighter::makeMoves(map<string, set<map<string, int>, CompareFrameTime > >& allCharMoves){
    for (map<string,int>::iterator it = moves.begin(); it != moves.end(); it++){
    string moveName = it->first;
    pair<string, int> charTime(name, it->second);
    map<string, int> characterTimes;
    characterTimes.insert(charTime);
    set<map<string, int>, CompareFrameTime > allCharTimes;
    allCharTimes.insert(characterTimes);
    allCharMoves.insert(pair<string, set<map<string,int>, CompareFrameTime > >(moveName, allCharTimes));
    }
}
//Function that adds the character's move's frametimes respectively to the allCharMoves map
void Fighter::addMoves(map<string, set<map<string, int >, CompareFrameTime > >& allCharMoves){
    map<string, set<map<string, int>, CompareFrameTime > >::iterator it1;
    for (map<string, int>::iterator it = moves.begin(); it != moves.end(); it++){
        string moveName = it->first;
        pair<string, int> charTime(name, it->second);
        map<string, int> characterTimes;
        characterTimes.insert(charTime);
        it1 = (allCharMoves.find(moveName));
        (it1->second).insert(characterTimes);
    }
}