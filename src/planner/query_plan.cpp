#include "query_plan.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#include "../catalog/catalog.hpp"

QueryPlan::QueryPlan(std::string query) {
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

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
    if (tokens.size() == 3 && tokens[0] == "drop" && tokens[1] == "table") {
        std::string table_name = tokens[2];
        this->root = (Operator *)(new OpDropTable(table_name));
    }
    // CREATE TABLE [table_name] (...)
    else if (tokens.size() > 3 && tokens[0] == "create" &&
             tokens[1] == "table") {
        /**
         * CREATE TABLE employees ( id string, name string, type string );
         */
        std::string table_name = tokens[2];
        std::vector<std::string> columns = {};
        // Mini State Machine
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
        // Add the root op
        this->root = (Operator *)(new OpCreateTable(table_name, columns));
    }
    // INSERT INTO [table_name] VALUES (...)
    else if (tokens.size() > 5 && tokens[0] == "insert" &&
             tokens[1] == "into" && tokens[3] == "values") {
        /**
         * INSERT INTO employees VALUES ('1', 'Alice', 'CEO');
         */
        std::string table_name = tokens[2];
        std::vector<std::string> tuple = {};
        std::string merged = "";
        for (int i = 4; i < tokens.size(); i++) {
            merged += tokens[i];
        }
        // find ' and '
        bool is_open = false;
        std::string value = "";
        for (int i = 0; i < merged.size(); i++) {
            if (!is_open && merged[i] == '\'') {
                is_open = true;
            } else if (is_open) {
                if (merged[i] == '\'') {
                    is_open = false;
                    tuple.push_back(value);
                    value = "";
                } else {
                    value += merged[i];
                }
            }
        }
        // Add the root op
        this->root = (Operator *)(new OpInsert(table_name, tuple));
    }
    // SELECT [column_name]... FROM [table_name]
    else if (tokens.size() > 3 && tokens[0] == "select") {
        std::vector<std::string> projections = {};
        int cur = 1;
        for (cur = 1; cur < tokens.size(); cur++) {
            if (tokens[cur] == "from") {
                break;
            }
            if (tokens[cur].back() == ',') {
                tokens[cur].pop_back();
            }
            projections.push_back(tokens[cur]);
        }
        cur++;
        std::string table_name = tokens[cur];
        if (cur + 1 != tokens.size()) {
            this->root = (Operator *)(new OpError());
        } else {
            // Rewrite *
            Catalog &catalog = Catalog::get_instance();
            std::vector<std::string> all_columns = catalog.get_columns_in_order(table_name);

            std::vector<std::string> post_projections = {};
            for (std::string s : projections) {
                if (s == "*") {
                    for (std::string col : all_columns) {
                        post_projections.push_back(col);
                    }
                } else {
                    post_projections.push_back(s);
                }
            }
            this->root = (Operator *)(new OpProject(table_name, post_projections));
            this->root->prev = (Operator *)(new OpScan(table_name));
        }
    }
    // Else
    else {
        this->root = (Operator *)(new OpError());
    }
}
