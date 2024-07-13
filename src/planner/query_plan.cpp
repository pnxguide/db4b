#include "query_plan.hpp"

QueryPlan::QueryPlan(std::string query) {
    this->root = (Operator *)(new OpProject("sample", {"x", "z"}));
    this->root->prev = (Operator *)(new OpScan("sample"));
}
