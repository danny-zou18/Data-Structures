#include <iostream>
#include <string> 
#include <utility>
#include <fstream>

#include "hashmap.h"

using std::cin; using std::cout; using std::endl;

//Hash Function borrowed from lab 11
class hash_string_obj {
public:
    unsigned int operator() ( const std::string& key ) const {
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
        hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
    }   

};
void initialize_hash(const string& genome, unsigned int kmer, hashmap<hash_string_obj>& hashmap){
    for (unsigned int i = 0; i < genome.size()-kmer-1; i++){
        string parsed = genome.substr(i, kmer);
        hashmap.insert(parsed, i);
    }
}
unsigned int compare_string(const string& s1, const string& s2){
    int differences = 0;
    for (unsigned int i = 0; i < s1.size(); i++){
        if (s1[i] != s2[i]){
            differences += 1;
        }
    }
    return differences;
}
void getResults(unsigned int num_mismatch, const string& genome,
    const string& query_string, const hashmap<hash_string_obj>& genome_hash){
        vector<int> found_positions;
        vector<int> errors;
        vector<string> parsed_genomes;
        vector<int> positions = genome_hash.findPositions(query_string);
        unsigned int query_size = query_string.size();
        if (positions.size() == 0){
            cout << "No match" << endl;
            return;
        }
        for (unsigned int i = 0; i < positions.size(); i++){
            string genome_match = genome.substr(positions[i], query_size);
            unsigned int differences = compare_string(genome_match, query_string);
            if (differences <= num_mismatch){
                found_positions.push_back(positions[i]);
                errors.push_back(differences);
                parsed_genomes.push_back(genome_match);
            }
        }
        if (found_positions.size() == 0){
            cout << "No Match" << endl;
            return;
        } else {
            for (unsigned int i = 0; i < found_positions.size(); i++){
                cout << found_positions[i] << " " << errors[i] << " " << parsed_genomes[i] << endl;
            }
        }
}

int main(){
    string filler;
    string input_file;
    
    cin >> filler >> input_file;
    std::ifstream in_file(input_file);
    if (!in_file.good()){
        std::cerr << "Cannot open " << input_file << "to read." << endl;
        exit(1);
    }
    hashmap<hash_string_obj> genome_hash;
    string genome = "";
    string parts;
    while (in_file >> parts){
        genome += parts;
    }

    while (cin >> filler){
        if (filler == "kmer"){
            unsigned int kmer;
            cin >> kmer;
            initialize_hash(genome, kmer, genome_hash);
            genome_hash.setKmer(kmer);
        } else if (filler == "table_size"){
            unsigned int table_size;
            cin >> table_size;
            genome_hash.setSize(table_size);
        } else if (filler == "occupancy"){
            unsigned int occupancy;
            cin >> occupancy;
            genome_hash.setOccupancy(occupancy);
        } else if (filler == "query"){
            unsigned int num_mismatch;
            string query_string;
            cin >> num_mismatch >> query_string;
            cout << "Query: " << query_string << endl;
            getResults(num_mismatch, genome, query_string, genome_hash);
        }
    }






    return 0;
}