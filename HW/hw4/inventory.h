#ifndef __inventory_h_
#define __inventory_h_
#include <string>
#include <list>
#include "customer.h"
using std::string; using std::list; 

class Inventory{
public:
    Inventory(const Inventory& item);
    Inventory(int item_id, unsigned aQuantity, const string& item_name);

    //Accessors
    unsigned getId() const {return id;}
    const string& getName() const {return name;}
    unsigned getQuantity() const {return quantity;}

    //Modifiers
    void setQuantity(int quantity);
    void rentQuantity(int change);
    void returnQuantity(int change);
    void addToRenting(const Customer& c);
    void addToPending(const Customer& c);

    
private:
    int id;
    string name;
    int quantity;
    list<Customer> pending_customers;
    list<Customer> renting_customers;
    
};










#endif