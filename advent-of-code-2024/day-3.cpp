#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <stdint.h>

int main(int argc, char** argv) {
    // Using streams to open files
    std::ifstream file_stream("day-3-input.txt");
    std::string storage_string;

    //Integer to store numbers
    long long final_result = 0; 

    //Regex pattern
    std::regex search_pattern("mul\\(\\d+,\\d+\\)");

    // Iterates each line or whitespace in the file. Whitespace is invalid so
    // code does not have to check for that really.
    while(file_stream) {
        file_stream >> storage_string;

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
    }

    printf("Final result: %lld\n", final_result);

    return 0;
}