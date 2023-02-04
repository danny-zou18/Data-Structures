#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

    int start = 1;

    for (int i = 1; i < argc ; i++){

         int y = stoi(argv[i]);
         start = start * y;

    }
    
    cout << start << endl;

    return 0;
}