#ifndef __inventory_h_
#define __inventory_h_
#include <string>
using std::string;

class Inventory{
public:
    Inventory(unsigned a_id, unsigned aQuantity, const string& item_name);

    //Accessors
    unsigned getId() const {return id;}
    const string& getName() const {return name;}
    unsigned getQuantity() const {return quantity;}



private:
    int id;
    string name;
    int quantity;
};










#endif