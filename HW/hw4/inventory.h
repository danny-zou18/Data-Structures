#ifndef __inventory_h_
#define __inventory_h_
#include <string>
#include <list>
using std::string; using std::list; 

class Customer;
class Inventory{
public:
    //Constructors
    Inventory(const Inventory& item); //Copy Constructor
    Inventory(int item_id, unsigned aQuantity, const string& item_name);

    //Accessors
    int getId() const {return id;}
    const string& getName() const {return name;}
    int getQuantity() const {return quantity;}

    //Modifiers
    void setQuantity(int quantity);
    void rentQuantity(int change);
    void returnQuantity(int change);

private:
    int id;
    string name;
    int quantity;
    
};

#endif