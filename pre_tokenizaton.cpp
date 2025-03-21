#include <iostream>
#include <string>
#include <unordered_map>
#include <codecvt>
#include <locale>
#include <algorithm>  

using namespace std;

unordered_map<wchar_t, wchar_t> accent_map = {
    {L'é', L'e'}, {L'è', L'e'}, {L'ê', L'e'}, {L'ë', L'e'},
    {L'á', L'a'}, {L'à', L'a'}, {L'â', L'a'}, {L'ä', L'a'},
    {L'í', L'i'}, {L'ì', L'i'}, {L'î', L'i'}, {L'ï', L'i'},
    {L'ó', L'o'}, {L'ò', L'o'}, {L'ô', L'o'}, {L'ö', L'o'},
    {L'ú', L'u'}, {L'ù', L'u'}, {L'û', L'u'}, {L'ü', L'u'},
    {L'ñ', L'n'}, {L'ç', L'c'}
};

// Function to remove accents
wstring removeAccents(const wstring &text) {
    wstring result;
    for (wchar_t c : text) {
        if (accent_map.find(c) != accent_map.end()) {
            result += accent_map[c];  
        } else {
            result += c;  
        }
    }
    return result;
}


wstring replaceUnicodeSymbols(const wstring &text) {
    wstring result = text;
    unordered_map<wstring, wstring> unicode_replacements = {
        {L"²", L"2"}, {L"³", L"3"}, {L"½", L"1/2"}, {L"⅓", L"1/3"},
        {L"¼", L"1/4"}, {L"⅔", L"2/3"}, {L"¾", L"3/4"}
    };

    for (const auto &pair : unicode_replacements) {
        size_t pos;
        while ((pos = result.find(pair.first)) != wstring::npos) {
            result.replace(pos, pair.first.length(), pair.second);
        }
    }
    return result;
}


wstring toLowerCase(const wstring &text) {
    wstring result = text;
    transform(result.begin(), result.end(), result.begin(),
              [](wchar_t c) { return towlower(c); });  
    return result;
}

// Function to strip leading/trailing whitespace
wstring stripWhitespace(const wstring &text) {
    size_t start = text.find_first_not_of(L" \t\n\r");
    size_t end = text.find_last_not_of(L" \t\n\r");
    return (start == wstring::npos) ? L"" : text.substr(start, end - start + 1);
}

// Full normalizer function
wstring normalizeText(const wstring &text) {
    wstring normalized = stripWhitespace(text);  // Step 1: Remove extra spaces
    normalized = toLowerCase(normalized);        // Step 2: Convert to lowercase
    normalized = removeAccents(normalized);      // Step 3: Remove accents
    normalized = replaceUnicodeSymbols(normalized); // Step 4: Replace Unicode symbols
    return normalized;
}

// Test function
int main() {
    wstring input = L"   HELLO Café! ²⅓   ";

    // Convert input to wide string
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale());

    wstring output = normalizeText(input);
    wcout << L"Normalized Text: " << output << endl;

    return 0;
}
