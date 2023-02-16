#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "inventory.h"
#include "customer.h"

using std::cerr; using std::cout; using std::endl; using std::string; using std::list;

//Function for sorting inventory list using insert and erase
void sort_inventory(list<Inventory>& inventory, const Inventory& i){
     if (inventory.size() == 0){
        inventory.push_back(i);
    } else {
        bool last = true;
        for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
            if (i.getId() < (it)->getId()){
                last = false;
                inventory.insert(it, i);
                break;
            }
        }
        if (last){
            inventory.push_back(i);
        }
    }
}
//Function for sorting customers list using insert and erase
void sort_customers(list<Customer>& customers, const Customer& c){
    if (customers.size() == 0){
        customers.push_back(c);
    } else {
        bool last = true;
        for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
            if (c.getId() < (it)->getId()){
                last = false;
                customers.insert(it, c);
                break;
            }
        }
        if (last){
            customers.push_back(c);
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
//Function that checks if a customer has rented the given item
bool check_rented(list<Customer>& customers, int part_id, int custo_id){
    for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
        if (it->getId() == custo_id){
            if (it->getItems().size() > 0){
                if (it->check_item(part_id)){
                    return true;
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
        if (in[0] != 'T' || item_id <= 0 || quantity <= 0){
            cerr << "Invalid inventory ID " << in << " found in the inventory file." << endl;
            continue;
        }
        //Sorts the inventory list as we read the inventory file by inserting into the correct index
        Inventory item(item_id,quantity,name);
        sort_inventory(inventory,item);  
    }
    list<Customer> customers; //Customers list that stores all the customers
    list<Customer*> pending_customers; //List of customer pointers that stores all the pending customers
                                       //The customer pointers points to the customers in the original         
    string in1;                        //customers list so we can make changes to the customer when we make
    string action;                     //changes to the pending customer pointers
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
        //Parse the customer id and item id to make them into integers
        int part_id = stoi(item_id.substr(1));
        int custo_id = stoi(in1.substr(1));
        if (in1[0] != 'C' || custo_id <= 0){
            cerr << "Invalid customer information found for ID " << in1 << " in the customer file." << endl;
            continue;
        }
        if (!check_customer(customers,custo_id)){ //Checks if the customer already exists in the customers list
            Customer cus(custo_id, custo_name);   //and adds the customer if she/he is not
            sort_customers(customers, cus);
        }
        if (action == "rent"){ 
            //Checks if the item the customer is trying to rent is in the inventory
            if (in_inventory(inventory,part_id)){ 
                //Checks if the inventory has enough of the item to fill the customers request
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
                } else { //If the inventory does not have enough of the item, add the customer to the waitlist/pending list
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
                        if (it->getId() == part_id){
                            for (list<Customer>::iterator it1 = customers.begin(); it1 != customers.end(); it1++){
                                if (it1->getId() == custo_id){
                                    Inventory temp(*it);
                                    temp.setQuantity(item_quantity);
                                    it1-> add_pending(temp);
                                    it1->setTime(timestamp);
                                    
                                    //Add the pending customers to the wait list based on timestamp
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
                cerr << "Customer " << in1 << " requested item " << item_id << " which is not in the inventory." << endl;
                continue;
            }
       } else if (action == "return"){ 
            if (in_inventory(inventory, part_id)){ //Checks if the item is in the inventory
                //Checks if the customer trying to return the item actually has the item
                if (check_rented(customers, part_id, custo_id)){ 
                    //if they do, adjust the item quantity in inventory
                    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
                        if (it->getId() == part_id){
                            it->returnQuantity(item_quantity);
                        }
                        /*Go through the wait list based on timestamp and check if any of the customers are waiting for the item
                        that is being returned. If they are waiting for the item, check if there is enough quantity of the item to
                        be rented out again, if there is enough, rent the item to the customer and remove the customer from the waitlist*/
                        for (list<Customer*>::iterator it1 = pending_customers.begin(); it1 != pending_customers.end(); it1++){
                            if ((*it1)->getPending().size() > 0){
                                if ((*it1)->check_pending(part_id)){ 
                                    if (check_quantity(inventory,item_quantity, part_id)){ 
                                        it->rentQuantity(item_quantity);
                                        Inventory temp(((*it1)->get_pending_item(part_id)));
                                        (*it1)->add_item(temp);
                                        (*it1)->remove_pending(part_id);
                                        it1 = pending_customers.erase(it1);
                                    } else {
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                    //Remove the item from the customers item list since he is returning
                    for (list<Customer>::iterator it2 = customers.begin(); it2 != customers.end();it2++){
                        if (custo_id == it2->getId()){
                            it2->remove_item(part_id);
                            //Checks if the customer has no more pending items or rental items
                            //If they don't have any, remove the customer from the customers list
                            if (it2->getItems().size() == 0 && it2->getPending().size() == 0){
                                it2 = customers.erase(it2);
                            }
                        }
                    }
                } else {
                    cerr << "Customer " << in1 << " attempted to return item " << item_id 
                    << " which she/he did not rent." << endl;
                }
            } else {
                cerr << "Customer " << in1 << " attempted to return item " << item_id 
                << " which is not in the inventory." << endl;
            }
        }
    }
    //Write the customers in correct format to the output file and also check for any leftover customers
    //that has no pending items or rental items
    for (list<Customer>::iterator it = customers.begin(); it != customers.end(); it++){
        if (it->getItems().size() == 0 && it->getPending().size() == 0){
            it = customers.erase(it);   
            it--;
        } else {
            out_custo << *it;
            out_custo << endl;
        }
    }
    //Write the items in correct format to the output file
    for (list<Inventory>::iterator it = inventory.begin(); it != inventory.end(); it++){
        int id = it->getId();
        out_inven << "T" << std::setfill('0') << std::setw(4) << id << " " << it->getQuantity() 
        << " available " << it->getName() << endl;
        bool rented = false;
        bool pending = false;
        for (list<Customer>::iterator it1 = customers.begin(); it1 != customers.end();it1++){
            if (it1->check_item(id)){
                if (rented == false){
                    out_inven << "Rental Customers: ";
                }
                out_inven << "C" << std::setfill('0') << std::setw(4) << it1->getId() << " " << it1->getName() 
                << " (" << it1->get_item(id).getQuantity() << ") ";
                rented = true;
           }
           if (it1->getId() == customers.back().getId() && rented){
                out_inven << endl;
           }
        }
        for (list<Customer>::iterator it2 = customers.begin(); it2 != customers.end(); it2++){
           if (it2->check_pending(id)){
                if (pending == false){
                    out_inven << "Pending Customers: ";
                }
                out_inven << "C" << std::setfill('0') << std::setw(4) << it2->getId() << " " << it2->getName() 
                << " (" << it2->get_pending_item(id).getQuantity() << ") ";
                pending = true;
           }
           if (it2->getId() == customers.back().getId() && pending){
                out_inven << endl;
           }
        }
        out_inven << endl;
    }
    out_custo.close();
    out_inven.close();
    return 0;
}