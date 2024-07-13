#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "operator/operator.hpp"
#include "util/braille.hpp"

class QueryPlan {
   public:
    std::vector<void *> args;
    Operator *root;

    QueryPlan(std::string q) {
        // TODO: Implement this
    }
};

std::string process_query(std::string q) {
    // Create a plan
    QueryPlan *plan = new QueryPlan(q);
    // Volcano model
    std::vector<std::string> outputs = plan->root->emit();
    // Format the vector of strings into a single string
    // FIXME: Change from "" to the other
    std::string final_output = "";
    return final_output;
}

int main() {
    while (true) {
        // Print the cursor
        std::cout << "😎 ";
        // Get the input
        std::string input;
        std::getline(std::cin, input);
        // Process the query and get the output
        std::string output = process_query(input);
        // Display the output in Braille
        std::cout << eng_to_braille(output).c_str() << std::endl;
    }
    return 0;
}
