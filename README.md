# Sines File Sanitizer

## Overview

Sines File Sanitizer is a robust C++ library designed to safely sanitize filenames across different character sets and encodings. It provides comprehensive filename cleaning, normalization, and validation to ensure cross-platform compatibility and prevent potential security issues.

## Features

- 🌐 Full Unicode support (UTF-8 and UTF-32)
- 🧹 Comprehensive character sanitization
- 📏 Optional filename length restriction
- 🔒 Filename validation
- 🔤 Lowercase conversion
- 🚫 Special character replacement
- 🌈 Multi-language filename handling

## Installation

### Prerequisites

- C++ Compiler with C++11 support (g++ recommended)
- CMake 

### CMake Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/sines-file-sanitizer.git
cd sines-file-sanitizer
```

2. Build and install:
```bash
mkdir build
cd build
cmake ..
make
sudo make install
```
### Manual Compilation

```bash
g++ test.cpp -o sanitizest -I/usr/local/include -L/usr/local/lib -lSinesFileSanitizer
```
## API Reference

### Static Methods

#### `sanitizeFileName(const std::string& fileName)`
Sanitizes a filename by:
- Converting to lowercase
- Replacing special characters with underscores
- Removing consecutive underscores
- Trimming leading/trailing underscores

```cpp
std::string cleanName = SinesFileSanitizer::sanitizeFileName("Hello World! 2024.txt");
// Result: "hello_world_2024.txt"
```

#### `sanitizeFileName(const std::string& fileName, size_t maxLength)`
Sanitizes filename with an additional length restriction:
- Same as basic sanitization
- Truncates filename if it exceeds `maxLength`
- Ensures clean truncation without awkward underscore endings

```cpp
std::string truncatedName = SinesFileSanitizer::sanitizeFileName("Very Long Filename.txt", 10);
// Result: "very_long.txt"
```

#### `isValidFileName(const std::string& fileName)`
Validates a filename, checking if it contains only:
- Alphanumeric characters
- Underscores
- Dots
- Hyphens

```cpp
bool valid = SinesFileSanitizer::isValidFileName("my_document.txt");
// Returns true
```

## Example Usage

```cpp
#include "SinesFileSanitizer.h"
#include <iostream>

int main() {
    // Basic sanitization
    std::string dirtyName = "Hello World! 2024.txt";
    std::string cleanName = SinesFileSanitizer::sanitizeFileName(dirtyName);
    std::cout << "Sanitized: " << cleanName << std::endl;

    // Length-restricted sanitization
    std::string longName = "A Very Very Long Filename.docx";
    std::string shortName = SinesFileSanitizer::sanitizeFileName(longName, 15);
    std::cout << "Truncated: " << shortName << std::endl;

    // Validation
    bool isClean = SinesFileSanitizer::isValidFileName(cleanName);
    std::cout << "Is Valid: " << (isClean ? "Yes" : "No") << std::endl;

    return 0;
}
```

## Supported Character Replacements

The library replaces various special characters, including but not limited to:
- Whitespace characters (space, tab, newline)
- Punctuation marks
- Currency symbols
- Mathematical symbols
- Trademark and copyright symbols

## Performance Considerations

- UTF-8 to UTF-32 conversion for comprehensive character handling
- Optimized with static initialization
- Minimal runtime overhead



