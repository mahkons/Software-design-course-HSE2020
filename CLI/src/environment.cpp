#include <string>

#include "environment.h"

namespace NCLI {

    const std::string& Environment::get_variable(const std::string& name) {
        return variable_value_[name];
    }

    void Environment::set_variable(const std::string& name, const std::string& value) {
        variable_value_[name] = value;
    }

} // namespace NCLI
