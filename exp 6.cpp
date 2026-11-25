#include <iostream>
#include <fstream>
#include <string>

// Function to replace all occurrences of a substring in a string
std::string replaceAll(const std::string& source, const std::string& search, const std::string& replace) {
    std::string result = source;
    size_t pos = 0;
    while ((pos = result.find(search, pos)) != std::string::npos) {
        result.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return result;
}

int main() {
    std::string filePath;
    std::string searchStr, replaceStr;

    // Get file path and words to search and replace from the user
    std::cout << "Enter the file path: ";
    std::cin >> filePath;
    std::cout << "Enter the word to search for: ";
    std::cin >> searchStr;
    std::cout << "Enter the word to replace it with: ";
    std::cin >> replaceStr;

    // Open the file for reading
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    // Read the entire file content
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Replace all occurrences of the search string with the replacement string
    content = replaceAll(content, searchStr, replaceStr);

    // Write the modified content back to the file
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filePath << std::endl;
        return 1;
    }
    outputFile << content;
    outputFile.close();

    std::cout << "File content modified successfully!" << std::endl;
    return 0;
}
