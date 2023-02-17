#include "Customer.h"

Customer::Customer(const std::string &n, const std::string &i, const std::string &t,const bool r,const bool p){
    name = n;
    id = i;
    renting = r;
    pending = p;
    timestamp = t;
}

void Customer::remove_rtool(const std::string id){
    typename std::list<Inventory>::iterator itr;
    //loops through all of the tools and erases the id 
    for(itr = rtools.begin(); itr!=rtools.end(); itr++){
        if((*itr).get_id()==id){
            itr = rtools.erase(itr);
            //if nothing is left then they are no longer renting
            if(rtools.size()==0)
                renting = false;
            break;
        }
    }
}
void Customer::remove_ptool(const std::string id){
    typename std::list<Inventory>::iterator itr;
    //loops through all of the tools and erases the id 
    for(itr = ptools.begin(); itr!=ptools.end(); itr++){
        if((*itr).get_id()==id){
            itr = ptools.erase(itr);
            //if nothing is left then they are no longer pending
            if(ptools.size()==0)
                pending = false;
            break;
        }
    }
}

void Customer::remove_ptool(){
    //erases the first tool
    ptools.erase(ptools.begin());
    //if nothing is left then they are no longer pending
    if(ptools.size()==0)
        pending = false;
}

void Customer::remove_rtool(){
    //erases the first tool 
    rtools.erase(rtools.begin());
    // if nothing is left then they are no longer renting
    if(rtools.size()==0)
        renting = false;
}

typename std::list<Inventory>::iterator Customer::get_ptool(std::string tid){
    typename std::list<Inventory>::iterator itr;
    //returns the iterator of the tool that has the same id
    for(itr = ptools.begin(); itr!=ptools.end(); itr++){
        if((*itr).get_id()==tid){
            return itr;
        }
    }
    //nothing in there so return the end id
    return ptools.end();
}
typename std::list<Inventory>::iterator Customer::get_rtool(std::string tid){
    typename std::list<Inventory>::iterator itr;
    //returns the iterator of the tool that has the same id
    for(itr = rtools.begin(); itr!=rtools.end(); itr++){
        if((*itr).get_id()==tid){
            return itr;
        }
    }
    //nothing in there so return the end id
    return rtools.end();
}

bool Customer::pendingContains(std::string toolid){
    typename std::list<Inventory>::iterator itr;
    //checks if the pending tools list contains the id in the argument
    for(itr = ptools.begin(); itr!=ptools.end(); itr++){
        if((*itr).get_id()==toolid){
            return true;
        }
    }
    return false;
}
bool Customer::rentingContains(std::string toolid){
    typename std::list<Inventory>::iterator itr;
    //checks if the renting tools list contains the id in the argument
    for(itr = rtools.begin(); itr!=rtools.end(); itr++){
        if((*itr).get_id()==toolid){
            return true;
        }
    }
    return false;
}