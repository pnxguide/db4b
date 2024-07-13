#include "query_plan.hpp"

QueryPlan::QueryPlan(std::string query) {
    this->root = (Operator *)(new OpProject("a", {"x"}));
    this->root->prev = (Operator *)(new OpScan("a"));
}
