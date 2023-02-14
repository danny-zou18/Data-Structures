#include "inventory.h"

Inventory::Inventory(const Inventory& item){
    id = item.getId();
    quantity = item.getQuantity();
    name = item.getName();
}
Inventory::Inventory(int item_id, unsigned aQuantity, const string& item_name){
    id = item_id;
    quantity = aQuantity;
    name = item_name;
}
void Inventory::setQuantity(int quantity){
    quantity = quantity;
}
void Inventory::rentQuantity(int change){
    quantity -= change;
}
void Inventory::returnQuantity(int change){
    quantity += change;
}
