#ifndef __loc_h_
#define __loc_h_
#include <vector>

class loc{
public:
    loc(int r = 0, int c = 0): row(r), col(c) {}
    void changeLoc(const std::vector<int> directions){row += directions[0]; col += directions[1];}
    int row, col;
};

#endif