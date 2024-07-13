#include <fstream>
#include <string>
#include <vector>

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
    std::ifstream file_stream;

    OpScan(std::string table_name);
    std::vector<std::string> emit();
};

class OpProject : Operator {
   public:
    std::string table_name;
    std::vector<std::string> projected_columns;

    OpProject(std::string table_name,
              std::vector<std::string> projected_columns);
    std::vector<std::string> emit();

   private:
    std::vector<int> projected_column_indices;
};

class OpCreateTable : Operator {
   public:
    std::string table_name;
    std::vector<std::string> columns;
    bool is_done;

    OpCreateTable(std::string table_name, std::vector<std::string> columns);
    std::vector<std::string> emit();
};

class OpDropTable : Operator {
   public:
    std::string table_name;
    bool is_done;

    OpDropTable(std::string table_name);
    std::vector<std::string> emit();
};

class OpInsert : Operator {
   public:
    std::string table_name;
    std::vector<std::string> tuple;
    bool is_done;

    OpInsert(std::string table_name, std::vector<std::string> tuple);
    std::vector<std::string> emit();
};

class OpError : Operator {
   public:
    OpError() {};
    std::vector<std::string> emit() { return {"ERROR"}; };
};
