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
    if (this->current_row < this->table_row_count) {
        std::string line;
        std::getline(this->file_stream, line);
        tuple = {line};
        this->current_row++;
    }
    return tuple;
}
