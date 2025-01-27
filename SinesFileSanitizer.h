#pragma once

#include <string>
#include <unordered_map>

class SinesFileSanitizer {
private:
    static std::unordered_map<char32_t, std::string> specialCharMap;
    
    static void initSpecialCharMap();
    static std::u32string utf8to32(const std::string& utf8str);
    static std::string utf32to8(const std::u32string& utf32str);
    static std::string cleanupFileName(const std::string& fileName);
    static std::u32string toLowercase(const std::u32string& str);

public:
    // Sanitize a filename without length restriction
    static std::string sanitizeFileName(const std::string& fileName);
    
    // Sanitize a filename with maximum length restriction
    static std::string sanitizeFileName(const std::string& fileName, size_t maxLength);
    
    // Check if a filename is valid
    static bool isValidFileName(const std::string& fileName);
};