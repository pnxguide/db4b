#include "query_plan.hpp"

QueryPlan::QueryPlan(std::string query) {
    // Remove the trailing space
    while (query.back() == ' ') {
        query.pop_back();
    }
    // If the query ends with ;, remove it
    if (query.back() == ';') {
        query.pop_back();
    }
    // Split
    std::string line = query;
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = line.find(" ")) != std::string::npos) {
        std::string token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + 1);
    }
    tokens.push_back(line);

    // DROP TABLE [table_name]
    if (tokens[0] == "DROP" && tokens[1] == "TABLE" && tokens.size() == 3) {
        std::string table_name = tokens[2];
        this->root = (Operator *)(new OpDropTable(table_name));
    }
    // CREATE TABLE [table_name] (...)
    else if (tokens[0] == "CREATE" && tokens[1] == "TABLE" &&
             tokens.size() > 3) {
        /**
         * CREATE TABLE employees ( id string, name string, type string );
         */

        std::string table_name = tokens[2];
        std::vector<std::string> columns = {};

        int stage = 0;
        for (int i = 3; i < tokens.size(); i++) {
            if (tokens[i] == "(" || tokens[i] == ")") continue;
            // Stage 0 - Name
            if (stage == 0) {
                // Remove leading ( if any
                std::string name = "";
                if (tokens[i][0] == '(') {
                    for (int j = 1; j < tokens[i].size(); j++) {
                        name.push_back(tokens[i][j]);
                    }
                } else {
                    name = tokens[i];
                }
                columns.push_back(name);
                stage = 1;
            }
            // Stage 1 - Type
            else if (stage == 1) {
                if (!(tokens[i] == "string" || tokens[i] == "string," ||
                      tokens[i] == "string)")) {
                    this->root = (Operator *)(new OpError());
                }
                stage = 0;
            }
        }

        this->root = (Operator *)(new OpCreateTable(table_name, columns));
    }
    else {
        this->root = (Operator *)(new OpError());
    }
    // INSERT INTO [table_name] VALUES (...)

    // DELETE FROM [table_name] WHERE [pred]...

    // SELECT [column_name]... FROM [table_name] WHERE [pred]...

    // Plan
    // this->root = (Operator *)(new OpProject("a", {"x"}));
    // this->root->prev = (Operator *)(new OpScan("a"));
}
