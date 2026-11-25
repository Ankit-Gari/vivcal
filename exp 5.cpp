#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// Function to check if a file contains a specific string
bool containsString(const std::string& filePath, const std::string& targetString) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(targetString) != std::string::npos) {
            return true;  // Found the target string
        }
    }

    return false;  // Target string not found
}

int main() {
    // Define the paths for the source and destination directories
    std::string sourceDir = "C:/Code/Source";            // Change this path as needed
    std::string destinationDir = "C:/Code/Destination";  // Change this path as needed
    std::string targetString = "sample";  // String to search for within files

    // Create the source directory if it does not exist
    if (!fs::exists(sourceDir)) {
        fs::create_directories(sourceDir);
        std::cout << "Created source directory: " << sourceDir << std::endl;

        // Optionally, create some sample files in the source directory
        std::ofstream sampleFile(sourceDir + "/sample1.txt");
        sampleFile << "This is a sample file." << std::endl;
        sampleFile.close();
    } else {
        std::cout << "Source directory already exists: " << sourceDir << std::endl;
    }

    // Create the destination directory if it does not exist
    if (!fs::exists(destinationDir)) {
        fs::create_directories(destinationDir);
        std::cout << "Created destination directory: " << destinationDir << std::endl;
    } else {
        std::cout << "Destination directory already exists: " << destinationDir << std::endl;
    }

    // Iterate over files and selectively copy those containing the target string
    try {
        for (const auto& entry : fs::directory_iterator(sourceDir)) {
            const auto& path = entry.path();
            auto destPath = fs::path(destinationDir) / path.filename();

            if (containsString(path.string(), targetString) && !fs::exists(destPath)) {
                fs::copy_file(path, destPath);
                std::cout << "Copied: " << path.filename().string() << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return 0;
}
