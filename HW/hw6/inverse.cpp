#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include "board.h"

using std::cout; using std::endl; using std::cerr; using std::string; using std::vector;
//Basic location class to help us keep track of grid location
class loc{
public:
    loc(int r = 0, int c = 0): row(r), col(c) {}
    void changeLoc(const std::vector<int> directions){row += directions[0]; col += directions[1];}
    int row, col;
};
//Function that returns a vector containing two values for directions, the first index
//changing the row and the second second changing the column
vector<int> getDyDx(const unsigned int direction) {
    if (direction == 1){
        vector<int> right;
        right.push_back(0);
        right.push_back(1);
        return right;
    } else if (direction == 2){
        vector<int> bottom_right;
        bottom_right.push_back(-1);
        bottom_right.push_back(1);
        return bottom_right;
    } else if (direction == 3){
        vector<int> bottom;
        bottom.push_back(-1);
        bottom.push_back(0);
        return bottom;
    } else if (direction == 4){
        vector<int> bottom_left;
        bottom_left.push_back(-1);
        bottom_left.push_back(-1);
        return bottom_left;
    } else if (direction == 5){
        vector<int> left;
        left.push_back(0);
        left.push_back(-1);
        return left;
    } else if (direction == 6){
        vector<int> top_left;
        top_left.push_back(1);
        top_left.push_back(-1);
        return top_left;
    } else if (direction == 7){
        vector<int> top;
        top.push_back(1);
        top.push_back(0);
        return top;
    } else if (direction == 8){
        vector<int> top_right;
        top_right.push_back(1);
        top_right.push_back(1);
        return top_right;
    }
    vector<int> empty;
    return empty;
}
//Recursive function that checks if a word is found in a specific direction and a specific location
bool searchDirection(const Board& board, const string& word, const unsigned int direction,const loc& cur_loc, unsigned int index) {
    // Check if we have found the entire word
    if (index == word.size()) {
        return true;
    }

    // Check if we have gone out of bounds or if the current character in the puzzle does not match the current letter in the word
    if (cur_loc.row < 0 || cur_loc.row >= board.getHeight() || cur_loc.col < 0 
    || cur_loc.col >= board.getWidth() || board.getPos(cur_loc.row,cur_loc.col) != word[index]) {
        return false;
    }
    vector<int> dydx = getDyDx(direction);
    return searchDirection(board, word, direction,loc(cur_loc.row + dydx[0], cur_loc.col + dydx[1]), index + 1);
}
//Function that searches a board for a word and uses the "searchDirection" function as a helper
bool searchWord(const Board& board, const string& word) {
    // Check each position in the puzzle for the first letter of the word
    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            if (board.getPos(y,x) == word[0]) {
                // If the first letter matches, recursively search in all 8 directions for the entire word
                for (int i = 1; i <= 8; i++){
                    if (searchDirection(board,word, i, loc(y,x), 0)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
//Function that checks if a board is already in a board vector
bool in_vector(const vector<Board>& boards, const Board& board){
    for (unsigned int i = 0; i < boards.size(); i++){
        if (boards[i] == board){
            return true;
        }
    }
    return false;
}
//Function that inserts a word into a board, returns true if the word can be inserted and returns false if the word cannot be inserted
bool insert_word(const string& word, Board& board, const loc& first_letter, const unsigned int direction){
    vector<int> dydx = getDyDx(direction);
    loc temp(first_letter.row,first_letter.col);
    //Checks if the first letter of the word to be inserted overlaps with a word already on the board
    for (unsigned int i = 0; i < word.size(); i++){
        if (i == 0 && board.getPos(temp.row,temp.col) != word[0] && board.getPos(temp.row, temp.col) != '*'){
            return false;
        }
        board.setPos(temp.row,temp.col,word[i]);
        temp.changeLoc(dydx);
    }
    return true;
}
//Recursive function that checks if a word can be inserted in a board, returns true if it can and false if it cannot
bool check_direction(const string& word, const Board& board, const unsigned int direction, const loc& cur_loc, unsigned int index){
    int width = board.getWidth();
    int height = board.getHeight();
    //This is the base case, where we have reached the end of the word and there are no more letters to be checked
    if (index == word.size()){
        return true;
    }
    //If any of these things happen, then we cannot insert the current letter onto the board, return false
    if (cur_loc.row < 0 || cur_loc.row >= height || cur_loc.col < 0 || cur_loc.col >= width 
    || (board.getPos(cur_loc.row, cur_loc.col) != '*' &&  (board.getPos(cur_loc.row, cur_loc.col)) != word[index])){
        return false;
    }
    vector<int> dydx = getDyDx(direction);
    return check_direction(word, board, direction, loc(cur_loc.row + dydx[0], cur_loc.col + dydx[1]), index + 1);
}
//Recursive function that finds a singular solution to a board, returns true if a board is successfully created and false if not
bool find_solution(const vector<string>& words, Board& board, int width, int height, unsigned int index){
    //This is the base case, where every word that should be inserted in the board is inserted
    if (index == words.size()){
        return true;
    }
    //Nested for loop that checks every scenario of a word being inserted recursively
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            for (int i = 1; i <= 8; i++){
                if (check_direction(words[index], board, i, loc(y,x), 0)){
                    if (insert_word(words[index], board, loc(y,x), i)){
                        ;
                    } else {
                        return false;
                    };
                    if (find_solution(words,board,  width, height, index + 1)){
                        return true;
                    } else {
                        insert_word(std::string(words[index].size(), '*'), board, loc(y,x), i);
                    }
                }
            }
        }
    }
    return false;
}
//Function that finds all possible solutions and returns it in a vector of boards
vector<Board> find_all_solutions(vector<string>& words, int width, int height){
    vector<Board> allBoards;
    vector<string> tempWords;
    for (unsigned int i = 0; i < words.size(); i++){
        tempWords.push_back(words[i]);
    }
    //Go through every single word and check if it can be inserted in every single possible spot 
    //and in every single possible direction. When you can insert it , remove it from the words list
    //and scramble on the remaining words onto the board.
    for (vector<string>::iterator it = tempWords.begin(); it != tempWords.end(); it++){
        for (vector<string>::iterator it1 = words.begin(); it1 != words.end(); it1++){
            if (*it == *it1){
                it1 = words.erase(it1);
            }
        }
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                for (int j = 1; j <= 8; j++){
                    Board board(width,height);
                    if (check_direction(*it, board, j, loc(y,x), 0)){
                        if (insert_word(*it,board, loc(y,x), j)){
                            if (find_solution(words, board, width, height, 0)){
                                allBoards.push_back(board);
                            }
                        }
                    }
                }
            }
        }
        words.push_back(*it);
    }
    return allBoards;
}
int main(int argc, char* argv[]){
    //Basic error checking
    if (argc != 4){
        cerr << "Not enough arguments." << endl;
        exit(1);
    }
    std::ifstream in_str(argv[1]);
    if (!in_str.good()){
        cerr << "Can not open " << argv[1] << " to read!" << endl;
        exit(1);
    }
    std::ofstream out_str(argv[2]);
    if (!out_str.good()){
        cerr << "Can not open " << argv[2] << " to write!" << endl;
        exit(1);
    }
    if (strcmp(argv[3], "one_solution") != 0 && strcmp(argv[3], "all_solutions") != 0){
        cerr << argv[3] << " is not a valid command." << endl;
        exit(1);
    }
    
    int width;
    int height;
    in_str >> width;
    in_str >> height;

    vector<string> words; //Vector that stores all the words that should appear in the board
    vector<string> not_allowed; //Vector that stores all the words that shouldn't appear in the board
    
    //Parse the allowed words and the non-allowed words
    char x;
    string word;
    while (in_str >> x){
        bool is_neg = false;
        in_str >> word;
        if (x == '-'){
            is_neg = true;
        }
        if (!is_neg){
            words.push_back(word);
        } else {
            not_allowed.push_back(word);
        }
    }
    //Find all the boards when given the normal, unreversed words list
    vector<Board> boards = find_all_solutions(words, width, height);
    //Make a list that contains all the words but have the words be reversed
    vector<string> reverse_words;
    for (unsigned int i = 0; i < words.size(); i++){
        string reverse = "";
        for (int j = words[i].length() - 1; j >= 0; j--) {
            reverse += words[i][j];
        }
        reverse_words.push_back(reverse);
    }
    //Find all the boards when given the reversed words list
    vector<Board> flipboards = find_all_solutions(reverse_words, width, height);
    //Now put them all into one vector
    vector<Board> allboards;
    for (unsigned int i = 0; i < boards.size(); i++){
        if (!in_vector(allboards, boards[i])){
            allboards.push_back(boards[i]);
        }
    }
    for (unsigned int i = 0; i < flipboards.size(); i++){
        if (!in_vector(allboards, flipboards[i])){
            allboards.push_back(flipboards[i]);
        }
    }
    //Check if a board contains any unallowed words, if it does, erase it from the vector
    for (vector<Board>::iterator it = allboards.begin(); it != allboards.end();){
        bool erased = false;
        for (unsigned int i = 0; i < not_allowed.size(); i++){
            if (searchWord(*it, not_allowed[i])){
                it = allboards.erase(it);
                erased = true;
                break;
            } 
        }
        if (!erased){
            it++;
        }
    }
    //Write to file
    if (strcmp(argv[3],"one_solution") == 0){
        out_str << allboards[0];
    } else {
        out_str << allboards.size() << " solution(s)" << endl;
        for (unsigned int i = 0; i < allboards.size(); i++){
            out_str << allboards[i];
        }
    }
    
    return 0;
}  