#include <fstream>
#include <iostream>

#include "../catalog/catalog.hpp"
#include "operator.hpp"

OpScan::OpScan(std::string table_name) : table_name(table_name) {
    Catalog &catalog = Catalog::get_instance();

    this->table_path = catalog.get_table_path(this->table_name);
    this->table_row_count = catalog.get_table_row_count(this->table_name);
    this->current_row = 0;
    this->file_stream.open(this->table_path);
    // Skip the header row
    std::string line;
    std::getline(this->file_stream, line);
}

std::vector<std::string> OpScan::emit() {
    std::vector<std::string> tuple = {};

    while (this->current_row < this->table_row_count) {
        // Get the next line
        std::string line;
        std::getline(this->file_stream, line);
        // Split
        size_t pos = 0;
        while ((pos = line.find("|")) != std::string::npos) {
            std::string token = line.substr(0, pos);
            tuple.push_back(token);
            line.erase(0, pos + 1);
        }
        tuple.push_back(line);
        this->current_row++;

        // If not active
        if (tuple[0] == "0") {
            tuple = {};
            continue;
        } else {
            std::vector<std::string> tmp = {};
            for (int i = 1; i < tuple.size(); i++) {
                tmp.push_back(tuple[i]);
            }
            tuple = tmp;
            break;
        }
    }
    
    return tuple;
}
