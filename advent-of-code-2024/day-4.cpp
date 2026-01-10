#include <iostream>
#include <string>
#include <fstream>

struct node {
    char c;
};

/**
 * @brief Creates a node with a letter initialization
 * 
 * @param letter 
 * @return struct node* 
 */
struct node* node_initialize(char letter) {
    struct node* temp = (struct node*)malloc(sizeof(struct node)); 
    temp->c = letter;
    return temp;
}

/**
 * @brief Initialize array for nodes structure
 * 
 * @param filename 
 * @return struct node** 
 */
struct node** initialize_array(std::string filename, int* extern_line_count, int* extern_column_count) {
    std::ifstream file(filename);
    std::string buffer;

    //Count lines to determine buffer size.
    int line_count = 0;
    while(!file.eof()) {
        file >> buffer;
        ++line_count;
    }

    file.seekg(0);  // Go back to start
    buffer.clear(); // Clear buffer

    struct node** return_array = (struct node**)malloc(sizeof(struct node*) * line_count);

    for(int i = 0; i < line_count; ++i) { // Go through each line
        file >> buffer;

        return_array[i] = (struct node*)malloc(sizeof(struct node*) * buffer.size());
        for(int j = 0; j < buffer.size(); ++j) { // Go through each character of each line
            return_array[i][j] = *node_initialize(buffer[j]);
        }
    }

    *extern_line_count = line_count;
    *extern_column_count = buffer.size();

    return return_array;
}

int main(int argc, char** argv) {
    std::string filename("day-4-input.txt");

    int line_count;
    int column_count;
    struct node** array = initialize_array(filename, &line_count, &column_count);

    std::cout << line_count << ' ' << column_count << '\n';

    std::cout << "node test: " << array[44][9].c << '\n';

    return 0;
}