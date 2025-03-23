#include <iostream>
#include <vector>
#include <fstream>

const int CLS_TOKEN = 101;  
const int SEP_TOKEN = 102;  
const int PAD_TOKEN = 0;  

std::vector<int> postProcessTokens(const std::vector<int>& token_ids, int max_length = 10) {
    std::vector<int> processed_tokens = token_ids;

    // Add special tokens
    processed_tokens.insert(processed_tokens.begin(), CLS_TOKEN); 
    processed_tokens.push_back(SEP_TOKEN);  

    // Apply Padding or Truncation
    if (processed_tokens.size() < max_length) {
        processed_tokens.resize(max_length, PAD_TOKEN);  
    } else if (processed_tokens.size() > max_length) {
        processed_tokens.resize(max_length);  
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
