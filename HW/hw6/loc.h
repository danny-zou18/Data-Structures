#ifndef __loc_h_
#define __loc_h_
#include <utility>

class loc{
public:
    loc(int r = 0, int c = 0): row(c), col(c) {}
    void changeLoc(const std::pair<int,int>& location){row += location.first; col += location.second;}
    int row, col;
};

#endif