#ifndef hashmap_h_
#define hashmap_h_

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using std::vector; using std::pair; using std::string;

template <class HashFunc>
class hashmap{
public:
    //Constructor
    hashmap(unsigned int init_size = 100, float init_occu = 0.5);
    //Copy constructor
    hashmap(const hashmap<HashFunc>& old)
    : m_table(old.m_table), num_keys(old.num_keys), occupancy(old.occupancy) {}
    //Deconstructor
    ~hashmap() {};

    //Accessors
    vector<int> findPositions(const string& query_string) const ;
    
    //Modifiers
    void setOccupancy(float new_occu) {occupancy = new_occu;}
    void setSize(unsigned int size);
    void setKmer(unsigned int Kmer) {kmer = Kmer;}
    void insert(const string& key, unsigned int position);

private:
    //Private variables and functions
    vector<pair<string, vector<int> > > m_table;
    float occupancy;
    unsigned int num_keys;
    HashFunc Hash;
    unsigned int kmer;
    void resize_table(unsigned int new_size);
};
//Constructor that sets the initial values and approprimate amount of empty pairs in the hash table
template <class HashFunc>
hashmap<HashFunc>::hashmap(unsigned int init_size, float init_occu){
    num_keys = 0;
    occupancy = init_occu;
    for (unsigned int i = 0; i < init_size; i++){
        m_table.push_back(std::make_pair("", vector<int>()));
    }
}
//Class function that returns a list of the different positions the query string is found at
template <class HashFunc>
vector<int> hashmap<HashFunc>::findPositions(const string& query_string) const {
    string parsed = query_string.substr(0, kmer);
    //Hash the parsed query string to get the right index to search
    unsigned int hash_value = Hash(parsed);
    unsigned int index = hash_value % m_table.size();
    unsigned int start_index = hash_value % m_table.size();

    std::cout << "start index: " << start_index << std::endl;
    

    //If the key does not match with the parsed kmer, then find using linear probing
    if (m_table[index].first != parsed){
        while (m_table[index].first != parsed){
            index += 1;
            //If we reach the end of the table, start from the beginning at index 0
            if (index >= m_table.size()){ 
                index = 0;
            }
            //We return to the starting position, meaning nothing is found.
            if (index == start_index){
                vector<int> empty;
                return empty;
            }
        }
    }
    return m_table[index].second;
}
//Class function that sets the size of the table and re-initializes the correct amount of 
//empty pairs in the hash table
template <class HashFunc>
void hashmap<HashFunc>::setSize(unsigned int size){
    m_table.clear();
    for (unsigned int i = 0; i < size; i++){
        m_table.push_back(std::make_pair("", vector<int>()));
    }
}
//Class function that takes a kmer and its position and hashes it into the hash table
template <class HashFunc>
void hashmap<HashFunc>::insert(const string& key, unsigned int position){
    //Calculate new occupancy, if it is greater then set occupancy, 2x the size of the table and rehash
    //the old values into the new size table
    unsigned int new_occu = float(num_keys/m_table.size());
    if (new_occu > occupancy){
        unsigned int new_size = m_table.size() * 2;
        resize_table(new_size);
    }
    unsigned int hash_value = Hash(key);
    unsigned int index = hash_value % m_table.size();

    //If the vector index is empty, then we have found a valid spot to insert the kmer and its position
    if (m_table[index].first == ""){
        vector<int> positions;
        positions.push_back(position);
        m_table[index] = make_pair(key, positions);
        num_keys += 1;
    } else {
        //Else check if the taken spot has the same key as current kmer and if it is, just push back
        //the position the current kmer is at into the existing key
        bool found = false;
        if (m_table[index].first != ""){
            while (m_table[index].first != ""){
                if (m_table[index].first == key){
                    m_table[index].second.push_back(position);
                    found = true;
                    break;
                }
                index += 1;
                if (index == m_table.size()){
                    index = 0;
                }
            }
        }
        //If no same key is found, and the current position is empty, insert the kmer and its position
        if (!found && m_table[index].first == ""){
            vector<int> positions;
            positions.push_back(position);
            m_table[index] = make_pair(key, positions);
            num_keys += 1;
        }
    }
} 
//Simple resize function that resizes the table and rehashes all the old keys/values
template <class HashFunc>
void hashmap<HashFunc>::resize_table(unsigned int new_size){
    //Create a temporary hash table that has the same values as old hash table
    vector<pair<string, vector<int> > > temp_table = m_table;
    m_table.clear(); //Clear old table
    for (unsigned int i = 0; i < new_size; i++){ // Initialize new amounts of empty pairs
        m_table.push_back(make_pair("", vector<int>()));
    }
    //Rehash the keys from old table into the newly sized table
    for (unsigned int i = 0; i < temp_table.size(); i++){
        if (temp_table[i].first != ""){
            string kmer_key = temp_table[i].first;
            unsigned int hash_value = Hash(kmer_key);
            unsigned int index = hash_value % new_size;
            //Avoid collision using linear probing
            if (m_table[index].first != ""){
                while (m_table[index].first != ""){
                    index += 1;
                }
            }
            m_table[index] = temp_table[i];
        }
    }
}




#endif