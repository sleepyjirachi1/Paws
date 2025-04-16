#include "util.hpp"

// Handle an error and exit with a failure
[[noreturn]] void handle_error (const std::string_view message) {
    std::cerr << message << std::endl;
    std::exit(EXIT_FAILURE);
}

// Read a file and return it as a string
std::string read_code_file_contents(const std::string_view path) {
    std::string path_str(path);
    
    std::ifstream file(path_str);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path_str);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
