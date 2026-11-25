#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

int main() {
    // Define the paths for the source and destination directories
    std::string sourceDir = "C:/Code/Source";            // Change this path as needed
    std::string destinationDir = "C:/Code/Destination";  // Change this path as needed

    // Create the source directory if it does not exist
    if (!fs::exists(sourceDir)) {
        fs::create_directories(sourceDir);
        std::cout << "Created source directory: " << sourceDir << std::endl;

        // Create some sample files in the source directory
        std::ofstream sampleFile(sourceDir + "/sample1.txt");
        sampleFile << "This is a sample file." << std::endl;
        sampleFile.close();

        std::ofstream sampleFile2(sourceDir + "/sample2.txt");
        sampleFile2 << "This is another sample file." << std::endl;
        sampleFile2.close();
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

    // Iterate over all files in the source directory and copy each to the destination
    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        const auto& path = entry.path();
        auto destPath = fs::path(destinationDir) / path.filename();

        // Copy only if the file does not already exist in the destination
        if (!fs::exists(destPath)) {
            fs::copy_file(path, destPath);
            std::cout << "Copied: " << path.filename().string() << std::endl;
        } else {
            std::cout << "File already exists in destination: " << path.filename().string() << std::endl;
        }
    }

    return 0;
}
