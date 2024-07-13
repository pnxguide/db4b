#include "catalog.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <ranges>
#include <string_view>

bool Catalog::recover_catalog() {
    // Reset the catalog
    this->tables = {};
    // Read the file
    std::string line;
    std::ifstream catalog_file("./db/.catalog");
    if (catalog_file.is_open()) {
        // Loop each line
        // Each line means a single entry in the catalog
        while (std::getline(catalog_file, line)) {
            // Split
            std::vector<std::string> tokens;
            size_t pos = 0;
            while ((pos = line.find("|")) != std::string::npos) {
                std::string token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            // New table
            TableInfo new_table;
            new_table.table_name = tokens[0];
            new_table.access_path = tokens[1];
            new_table.row_count = std::stoull(tokens[2]);
            new_table.column_count = std::stoull(tokens[3]);
            for (int i = 0; i < new_table.column_count; i++) {
                new_table.column_names.push_back(tokens[4+i]);
            }
            this->tables.push_back(new_table);
        }
        catalog_file.close();
    }
    return true;
}

bool Catalog::persist() {
    // Create the catalog file
    std::ofstream catalog_file;
    // Open the file
    catalog_file.open("./db/.catalog");
    for (TableInfo table : this->tables) {
        catalog_file << table.table_name << "|";
        catalog_file << table.access_path << "|";
        catalog_file << table.row_count << "|";
        catalog_file << table.column_count << "|";
        for (std::string column : table.column_names) {
            catalog_file << column << "|";
        }
        catalog_file << "\n";
    }
    // Close the file
    catalog_file.close();
    // Return
    return true;
}

bool Catalog::create_table(std::string table_name,
                           std::vector<std::string> columns) {
    // Table name must not be illegal (alphabet only)
    for (char c : table_name) {
        if (std::isalpha(c) || c == '_') {
            
        } else {
            return false;
        }
    }
    // Check if this table name has not been registered
    for (TableInfo table : this->tables) {
        if (table.table_name == table_name) {
            return false;
        }
    }
    // If columns is empty, don't create the table
    if (columns.size() == 0) {
        return false;
    }
    // Register
    TableInfo new_table(table_name, columns);
    this->tables.push_back(new_table);
    // Create the db file
    std::ofstream new_db_file;
    // Open the file
    new_db_file.open(new_table.access_path);
    // Write the header
    for (int i = 0; i < new_table.column_count - 1; i++) {
        new_db_file << new_table.column_names[i] << "|";
    }
    new_db_file << new_table.column_names[new_table.column_count - 1] << "\n";
    // Close the file
    new_db_file.close();
    // Persist catalog
    this->persist();
    // Return
    return true;
}

bool Catalog::drop_table(std::string table_name) {
    // Check if this table name has been registered
    for (int i = 0; i < this->tables.size(); i++) {
        if (this->tables[i].table_name == table_name) {
            // TODO: Physical remove
            // Remove the table from the catalog
            this->tables.erase(this->tables.begin() + i);
            // Persist catalog
            this->persist();
            // Early return
            return true;
        }
    }
    // Return
    return false;
}

std::string Catalog::get_table_path(std::string table_name) {
    for (TableInfo table : this->tables) {
        if (table.table_name == table_name) {
            return table.access_path;
        }
    }
    return "";
}

uint64_t Catalog::get_table_row_count(std::string table_name) {
    for (TableInfo table : this->tables) {
        if (table.table_name == table_name) {
            return table.row_count;
        }
    }
    return 0U;
}

void Catalog::print_all() {
    for (TableInfo table : this->tables) {
        std::cout << table.table_name << "|";
        std::cout << table.access_path << "|";
        std::cout << table.row_count << "|";
        std::cout << table.column_count << "|";
        for (std::string column : table.column_names) {
            std::cout << column << "|";
        }
        std::cout << "\n";
    }
}