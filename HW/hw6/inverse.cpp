#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <fstream>
#include <vector>
#include <algorithm>
#include "board.h"
#include "loc.h"

using std::cout; using std::endl; using std::cerr; using std::string; using std::vector;

// dy dx
std::pair<int, int> getDyDx(const unsigned int direction) {
    if (direction == 1){
        return std::make_pair(0, 1);
    } else if (direction == 2){
        return std::make_pair(1, 1);
    } else if (direction == 3){
        return std::make_pair(1,0);
    } else if (direction == 4){
        return std::make_pair(1,-1);
    } else if (direction == 5){
        return std::make_pair(0,-1);
    } else if (direction == 6){
        return std::make_pair(-1,-1);
    } else if (direction == 7){
        return std::make_pair(-1,0);
    } else if (direction == 8){
        return std::make_pair(-1,1);
    }
    return std::make_pair(0,0);
}
void pop_front(std::vector<int>& vec) {
    if (!vec.empty()) {
        std::rotate(vec.begin(), vec.begin() + 1, vec.end());
        vec.pop_back();
    }
}
bool searchWord(vector<Board>& board, vector<string>& words, loc& cur_loc, int row, int col, int wordIndex) {
    // Check if we have found all the words in the vector
    if (wordIndex == words.size()) {
        return true;
    }

    // Check if we have gone out of bounds or if the current character in the grid does not match the current word
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[cur_loc.row][cur_loc.col] != words[wordIndex][0]) {
        return false;
    }

    // Check all 8 adjacent cells for the first letter of the current word
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // skip the current cell

            int newRow = row + i;
            int newCol = col + j;

            if (searchWord(grid, words, newRow, newCol, wordIndex+1)) {
                return true;
            }
        }
    }

    return false;
}
void insert_word(const string& word, Board& board, const loc& first_letter, const unsigned int direction){
    //cout << first_letter.row << " " << first_letter.col << endl;
    std::pair<int,int> dydx = getDyDx(direction);
    loc temp(first_letter.row,first_letter.col);
    for (unsigned int i = 0; i < word.size(); i++){
        board.setPos(temp.row,temp.col,word[i]);
        temp.changeLoc(dydx);
    }
}
bool check_direction(const string& word, const Board& board, const unsigned int direction, const loc& cur_loc, unsigned int index){
    int width = board.getWidth();
    int height = board.getHeight();
    if (index == word.size()){
        return true;
    }
    if (cur_loc.row < 0 || cur_loc.row >= height || cur_loc.col < 0 || cur_loc.col >= width 
    || (board.getPos(cur_loc.row, cur_loc.col) != ' ' &&  (board.getPos(cur_loc.row, cur_loc.col)) != word[index])){
        if (cur_loc.row >= 0 && cur_loc.row < height && cur_loc.col > 0 && cur_loc.col < width){
            if ((board.getPos(cur_loc.row, cur_loc.col)) != word[index]){
                if (word == "fun" && index == 0){
                    cout << board.getPos(cur_loc.row, cur_loc.col) << endl;
                }
            }
        }
        return false;
    }

    std::pair<int, int> dydx = getDyDx(direction);
    return check_direction(word, board, direction, loc(cur_loc.row + dydx.first, cur_loc.col + dydx.second), index + 1);
}

bool find_solution(const vector<string>& words, Board& board, const vector<string>& non_allowed, int width, int height, unsigned int index){
    if (index == words.size()){
        return true;
    }
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            for (int i = 1; i <= 8; i++){
                if (check_direction(words[index], board, i, loc(y,x), 0)){
                    insert_word(words[index], board, loc(y,x), i);
                    if (find_solution(words,board, non_allowed, width, height, index + 1)){
                        return true;
                    } else {
                        insert_word(std::string(words[index].size(), ' '), board, loc(y,x), i);
                    }
                }
            }
        }
    }
    return false;
}
vector<Board> find_all_solutions(vector<string>& words, const vector<string>& non_allowed, int width, int height){
    vector<Board> allBoards;
    vector<string> tempWords;
    for (unsigned int i = 0; i < words.size(); i++){
        tempWords.push_back(words[i]);
    }
    for (unsigned int i = 0; i < tempWords.size(); i++){
        for (int y = 0; y < height; y++){
            for (int x = 0; x < width; x++){
                for (int j = 1; j <= 8; j++){
                    if (check_direction(words[i]))
                }
            }
        }
    }
    

}

int main(int argc, char* argv[]){
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
    if (strcmp(argv[3],"one_solution") == 0){
        Board board(width,height);
        find_solution(words, board, not_allowed, width, height, 0);
        out_str << board;
    }
    
    return 0;
}  