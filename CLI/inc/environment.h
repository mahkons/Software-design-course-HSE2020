#pragma once

#include <string>
#include <unordered_map>

// empty string by default
namespace NCLI {
    
    class Environment {
    public:
        const std::string& get_variable(const std::string& name);
        void set_variable(const std::string& name, const std::string& value);

    private:
        std::unordered_map<std::string, std::string> variable_value_;
    };

} // namespace NCLI
