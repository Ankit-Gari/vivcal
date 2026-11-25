#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <string>

int main() {
    CURL *curl;
    CURLcode res;

    std::string inputFileName, outputFileName;

    // Get input and output file names from user
    std::cout << "Enter input file name: ";
    std::cin >> inputFileName;
    std::cout << "Enter output file name: ";
    std::cin >> outputFileName;

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Open the input file
        std::ifstream inputFile(inputFileName, std::ios::binary);
        if (!inputFile) {
            std::cerr << "Error opening input file: " << inputFileName << std::endl;
            return 1;
        }

        // Prepare the form data
        curl_mime *form = curl_mime_init(curl);
        curl_mimepart *part = curl_mime_addpart(form);
        curl_mime_name(part, "file");
        curl_mime_filedata(part, inputFileName.c_str());

        // Set the URL for the POST request
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:4000/upload");
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Error during upload: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "File content copied!" << std::endl;
        }

        // Cleanup
        curl_mime_free(form);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
