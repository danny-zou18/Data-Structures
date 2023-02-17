#include "Inventory.h"

Inventory::Inventory(const std::string &n, const std::string &i, const int q){
    name = n;
    id = i;
    quantity = q;
    //sets this at when it is created and never changes it
    originalQuantity = q;
}