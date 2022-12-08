#include <string>
#include <vector>

#ifndef TOOLS_H
#define TOOLS_H


void read_file(std::string file_path, std::vector<std::string> *storage);
void print(int value);
void clean_input_buffer();
void convert_string(std::string line);

#endif