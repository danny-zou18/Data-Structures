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

//Function for if the command is Q, write the data to a outfile by passing the oufile as a reference.
// Then check if it wants a specific move or all the moves, if they only want a specific move, find the character
// and then get the move's frame count using the getMoveTime function. Else if we want all the moves, we find the character
// and then call "printSortedMoves" to write all the characters moves to the outfile by reference
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
//Function for if the command if F, write the data to a outfile by passing the oufile as a reference.
// First we find the move in the moves map, then insert all the character run times into a new correctly sorted set
// and then write out the correct number of characters to the outfile
void commandF(std::ostream& out, const map<string, set<map<string, int>, CompareFrameTime> >& moves, 
	const string& moveName, unsigned int limit){
		map<string, set<map<string, int>, CompareFrameTime> >::const_iterator it;
		it = moves.find(moveName);
		set<map<string, int>, CompareFrameTime2> new_set;
		new_set.insert((it->second).begin(),(it->second).end());
		out << "-f " << moveName << " " << limit << endl;
		//If the limit is smaller then the amount of characters
		if (limit <= (it->second).size()){
			set<map<string, int>, CompareFrameTime2>::iterator it1 = (new_set).begin();
			for (unsigned int i = 0; i < limit; i++){
				for (map<string, int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
					out << it2->first << " " << it2->second << endl;
				}
				it1++;
			}
		// if the limit is greater then the amount of characters, then we just write out every 
		// single character and their data
		} else {
			set<map<string, int>, CompareFrameTime2>::iterator it1;
			for (it1 = (new_set).begin(); it1 != (new_set).end(); it1++){
				for (map<string, int>::const_iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++){
					out << it2->first << " " << it2->second << endl;
				}
			}
		}
}
//Function for if the command is S, write the data to a outfile by passing the oufile as a reference.
// First we find the move in the moves map, and then determine if the limit is smaller or greater then the
// amount of characters. Then respectively write out the correct number of data
void commandS(std::ostream& out, const map<string, set<map<string, int>, CompareFrameTime> >& moves, 
	const string& moveName, unsigned int limit){
		map<string, set<map<string, int>, CompareFrameTime> >::const_iterator it;
		it = moves.find(moveName);
		out << "-s " << moveName << " " << limit << endl;
		//Iterate backwards to get the slowest moving characters
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
//Function for if the command is D, write the data to a outfile by passing the oufile as a reference.
// Make a new set to store the characters that have the specified move frametime, then iterate through
// the all the fighters to determine which fighter has that move frametime, if they do, put their name into
// the new set. Then write it out.
void commandD(std::ostream& out, const map<string, Fighter>& fighters, const string& moveName, int frameTime){
	set<string, CompareName> characters;
	for (map<string, Fighter>::const_iterator it = fighters.begin(); it != fighters.end(); it++){
		if ((it->second).hasMoveFrame(moveName, frameTime)){
			characters.insert((it->second).getName());
		}
	}
	out << "-d " << moveName << " " << frameTime << endl;
	for (set<string, CompareName>::const_iterator it = characters.begin(); it != characters.end(); it++){
		out << *it << endl;
	}
}

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
	//Initialize a map that has the character names as the keys and the Fighter objects as the values
	//Used for easy accessing a specific fighters class profile
	map<string, Fighter> fighters; 

	//Initialize a map that has the move name as the keys and a set of another map has the values
	// In the set, it contains each character and their respective move frametime in the form of a map.
	// With the character name being the key value and the move frametime as the value value
	// Use this to find the fastest and slowest frametimes per character for each move.
	map<string, set<map<string, int>, CompareFrameTime> > moves;

	//Initialize variables for reading
	string charName, jab, forwardTilt, upTilt, downTilt, forwardSmash, upSmash, downSmash;
	int jabT, forwardTiltT, upTiltT, downTiltT, forwardSmashT, upSmashT, downSmashT;

	dbfile >> charName >> jab >> forwardTilt >> upTilt >> downTilt >> forwardSmash >> upSmash >> downSmash;

	//Initialize each fighter object and all their move's frametimes. Then insert it into the fighters map.
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
	//Iterate through the fighters and add their move frametimes to the moves map
	for (map<string, Fighter>::iterator it = fighters.begin(); it != fighters.end(); it++){
		//Initialize the moves in the moves set
		if (it == fighters.begin()){
			(it->second).makeMoves(moves);
			continue;
		}
		(it->second).addMoves(moves);
	}

	//Read in the command and run the respective functions to take care of the commands
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
			infile >> theMove >> frameCount;
			if (moves.find(theMove) != moves.end()){
				commandD(outfile, fighters, theMove, frameCount);
			} else {
				outfile << "Invalid move name: " << theMove << endl;
			}
			outfile << endl;
		}
	}


	return 0;
}
