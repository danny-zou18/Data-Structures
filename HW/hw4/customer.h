#ifndef __customer_h_
#define __customer_h_
#include <list>
#include <string>
#include "inventory.h"
using std::list; using std::string;

class Customer{
public:
    //Constructors
    Customer(const Customer& c);
    Customer(int custo_id, const std::string& custo_name);

    //Accessors
    int getId() const {return id;}
    string getName() const {return name;}
    list<Inventory> getItems() const {return items;}
    list<Inventory> getPending() const {return pending_items;}
    int getTimeStamp() const {return timeStamp;}

    //Modifiers
    void add_item(const Inventory item);
    void add_pending(const Inventory item);
    void setTime(int time);
    void setItemId(int itemId);

private:
    int id;
    string name;
    int timeStamp;
    int item_id;
    
    list<Inventory> items;
    list<Inventory> pending_items;

};























#endif