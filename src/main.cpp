#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "catalog/catalog.hpp"
#include "planner/query_plan.hpp"
#include "util/braille.hpp"

std::string process_query(std::string q) {
    // Create a plan
    QueryPlan *plan = new QueryPlan(q);
    // Execute the plan
    uint64_t result_count = 0;
    std::string final_output = "";
    std::vector<std::string> outputs = plan->root->emit();
    while (outputs.size() != 0) {
        // Format the output
        std::string formatted_output = "";
        for (int i = 0; i < outputs.size() - 1; i++) {
            formatted_output += outputs[i] + " | ";
        }
        formatted_output += outputs.back();
        // Append to the final output
        final_output += formatted_output + "\n";
        result_count++;
        // Emit more
        outputs = plan->root->emit();
    }
    // Add the result counter
    if (result_count == 1) {
        final_output += "(" + std::to_string(result_count) + " row)";
    } else {
        final_output += "(" + std::to_string(result_count) + " rows)";
    }
    // Free allocated memory for the plan
    delete plan;
    // Return the final output
    return final_output;
}

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
        // FIXME: Change to Braille "exit"
        if (braille_to_eng(input) == "exit") {
            std::cout << eng_to_braille("Exiting this program...").c_str()
                      << std::endl;
            break;
        }
        // Convert the input into English
        std::string eng_input = braille_to_eng(input);
        // Process the query and get the output
        std::string output = process_query(eng_input);
        if (output == "ERROR\n(1 row)") {
            // Display error
            std::cout
                << eng_to_braille(
                       "An error has occurred! Perhaps, the syntax is error!")
                       .c_str()
                << std::endl;
            continue;
        }
        // Display the output in Braille
        std::cout << eng_to_braille(output).c_str() << std::endl;
    }
    return 0;
}
