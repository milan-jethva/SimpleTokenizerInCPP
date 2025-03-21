#include <iostream>
#include <vector>
#include <fstream>

// Special token constants
const int CLS_TOKEN = 101;  // [CLS]
const int SEP_TOKEN = 102;  // [SEP]
const int PAD_TOKEN = 0;    // [PAD]

// Function to apply post-processing
std::vector<int> postProcessTokens(const std::vector<int>& token_ids, int max_length = 10) {
    std::vector<int> processed_tokens = token_ids;

    // Add special tokens
    processed_tokens.insert(processed_tokens.begin(), CLS_TOKEN);  // Add [CLS] at start
    processed_tokens.push_back(SEP_TOKEN);  // Add [SEP] at end

    // Apply Padding or Truncation
    if (processed_tokens.size() < max_length) {
        processed_tokens.resize(max_length, PAD_TOKEN);  // Pad with [PAD] tokens
    } else if (processed_tokens.size() > max_length) {
        processed_tokens.resize(max_length);  // Truncate if too long
    }

    return processed_tokens;
}

// Function to save tokenized output to a file
void saveTokensToFile(const std::vector<int>& token_ids, const std::string& filename) {
    std::ofstream file(filename);
    for (int id : token_ids) {
        file << id << " ";
    }
    file.close();
}

int main() {
    std::vector<int> token_ids = {7592, 2088, 2003, 1037, 2146};  // Example: "Hello world is a test"

    std::vector<int> processed_tokens = postProcessTokens(token_ids, 10);

    saveTokensToFile(processed_tokens, "tokens.txt");

    std::cout << "Processed tokens saved successfully!" << std::endl;
    return 0;
}
