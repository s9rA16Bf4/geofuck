#include <iostream>
#include <vector>
#include <string>
#include "notify.hpp"
#include "tools.hpp"
#include "interpreter.hpp"
#include "args.hpp"

int main(int argc, char** argv){
    arg _arg;
    _arg.addArgument("--help", "-h", false, "Prints the help screen"); 
    _arg.addArgument("--file", "-f", true, "File to parse [REQUIRED]");
    _arg.addArgument("--detailed_view", "-dv", false, "Prints all cells after execution, use '-l' to limit the amount of cells!");
    _arg.addArgument("--step_by_step_view", "-sv", false, "Prints the affected cell after each instruction");
    _arg.addArgument("--limit", "-l", true, "Limits how many cells that will be printed.");
    _arg.addArgument("--convert", "-c", true, "Converts the provided string into a geofuck equivalent");
    _arg.addArgument("--interpret", "-i", true, "Interpretes the provided string");

    if (argc < 2){
        error("No file was provided!\nUSAGE: ./bf -f <file/to/read>");
    }
    _arg.parseArgs(argc, argv);

    if (_arg.checkArg("--help")){
        _arg.help();
        return 0;
    }
    
    else if (_arg.checkArg("--convert")){
        convert_string(_arg.getValue("--convert"));
        return 0;
    }

    if (!_arg.checkArg("--file") && !_arg.checkArg("--interpret")){
        error("The '-f' was not passed!");
    }

    int limit = 30000;
    bool detailed_view = false;
    bool step_by_step_view = false;

    if (_arg.checkArg("--detailed_view")){
        detailed_view = true;
    }

    if (_arg.checkArg("--step_by_step_view")){
        step_by_step_view = true;
    }

    if (_arg.checkArg("--limit")){
        try{
            limit = std::atoi(_arg.getValue("--limit").c_str());
        }catch(const std::exception& e){
            error("The '-l' flag didn't receive an integer value!");
        }
    }

    std::vector<std::string> content;

    if (_arg.checkArg("--file")){
        read_file(_arg.getValue("--file"), &content);
    }else{
        content.push_back(_arg.getValue("--interpret"));
    }

    interpreter(&content, detailed_view, step_by_step_view, limit);

    return 0;
}