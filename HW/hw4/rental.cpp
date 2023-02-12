#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "customer.h"
#include "inventory.h"

using std::cerr; using std::cout; using std::endl; using std::string; using std::list;

int main(unsigned int argc, char* argv[]){

    if (argc != 5){
        cerr << "Not enough arguments." << endl;
        exit(1);
    }
    std::ifstream in_inven(argv[1]);
    if (!in_inven.good()){
        cerr << "Can not open " << argv[1] << " to read!" << endl;
        exit(1);
    }
    std::ifstream in_custo(argv[2]);
    if (!in_custo.good()){
        cerr << "Can not open " << argv[2] << " to read!" << endl;
        exit(1);
    }
    std::ofstream out_inven(argv[3]);
    if (!out_inven.good()){
        cerr << "Can not open " << argv[3] << " to write!" << endl;
        exit(1);
    }
    std::ofstream out_custo(argv[4]);
    if (!out_custo.good()){
        cerr << "Can not open " << argv[4] << " to write!" << endl;
        exit(1);
    }

    string in;
    int quantity;
    string name;
    while (in_inven >> in){
        in_inven >> quantity;
        in_inven >> name;
        int id = stoi(in.substr(1));
        if (in[0] != 'T' || id <= 0){
            cerr << "Invalid inventory ID " << id << " found in the inventory file." << endl;
        }
        list<Inventory> inventory;
        
        list<Inventory>::iterator it;
        for (it = inventory.begin(); it != inventory.end(); it++){
            if ((*(it++)) > (*)){

            }


            
        }






    }
    
    
    

















    return 0;
}