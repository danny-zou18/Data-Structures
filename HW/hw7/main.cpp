#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <set>
#include "fighter.h"
//You may add additional typedefs, includes, etc. up here

using std::string; using std::map; using std::pair; using std::cout; using std::endl;
using std::set;

void commandQ(std::ostream& out, const map<string, Fighter> fighters, const string& theMove, const string& charName){
	if (theMove == "all"){
		map<string, Fighter>::const_iterator it;
		it = fighters.find(charName);
		(it->second).printSortedMoves(out);
	} else {
		map<string, Fighter>::const_iterator it;
		it = fighters.find(charName);
		out << charName << " " << theMove << ": " << (it->second).getMoveTime(theMove) << endl;
	}
}
void commandF(std::ostream& out, const map<string, set<map<string, int>, CompareFrameTime> >& moves, 
	const string& moveName, unsigned int limit){
		map<string, set<map<string, int>, CompareFrameTime> >::const_iterator it;
		it = moves.find(moveName);
		out << "-f " << moveName << " " << limit << endl;
		if (limit <= (it->second).size()){
		set<map<string, int>, CompareFrameTime>::iterator it1 = (it->second).begin();
		for (unsigned int i = 0; i < limit; i++){
			for (map<string, int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
				out << it2->first << " " << it2->second << endl;
			}
			it1++;
		}
		} else {
			set<map<string, int>, CompareFrameTime>::iterator it1;
			for (it1 = (it->second).begin(); it1 != (it->second).end(); it1++){
				for (map<string, int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
					out << it2->first << " " << it2->second << endl;
				}
			}
		}
}
void commandS(std::ostream& out, const map<string, set<map<string, int>, CompareFrameTime> >& moves, 
	const string& moveName, unsigned int limit){
		map<string, set<map<string, int>, CompareFrameTime> >::const_iterator it;
		it = moves.find(moveName);
		out << "-s " << moveName << " " << limit << endl;
		if (limit <= (it->second).size()){
			set<map<string, int>, CompareFrameTime>::reverse_iterator it1 = (it->second).rbegin();
			for (unsigned int i = 0; i < limit; i++){
				for (map<string, int>::const_iterator it = (*it1).begin(); it != (*it1).end(); it++){
					out << it->first << " " << it->second << endl;
				}
				it1++;
			}
		} else {
			set<map<string, int>, CompareFrameTime>::reverse_iterator it1;
			for (it1 = (it->second).rbegin(); it1 != (it->second).rend(); it1++){
				for (map<string, int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
					out << it2->first << " " << it2->second << endl;
				}
			}
		}
}
void commandD(std::ostream& out, )

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}
	map<string, Fighter> fighters;
	map<string, set<map<string, int>, CompareFrameTime> > moves;

	string charName, jab, forwardTilt, upTilt, downTilt, forwardSmash, upSmash, downSmash;
	int jabT, forwardTiltT, upTiltT, downTiltT, forwardSmashT, upSmashT, downSmashT;

	dbfile >> charName >> jab >> forwardTilt >> upTilt >> downTilt >> forwardSmash >> upSmash >> downSmash;

	while (dbfile >> charName){
		dbfile >> jabT >> forwardTiltT >> upTiltT >> downTiltT >> forwardSmashT >> upSmashT >> downSmashT;
		Fighter fighter(charName);
		fighter.setMove(jab, jabT);
		fighter.setMove(forwardTilt, forwardTiltT);
		fighter.setMove(upTilt, upTiltT);
		fighter.setMove(downTilt, downTiltT);
		fighter.setMove(forwardSmash, forwardSmashT);
		fighter.setMove(upSmash, upSmashT);
		fighter.setMove(downSmash, downSmashT);
		fighter.sortMoves();
		fighters.insert(pair<string, Fighter>(charName, fighter));
		
	}
	for (map<string, Fighter>::iterator it = fighters.begin(); it != fighters.end(); it++){
		if (it == fighters.begin()){
			(it->second).makeMoves(moves);
			continue;
		}
		(it->second).addMoves(moves);
	}
	string dashCommand, theMove;
	int frameCount, limit;
	while (infile >> dashCommand){
		char command = dashCommand[1];
		if (command == 'q'){
			infile >> charName >> theMove;
			if (fighters.find(charName) != fighters.end()){
				if (moves.find(theMove) != moves.end() || theMove == "all"){
					commandQ(outfile, fighters, theMove, charName);
				} else {
					outfile << "Invalid move name: " << theMove << endl;
				}
			} else {
				outfile << "Invalid character name: " << charName << endl;
			}
			outfile << endl;
		} else if (command == 'f'){
			infile >> theMove >> limit;
			if (moves.find(theMove) != moves.end()){
				commandF(outfile, moves, theMove, limit);
			} else {
				outfile << "Invalid move name: " << theMove << endl;
			}
			outfile << endl;
		} else if (command == 's'){
			infile >> theMove >> limit;
			if (moves.find(theMove) != moves.end()){
				commandS(outfile, moves, theMove, limit);
			} else {
				outfile << "Invalid move name: " << theMove << endl;
			}
			outfile << endl;
		} else if (command == 'd'){

		}
	}


	return 0;
}
