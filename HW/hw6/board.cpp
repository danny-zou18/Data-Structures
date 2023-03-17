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
std::ostream& operator<< (std::ostream& out, const Board& b){
    out << "Board:" << endl;
    for (int y = 0; y < b.getHeight(); y++){
        out << "  ";
        for (int x = 0; x < b.getWidth(); x++){
            out << b.getPos(y,x) << " ";
        }
        out << endl;
    }
    return out;
}