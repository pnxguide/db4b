#include "query_plan.hpp"

QueryPlan::QueryPlan(std::string query) {
    this->root = (Operator *)(new OpScan("sample"));
}
