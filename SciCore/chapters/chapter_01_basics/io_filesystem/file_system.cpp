#include <iostream>
#include <fstream>
#include <expected> // C++23
#include <string>
#include <print>   // C++23

// We define a custom error type for our scientific application
enum class IOError {
    FileNotFound,
    InvalidFormat,
    EmptyFile
};

struct ConfigData {
    int iterations;
    double tolerance;
};

// This function returns either ConfigData OR an IOError
std::expected<ConfigData, IOError> read_config(const std::string& filename) {
    std::ifstream infile(filename);
    
    if (!infile.is_open()) {
        return std::unexpected(IOError::FileNotFound);
    }

    int i;
    double d;
    if (!(infile >> i >> d)) {
        return std::unexpected(IOError::InvalidFormat);
    }

    return ConfigData{i, d}; // Success!
}

int main() {
    auto result = read_config("params.txt");

    if (result) {
        // Access data using pointer-like syntax (* or ->)
        const auto& [iter, tol] = *result; 
        std::print("Running {} iterations with tol: {}\n", iter, tol);
    } else {
        // Handle specific errors without a try-catch block
        switch (result.error()) {
            case IOError::FileNotFound:  std::print(stderr, "Error: Config file missing.\n"); break;
            case IOError::InvalidFormat: std::print(stderr, "Error: Non-numeric data found.\n"); break;
            case IOError::EmptyFile:    std::print(stderr, "Error: File is empty.\n"); break;
        }
        return 1;
    }
}
