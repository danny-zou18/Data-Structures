#include <vector>
#include <fstream>
#include <iostream>
#ifndef __board_h_
#define __board_h_

using std::vector;
//Board class that makes manipulating the board easier
class Board{
public:
    //Constructors
    Board(int Awidth, int Aheight);
    //Accessors
    char getPos(int row, int col) const {return board[row][col];}
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    //Modifiers
    void setPos(int row, int col, char letter) {board[row][col] = letter;}
private:
    vector<vector<char> > board;
    int width;
    int height;
};
//Non-member variables
std::ostream& operator<< (std::ostream& out, const Board& b);

bool operator== (const Board& b1, const Board& b2);

#endif