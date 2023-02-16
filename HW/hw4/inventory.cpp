#include "inventory.h"
//Copy Constructor
Inventory::Inventory(const Inventory& item){
    id = item.getId();
    quantity = item.getQuantity();
    name = item.getName();
}
//Normal Constructor
Inventory::Inventory(int item_id, unsigned aQuantity, const string& item_name){
    id = item_id;
    quantity = aQuantity;
    name = item_name;
}
//Member function that sets the quantity of the item
void Inventory::setQuantity(int aQuantity){
    quantity = aQuantity;
}
//Member function that decreases the quantity of the item because its getting rented out
void Inventory::rentQuantity(int change){
    quantity -= change;
}
//Member function that increases the quantity of the item because its getting returned
void Inventory::returnQuantity(int change){
    quantity += change;
}
