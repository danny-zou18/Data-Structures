#ifndef __inventory_h_
#define __inventory_h_
#include <string>
#include <list>
using std::string; using std::list; 

class Inventory{
public:
    Inventory(unsigned item_id, unsigned aQuantity, const string& item_name);

    //Accessors
    unsigned getId() const {return id;}
    const string& getName() const {return name;}
    unsigned getQuantity() const {return quantity;}

    //Modifiers
    void changeQuantity(int change);
    void addToRenting();
    void addToPending();

    
private:
    int id;
    string name;
    int quantity;
    list<string> pending_customers;
    list<int> pending_quantity;
    list<string> renting_customers;
    list<int> renting quantity;
};










#endif