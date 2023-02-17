#ifndef __Inventory__h__
#define __Inventory__h__

#include <string>
//this class is essentially just to hold the info of the tools and no other logic
class Inventory{
public:
    //constructor
    Inventory(const std::string &n, const std::string &i, const int q);

    //accessors
    std::string get_name() const{return name;}
    std::string get_id() const{return id;}
    int get_quantity() const{return quantity;} 
    int get_original_quantity() const{return originalQuantity;}

    //mutators
    void set_name(const std::string &n) {name = n;}
    void set_id(const std::string &i) {id = i;}
    void set_quantity(const int q) {quantity = q;}
private:
    std::string name;
    std::string id;
    //the start quantity and the current quantity if they are different that means someone has rented some of the tools
    int originalQuantity;
    int quantity;
};


#endif