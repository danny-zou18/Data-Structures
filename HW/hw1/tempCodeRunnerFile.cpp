//Creating the first and final line of the text, consisting of (4+width) hyphens ("-")
    string top_bottom = string(width + 4,'-');

    //Creating a string vector that holds the seperate lines of the text
    std::vector<string> lines;

    lines.push_back(top_bottom);

    int length_count = 0;

    std::vector<string> words_on_line;

    for (int i = 0; i < words.size(); i++){

        if ((length_count + words[i].size()) < width){

            length_count += words[i].size() + 1;

            words_on_line.push_back(words[i]);

        } else {


            // cout << "WORDS FOR LINE: " << endl;
            // for(unsigned int i = 0; i < words_on_line.size(); i++) {
            //     cout << words_on_line[i] << " ";
            // }'
            // cout << endl;
            length_count = 0;

            string middle_line = "| ";

            string words_to_line = "";

            for (unsigned int i = 0; i < words_on_line.size(); i++){

                if (i == words_on_line.size()-1){

                    words_to_line += words_on_line[i];

                } else {

                    string add_to_line = words_on_line[i] + " ";

                    words_to_line += add_to_line;
                
                }
            }
            int white_spaces = width -  words_to_line.size();

            middle_line += words_to_line + string(white_spaces,' ') + " |";

            lines.push_back(middle_line);

            words_on_line.clear();

            words_on_line.push_back(words[i]);

            length_count += words_on_line[0].size() + 1;

        }

    }

    if (words_on_line.size() > 0){

        string middle_line = "| ";

        string words_to_line = "";

        for (unsigned int i = 0; i < words_on_line.size(); i++){

            if (i == words_on_line.size()-1){

                words_to_line += words_on_line[i];

            } else {

                string add_to_line = words_on_line[i] + " ";

                words_to_line += add_to_line;
            
            }
            }
        int white_spaces = width -  words_to_line.size();

        middle_line += words_to_line + string(white_spaces,' ') + " |";

        lines.push_back(middle_line);
        
    }