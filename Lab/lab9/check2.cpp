#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <fstream>

using std::cout; using std::endl;

int main(int argc, char* argv[]){
    std::ifstream in_str(argv[1]);
    std::map<int,int> map;
    int x;
    while (in_str >> x){
        
        if (map.find(x) != map.end()){
            map.find(x)->second += 1;
        } else {
            map.insert(std::pair<int,int>(x,1));
        }
    }
    int max_amount = 0;
    for (std::map<int,int>::iterator it = map.begin(); it != map.end(); it++){
        if (it->second > max_amount){
            max_amount = it->second;
        }
    }
    std::vector<int> mean_values;
    for (std::map<int,int>::iterator it = map.begin(); it != map.end(); it++){
        if (it->second == max_amount){
            mean_values.push_back(it->first);
        }
    }
    cout << "The mean values in " << argv[1] << " are/is ";
    for (unsigned int i = 0; i < mean_values.size(); i++){
        cout << mean_values[i] << " ";
    }
    cout << endl;

}