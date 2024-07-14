#include <fstream>
#include <iostream>

#include "../catalog/catalog.hpp"
#include "operator.hpp"

OpProject::OpProject(std::string table_name,
                     std::vector<std::string> projected_columns)
    : table_name(table_name), projected_columns(projected_columns) {
    // Compute the projected column indices
    this->projected_column_indices = {};
    // Need the catalog
    Catalog &catalog = Catalog::get_instance();
    std::vector<std::string> all_columns =
        catalog.get_columns_in_order(this->table_name);
    for (std::string column : projected_columns) {
        for (int i = 0; i < all_columns.size(); i++) {
            if (column == all_columns[i]) {
                this->projected_column_indices.push_back(i);
            }
        }
    }
}

std::vector<std::string> OpProject::emit() {
    std::vector<std::string> tuple = {};
    std::vector<std::string> prev_tuple = prev->emit();
    if (prev_tuple.size() != 0) {
        for (int i : this->projected_column_indices) {
            tuple.push_back(prev_tuple[i]);
        }
    }
    return tuple;
}
