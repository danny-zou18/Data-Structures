#include <iostream>
#include <vector>

using namespace std;

std::vector<string> seperate_word(string word, unsigned int width){
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
    return seperated_word;
}

int main(){
    string word = "sdiufhioughoifudghdofiuhfoiduhgiodfhgiuodfhgiudfhgiufdhgiufdhgiufdhighfdiughdfiughufd";
    unsigned int width = 15;
    std::vector<string> seperated_word = seperate_word(word,width);
    for (unsigned int i = 0; i < seperated_word.size();i++){
        cout << seperated_word[i] << endl;
    }
  
    return 0;
}