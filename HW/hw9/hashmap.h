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
    hashmap(unsigned int init_size = 100, float init_occu = 0.5);

    hashmap(const hashmap<HashFunc>& old)
    : m_table(old.m_table), num_keys(old.num_keys), occupancy(old.occupancy) {}

    ~hashmap() {};

    vector<int> findPositions(const string& query_string) const ;

    void setOccupancy(float new_occu) {occupancy = new_occu;}
    void setSize(unsigned int size);
    void setKmer(unsigned int Kmer) {kmer = Kmer;}

    void insert(const string& key, unsigned int position);

private:
    vector<pair<string, vector<int> > > m_table;
    float occupancy;
    unsigned int num_keys;
    HashFunc Hash;
    unsigned int kmer;
    void resize_table(unsigned int new_size);
};
template <class HashFunc>
hashmap<HashFunc>::hashmap(unsigned int init_size, float init_occu){
    num_keys = 0;
    occupancy = init_occu;
    for (unsigned int i = 0; i < init_size; i++){
        m_table.push_back(std::make_pair("", vector<int>()));
    }
}
template <class HashFunc>
vector<int> hashmap<HashFunc>::findPositions(const string& query_string) const {
    string parsed = query_string.substr(0, kmer);
    unsigned int hash_value = Hash(parsed);
    unsigned int index = hash_value % m_table.size();
    unsigned int start_index = hash_value % m_table.size();
    //If the key does not match with the parsed kmer, then find using linear probing
    if (m_table[index].first != parsed){
        while (m_table[index].first != parsed){
            index += 1;
            if (index >= m_table.size()){
                index = 0;
            }
            if (index == start_index){
                vector<int> empty;
                return empty;
            }
        }
    }
    return m_table[index].second;
}
template <class HashFunc>
void hashmap<HashFunc>::setSize(unsigned int size){
    m_table.clear();
    for (unsigned int i = 0; i < size; i++){
        m_table.push_back(std::make_pair("", vector<int>()));
    }
}
template <class HashFunc>
void hashmap<HashFunc>::insert(const string& key, unsigned int position){
    unsigned int new_occu = float(num_keys/m_table.size());
    if (new_occu > occupancy){
        unsigned int new_size = m_table.size() * 2;
        resize_table(new_size);
    }
    unsigned int hash_value = Hash(key);
    unsigned int index = hash_value % m_table.size();

    if (m_table[index].first == ""){
        vector<int> positions;
        positions.push_back(position);
        m_table[index] = make_pair(key, positions);
        num_keys += 1;
    } else {
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
        if (!found && m_table[index].first == ""){
            vector<int> positions;
            positions.push_back(position);
            m_table[index] = make_pair(key, positions);
            num_keys += 1;
        }
    }
} 
template <class HashFunc>
void hashmap<HashFunc>::resize_table(unsigned int new_size){
    vector<pair<string, vector<int> > > temp_table = m_table;
    m_table.clear();
    for (unsigned int i = 0; i < new_size; i++){
        m_table.push_back(make_pair("", vector<int>()));
    }
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