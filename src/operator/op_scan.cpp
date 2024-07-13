#include <fstream>
#include <iostream>

#include "operator.hpp"

std::vector<std::string> get_column_names(std::string table_path) {
    std::vector<std::string> column_names;

    // TODO: Get the first row and split into strings delimited by ,

    return column_names;
}

uint64_t get_table_size(std::string table_path) {
    uint64_t row_count = 0;

    std::string line;
    std::ifstream table_file(table_path);
    if (table_file.is_open()) {
        while (getline(table_file, line)) {
            row_count++;
        }
        table_file.close();
    } 

    return row_count;
}

OpScan::OpScan(std::string table_name) {
    this->table_path = "./db/" + table_name + ".4b";
    this->table_row_count = get_table_size(this->table_path);
    this->current_row = 1;
}

std::vector<std::string> OpScan::emit() {
    std::vector<std::string> tuple = {};
    if (this->current_row < this->table_row_count) {
        tuple = {"hello", "annaa", "bobby", "emmyi"};
        this->current_row++;
    }
    return tuple;
}
