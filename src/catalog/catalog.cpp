#include "catalog.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <set>
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
                new_table.column_names.push_back(tokens[4 + i]);
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
    // No duplicated column names
    std::set<std::string> unique_set;
    for (std::string s : columns) {
        unique_set.insert(s);
    }
    if (unique_set.size() < columns.size()) {
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
    new_db_file << new_table.column_names.back() << "\n";
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

bool Catalog::insert_tuple(std::string table_name,
                           std::vector<std::string> tuple) {
    for (TableInfo &table : this->tables) {
        // Found the table
        if (table.table_name == table_name) {
            // Check if the column sizes are the same
            if (table.column_count != tuple.size()) {
                return false;
            }
            // Create the db file
            std::ofstream db_file;
            // Open the file
            db_file.open(table.access_path, std::ios::app);
            // Write the "active" flag
            db_file << 1 << "|";
            // Write the tuple
            for (int i = 0; i < tuple.size() - 1; i++) {
                db_file << tuple[i] << "|";
            }
            db_file << tuple.back() << "\n";
            // Close the file
            db_file.close();
            // Increment
            table.row_count++;
            // Persist
            this->persist();
            // Return
            return true;
        }
    }
    return false;
}

bool Catalog::delete_tuple(std::string table_name, uint64_t tuple_sequence) {
    for (TableInfo &table : this->tables) {
        // Found the table
        if (table.table_name == table_name) {
            // Create the db file
            std::fstream db_file(table.access_path,
                                 std::fstream::in | std::fstream::out);
            // Open the file
            uint64_t current_sequence = 0;
            if (db_file.is_open()) {
                while (!db_file.eof()) {
                    if (db_file.get() == '\n') {
                        current_sequence++;
                        if (current_sequence == (tuple_sequence + 1)) {
                            db_file.put('0');
                            break;
                        }
                    }
                }
                // Close the file
                db_file.close();
            } else {
                return false;
            }
            // Return
            return true;
        }
    }
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

std::vector<std::string> Catalog::get_columns_in_order(std::string table_name) {
    for (TableInfo table : this->tables) {
        if (table.table_name == table_name) {
            return table.column_names;
        }
    }
    return {};
}

void Catalog::print_all() {
    std::cout << "Catalog" << std::endl;
    for (TableInfo table : this->tables) {
        std::cout << table.table_name << "|";
        std::cout << table.access_path << "|";
        std::cout << table.row_count << "|";
        std::cout << table.column_count << "|";
        for (std::string column : table.column_names) {
            std::cout << column << "|";
        }
        std::cout << std::endl;
    }
}
