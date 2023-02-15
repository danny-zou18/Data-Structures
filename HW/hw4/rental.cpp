#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "inventory.h"
#include "customer.h"

using std::cerr; using std::cout; using std::endl; using std::string; using std::list;

//Function for sorting inventory list using insert and erase
void sort_inventory(list<Inventory>& inventory){
    list<Inventory>::iterator it = inventory.begin();
    for(it = inventory.begin(); it != inventory.end(); it++){
        for (list<Inventory>::iterator nextIt = inventory.begin(); nextIt != it;){
            if (nextIt->getId() > it->getId()){
                Inventory temp = *it;
                inventory.erase(it);
                inventory.insert(nextIt, temp);
                break;
            } else {
                nextIt++;
            }
        }
    }
}
//Function for sorting customers list using insert and erase
void sort_customers(list<Customer>& customers){
    list<Customer>::iterator it = customers.begin();
    for(it = customers.begin(); it != customers.end(); it++){
        for (list<Customer>::iterator nextIt = customers.begin(); nextIt != it;){
            if (nextIt->getId() > it->getId()){
                Customer temp(*it);
                customers.erase(it);
                customers.insert(nextIt, temp);
                break;
            } else {
                nextIt++;
            }
        }
    }
}
//Function that checks if a customer is already in the customers list
bool check_customer(list<Customer>& customers, int custo_id){
    for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
        if (it->getId() == custo_id){
            return true;
        }
    }
    return false;
}
//Function that checks if a item is in the inventory list
bool in_inventory(list<Inventory>& inventory, int item_id){
    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
        if (it->getId() == item_id){
            return true;
        }
    }
    return false;
}
//Function that checks if there is enough quantity of a item in the inventory to be lent out to a customer
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
    return false;
}
bool check_rented(list<Customer>& customers, int part_id, int custo_id){
    for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
        if (it->getId() == custo_id){
            if (it->getItems().size() > 0){
                if (it->getItems().size() == 1){
                    if (it->getItems().front().getId() == part_id){
                        return true;
                    } else {
                        return false;
                    }
                } else if (it->getItems().size() == 2){
                    if (it->getItems().size() == 2){
                        if (it->getItems().front().getId() == part_id || it->getItems().back().getId() == part_id){
                            return true;
                        } else {
                            return false;
                        }
                    }
                } else {
                    for (list<Inventory>::iterator it1 = it->getItems().begin(); it1 != it->getItems().end(); it1++){
                        if (it1->getId() == part_id){
                            return true;
                        }
                    }
                    return false;
                }
            }
            
        }   
    }
    return false;
}

int main(int argc, char* argv[]){
    //Checks if there are enough command line arguments
    if (argc != 5){
        cerr << "Not enough arguments." << endl;
        exit(1);
    }
    //Checks if input inventory file is opened correctly
    std::ifstream in_inven(argv[1]);
    if (!in_inven.good()){
        cerr << "Can not open " << argv[1] << " to read!" << endl;
        exit(1);
    }
    //Checks if input customer file is opened correctly
    std::ifstream in_custo(argv[2]);
    if (!in_custo.good()){
        cerr << "Can not open " << argv[2] << " to read!" << endl;
        exit(1);
    }
    //Checks if output inventory file is opened correctly
    std::ofstream out_inven(argv[3]);
    if (!out_inven.good()){
        cerr << "Can not open " << argv[3] << " to write!" << endl;
        exit(1);
    }
    //Checks if output customer file is opened correctly
    std::ofstream out_custo(argv[4]);
    if (!out_custo.good()){
        cerr << "Can not open " << argv[4] << " to write!" << endl;
        exit(1);
    }
    list<Inventory> inventory; //Inventory list that stores all the items

    //Initialize variables of appropriate type to read
    string in;
    int quantity;
    string name;
    //Goes through the input inventory file and adds all appropriate items to inventory
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
    sort_inventory(inventory); //Sort the inventory based on item id

    list<Customer> customers;

    list<Customer*> pending_customers;

    string in1;
    string action;
    int timestamp;
    int item_quantity;
    string item_id;
    string custo_name;
    while (in_custo >> in1){
        in_custo >> action;
        in_custo >> timestamp;
        in_custo >> item_quantity;
        in_custo >> item_id;
        in_custo >> custo_name;
        int part_id = stoi(item_id.substr(1));
        int custo_id = stoi(in1.substr(1));
        if (in1[0] != 'C' || custo_id <= 0){
            cerr << "Invalid customer information found for ID " << custo_id << " in the customer file." << endl;
            continue;
        }

        if (!check_customer(customers,custo_id)){
            customers.push_back(Customer(custo_id,custo_name));
        }
        if (action == "rent"){
            if (in_inventory(inventory,part_id)){
                if (check_quantity(inventory,item_quantity,part_id)){
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
                        if (it->getId() == part_id){
                            it->rentQuantity(item_quantity);
                            for (list<Customer>::iterator it1 = customers.begin(); it1 != customers.end(); it1++){
                                if (it1->getId() == custo_id){
                                    Inventory temp(*it);
                                    temp.setQuantity(item_quantity);
                                    it1->add_item(temp);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                } else {
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
                        if (it->getId() == part_id){
                            for (list<Customer>::iterator it1 = customers.begin(); it1 != customers.end(); it1++){
                                if (it1->getId() == custo_id){
                                    Inventory temp(*it);
                                    temp.setQuantity(item_quantity);
                                    it1-> add_pending(temp);
                                    it1->setTime(timestamp);
                                    if (pending_customers.size() == 0){
                                        pending_customers.push_back(&(*it1));
                                    } else {
                                        bool last = true;
                                        for (list<Customer*>::iterator it2 = pending_customers.begin(); it2 != pending_customers.end(); it2++){
                                            if (it1->getTimeStamp() < (*it2)->getTimeStamp()){
                                                last = false;
                                                pending_customers.insert(it2, (&(*it1)));
                                                break;
                                            }
                                        }
                                        if (last){
                                            pending_customers.push_back(&(*it1));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                cerr << "Customer C" << custo_id << " requested item T" << part_id << " which is not in the inventory." << endl;
                continue;
            }
       } else if (action == "return"){
            if (in_inventory(inventory, part_id)){
                if (check_rented(customers, part_id, custo_id)){
                    cout << "true" << endl;
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
                        if (it->getId() == part_id){
                            it->returnQuantity(item_quantity);
                        }
                        for (list<Customer*>::iterator it1 = pending_customers.begin(); it1 != pending_customers.end(); it1++){
                            if ((*it1)->getPending().size() > 0){
                                if ((*it1)->getPending().size() == 1){
                                    if ((*it1)->getPending().front().getId() == part_id){
                                        cout << "true" << endl;
                                        if (check_quantity(inventory,item_quantity, part_id)){
                                            cout << "true" << endl;
                                            Inventory temp(((*it1)->getPending().front()));
                                            (*it1)->add_item(temp);
                                            (*it1)->getPending().pop_front();
                                            if ((*it1)->getItems().size() == 0 && (*it1)->getItems().size() == 0){
                                                for (list<Customer>::iterator it2 = customers.begin(); it2 != customers.end(); it2++){
                                                    if (it2->getId() == (*it1)->getId()){
                                                        customers.erase(it2);
                                                    }
                                                }
                                            }
                                            pending_customers.erase(it1);
                                        } else {
                                            continue;
                                        }
                                    }
                                } 
                            }
                        }
                    }
                }
            }
        }
    }
    // sort_customers(customers);
    // for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
    //     cout << "C" << it->getId() << " " << it->getName() << endl;
    //     if (it->getItems().size() > 2){
    //         for (list<Inventory>::iterator it1 = (it->getItems()).begin(); it1 != (it->getItems()).end(); it1++){
    //             cout << it1->getId() << " ";
    //         }
    //     } else if (it->getItems().size() == 2) {
    //         cout << it->getItems().front().getId() << " " << it->getItems().back().getId();
    //     } else if (it->getItems().size() == 1){
    //         cout << it->getItems().front().getId();
    //     }
    //     cout << endl;
    // }
   
    
    return 0;
}