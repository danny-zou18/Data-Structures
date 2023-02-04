#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using std::cout; using std::endl; using std::string;
using std::ifstream; using std::ofstream;

// Function to split a given word with hyphens if the word is bigger then the given width
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

void format_end(std::vector<string>& words_on_line, unsigned int width, std::vector<string>& lines){
    string words_to_line = parsing(words_on_line);
    int white_spaces = width -  words_to_line.size();
    string middle_line = "| " + words_to_line + string(white_spaces,' ') + " |";
    lines.push_back(middle_line);
}

//Flushing left function
string flush_left(const std::vector<string> & words, unsigned int width){

    string top_bottom = string(width + 4,'-'); //Creating the first and final line of the text, consisting of (4+width) hyphens ("-")
    std::vector<string> lines;  //Creating a string vector that holds the seperate lines of the text
   
    lines.push_back(top_bottom);
    int length_count = 0;

    std::vector<string> words_on_line; //A vector that stores all the words that can fit in a single line

    for (unsigned int i = 0; i < words.size(); i++){
        
        if ((length_count + words[i].size()) <= width){ //Checks if the next word can be added to the current line
            length_count += words[i].size() + 1; 
            words_on_line.push_back(words[i]); 
        } else {
            length_count = 0;
            /*Takes everything and formats it to the wanted line, then 
            adds that line to the vector that contains all the lines*/
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size(); //Determines the number of white spaces needed for the line
            string middle_line = "| " + words_to_line + string(white_spaces,' ') + " |"; 
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
        }
    }
    //Formats the words on the second to last line (basically leftovers), that the for-loop above did not use
    if (words_on_line.size() > 0){
        format_end(words_on_line, width, lines);
    }
    lines.push_back(top_bottom);

    string final;//Final fully formated string
    for (unsigned int i = 0; i < lines.size(); i++){ //For loop that goes through all the lines and adds it to the final string
        final += lines[i] + "\n";
    }
    return final;
}

// Flushing right function
// Has almost the same code as in the flush_left function, only change is where I put the white spaces
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
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size();
            string middle_line = "| " + string(white_spaces,' ') + words_to_line + " |"; // Only change
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
        }
    }
    if (words_on_line.size() > 0){
        format_end(words_on_line, width, lines);
    }

    lines.push_back(top_bottom);

    string final;
    for (unsigned int i = 0; i < lines.size(); i++){
        
        final += lines[i] + "\n";
    }
    return final;
}

// Full justify function
string full_justify(const std::vector<string> & words, unsigned int width){

    string top_bottom = string(width+ 4,'-');

    std::vector<string> lines;  //Creating a string vector that holds the seperate lines of the text
   
    lines.push_back(top_bottom);
    int length_count = 0;

    std::vector<string> words_on_line;

    for (unsigned int i = 0; i < words.size(); i++){
        //Checks if a singular word is equal to the width, if it is, format it and add to lines
        if (words[i].size() == width){
            if (words_on_line.size() == 1){ // Formats the line before the splitted words
                int white_spaces = width - words_on_line[0].size();
                string middle_line = "| " + words_on_line[0] + string(white_spaces,' ') + " |";
                lines.push_back(middle_line);
                length_count = 0;
                words_on_line.clear();
            }
            string middle_line = "| " + words[i] + " |";
            lines.push_back(middle_line);
            continue;
        }
        if ((length_count + words[i].size()) <= width){ // Checks if the next word can be added to the current line
            length_count += words[i].size() + 1;
            words_on_line.push_back(words[i]);
        } else {
            if (words_on_line.size() == 1){
                int white_spaces = width - words_on_line[0].size();
                string middle_line = "| " + words_on_line[0] + string(white_spaces,' ') + " |";
                lines.push_back(middle_line);
                length_count = 0;
                words_on_line.clear();
                continue;
            }
            length_count = 0;
            string words_to_line = parsing(words_on_line);
            int white_spaces = width -  words_to_line.size(); // Get the number of whitespaces on the line
            std::vector<string> words_vector; // Creates a vector that the basic formatted line, ex {"Here ", "is ", "an"}
            for (unsigned int i = 0; i < words_on_line.size(); i++){    // that comes out to "Here is an"
                if (i == words_on_line.size()-1){
                    words_vector.push_back(words_on_line[i]);
                } else {
                    string part_of_line = words_on_line[i] + " ";
                    words_vector.push_back(part_of_line);
                }
            }
            // x is the amount of whitespaces we have used, once there are no more whitespaces or equivalently 
            // when x is == the number of white_space, break both loops
            int x = 0;
            while (x < white_spaces){
                for (unsigned int i = 0; i < (words_vector.size()-1); i++){ //Each time this for loop runs, add a white space to a word
                    words_vector[i] += " ";                                 //and increase x by 1
                    x++;
                    if (x == white_spaces){
                        break;
                    }
                }
            }
            // Adds every word in word vector with the correct amount of white spaces into one complete, correctly formatted string
            string final_add_line;
            for (unsigned int i = 0; i < words_vector.size(); i++){
                final_add_line += words_vector[i];
            }
            // Finishes formatting the middle line and adds the complete line to all the existing lines
            string middle_line = "| " + final_add_line + " |";
            lines.push_back(middle_line);
            words_on_line.clear();
            words_on_line.push_back(words[i]);
            length_count += words_on_line[0].size() + 1;
        }
    }
    // For leftover words
    if (words_on_line.size() > 0){
        format_end(words_on_line, width, lines);
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

        if (x.size() > width){ // If the inputted word is bigger then the given width
            std::vector<string> seperated_word = seperate_word(x,width); // Call "seperate_word" to split the word
            for (unsigned int i = 0; i < seperated_word.size(); i++){ //Appends each each of the splitted word to the end of string
                words.push_back(seperated_word[i]);                   //vector,words
            }
            continue;
        }

        words.push_back(x); //Appends the word to the end of string vector ,words
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