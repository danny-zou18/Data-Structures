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
            bool last = true;
            for (list<int>::iterator it = test_list.begin(); it != test_list.end(); it++){
                if (test[i] < *it){
                    test_list.insert(it, test[i]);
                    last = false;
                    break;
                }
            }
            if (last){
                test_list.push_back(test[i]);
            }
        }
    }
    for (list<int>::iterator it = test_list.begin(); it != test_list.end(); it++){
        cout << *it << endl;
    }

    return 0;

}

// bool check_rented(list<Customer>& customers, int part_id, int custo_id){
//     for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
//         if (it->getId() == custo_id){
//             if (it->getItems().size() > 2){
//             for (list<Inventory>::iterator it1 = it->getItems().begin(); it1 != it->getItems().end(); it1++){
//                 if (it1->getId() == part_id){
//                     return true;
//                 }
//             }
//             }
//             return false;
//         }   
//     }
//     return false;
// }