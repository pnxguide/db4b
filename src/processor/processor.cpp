#include "processor.hpp"

#include "planner/query_plan.hpp"

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