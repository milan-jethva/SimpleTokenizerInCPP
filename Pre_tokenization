#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// Mapping of accented characters to their ASCII equivalents
std::unordered_map<char, char> accent_map = {
    {'é', 'e'}, {'è', 'e'}, {'ê', 'e'}, {'ë', 'e'},
    {'á', 'a'}, {'à', 'a'}, {'â', 'a'}, {'ä', 'a'},
    {'í', 'i'}, {'ì', 'i'}, {'î', 'i'}, {'ï', 'i'},
    {'ó', 'o'}, {'ò', 'o'}, {'ô', 'o'}, {'ö', 'o'},
    {'ú', 'u'}, {'ù', 'u'}, {'û', 'u'}, {'ü', 'u'},
    {'ñ', 'n'}, {'ç', 'c'}
};

// Function to remove accents
std::string removeAccents(const std::string &text) {
    std::string result;
    for (char c : text) {
        if (accent_map.find(c) != accent_map.end()) {
            result += accent_map[c]; // Replace accented character
        } else {
            result += c; // Keep unchanged
        }
    }
    return result;
}

// Function to replace Unicode symbols (fractions, superscripts, etc.)
std::string replaceUnicodeSymbols(const std::string &text) {
    std::string result = text;
    std::unordered_map<std::string, std::string> unicode_replacements = {
        {"²", "2"}, {"³", "3"}, {"½", "1/2"}, {"⅓", "1/3"}, {"¼", "1/4"},
        {"⅔", "2/3"}, {"¾", "3/4"}
    };

    for (const auto &pair : unicode_replacements) {
        size_t pos;
        while ((pos = result.find(pair.first)) != std::string::npos) {
            result.replace(pos, pair.first.length(), pair.second);
        }
    }
    return result;
}

// Function to convert text to lowercase
std::string toLowerCase(const std::string &text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to strip leading/trailing whitespace (without regex)
std::string stripWhitespace(const std::string &text) {
    size_t start = text.find_first_not_of(" \t\n\r");
    size_t end = text.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : text.substr(start, end - start + 1);
}

// Full normalizer function
std::string normalizeText(const std::string &text) {
    std::string normalized = stripWhitespace(text);    // Step 1: Remove extra spaces
    normalized = toLowerCase(normalized);             // Step 2: Convert to lowercase
    normalized = removeAccents(normalized);           // Step 3: Remove accents
    normalized = replaceUnicodeSymbols(normalized);   // Step 4: Replace Unicode symbols
    return normalized;
}

// Test function
int main() {
    std::string input = "   HELLO Café! ²⅓   ";
    std::string output = normalizeText(input);
    std::cout << "Normalized Text: " << output << std::endl;
    return 0;
}
