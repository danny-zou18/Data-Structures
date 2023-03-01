#include <iostream>

using namespace std;
int recursivePaths(int x, int y) {
    int count = 0;
    if ( x == 0 || y == 0) {
        return 1;
    } else {
        count += recursivePaths(x-1, y) + recursivePaths(x, y-1);
    }
    return count;
}

int main()
{
    cout<< recursivePaths(2,3) << endl;
    return 0;
}
