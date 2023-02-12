#ifndef __inventory_h_
#define __inventory_h_
#include <string>
using std::string;

class Inventory{
public:
    Inventory(unsigned a_id, unsigned aQuantity, const string& the_name);



private:
    unsigned id;
    string name;
    unsigned quantity;
};










#endif