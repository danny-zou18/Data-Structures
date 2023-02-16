#include "customer.h"
//Copy Constructor
Customer::Customer(const Customer& c){
    id = c.getId();
    name = c.getName();
    items = c.getItems();
    pending_items = c.getPending();
    
}
//Normal Constructor that takes in customer id and customer name and initializes them in a member object
Customer::Customer(int custo_id, const std::string& custo_name){
    id = custo_id;
    name = custo_name;
    timeStamp = 0;
    item_id = 0;
}
//Member function that checks if a customer contains a certain item
bool Customer::check_item(int part_id) const {
    for (list<Inventory>::const_iterator it = items.begin(); it != items.end();it++){
        if (it->getId() == part_id){
            return true;
        }
    }
    return false;
}
//Member function that checks if a customer is currently waiting for a item
bool Customer::check_pending(int part_id) const {
    for (list<Inventory>::const_iterator it = pending_items.begin(); it != pending_items.end();it++){
        if (it->getId() == part_id){
            return true;
        }
    }
    return false;
}
//Member function that returns a inventory type item from the customers items list based on the given item id
Inventory Customer::get_item(int part_id) const {
    for (list<Inventory>::const_iterator it = items.begin(); it != items.end();it++){
        if (it->getId() == part_id){
            return (*it);
        }
    }
    return items.front();
}
//Member function that returns a inventory type item from the customers pending items list based on the given item id
Inventory Customer::get_pending_item(int part_id) const{
    for (list<Inventory>::const_iterator it = pending_items.begin(); it != pending_items.end();it++){
        if (it->getId() == part_id){
            return (*it);
        }
    }
    return items.front();
}
//Member function that adds a item to the items list
void Customer::add_item(const Inventory& item){
    items.push_back(item);
}
//Member function that adds a item to the pending items list
void Customer::add_pending(const Inventory& item){
    pending_items.push_back(item);
}
//Member function that sets the timestamp of the customer if they goes into the waitlist
void Customer::setTime(int time){
    timeStamp = time;
}
//Member function that removes a item from the customers item list
void Customer::remove_item(int part_id){
    for (list<Inventory>::iterator it = items.begin(); it != items.end(); it++){
        if (it->getId() == part_id){
            it = items.erase(it);
            break;
        }
    }
}
//Member function that removes a item from the customers pending items list
void Customer::remove_pending(int part_id) {
    for (list<Inventory>::iterator it = pending_items.begin(); it != pending_items.end(); it++){
        if (it->getId() == part_id){
            it = pending_items.erase(it);
            break;
        }
    }
}
//Out operator that correctly formats the customers information and outs it
std::ostream& operator<< (std::ostream& out, const Customer& c){
    out << "C" << std::setfill('0') << std::setw(4) << c.id << " " << c.getName() << std::endl;
    if (c.items.size() > 0){
        out << "Rentals: ";
        for (list<Inventory>::const_iterator it = c.items.begin(); it != c.items.end(); it++){
            out << "T" << std::setfill('0') << std::setw(4) << it->getId() << " (" << it->getQuantity() << ") ";
        }
        out << std::endl;
    }
    if (c.pending_items.size() > 0){
        out << "Pending: ";
        for (list<Inventory>::const_iterator it1 = c.pending_items.begin(); it1 != c.pending_items.end(); it1++){
            out <<  "T" << std::setfill('0') << std::setw(4) << it1->getId() << " (" << it1->getQuantity() << ") ";
        }
        out << std::endl;
    } 
    return out;
}
