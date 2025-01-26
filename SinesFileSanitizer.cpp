#include "SinesFileSanitizer.h"

// Initialize the static map
std::unordered_map<char32_t, std::string> SinesFileSanitizer::specialCharMap;

// Implementation of static methods that need to be defined outside the header

void SinesFileSanitizer::initSpecialCharMap() {
    // Whitespace and punctuation characters
    specialCharMap[U' '] = "_";
    specialCharMap[U'\t'] = "_";
    specialCharMap[U'\n'] = "_";
    specialCharMap[U'\r'] = "_";

    // Symbols and special characters
    const char32_t symbols[] = {
        U'@', U'#', U'£', U'&', U'-', U'+', U'(', U')', U'/', U'*', 
        U'"', U'\'', U':', U';', U'!', U'?', U'~', U'`', U'|', 
        U'•', U'√', U'π', U'÷', U'×', U'§', U'∆', U'€', U'¥', 
        U'$', U'¢', U'^', U'°', U'=', U'{', U'}', U']', U'[', 
        U'✓', U'™', U'®', U'©', U'%'
    };

    for (char32_t sym : symbols) {
        specialCharMap[sym] = "_";
    }
}

std::u32string SinesFileSanitizer::utf8to32(const std::string& utf8str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.from_bytes(utf8str);
}

std::string SinesFileSanitizer::utf32to8(const std::u32string& utf32str) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    return converter.to_bytes(utf32str);
}

std::string SinesFileSanitizer::cleanupFileName(const std::string& fileName) {
    // Remove consecutive underscores
    std::string cleaned = std::regex_replace(fileName, std::regex("_+"), "_");
    
    // Remove leading and trailing underscores
    cleaned = std::regex_replace(cleaned, std::regex("^_+|_+$"), "");
    
    // If the filename is empty after cleanup, use a default name
    return cleaned.empty() ? "unnamed_file" : cleaned;
}

std::u32string SinesFileSanitizer::toLowercase(const std::u32string& str) {
    std::u32string lowercase = str;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), 
        [](char32_t c) { return std::tolower(c); });
    return lowercase;
}

std::string SinesFileSanitizer::sanitizeFileName(const std::string& fileName) {
    // Ensure the special character map is initialized
    static bool initialized = false;
    if (!initialized) {
        initSpecialCharMap();
        initialized = true;
    }

    // Convert to UTF-32 for comprehensive character handling
    std::u32string sanitized = utf8to32(fileName);

    // Convert to lowercase
    sanitized = toLowercase(sanitized);

    // Replace special characters
    for (char32_t& c : sanitized) {
        auto it = specialCharMap.find(c);
        if (it != specialCharMap.end()) {
            // Replace with underscore or predefined replacement
            c = U'_';
        }
    }

    // Convert back to UTF-8 and clean up
    return cleanupFileName(utf32to8(sanitized));
}

std::string SinesFileSanitizer::sanitizeFileName(const std::string& fileName, size_t maxLength) {
    std::string sanitized = sanitizeFileName(fileName);
    
    // Truncate if exceeds max length
    if (sanitized.length() > maxLength) {
        sanitized = sanitized.substr(0, maxLength);
        // Ensure we don't end with an underscore after truncation
        sanitized = cleanupFileName(sanitized);
    }

    return sanitized;
}

bool SinesFileSanitizer::isValidFileName(const std::string& fileName) {
    std::u32string utf32Name = utf8to32(fileName);
    
    for (char32_t c : utf32Name) {
        // Allow alphanumeric, underscore, dot, and hyphen
        if (!std::isalnum(c) && 
            c != U'_' && 
            c != U'.' && 
            c != U'-') {
            return false;
        }
    }
    return true;
}