#ifndef __Customer__h__
#define __Customer__h__

#include <string>
#include <list>
#include "Inventory.h"
class Customer{
public:
    //constructor
    Customer(const std::string &n, const std::string &i, const std::string &t,const bool r,const bool p);

    //accessprs
    std::string get_name() const{return name;}
    std::list<Inventory> get_rtools() {return rtools;}
    std::list<Inventory> get_ptools() {return rtools;}
    //returning the iterator for the tool in the list that has a specific id or is in the first position
    typename std::list<Inventory>::iterator get_ptool(std::string tid);
    typename std::list<Inventory>::iterator get_ptool() {return ptools.begin();}
    typename std::list<Inventory>::iterator get_rtool(std::string tid);
    typename std::list<Inventory>::iterator get_rtool() {return rtools.begin();}
    std::string get_id() const{return id;}
    std::string get_timestamp() const{return timestamp;}
    bool isRenting() const{return renting;}
    bool isPending() const{return pending;}
    bool pendingContains(std::string toolid);
    bool rentingContains(std::string toolid);
    //mutators
    void set_name(const std::string &n){name = n;}
    void set_id(const std::string &i){id = i;}
    void set_timestamp(const std::string &t){timestamp = t;} 
    void set_pending(const bool p){pending = p;}
    void set_renting(const bool r){renting = r;}
    void add_rtool(const Inventory tid){rtools.push_back(tid);}
    void add_ptool(const Inventory tid){ptools.push_back(tid);}
    //removes a tool from the list at an id or the first id
    void remove_rtool(const std::string id);
    void remove_rtool();
    void remove_ptool(const std::string id);
    void remove_ptool();


private:
    //the lists hold the tools that they are either pending for or renting
    std::list<Inventory> rtools;
    std::list<Inventory> ptools;
    
    std::string timestamp;
    std::string id;
    std::string name;
    bool renting;
    bool pending;
};

#endif