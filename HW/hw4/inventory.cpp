#include "inventory.h"

Inventory::Inventory(int item_id, unsigned aQuantity, const string& item_name){
    id = item_id;
    quantity = aQuantity;
    name = item_name;
}

