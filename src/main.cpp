#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "catalog/catalog.hpp"
#include "processor/processor.hpp"
#include "util/io_rewriter.hpp"

void print_intro() {
    std::string line;
    std::ifstream startup_file("./data/.startup");
    if (startup_file.is_open()) {
        // Loop each line
        while (std::getline(startup_file, line)) {
            std::cout << line << std::endl;
        }
        startup_file.close();
    }
}

int main() {
    // Initialize the catalog
    Catalog &catalog = Catalog::get_instance();
    catalog.recover_catalog();
    // catalog.print_all();

    print_intro();

    // Start the command loop
    while (true) {
        // Print the cursor
        std::cout << "😎 ";
        // Get the input
        std::string input;
        std::getline(std::cin, input);
        // If exit
        if (rewrite_input(input) == "exit") {
            std::cout << rewrite_output("Exiting this program...").c_str()
                      << std::endl;
            break;
        }
        // Convert the input into English
        std::string eng_input = rewrite_input(input);
        // Process the query and get the output
        std::string output = process_query(eng_input);
        if (output == "ERROR\n(1 row)") {
            // Display error
            std::cout
                << rewrite_output(
                       "An error has occurred! Perhaps, the syntax is error!")
                       .c_str()
                << std::endl;
            continue;
        }
        // Display the output in Braille
        std::cout << rewrite_output(output).c_str() << std::endl;
    }
    return 0;
}
