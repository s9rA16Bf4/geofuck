#include <math.h>
#include "interpreter.hpp"
#include "notify.hpp"
#include "tools.hpp"

struct cell_map_t{
    int** grid;
    int x_cord;
    int y_cord;
    int x_max;
    int y_max;

    cell_map_t(){
        this->y_max = 30000; // Default value
        this->x_max = 30000; // Default value
        this->default_init();
    }

    void default_init(){
        this->grid = (int**)calloc((this->x_max*this->y_max), sizeof(int*)); // Allocate our 2d array
        for (int i = 0; i < this->y_max; i++){
            this->grid[i] = (int*)calloc(this->x_max, sizeof(int));
        }

        this->y_cord = 0;
        this->x_cord = 0;
    }
    
    ~cell_map_t(){
        delete this->grid;
        this->grid = nullptr;
    }

} cell_map;


// Parses the input file and executes the instructions found
void parsing_n_execution(std::string line, int line_number, bool step_by_step){
    for (int i = 0; i < line.size(); i++){
        if (step_by_step){
            step_by_step_view(line[i]);
        }

        switch (line[i]){            
            
            // Math operators
            case '+': // Increase the value in the cell
                cell_map.grid[cell_map.x_cord][cell_map.y_cord]++;
                break;

            case '-': // Decrease the value in the cell
                cell_map.grid[cell_map.x_cord][cell_map.y_cord]--;
                break;
            
            case '*': // Multiplies the value with two
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] *= 2;
                break;

            case '/': // Divides the value with two
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] /= 2;
                break;

            case '^': // Utilized the magic of power by 2 on the current cell
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] = pow(cell_map.grid[cell_map.x_cord][cell_map.y_cord], 2);
                break;

            case '%': // Peforms mod 2 on the current cell
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] %= 2;
                break;

            // Navigation
            case 'n': // north
                if (cell_map.y_cord+1 > cell_map.y_max){
                    runtime_error("Moving one cell north results in out-of-bound error!\nIndex: ", line_number, i);
                }

                cell_map.y_cord++;

                break;

            case 's': // south
                if (cell_map.y_cord-1 < 0){
                    runtime_error("Moving one cell south results in out-of-bound error!", line_number, i);
                }

                cell_map.y_cord--;
                
                break;

            case 'e': // east
                if (cell_map.x_cord+1 > cell_map.x_max){
                    runtime_error("Moving one cell east results in out-of-bound error!\nIndex: ", line_number, i);
                }

                cell_map.x_cord++;

                break;
            

            case 'w': // west
                if (cell_map.x_cord-1 < 0){
                    runtime_error("Moving one cell east results in out-of-bound error!", line_number, i);
                }

                cell_map.x_cord--;
                
                break;

            // Loops
            case '[':{ // Start of the while loop

                int location = line.find("]"); // Find the terminating character for the while loop
                if (location == std::string::npos){
                    runtime_error("Failed to find ']' in a while-clause", line_number, i);
                }

                if (cell_map.grid[cell_map.x_cord][cell_map.y_cord] == 0){ // Don't go into the while statement if the value already is zero
                    i = location; // We must do this to jump over the while statement
                }              

                break;
            }
            
            case ']':{ // End of the while loop
                int location = i;
                
                while(location >= 0 && line[location] != '[') {location--; }

                if (line[location] != '['){
                    runtime_error("Failed to find '[' in a while-clause", line_number, i);
                }

                if (cell_map.grid[cell_map.x_cord][cell_map.y_cord] != 0){ // We are not done yet
                    i = location; // Jump back to the value after [
                }

                break;
            } 
            
            case '{': // Start of a do-while loop, and it's not supposed to do anything
                if (line.find("}") == std::string::npos){
                    runtime_error("Failed to find '}' in a do-while-clause", line_number, i);
                }

                break;

            case '}':{
                    int location = i;
                    
                    while(location >= 0 && line[location] != '{') {location--; }

                    if (line[location] != '{'){
                        runtime_error("Failed to find '{' in a do-while-clause", line_number, i);
                    }

                    if (cell_map.grid[cell_map.x_cord][cell_map.y_cord] != 0){ // We are not done yet
                        i = location; // Jump back to the value after {
                    }

                    break;
                }

            // I/O
            case '.': // Print the contents of the current cell
                print(cell_map.grid[cell_map.x_cord][cell_map.y_cord]);
                break;

            case ':': // Prints the cells value but with a newline in at the end
                print(cell_map.grid[cell_map.x_cord][cell_map.y_cord]);
                std::cout << std::endl;
                break;

            case ',': // Grab an input from the user
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] = getchar();
                clean_input_buffer();
                break;

            case ';': // Grab user input and prints it
                cell_map.grid[cell_map.x_cord][cell_map.y_cord] = getchar();
                print(cell_map.grid[cell_map.x_cord][cell_map.y_cord]);
                clean_input_buffer();
                break;

            // Control flow
            case '(':{

                int location = line.find(")"); // Find the terminating character for the while loop
                if (location == std::string::npos){
                    runtime_error("Failed to find ')' in a if-clause", line_number, i);
                }

                if (cell_map.grid[cell_map.x_cord][cell_map.y_cord] == 0){ // Don't go into the if statement if the value already is zero
                    i = location; // We must do this to jump over the if statement
                }              

                break;
            }
            

            case ')':
                if (line.find("(") == std::string::npos){
                    runtime_error("Failed to find '(' in a if-clause", line_number, i);
                }

                break;

            default: // Ignore everything else
                continue;
                break;

        }
        
    }
}

// Essentially a wrapper
void interpreter(std::vector<std::string>* contents, bool detailed_view, bool step_by_step, int limit){
    
    for (int i = 0; i < contents->size(); i++){
        parsing_n_execution(contents->at(i), i, step_by_step);
    }
    std::cout << std::endl; // See this as some kind of clean-up


    if (detailed_view){
        advance_view(limit);
    }
}

// Prints all 30k cells unless @limit is set to a lower number.
void advance_view(int limit){
    for (cell_map.y_cord = 0; cell_map.y_cord < limit; cell_map.y_cord++){
        for (cell_map.x_cord = 0; cell_map.x_cord < limit; cell_map.x_cord++){
            if (cell_map.x_cord%5 == 0 && cell_map.x_cord != 0){
                std::cout << std::endl << "# Press enter to continue ";
                std::cin.get(); // Makes the user press enter to continue
            }

            std::cout << "(" <<cell_map.x_cord << ", "<< cell_map.y_cord << ")" << ": [";
            
            print(cell_map.grid[cell_map.x_cord][cell_map.y_cord]);

            std::cout << "] ";
        }

    }

    std::cout << std::endl;
}


// Prints the action peformed and the value of the current cell
void step_by_step_view(char instruction){
    std::cout << "(" <<cell_map.x_cord << ", "<< cell_map.y_cord << ")" << ": ['";
    
    print(cell_map.grid[cell_map.x_cord][cell_map.y_cord]);

    std::cout << "'] {'"<<instruction<<"'}";

    std::cout << std::endl << "# Press enter to continue ";
    std::cin.get(); // Makes the user press enter to continue
}