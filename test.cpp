#include <iostream>
#include "SinesFileSanitizer.h"

int main() {
    // Basic filename sanitization
    std::string originalName1 = "Hello World! 2024.txt";
    std::string sanitizedName1 = SinesFileSanitizer::sanitizeFileName(originalName1);
    std::cout << "Original: " << originalName1 << std::endl;
    std::cout << "Sanitized: " << sanitizedName1 << std::endl;
    // Expected output: "hello_world_2024.txt"

    // Sanitization with length restriction
    std::string originalName2 = "Very Long Filename with Multiple Words.docx";
    std::string sanitizedName2 = SinesFileSanitizer::sanitizeFileName(originalName2, 15);
    std::cout << "Original: " << originalName2 << std::endl;
    std::cout << "Truncated: " << sanitizedName2 << std::endl;
    // Expected output: "very_long.docx"

    // Filename validation
    std::string validName = "my_document.txt";
    std::string invalidName = "file@invalid.pdf";
    
    std::cout << "Validating '" << validName << "': " 
              << (SinesFileSanitizer::isValidFileName(validName) ? "Valid" : "Invalid") << std::endl;
    std::cout << "Validating '" << invalidName << "': " 
              << (SinesFileSanitizer::isValidFileName(invalidName) ? "Valid" : "Invalid") << std::endl;

    // Handling special characters and international names
    std::string specialName = "Über Große Datei! 2024.txt";
    std::string sanitizedSpecialName = SinesFileSanitizer::sanitizeFileName(specialName);
    std::cout << "Special Name: " << specialName << std::endl;
    std::cout << "Sanitized: " << sanitizedSpecialName << std::endl;
    // Expected output: "uber_grosse_datei_2024.txt"

    return 0;
}