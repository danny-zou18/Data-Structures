#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "Inventory.h"
#include "Customer.h"

using std::string; using std::cout; using std::cin; using std::cerr; using std::endl;

bool getInvPos(std::string &id,std::list<Inventory> &inventory,typename std::list<Inventory>::iterator &changer){
    typename std::list<Inventory>::iterator itr;
    //looping through all of inventory list
    for(itr = inventory.begin(); itr!=inventory.end(); itr++){
        //returns true and changes the argument iterator to that position if it has the same id as the argument
        if((*itr).get_id()==id){
            changer = itr;
            return true;
        }
    }
    //that id was not found (it doesnt exist in inventory)
    return false;
}

bool getCustPos(std::string &id,std::list<Customer> &customers,typename std::list<Customer>::iterator &changer){
    typename std::list<Customer>::iterator itr;
    //looping through all of customer list
    for(itr = customers.begin(); itr!=customers.end(); itr++){
        //return true and changes the argument iterator to that position if it has the same id as the argument
        if((*itr).get_id()==id){
            changer = itr;
            return true;
        }
    }
    //argument id was not found in the customers(there is no customer with that id)
    return false;

}

void insertCorrectly(const Inventory &tool, std::list<Inventory> &inventory){
    if(inventory.size()>0){
        //there has to be something in inventory to loop through it
        bool added = false;
        typename std::list<Inventory>::iterator itr;
        //looping through everything in inventory
        for(itr = inventory.begin(); itr!=inventory.end(); itr++){
            //if there is something that goes after the id of the tool then insert the tool before that
            if((*itr).get_id()>tool.get_id()){
                inventory.insert(itr,tool);
                added = true;
                break;
            }
        }
        if(!added){
            //nothing was supposed to go before the tool so add it to the end
            inventory.push_back(tool);    
        }
    }else{
        //if theres nothing in inventory put the tool in the first position
        inventory.push_back(tool);
    }
    
}

void insertCorrectly(const Customer &cust, std::list<Customer> &customers){
    if(customers.size()>0){
        //there has to be something in customers to loop through it
        bool added = false;
        typename std::list<Customer>::iterator itr;
        //looping through everything in customers
        for(itr = customers.begin(); itr!=customers.end(); itr++){
            //if there is an id that goes after the id of the customer then insert the customer before that
            if((*itr).get_id()>cust.get_id()){
                customers.insert(itr,cust);
                added = true;
                break;
            }
        }
        if(!added){
            //nothing was supposed to go before the customer so add it to the end
            customers.push_back(cust);    
        }
    }else{
        //if theres nothing in customers put the customer in the first position
        customers.push_back(cust);
    }
}

bool penders(std::list<Customer> &customers,const string &toolid,const int quantity, typename std::list<Customer>::iterator &changer){
    string lowestTimestamp = "";
    typename std::list<Customer>::iterator litr = customers.end();
    //iterator representing the customer with the lowest timestamp
    typename std::list<Customer>::iterator itr;
    //looping through all of the customers
    for(itr = customers.begin(); itr!=customers.end(); itr++){
        //checks that the customer is pending for the argument tool
        if((*itr).isPending()&&(*itr).pendingContains(toolid)){
            //checks that the quantity in inventory is less than the quantity that the customer wants
            if((*(*itr).get_ptool(toolid)).get_quantity()<=quantity){
                //picks the customer with the lowest timestamp
                if((*itr).get_timestamp()<lowestTimestamp||lowestTimestamp==""){
                    lowestTimestamp = (*itr).get_timestamp();
                    litr = itr;
                }
            }
        }        
    }
    //if none of the customers are pending for the tool returns false
    if(litr==customers.end())
        return false;
    //changes the argument iterator to the correct position and returns true
    changer = litr;
    return true;
}

void parseInventory(std::list<string> &inventoryInput,std::list<Inventory> &inventory){
    typename std::list<string>::iterator itr;
    //loops through all of the lines in inventory input
    for(itr = inventoryInput.begin(); itr!=inventoryInput.end(); itr++){
        //checks if the first letter is T and that the id is length 5
        if(((*itr)[0])!='T'||(*itr).size()!=5){
            cerr << "Invalid inventory ID " << *itr << " found in the inventory file." << endl;
            itr++;
            itr++;
            continue;
        }
        string id = *itr;
        itr++;
        int quantity = std::stoi(*itr);
        //checks that quantity is greater than 0
        if(!(quantity>0)){
            cerr << "Invalid inventory ID " << id << " found in the inventory file." << endl;
            itr++;
            continue;
        }
        itr++;
        string name = *itr;
        //creates a new inventory object and adds it to the inventory
        insertCorrectly(Inventory(name,id,quantity),inventory);

    }
}

void parseCustomers(std::list<string> &customerInput,std::list<Customer> &customers,std::list<Inventory> &inventory){
    typename std::list<string>::iterator itr;
    typename std::list<Customer>::iterator pitr;
    typename std::list<Inventory>::iterator invitr;
    typename std::list<Customer>::iterator custitr;
    //loop through all the input
    for(itr = customerInput.begin(); itr!=customerInput.end(); itr++){
        string id = *itr;
        //error checking the ids
        if((id[0])!='C'||id.size()!=5){
            cerr << "Invalid customer information found for ID " << id << " in the customer file." << endl;
            std::advance(itr,5);
            continue;
        }
        itr++;
        string doing = *itr;
        itr++;
        string timestamp = *itr;
        itr++;
        int quanitityWanted = std::stoi(*itr);
        itr++;
        string toolid = *itr;
        //error checking if the id is actually in the inventory
        if(!getInvPos(toolid,inventory,invitr)){
            if(doing == "rent")
                cerr << "Customer " << id << " requested item " << toolid << " which is not in the inventory." << endl;
            if(doing == "return")
                cerr << "Customer " << id << " attempted to return item " << toolid << " which is not in the inventory." << endl;
            itr++;
            continue;
        }
        itr++;
        string name = *itr;
        //gettting the customer iterator position so we can call it later
        if(!getCustPos(id,customers,custitr)){
            insertCorrectly(Customer(name,id,timestamp,false,false),customers);
            getCustPos(id,customers,custitr);
        }
        //rental event 
        if(doing=="rent"){
            //changing the quanitity if there is enough and setting the customer to renting
            if((*invitr).get_quantity()>=quanitityWanted){
                (*invitr).set_quantity((*invitr).get_quantity()-quanitityWanted);
                (*custitr).set_renting(true);
                (*custitr).add_rtool(Inventory((*invitr).get_name(),(*invitr).get_id(),quanitityWanted));
            } else {
            //there is not enough quantity so the customer is set to pending
                (*custitr).set_pending(true);
                (*custitr).add_ptool(Inventory((*invitr).get_name(),(*invitr).get_id(),quanitityWanted));
            }
        }
        //return event
        else if(doing=="return"){
            //error checking if the customer can actually return the item
            if(!(*custitr).rentingContains(toolid)){
                cerr<< "Customer " << id << " attempted to return item " << toolid << " which she/he did not rent." <<  endl;
                if(!((*custitr).isPending()||(*custitr).isRenting()))
                    custitr = customers.erase(custitr);    
                continue;
            }
            //adding the quantity back and if the customer is not renting or pending for anything else removing them
            (*invitr).set_quantity((*invitr).get_quantity()+quanitityWanted);
            (*custitr).remove_rtool(toolid);
            if(!((*custitr).isPending()||(*custitr).isRenting())){
                custitr = customers.erase(custitr);
            }
            //checks if there are more pending customers and changes the quantity of the item
            bool morepending = penders(customers,(*invitr).get_id(),(*invitr).get_quantity(),pitr);
            while(morepending){ //loops until there are no more people pending for this item
                int pendingQuantityWanted = (*(*pitr).get_ptool((*invitr).get_id())).get_quantity();
                (*pitr).remove_ptool((*invitr).get_id());
                (*pitr).set_renting(true);
                (*pitr).add_rtool(Inventory((*invitr).get_name(),(*invitr).get_id(),pendingQuantityWanted));
                (*invitr).set_quantity((*invitr).get_quantity()-pendingQuantityWanted);
                morepending = penders(customers,(*invitr).get_id(),(*invitr).get_quantity(),pitr);
            }
        }
    }
}

void printCustomers(std::list<Customer> &customers, std::ofstream &out){
    typename std::list<Customer>::iterator itr = customers.begin();
    //looping through all the customers
    for(itr =  customers.begin(); itr != customers.end(); itr++){
        //printing name and id
        out << (*itr).get_id() << " " << (*itr).get_name() << endl;
        //if they are renting list out the tools and quantites that they are renting
        if((*itr).isRenting()){
            out << "Rentals: ";
            while((*itr).isRenting()){
                out << (*(*itr).get_rtool()).get_id() << " (" << (*(*itr).get_rtool()).get_quantity() << ") ";
                (*itr).remove_rtool();
            }
            out << endl;
        }
        //if they are pending list out the tools and the quantites that they are pending for
        if((*itr).isPending()){
            out << "Pending: ";
            while((*itr).isPending()){
                out << (*(*itr).get_ptool()).get_id() << " (" << (*(*itr).get_ptool()).get_quantity() << ") ";
                (*itr).remove_ptool();
            }
            out << endl;
        } 
        out << endl;        
    }
}

void printInventory(std::list<Inventory> &inventory, std::list<Customer> &customers,  std::ofstream &out){
    typename std::list<Inventory>::iterator itr;
    //looping through all of the inventory
        for(itr = inventory.begin(); itr!=inventory.end(); itr++){
            //prints the id name and quantitiy of the tool
            out << (*itr).get_id() << " " << (*itr).get_quantity() << " available " << (*itr).get_name() << endl;
            //if the current quantity is not equal to the quanitity at the beggining someone has rented it
            if((*itr).get_quantity()!=(*itr).get_original_quantity()){
                out << "Rental Customers: ";
                typename std::list<Customer>::iterator custitr;
                //prints all the customers that have the id of the tool in their rented tools
                for(custitr = customers.begin(); custitr!=customers.end(); custitr++){
                    if((*custitr).rentingContains((*itr).get_id())){
                        out << (*custitr).get_id() << " " << (*custitr).get_name() << " (" << (*(*custitr).get_rtool((*itr).get_id())).get_quantity() << ") ";
                    }
                }
                out << endl;
            }
            string output = "Pending Customers: ";
            typename std::list<Customer>::iterator pitr;
            //adds all of the customers that have the id of the tool in thier pending tools to the output string
            for(pitr = customers.begin(); pitr!=customers.end(); pitr++){
                if((*pitr).pendingContains((*itr).get_id())){
                    output += (*pitr).get_id() + " " + (*pitr).get_name() + " (" + std::to_string((*(*pitr).get_ptool((*itr).get_id())).get_quantity()) + ") ";
                }
            }
            // checks if the output string changes meaning that there was someone who was pending the item meaning we need to print it
            if(output!="Pending Customers: "){
                out << output;
                out << endl;
            }
            out << endl;
        }
        
}

int main(int argc, char* argv[]){
    //Checking if number of command line arguments is valid
    if(argc != 5){
       cerr << "Incorrect Number of Command Line Arguments" << endl;
       exit(1); 
    }
    //opening files streams and checking that they can be read from and written to
    char* input_inventory_file_name = argv[1];
    char* input_customer_file_name = argv[2];
    char* output_inventory_file_name = argv[3];
    char* output_customer_file_name = argv[4];

    std::ifstream in_inv(input_inventory_file_name);
    std::ifstream in_cust(input_customer_file_name);
    std::ofstream out_inv(output_inventory_file_name);
    std::ofstream out_cust(output_customer_file_name);
    
    if(!in_inv.good()){
        cerr << "Trouble reading" << input_inventory_file_name << endl;
        exit(1);
    } else if(!out_cust.good()){
        cerr << "Trouble writing" << output_customer_file_name << endl;
        exit(1);
    } else if(!out_inv.good()){
        cerr << "Trouble writing" << output_inventory_file_name << endl;
        exit(1);
    } else if(!in_cust.good()){
        cerr << "Trouble reading" << input_customer_file_name << endl;
        exit(1);
    }
    //creating the lists to hold the customers the inventory as well as all the words in the input files
    std::list<string> customerInput;
    std::list<string> inventoryInput;
    std::list<Customer> customers;
    std::list<Inventory> inventory;
    
    string temp = "";
    //filling both the input lists with the words from the input files
    while(in_inv>>temp){
        inventoryInput.push_back(temp);
    }
    while(in_cust>>temp){
        customerInput.push_back(temp);
    }
    //calling our methods to parse the words and edit the inventory and customer objects
    parseInventory(inventoryInput,inventory);
    parseCustomers(customerInput,customers,inventory);
    //printing out the parsed info into the out files
    printInventory(inventory,customers,out_inv);
    printCustomers(customers,out_cust);

    
    
    return 0;
}