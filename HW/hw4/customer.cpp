#include "customer.h"
Customer::Customer(const Customer& c){
    id = c.getId();
    name = c.getName();
    items = c.getItems();
    pending_items = c.getPending();
    
}
Customer::Customer(int custo_id, const std::string& custo_name){
    id = custo_id;
    name = custo_name;
    timeStamp = 0;
    item_id = 0;
}
bool Customer::check_item(int part_id) const {
    for (list<Inventory>::const_iterator it = items.begin(); it != items.end();it++){
        if (it->getId() == part_id){
            return true;
        }
    }
    return false;
}
bool Customer::check_pending(int part_id) const {
    for (list<Inventory>::const_iterator it = pending_items.begin(); it != pending_items.end();it++){
        if (it->getId() == part_id){
            return true;
        }
    }
    return false;
}
Inventory Customer::get_item(int part_id) const {
    for (list<Inventory>::const_iterator it = items.begin(); it != items.end();it++){
        if (it->getId() == part_id){
            return (*it);
        }
    }
    return items.front();
}
Inventory Customer::get_pending_item(int part_id) const{
    for (list<Inventory>::const_iterator it = pending_items.begin(); it != pending_items.end();it++){
        if (it->getId() == part_id){
            return (*it);
        }
    }
    return items.front();
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
void Customer::remove_item(int part_id){

    for (list<Inventory>::iterator it = items.begin(); it != items.end(); it++){
        if (it->getId() == part_id){
            it = items.erase(it);
            break;
        }
    }
}
void Customer::remove_pending() {
    pending_items.pop_front();
}

std::ostream& operator<< (std::ostream& out, const Customer& c){
    out << "C" << std::setfill('0') << std::setw(4) << c.id << " " << c.getName() << std::endl;
    if (c.items.size() > 0){
        out << "Rentals:";
        for (list<Inventory>::const_iterator it = c.items.begin(); it != c.items.end(); it++){
            out << " T" << std::setfill('0') << std::setw(4) << it->getId() << " (" << it->getQuantity() << ")";
        }
        out << std::endl;
    }
    if (c.pending_items.size() > 0){
        out << "Pending:";
        for (list<Inventory>::const_iterator it1 = c.pending_items.begin(); it1 != c.pending_items.end(); it1++){
            out << " T" << std::setfill('0') << std::setw(4) << it1->getId() << " (" << it1->getQuantity() << ")";
        }
        out << std::endl;
    } 
    return out;
}
