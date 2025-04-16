#include <iostream>
#include <string>
#include <cstdlib>

#include "interpreter.hpp"
#include "util.hpp"

// Enumerate commands
enum OperatorCommand {
    SIMULATE_CMD = 0,
    COMPILE_CMD = 1,
    INVALID_CMD = -1
};

// Constants
constexpr auto USAGE = "USAGE: ./paws <simulate | compile> <file_path>";
constexpr auto SIMULATE_ARG = "simulate";
constexpr auto COMPILE_ARG = "compile";

// Evaluate argv[1]
static int cast_cmd_arg_to_id (const std::string_view arg) {
    if (arg == SIMULATE_ARG) return SIMULATE_CMD;
    if (arg == COMPILE_ARG) return COMPILE_CMD;
    return INVALID_CMD; // Operator command not recognized
}

// Read a file
static std::string try_read_file (const std::string_view path) {
    try {
        return read_code_file_contents(path);
    }
    catch (const std::runtime_error& error) {
        handle_error(error.what());
    }
}

// Execute file via interpreter
static void try_read_and_exec (const std::string_view path) {
    std::string code = try_read_file(path);
    exec(code);
}

// Entrypoint
int main (int argc, char* argv[]) {
    if (argc != 3) handle_error(USAGE);

    int cmd_id = cast_cmd_arg_to_id(argv[1]);
    if (cmd_id == INVALID_CMD) {
        handle_error("Invalid operator command '" + std::string(argv[1]) + "'.");
    }

    switch (cmd_id) {
        case SIMULATE_CMD:
            try_read_and_exec(argv[2]);
            break;
        case COMPILE_CMD:
            handle_error("Compilation is not implemented!");
        default:
            handle_error("Unexpected error occured.");
    }

    return 0;
}
