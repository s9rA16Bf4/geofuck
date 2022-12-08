#include "notify.hpp"


void error(std::string msg){
    std::cout << "[!] Error: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

void runtime_error(std::string msg, int line, int column){
    std::cout << "[!] Error: " << msg << std::endl;
    std::cout << "* Line: " << line+1 << std::endl;
    std::cout << "* Column: " << column+1 << std::endl;
    exit(EXIT_FAILURE);
}


void notify(std::string msg){
    std::cout << "[~] " << msg << std::endl;
}