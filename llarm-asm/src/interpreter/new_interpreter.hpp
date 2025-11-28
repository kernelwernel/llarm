#include <vector>

#include "shared/string_view.hpp"


namespace interpreter {
    using tokens_t = std::vector<llarm::string_view>;
    
    // tokenization/lexing management 
    tokens_t tokenize(const std::string &code);

}