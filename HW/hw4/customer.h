#ifndef __customer_h_
#define __customer_h_
#include <list>
#include <string>
using std::list; using std::string;

class Customer{
public:
    Customer(int custo_id, const std::string& custo_name);

    int getId() const {return id;}
    string getName() const {return name;}
    list<int> getItems() const {return items;}


private:
    int id;
    string name;
    list<int> items;
    
};























#endif