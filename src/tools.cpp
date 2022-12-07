#include <iostream>
#include <fstream>
#include <string>
#include "tools.hpp"
#include "notify.hpp"

void read_file(std::string file_path, std::vector<std::string> *storage){
    
    std::ifstream open_file(file_path);
    std::string current_line = "";
    
    if (open_file.is_open()){
        while (open_file.good()) { // Until EOF
            open_file >> current_line;
            storage->push_back(current_line);
        }

    }else{
        error("Failed to open file '"+file_path+"'");
    }
}