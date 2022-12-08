#include <vector>
#include <string>

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

void parsing_n_execution(std::string line, int line_number, bool step_by_step);
void interpreter(std::vector<std::string>* contents, bool detailed_view, bool step_by_step_view, int limit);

void advance_view(int limit);
void step_by_step_view(char instruction);

#endif