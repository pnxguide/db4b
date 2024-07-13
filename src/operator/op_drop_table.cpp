#include <fstream>
#include <iostream>

#include "../catalog/catalog.hpp"
#include "operator.hpp"

OpDropTable::OpDropTable(std::string table_name) : table_name(table_name){};

std::vector<std::string> OpDropTable::emit() {
    std::vector<std::string> tuple = {""};

    Catalog &catalog = Catalog::get_instance();
    if (catalog.drop_table(this->table_name)) {
        tuple[0] =
            "The table " + this->table_name + " has dropped successfully!";
    } else {
        tuple[0] =
            "The table " + this->table_name + " has not successfully dropped!";
    }

    return tuple;
}
