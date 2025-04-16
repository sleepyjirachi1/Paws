#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

[[noreturn]] void handle_error(const std::string_view message);
std::string read_code_file_contents(const std::string_view path);
