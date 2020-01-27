#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace NCLI {
    
    /* Stores variables with string value by string name
     * Copy of environment uses same storage for variables
     *  and if modified in copy, variables value will be modified in original environment */
    class Environment {
    public:
        Environment() : variable_value_(new std::unordered_map<std::string, std::string>()) {}
        /* Returns variable value by name
         * If variable have not been set yet, returns empty string */
        const std::string& get_variable(const std::string& name);
        /* Sets variable value by name */
        void set_variable(const std::string& name, const std::string& value);

    private:
        std::shared_ptr<std::unordered_map<std::string, std::string>> variable_value_;
    };

} // namespace NCLI
