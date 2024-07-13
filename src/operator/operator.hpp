#include <vector>
#include <string>

class Operator {
   public:
    Operator *prev;
    virtual std::vector<std::string> emit() = 0;
};

class OpScan : Operator {
   public:
    std::string table_name;
    std::string table_path;
    uint64_t table_row_count;
    uint64_t current_row;

    OpScan(std::string table_name);
    std::vector<std::string> emit();
};

class OpCreateTable : Operator {
   public:
    std::string table_name;
    std::vector<std::string> columns;
    
    OpCreateTable(std::string table_name, std::vector<std::string> columns);
    std::vector<std::string> emit();
};

