#include "fighter.h"

Fighter::Fighter(const string& charName){
    name = charName;
}
int Fighter::getMoveTime(const string& moveName) const {
    map<string,int>::const_iterator it = moves.find(moveName);
    if (it != moves.end()){
        return it->second;
    } else {
        return -1;
    }
}
void Fighter::printSortedMoves(std::ostream& out) const {
    for (set<map<string, int> >::const_iterator it = sortedMoves.begin(); it != sortedMoves.end(); it++){
        for (map<string, int>::const_iterator it1 = (*it).begin(); it1 != (*it).end(); it1++){
            out << name << " " << it1->first << ": " << it1->second << endl;
        }
    }
}
void Fighter::sortMoves(){
    for (map<string, int>::const_iterator it = moves.begin(); it != moves.end(); it++){
        map<string, int> tempMap;
        tempMap.insert(pair<string,int>(it->first, it->second));
        sortedMoves.insert(tempMap);
    }
}
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