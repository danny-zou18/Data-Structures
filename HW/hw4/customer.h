#ifndef __customer_h_
#define __customer_h_
#include <list>
#include <string>


class Customer{
public:
    Customer(int custo_id, const std::string& custo_name);


private:
    int id;
    std::string name;
    std::list<int> items;
    std::list<int> item_quantities;
    
};























#endif