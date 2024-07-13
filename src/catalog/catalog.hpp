#include <string>
#include <vector>

class TableInfo {
   public:
    std::string table_name;
    std::string access_path;
    uint64_t row_count;
    uint64_t column_count;
    std::vector<std::string> column_names;

    TableInfo() {}

    TableInfo(std::string table_name, std::vector<std::string> columns)
        : table_name(table_name),
          access_path("./db/" + table_name + ".4b"),
          row_count(0),
          column_count(columns.size()),
          column_names(columns) {}
};

// Catalog as a singleton
class Catalog {
   public:
    // Add upon registration
    std::vector<TableInfo> tables;
    static Catalog &get_instance() {
        static Catalog INSTANCE;
        return INSTANCE;
    }

    bool create_table(std::string table_name, std::vector<std::string> columns);
    bool drop_table(std::string table_name);
    bool import_table(std::string table_name, std::string table_path);

    std::string get_table_path(std::string table_name);
    uint64_t get_table_row_count(std::string table_name);

    bool recover_catalog();

    void print_all();

   private:
    Catalog() {}
    bool persist();
};
