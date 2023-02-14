#include "customer.h"
Customer::Customer(const Customer& c){
    id = c.getId();
    name = c.getName();
    
}
Customer::Customer(int custo_id, const std::string& custo_name){
    id = custo_id;
    name = custo_name;
    timeStamp = 0;
    item_id = 0;
}
void Customer::add_item(const Inventory& item){
    items.push_back(item);
}
void Customer::add_pending(const Inventory& item){
    pending_items.push_back(item);
}
void Customer::setTime(int time){
    timeStamp = time;
}
void Customer::setItemId(int itemId){
    item_id = itemId;
}