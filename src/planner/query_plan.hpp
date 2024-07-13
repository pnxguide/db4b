#include <string>
#include <vector>

#include "../operator/operator.hpp"

class QueryPlan {
   public:
    std::vector<void *> args;
    Operator *root;

    QueryPlan(std::string q);
};
