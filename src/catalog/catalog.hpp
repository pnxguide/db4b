#include <string>
#include <vector>

class TableInfo {
    std::string table_name;
    std::string access_path;
    uint64_t row_count;
    uint64_t column_count;
    std::vector<std::string> column_names;
};

// Catalog as a singleton
class Catalog {
   public:
    // Add upon registration
    std::vector<TableInfo *> tables;
    static Catalog &get_instance() {
        static Catalog INSTANCE;
        return INSTANCE;
    }

    bool create_table(std::string table_name);
    bool drop_table(std::string table_name);
    bool import_table(std::string table_name, std::string table_path);
    
    std::string get_table_path(std::string table_name);
    uint64_t get_table_row_count(std::string table_name);

   private:
    Catalog();
};
