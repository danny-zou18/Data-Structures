#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "customer.h"
#include "inventory.h"

using std::cerr; using std::cout; using std::endl; using std::string; using std::list;

void sort_inventory(list<Inventory>& inventory){
    list<Inventory>::iterator it = inventory.begin();
    list<Inventory>::iterator nextIt = it; nextIt++;
    for(it = inventory.begin(); it != inventory.end(); it++){
        while (nextIt != inventory.end() && nextIt != it){
            if (nextIt->getId() > it->getId()){
                Inventory temp = *it;
                inventory.erase(it);
                inventory.insert(nextIt,temp);
                break;
            } else {
                nextIt++;
            }
        }

        // for (list<Inventory>::iterator nextIt = inventory.begin(); nextIt != it;){
        //     if (nextIt->getId() > it->getId()){
        //         Inventory temp = *it;
        //         inventory.erase(it);
        //         inventory.insert(nextIt, temp);
        //         break;
        //     } else {
        //         nextIt++;
        //     }
        // }
    }
}
bool check_customer(list<Customer>& customers, int custo_id){
    for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
        if (it->getId() == custo_id){
            return true;
        }
    }
    return false;
}
bool in_inventory(list<Inventory>& inventory, int item_id){
    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
        if (it->getId() == item_id){
            return true;
        }
    }
    return false;
}
bool check_quantity(list<Inventory>& inventory, int quantity, int item_id){
    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
        if (it->getId() == item_id){
            if (quantity <= it->getQuantity()){
                return true;
            } else {
                return false;
            }
        }
    }
    
}

int main(int argc, char* argv[]){

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
    list<Inventory> inventory;

    string in;
    int quantity;
    string name;
    while (in_inven >> in){
        in_inven >> quantity;
        in_inven >> name;
        int item_id = stoi(in.substr(1));
        if (in[0] != 'T' || item_id <= 0){
            cerr << "Invalid inventory ID " << item_id << " found in the inventory file." << endl;
            continue;
        }
        Inventory item(item_id,quantity,name);
        inventory.push_back(item);

    }
    sort_inventory(inventory);

    list<Customer> customers;

    list<string> wait_list;

    string in;
    string action;
    string timestamp;
    int item_quantity;
    int part_id;
    string custo_name;
    while (in_custo >> in){
        in_custo >> action;
        in_custo >> timestamp;
        in_custo >> item_quantity;
        in_custo >> part_id;
        in_custo >> custo_name;
        int custo_id = stoi(in.substr(1));
        if (in[0] != 'C' || custo_id <= 0){
            cerr << "Invalid customer information found for ID " << custo_id << " in the customer file." << endl;
            continue;
        }
        if (!check_customer(customers,custo_id)){
            customers.push_back(Customer(custo_id,custo_name));
        }
        if (action == "rent"){
            if (in_inventory(inventory,part_id)){
                if (check_quantity(inventory,item_quantity,part_id)){
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.begin(); it++){
                        if (it->getId() == part_id){
                            it->changeQuantity(item_quantity);
                            break;
                        }
                    }
                } else {
                    string combined = 
                }
            }
        }    
    }


    
    return 0;
}