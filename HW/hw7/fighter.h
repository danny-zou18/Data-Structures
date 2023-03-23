#ifndef __fighter_h_
#define __fighter_h_
#include <string>
#include <map>
#include <utility>
#include <set>
#include <fstream>

using std::string; using std::map; using std::pair; using std::set; using std::endl;

//Custom comparator that sorts a set based off the character frametimes
class CompareFrameTime {
public:
    bool operator()(const map<string, int>& lhs, const map<string, int>& rhs) const {
        if (lhs.begin()->second != rhs.begin()->second){
            return lhs.begin()->second < rhs.begin()->second;
        } else {
            return lhs.begin()->first > rhs.begin()->first;
        }
        
    }
};
//Basically the same comparator as the one above, but sorts the cases where the frametime is the same differently
class CompareFrameTime2 {
public:
    bool operator()(const map<string, int>& lhs, const map<string, int>& rhs) const {
        if (lhs.begin()->second != rhs.begin()->second){
            return lhs.begin()->second < rhs.begin()->second;
        } else {
            return lhs.begin()->first < rhs.begin()->first;
        }
        
    }
};
//Custom comparator that sorts a set based on moveName
class CompareMoveName {
public:
    bool operator()(const map<string, int>& lhs, const map<string, int>& rhs) const {
        return lhs.begin()->first < rhs.begin()->first;
    }
};
//Custom comparator that sorts a set based on names
class CompareName {
public:
    bool operator()(const string& ls, const string& rs) const {
        return ls < rs;
	}
};
class Fighter{
public:
    //Constructor
    Fighter(const string& charName);

    //Accessors
    int getMoveTime(const string& moveName) const;
    string getName() const {return name;}
    map<string, int> getMoves() const {return moves;}
    set<map<string, int>, CompareMoveName > getSortedMoves() const {return sortedMoves;}
    void printSortedMoves(std::ostream& out) const;
    bool hasMoveFrame(const string& moveName, int frameTime) const;

    //Modifiers
    void setMove(const string& moveName, int frameCount) {moves[moveName] = frameCount;}
    void sortMoves();
    void makeMoves(map<string, set<map<string, int>, CompareFrameTime > >& allCharMoves);
    void addMoves(map<string, set<map<string, int >, CompareFrameTime > >& allCharMoves);

private:
    //Private variables
    string name;
    map<string,int> moves;
    set<map<string, int>, CompareMoveName> sortedMoves;
};
#endif