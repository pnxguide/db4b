#include <iostream>
#include <string>

// TODO:
// - Database Catalog
// - Query Engine
// - Storage Manager -> File Format?

// Coverage:
// - CREATE TABLE
// - DROP TABLE
// - SELECT / INSERT / DELETE / UPDATE
//   - Projection - single column
//   - Filter - single predicate filter
//   - Delete - single predicate delete
//   - Update - single predicate update
// - No Join
// - No Subquery
// - CREATE EXTENSION
// - DROP EXTENSION

int main() {
    std::cout << "Little John Database (LJDB) is running!" << std::endl;

    while (true) {
        std::string cmd;
        std::cout << "🦅 ";
        std::getline(std::cin, cmd);
        std::cout << "Little John is helping you " << cmd << std::endl;
    }

    return 0;
}
