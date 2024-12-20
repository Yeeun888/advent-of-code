#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <stdint.h>

int main(int argc, char** argv) {
    // Pre do and don't processing. Creates new file temporary
    std::ifstream raw_stream("day-3-input.txt");
    std::string temp_string;
    std::string storage_string("");

    while(!raw_stream.eof()) {
        raw_stream >> temp_string;

        // if (raw_stream.eof()) break; //EOF prevents double parsing final 
        
        storage_string.append(temp_string);
    }
    storage_string.append("do()"); // Incase don't in the end without a do

    std::ofstream concat_stream("concat_output");
    concat_stream << storage_string;
    
    std::ofstream debug_stream("debug_stream");

    int start = 0;
    int end = 0;
    while(true) {
        start = storage_string.find("don't()");
        end = storage_string.find("do()", start + 1);

        printf("Got pair %d %d\n", start, end);

        //Exit condition
        if(start == -1) break;

        //Start position and end position found
        debug_stream << "Got pair " << start << ' ' << end << '\n';
        debug_stream << storage_string.substr(start, end - start + 3) << '\n';
        debug_stream << '\n';
        storage_string.erase(start, end - start + 3);
    }

    std::ofstream output_stream("filtered_output");
    output_stream << storage_string;

    //Integer to store numbers
    long long final_result = 0; 

    //Regex pattern
    std::regex search_pattern("mul\\(\\d+,\\d+\\)");

    // Iterates each line or whitespace in the file. Whitespace is invalid so
    // code does not have to check for that really.

    //regex replace all instances
    auto words_begin = std::sregex_iterator(storage_string.begin(), storage_string.end(), search_pattern);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();

            std::size_t comma = match_str.find_first_of(","); // Is zero indexed
            int a = stoi(match_str.substr(4, comma - 1));
            int b = stoi(match_str.substr(comma + 1, match_str.size() - 2));

            int mul = a*b;
            std::cout << match_str << ' ' << a << ' ' << b << ' ' << mul << '\n';
            final_result += mul;
        }

    storage_string.clear();

    printf("Final result: %lld\n", final_result);

    remove("concat_output");
    remove("debug_stream");
    remove("filtered_output");
    remove("output_stream");

    return 0;
}