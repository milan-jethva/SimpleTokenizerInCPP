#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

std::unordered_map<int, std::string> vocab = {
    {101, "[CLS]"}, {102, "[SEP]"}, {0, "[PAD]"}, {7592, "Hello"}, {2088, "world"},
    {2003, "is"}, {1037, "a"}, {2146, "test"}, {999, "!"}, {103, "##ing"} 
};

std::string decodeTokens(const std::vector<int>& token_ids) {
    std::string decoded_text;
    for (int token_id : token_ids) {
        if (vocab.find(token_id) != vocab.end()) {
            std::string word = vocab[token_id];

            if (word == "[CLS]" || word == "[SEP]" || word == "[PAD]") continue;

            if (!decoded_text.empty() && word.substr(0, 2) == "##") {
                decoded_text += word.substr(2);
            } else {
                if (!decoded_text.empty()) decoded_text += " ";
                decoded_text += word;
            }
        }
    }
    return decoded_text;
}

int main() {
    std::vector<int> token_ids = {101, 7592, 2088, 2003, 1037, 2146, 102, 999};
    std::string decoded_text = decodeTokens(token_ids);
    std::cout << "Decoded text: " << decoded_text << std::endl;
    return 0;
}
