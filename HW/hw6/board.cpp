#include "board.h"



Board::Board(int Awidth, int Aheight){
    width = Awidth;
    height = Aheight;
    for (int i = 0; i < height; i++){
        vector<char> row(width, ' ');
        board.push_back(row);
    }
}
