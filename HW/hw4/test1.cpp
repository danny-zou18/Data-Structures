#include <list>
#include <iostream>
#include <vector>
using namespace std;
int main(){
    
    vector<int> test;
    test.push_back(6);
    test.push_back(3);
    test.push_back(7);
    test.push_back(3);
    test.push_back(8);
    test.push_back(5);
    test.push_back(0);
    test.push_back(34);
    test.push_back(3324);
    test.push_back(525252);

    list<int> test_list;
    for (unsigned int i = 0; i < test.size(); i++){
        if (test_list.size() == 0){
            test_list.push_back(test[i]);
        } else {
            for (list<int>::iterator it = test_list.begin(); it != test_list.end(); it++){
                if (test[i] < *it){
                    test_list.insert(it, test[i]);
                    break;
                }
            }
            test_list.push_back(test[i]);
        }
    }
    for (list<int>::iterator it = test_list.begin(); it != test_list.end(); it++){
        cout << *it << endl;
    }

    return 0;
}