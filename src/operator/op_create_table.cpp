#include <fstream>
#include <iostream>

#include "../catalog/catalog.hpp"
#include "operator.hpp"

OpCreateTable::OpCreateTable(std::string table_name,
                             std::vector<std::string> columns)
    : table_name(table_name), columns(columns), is_done(false){};

std::vector<std::string> OpCreateTable::emit() {
    std::vector<std::string> tuple = {};

    if (!this->is_done) {
        tuple = {""};
        Catalog &catalog = Catalog::get_instance();
        if (catalog.create_table(this->table_name, this->columns)) {
            tuple[0] = "The table " + this->table_name +
                       " has been created successfully!";
        } else {
            tuple[0] = "The table " + this->table_name +
                       " has not been successfully created!";
        }
        this->is_done = true;
    }

    return tuple;
}
