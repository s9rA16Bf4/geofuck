#include "interpreter.hpp"
#include "notify.hpp"

struct cell_map_t{
    int* grid;
    int index;
    int max;
    int index_of_while;

    cell_map_t(){
        this->max = 30000; // Default value
        this->default_init();
    }

    cell_map_t(int size){
        this->max = size;
        this->default_init();
    }

    void default_init(){
        this->grid = (int*)calloc(this->max, sizeof(int)); // Allocate our array
        this->index = 0;
        this->index_of_while = -1;
    }
    
    ~cell_map_t(){
        delete this->grid;
        this->grid = nullptr;
    }

} cell_map;


// Prints the provided @value either as a char or as an integer
void print(int value){
    if (value >= 32 && value <= 57 || value >= 58 && value <= 126){ // Autoconvert if it's readable chars!
        std::cout << (char)value;
    }else{
        std::cout << value;
    }
}


// Parses the input file and executes the instructions found
void parsing_n_execution(std::string line, int line_number, bool step_by_step){
    for (int i = 0; i < line.size(); i++){
        
        if (step_by_step){
            step_by_step_view(line[i]);
        }

        switch (line[i]){            
            
            case '+': // Increase the value in the cell
                cell_map.grid[cell_map.index]++;
                break;
        

            case '-': // Decrease the value in the cell
                cell_map.grid[cell_map.index]--;
                break;
            

            case '>': // Move one cell to the right
                if (cell_map.index+1 > cell_map.max){
                    runtime_error("Moving one cell to the right results in out-of-bound error!\nIndex: ", line_number, i);
                }

                cell_map.index++;

                break;
            

            case '<': // Move one cell to the left
                if (cell_map.index-1 < 0){
                    runtime_error("Moving one cell to the left results in out-of-bound error!", line_number, i);
                }

                cell_map.index--;
                
                break;

            case '[':{ // Start of the while loop

                int location = line.find("]"); // Find the terminating character for the while loop
                if (location == std::string::npos){
                    runtime_error("Failed to find ']' in a while-clause", line_number, i);
                }

                if (cell_map.grid[cell_map.index] == 0){ // Don't go into the while statement if the value already is zero
                    i = location; // We must do this to jump over the while statement
                }              

                break;
            }
            
            case ']':{ // End of the while loop
                int location = i;
                
                while(location > 0 && line[location] != '[') { location--; }

                if (location == 0){
                    runtime_error("Failed to find '[' in a while-clause", line_number, i);
                }

                if (cell_map.grid[cell_map.index] != 0){ // We are not done yet
                    i = location; // Jump back to the value after [
                }

                break;
            } 
                

            case '.': // Print the contents of the current cell
                print(cell_map.grid[cell_map.index]);
                break;


            case ',': // Grab an input from the user
                cell_map.grid[cell_map.index] = getchar();
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
    for (cell_map.index = 0; cell_map.index < limit; cell_map.index++){
        if (cell_map.index%5 == 0 && cell_map.index != 0){
            std::cout << std::endl << "# Press enter to continue" << std::endl;
            std::cin.get(); // Makes the user press enter to continue
        }

        std::cout << cell_map.index << ": [";
        
        print(cell_map.grid[cell_map.index]);

        std::cout << "] ";
    }

    std::cout << std::endl;
}


// Prints the action peformed and the value of the current cell
void step_by_step_view(char instruction){
    std::cout << std::endl << cell_map.index << ": ['";
    
    print(cell_map.grid[cell_map.index]);

    std::cout << "'] {'"<<instruction<<"'}";

    std::cout << std::endl << "# Press enter to continue ";
    std::cin.get(); // Makes the user press enter to continue
}