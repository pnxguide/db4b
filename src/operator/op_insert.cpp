#include <fstream>
#include <iostream>

#include "../catalog/catalog.hpp"
#include "operator.hpp"

OpInsert::OpInsert(std::string table_name, std::vector<std::string> tuple)
    : table_name(table_name), tuple(tuple), is_done(false){};

std::vector<std::string> OpInsert::emit() {
    std::vector<std::string> tuple = {};

    if (!this->is_done) {
        tuple = {""};
        Catalog &catalog = Catalog::get_instance();
        if (catalog.insert_tuple(this->table_name, this->tuple)) {
            tuple[0] = "The tuple has been inserted successfully!";
        } else {
            tuple[0] = "The tuple has not been successfully created!";
        }
        this->is_done = true;
    }

    return tuple;
}
