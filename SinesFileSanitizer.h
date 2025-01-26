#ifndef SINES_FILE_SANITIZER_H
#define SINES_FILE_SANITIZER_H

#include <string>
#include <algorithm>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <regex>

class SinesFileSanitizer {
private:
    // Mapping of special characters to be replaced
    static std::unordered_map<char32_t, std::string> specialCharMap;

    // Initialize the special character map
    static void initSpecialCharMap();

    // Convert UTF-8 string to UTF-32 for comprehensive character handling
    static std::u32string utf8to32(const std::string& utf8str);

    // Convert UTF-32 string back to UTF-8
    static std::string utf32to8(const std::u32string& utf32str);

    // Remove consecutive underscores and trim start/end underscores
    static std::string cleanupFileName(const std::string& fileName);

    // Convert string to lowercase
    static std::u32string toLowercase(const std::u32string& str);

public:
    // Static method to sanitize filename
    static std::string sanitizeFileName(const std::string& fileName);

    // Method to sanitize filename with optional max length
    static std::string sanitizeFileName(const std::string& fileName, size_t maxLength);

    // Validate if filename is safe (contains only safe characters)
    static bool isValidFileName(const std::string& fileName);
};

#endif // SINES_FILE_SANITIZER_H