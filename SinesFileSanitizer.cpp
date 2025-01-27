#include "SinesFileSanitizer.h"
#include <mutex>
#include <codecvt>
#include <locale>
#include <regex>
#include <algorithm>
#include <unordered_map>

// Initialize the static map
std::unordered_map<char32_t, std::string> SinesFileSanitizer::specialCharMap;

void SinesFileSanitizer::initSpecialCharMap() {
    // Whitespace characters
    specialCharMap[U' '] = "_";
    specialCharMap[U'\t'] = "_";
    specialCharMap[U'\n'] = "_";
    specialCharMap[U'\r'] = "_";

    // Special characters that need to be mapped
    const char32_t symbols[] = {
        // Basic punctuation and operators
        U'@', U'#', U'£', U'&', U'+', U'(', U')', U'/', U'*', 
        U'"', U'\'', U':', U';', U'!', U'?', U'~', U'`', U'|', 
        
        // Mathematical and currency symbols
        U'•', U'√', U'π', U'÷', U'×', U'§', U'∆', U'€', U'¥', 
        U'$', U'¢', U'^', U'°', U'=', U'{', U'}', U'[', U']',
        
        // Special marks
        U'✓', U'™', U'®', U'©', U'%', U',', U'.',U'<',U'>'
    };

    // Map all special characters to underscore
    for (char32_t sym : symbols) {
        specialCharMap[sym] = "_";
    }
}

std::u32string SinesFileSanitizer::utf8to32(const std::string& utf8str) {
    try {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.from_bytes(utf8str);
    } catch (const std::exception&) {
        return std::u32string();  // Return empty string on conversion failure
    }
}

std::string SinesFileSanitizer::utf32to8(const std::u32string& utf32str) {
    try {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(utf32str);
    } catch (const std::exception&) {
        return std::string();  // Return empty string on conversion failure
    }
}

std::string SinesFileSanitizer::cleanupFileName(const std::string& fileName) {
    // Remove consecutive underscores
    std::string cleaned = std::regex_replace(fileName, std::regex("_+"), "_");
    
    // Remove leading and trailing underscores
    cleaned = std::regex_replace(cleaned, std::regex("^_+|_+$"), "");
    
    // If the filename is empty after cleanup, use a default name
    if (cleaned.empty()) {
        return "unnamed_file";
    }
    
    // Ensure the filename doesn't start with a hyphen
    if (cleaned[0] == '-') {
        cleaned = "_" + cleaned;
    }
    
    return cleaned;
}

std::u32string SinesFileSanitizer::toLowercase(const std::u32string& str) {
    std::u32string lowercase = str;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), 
        [](char32_t c) { return std::tolower(static_cast<unsigned char>(c)); });
    return lowercase;
}

std::string SinesFileSanitizer::sanitizeFileName(const std::string& fileName) {
    static std::once_flag flag;
    std::call_once(flag, []() {
        initSpecialCharMap();
    });

    if (fileName.empty()) {
        return "unnamed_file";
    }

    // Convert to UTF-32 for comprehensive character handling
    std::u32string sanitized = utf8to32(fileName);
    if (sanitized.empty()) {
        return "unnamed_file";
    }

    // Convert to lowercase
    sanitized = toLowercase(sanitized);

    // Replace special characters
    for (size_t i = 0; i < sanitized.length(); ++i) {
        auto it = specialCharMap.find(sanitized[i]);
        if (it != specialCharMap.end()) {
            sanitized[i] = U'_';
        } else if (!std::isalnum(static_cast<unsigned char>(sanitized[i])) && 
                   sanitized[i] != U'_' && 
                   sanitized[i] != U'.' && 
                   sanitized[i] != U'-') {
            sanitized[i] = U'_';
        }
    }

    // Convert back to UTF-8 and clean up
    std::string result = utf32to8(sanitized);
    return cleanupFileName(result);
}

std::string SinesFileSanitizer::sanitizeFileName(const std::string& fileName, size_t maxLength) {
    if (maxLength == 0) {
        return "unnamed_file";
    }
    
    std::string sanitized = sanitizeFileName(fileName);
    
    // Check if UTF-8 encoded string needs truncation
    if (sanitized.length() > maxLength) {
        // Truncate at byte boundary
        while (maxLength > 0 && (sanitized[maxLength] & 0xC0) == 0x80) {
            --maxLength;
        }
        sanitized = sanitized.substr(0, maxLength);
        sanitized = cleanupFileName(sanitized);
    }

    return sanitized;
}

bool SinesFileSanitizer::isValidFileName(const std::string& fileName) {
    if (fileName.empty()) {
        return false;
    }

    std::u32string utf32Name = utf8to32(fileName);
    if (utf32Name.empty()) {
        return false;
    }
    
    // Check first character isn't a dot or hyphen
    if (utf32Name[0] == U'.' || utf32Name[0] == U'-') {
        return false;
    }

    for (char32_t c : utf32Name) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != U'_' && 
            c != U'.' && 
            c != U'-') {
            return false;
        }
    }
    
    return true;
}