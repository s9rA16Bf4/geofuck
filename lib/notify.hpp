#include <iostream>

#ifndef NOTIFY_H
#define NOTIFY_H

void error(std::string msg);
void runtime_error(std::string msg, int line, int column);
void notify(std::string msg);

#endif