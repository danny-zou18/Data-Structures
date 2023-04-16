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
//Helper function to initialize the hash table, inserting all the keys/positions into their correct indexes
void initialize_hash(const string& genome, unsigned int kmer, hashmap<hash_string_obj>& hashmap){
    for (unsigned int i = 0; i < genome.size()-kmer-1; i++){
        string parsed = genome.substr(i, kmer);
        hashmap.insert(parsed, i);
    }
}
//Helper function compares two strings and returns an unsigned integer representing how many differences
//the two words have
unsigned int compare_string(const string& s1, const string& s2){
    int differences = 0;
    string temp = s1;
    if (s2.size() > s1.size()){ //If the genome match is shorter then the query string
        for (unsigned int i = 0; i < s2.size()-s1.size(); i++){
            temp += " ";
        }
    }
    for (unsigned int i = 0; i < s2.size(); i++){
        if (temp[i] != s2[i]){
            differences += 1;
        }
    }
    return differences;
}
//Function that gets the results of the query command and prints them out. 
void getResults(unsigned int num_mismatch, const string& genome,
    const string& query_string, const hashmap<hash_string_obj>& genome_hash){
        //Create 3 corresponding vectors that tracks related values from the results
        vector<int> found_positions;
        vector<int> errors;
        vector<string> parsed_genomes;
        //Find the positions that the query string is found at in the genome using the hashmap
        vector<int> positions = genome_hash.findPositions(query_string);
        unsigned int query_size = query_string.size();
        //If no positions are found, print "No match" and exit the function
        if (positions.size() == 0){
            cout << "No Match" << endl;
            return;
        }
        //Loop through the different positions and check if the partial genome is a valid match 
        // for the query string. If it is, push the 3 different values, which are the position 
        // it was found at, the number of differences it contains and then the partial genome itself
        // into its respective vectors
        for (unsigned int i = 0; i < positions.size(); i++){
            string genome_match = genome.substr(positions[i], query_size);
            unsigned int differences = compare_string(genome_match, query_string);
            if (differences <= num_mismatch){
                found_positions.push_back(positions[i]);
                errors.push_back(differences);
                parsed_genomes.push_back(genome_match);
            }
        }
        //If one of the result vectors is empty, then all of them are. Print "No match" and exit the function
        if (found_positions.size() == 0){
            cout << "No Match" << endl;
            return;
        } else {
            //Else, print the results
            for (unsigned int i = 0; i < found_positions.size(); i++){
                cout << found_positions[i] << " " << errors[i] << " " << parsed_genomes[i] << endl;
            }
        }
}

int main(){
    //Initialize variables to be read
    string filler;
    string input_file;
    //First read in the input file
    cin >> filler >> input_file;
    std::ifstream in_file(input_file); 
    if (!in_file.good()){ //Check if the input file is valid
        std::cerr << "Cannot open " << input_file << "to read." << endl;
        exit(1);
    }
    hashmap<hash_string_obj> genome_hash; //Initialize our genome hash table
    string genome = ""; //Create a string that stores the entire genome sequence
    string parts;
    while (in_file >> parts){
        genome += parts;
    }
    //While we take in different commands, keep running 
    while (cin >> filler){
        if (filler == "kmer"){ 
            unsigned int kmer;
            cin >> kmer;
            //Initialize hash table with values and set the kmer length
            initialize_hash(genome, kmer, genome_hash); 
            genome_hash.setKmer(kmer);
        } else if (filler == "table_size"){
            unsigned int table_size;
            cin >> table_size;
            //Set the size of the table if specified
            genome_hash.setSize(table_size);
        } else if (filler == "occupancy"){
            //Set the occupancy of the table if specified
            unsigned int occupancy;
            cin >> occupancy;
            genome_hash.setOccupancy(occupancy);
        } else if (filler == "query"){
            unsigned int num_mismatch;
            string query_string;
            cin >> num_mismatch >> query_string;
            cout << "Query: " << query_string << endl;
            //Get the results from the query and print it out using the function below
            getResults(num_mismatch, genome, query_string, genome_hash);
        }
    }






    return 0;
}