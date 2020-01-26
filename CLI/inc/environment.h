#pragma once

#include <string>
#include <unordered_map>
#include <memory>

// empty string by default
namespace NCLI {
    
    class Environment {
    public:
        Environment() : variable_value_(new std::unordered_map<std::string, std::string>()) {}
        const std::string& get_variable(const std::string& name);
        void set_variable(const std::string& name, const std::string& value);

    private:
        std::shared_ptr<std::unordered_map<std::string, std::string>> variable_value_;
    };

} // namespace NCLI
