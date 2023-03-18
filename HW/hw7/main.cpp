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
	set<string> moves;

	string charName, jab, forwardTilt, upTilt, downTilt, forwardSmash, upSmash, downSmash;
	int jabT, forwardTiltT, upTiltT, downTiltT, forwardSmashT, upSmashT, downSmashT;

	dbfile >> charName >> jab >> forwardTilt >> upTilt >> downTilt >> forwardSmash >> upSmash >> downSmash;

	moves.insert(jab); moves.insert(forwardTilt); moves.insert(upTilt); moves.insert(downTilt); 
	moves.insert(forwardSmash); moves.insert(upSmash); moves.insert(downSmash);

	while (dbfile >> charName){
		dbfile >> jabT >> forwardTiltT >> upTiltT >> downTiltT >> forwardSmashT >> upSmashT >> downSmashT;
		Fighter fighter(charName);
		fighter.setMove("jab", jabT);
		fighter.setMove("forward-tilt", forwardTiltT);
		fighter.setMove("up-tilt", upTiltT);
		fighter.setMove("down-tilt", downTiltT);
		fighter.setMove("forward-smash", forwardSmashT);
		fighter.setMove("up-smash", upSmashT);
		fighter.setMove("down-smash", downSmashT);
		fighters[charName] = fighter;
	}
	for (map<string,Fighter>::iterator it = fighters.begin(); it != fighters.end(); it++){
		cout << it->first << endl;
	}























	return 0;
}
