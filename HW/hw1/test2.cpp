#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using std::cout; using std::endl; using std::cin;  using std::string;
using std::ifstream; using std::ofstream;

std::vector<string> seperate_word(string word, unsigned int width){
    std::vector<string> seperated_word;
    int index = 0;
            int limit = width - 1;
            while (true){
                if (word.size() - index > (width - 1)){
                    string split_word = word.substr(index, limit) + "-";
                    seperated_word.push_back(split_word);
                    index += (width-1);
                } else {
                    string split_word = word.substr(index);
                    seperated_word.push_back(split_word);
                    break;
                }
            }
    return seperated_word;
}

/* Function that takes in parameter a vector of words for a single line 
and returns a parsed string with a white space between every word */
string parsing(const std::vector<string> & words_on_line){
    string words_to_line = "";
    for (unsigned int i = 0; i < words_on_line.size(); i++){
        if (i == words_on_line.size()-1){
            words_to_line += words_on_line[i];
        } else {
            string add_to_line = words_on_line[i] + " ";
            words_to_line += add_to_line;
        }
    }
    return words_to_line;
}
//Flushing left function
string flush_left(const std::vector<string> & words, unsigned int width){

    string top_bottom = string(width + 4,'-'); //Creating the first and final line of the text, consisting of (4+width) hyphens ("-")
    std::vector<string> lines;  //Creating a string vector that holds the seperate lines of the text
   
    lines.push_back(top_bottom);
    int length_count = 0;

    std::vector<string> words_on_line; //A vector that stores all the words that can fit in a single line

    for (unsigned int i = 0; i < words.size(); i++){
        
        if ((length_count + words[i].size()) <= width){ //Checks to see if the next word can be added to the current line
            length_count += words[i].size() + 1; 
            words_on_line.push_back(words[i]); 
        } else {
            length_count = 0;
            /*Takes everything and formats it to the wanted line, then 
            adds that line to the vector that contains all the lines*/
            string middle_line = "| ";
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size(); //Determines the number of white spaces needed for the line
            middle_line += words_to_line + string(white_spaces,' ') + " |"; 
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
        }
    }
    //For the words on the second to last line (basically leftovers), that the for-loop above did not use and formats it seperately
    if (words_on_line.size() > 0){
        string middle_line = "| ";
        string words_to_line = parsing(words_on_line);
        int white_spaces = width -  words_to_line.size();
        middle_line += words_to_line + string(white_spaces,' ') + " |";
        lines.push_back(middle_line);
    }

    lines.push_back(top_bottom);

    string final;//Final fully formated string
    for (unsigned int i = 0; i < lines.size(); i++){ //For loop that goes through all the lines and adds it to the final string
        
        final += lines[i] + "\n";
    }
    return final;
}

string flush_right(const std::vector<string> & words, unsigned int width){

    string top_bottom = string(width + 4,'-'); //Creating the first and final line of the text, consisting of (4+width) hyphens ("-")
    std::vector<string> lines;  //Creating a string vector that holds the seperate lines of the text
   
    lines.push_back(top_bottom);
    int length_count = 0;

    std::vector<string> words_on_line;

    for (unsigned int i = 0; i < words.size(); i++){

        if ((length_count + words[i].size()) < width){
            length_count += words[i].size() + 1;
            words_on_line.push_back(words[i]);
        } else {
            length_count = 0;
            string middle_line = "| ";
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size();
            middle_line += string(white_spaces,' ') + words_to_line + " |";
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
        }
    }
    if (words_on_line.size() > 0){
        string middle_line = "| ";
        string words_to_line = parsing(words_on_line);
        int white_spaces = width -  words_to_line.size();
        middle_line += string(white_spaces,' ') + words_to_line + " |";
        lines.push_back(middle_line);
    }

    lines.push_back(top_bottom);

    string final;
    for (unsigned int i = 0; i < lines.size(); i++){
        
        final += lines[i] + "\n";
    }
    return final;
}

string full_justify(const std::vector<string> & words, unsigned int width){

    string top_bottom = string(width+ 4,'-');

    std::vector<string> lines;  //Creating a string vector that holds the seperate lines of the text
   
    lines.push_back(top_bottom);
    int length_count = 0;

    std::vector<string> words_on_line;

    for (unsigned int i = 0; i < words.size(); i++){
        
        if (words[i].size() == width){
            string middle_line = "| " + words[i] + " |";
            lines.push_back(middle_line);
            continue;
        }

        if ((length_count + words[i].size()) <= width){
            length_count += words[i].size() + 1;
            words_on_line.push_back(words[i]);
        } else {
        
            length_count = 0;
            string middle_line = "| ";
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size();
            std::vector<string> words_vector;
            for (unsigned int i = 0; i < words_on_line.size(); i++){
                if (i == words_on_line.size()-1){
                    words_vector.push_back(words_on_line[i]);
                } else {
                    string part_of_line = words_on_line[i] + " ";
                    words_vector.push_back(part_of_line);
                }
            }
            if (words_vector.size()==1){
                continue;
            }
            int x = 0;
            while (x < white_spaces){
                for (unsigned int i = 0; i < (words_vector.size()-1); i++){
                    words_vector[i] += " ";
                    x++;
                    if (x == white_spaces){
                        break;
                    }
                }
            }
            string final_add_line;
            for (unsigned int i = 0; i < words_vector.size(); i++){
                final_add_line += words_vector[i];
            }
            middle_line += final_add_line + " |";
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
            
        }
    }
    
    if (words_on_line.size() > 0){
        string middle_line = "| ";
        string words_to_line = parsing(words_on_line);
        int white_spaces = width -  words_to_line.size();
        middle_line += words_to_line + string(white_spaces,' ')+ " |";
        lines.push_back(middle_line);
    }
    lines.push_back(top_bottom);

    string final;
    for (unsigned int i = 0; i < lines.size(); i++){
        
        final += lines[i] + "\n";
    }
    return final;
}

int main(int argc, char* argv[]){
    //Checking to see if 4 Arguments are given
    if (argc != 5) {
        std::cerr << "Not the correct Amount of Arguments!";
        exit(1);
    }

    //Checking to see if the input file is opened correctly
    ifstream inFile;
    inFile.open(argv[1]);
    if (!inFile.good()) {
        std::cerr << "Can not open the file!" << argv[1] << endl;
        exit(1);
    }
    
    //Checking to see if the output file is opened correctly
    ofstream outFile;
    outFile.open(argv[2]);
    if (!outFile.good()){
        std::cerr << "Can not open file " << argv[2] << " to write." << endl;
        exit(1);
    }

    //Checks if the third argument is valid
    try{
        std::stoi(argv[3]); //Tests to see if third argument is an integer by test-casting it
    } catch(...){ // Catches the error
        cout << argv[3] << " is not a valid argument" << endl;
        exit(1);
    }

    //Checking to see if the 4th argument is a valid command
    if ( strcmp(argv[4], "flush_left") != 0 && strcmp( argv[4], "flush_right") != 0 && strcmp( argv[4], "full_justify") != 0){
        std::cerr << argv[4] << " is not a valid argument." << endl;
        exit(1);
    }

    //Casting the given width into a intege
    unsigned int width = std::stoi(argv[3]);
    
    //Defining a int var x for inputting from input file
    string x;
    //Defining a string vector to store the words in the input file
    std::vector<std::string> words;

    while (inFile >> x){ //Reads the words in the input file

        if (x.size() > width){
            std::vector<string> seperated_word = seperate_word(x,width);
            for (unsigned int i = 0; i < seperated_word.size(); i++){
                words.push_back(seperated_word[i]);
            }
            continue;
        }

        words.push_back(x); //Appends the word to the end of string vector ,words
    }

    for (unsigned int i = 0; i < words.size(); i++){

        if (words[i].size() > width ){
            cout << "Word exceeds width, Error ";
            exit(1);
        }
    }

    if (strcmp(argv[4],"flush_left") == 0){
        outFile << flush_left(words,width);
    } else if (strcmp(argv[4],"flush_right") == 0){
        outFile << flush_right(words,width);   
    } else {
        outFile << full_justify(words,width);
    }
    outFile.close();
    return 0;
}