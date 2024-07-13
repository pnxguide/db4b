#include <vector>
#include <string>

class Operator {
   public:
    Operator *prev;
    virtual std::vector<std::string> emit();
};
