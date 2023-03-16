#include <vector>
#include <utility>
#include <iostream>
#ifndef __board_h_
#define __board_h_

using std::vector;


class Board{
public:
    //Constructors
    Board(int Awidth, int Aheight);

    char getPos(int row, int col) const {return board[row][col];}
    int getWidth() const {return width;}
    int getHeight() const {return height;}

    void setPos(int row, int col, char letter) {board[row][col] = letter;}
    void printBoard() const;

private:
    vector<vector<char> > board;
    int width;
    int height;
};











#endif