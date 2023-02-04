#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using std::cout; using std::endl; using std::cin;  using std::string;
using std::ifstream; using std::ofstream;


int main(){
    string word = "Supercalifragilisticexpialidocious!";
    int width = 15;
    if (word.size() > width){
        std::vector<string> seperated_word;
        int index = 0;
        int limit = width - 1;
        while (true){
            if (word.size() - index > (width - 1)){
                string split_word = word.substr(index, limit) + "-";
                seperated_word.push_back(split_word);
                index += (width-1);
            } else {
                string split_word = word.substr(index);
                seperated_word.push_back(split_word);
                break;
            }

        }

    for (unsigned int i = 0; i < seperated_word.size();i++){
        cout << seperated_word[i] << endl;
    }

    return 0;

    }
}