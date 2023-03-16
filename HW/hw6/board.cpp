#include "board.h"

using std::cout; using std::endl;

Board::Board(int Awidth, int Aheight){
    width = Awidth;
    height = Aheight;
    for (int i = 0; i < height; i++){
        vector<char> row(width, ' ');
        board.push_back(row);
    }
}
void Board::printBoard() const {
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            cout << board[y][x] << " ";
        }
        cout << endl;
    }
}