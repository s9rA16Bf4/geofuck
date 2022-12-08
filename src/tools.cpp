#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 

#include "tools.hpp"
#include "notify.hpp"

void read_file(std::string file_path, std::vector<std::string> *storage){
    
    std::ifstream open_file(file_path);
    std::string current_line = "";
    
    if (open_file.is_open()){
        while (getline(open_file, current_line)) { // Until EOF

            if (current_line.find("§") == std::string::npos){ // Ignore the line if it contains a comment
                storage->push_back(current_line);
            }

        }

    }else{
        error("Failed to open file '"+file_path+"'");
    }
}

// Prints the provided @value either as a char or as an integer
void print(int value){
    if (value >= 32 && value <= 57 || value >= 58 && value <= 126){ // Autoconvert if it's readable chars!
        std::cout << (char)value;
    }else{
        std::cout << value;
    }
}

// Cleans the input buffer
void clean_input_buffer(){
    while((getchar())!='\n');
}

// Converts the provied string into the geofuck equivalent
void convert_string(std::string line){
    std::string converted_string = "";
    for (int i = 0; i < line.size(); i++){
        char c = line[i];
        std::string tmp_line = "";
        
        while(c > 1){
            if (c%2 != 0){
                tmp_line += "+";
                c--;
            }

            c /= 2;
            tmp_line += "*" ;
        }
        tmp_line += "+";
        std::reverse(tmp_line.begin(), tmp_line.end());
        tmp_line += ".";

        if (i+1 < line.size()){ // It already contains a set value
            tmp_line += "e";
        }

        converted_string += tmp_line;
    }

    notify(converted_string);
}