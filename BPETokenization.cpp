#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Function to load BPE vocabulary from a file
unordered_map<string, int> load_vocab(const string& filename) {
    unordered_map<string, int> vocab;
    ifstream file(filename);
    string token;
    int id;

    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    while (file >> token >> id) {
        vocab[token] = id;
    }
    file.close();
    return vocab;
}

// Function to tokenize text into token IDs using BPE vocab
vector<int> tokenize(const string& text, const unordered_map<string, int>& bpe_vocab) {
    vector<int> token_ids;
    istringstream ss(text);
    string word;

    while (ss >> word) {
        // Check if whole word exists in vocabulary
        if (bpe_vocab.find(word) != bpe_vocab.end()) {
            token_ids.push_back(bpe_vocab.at(word));
        } else {
            // Split into characters if word is not in vocab
            for (char c : word) {
                string char_str(1, c);
                if (bpe_vocab.find(char_str) != bpe_vocab.end()) {
                    token_ids.push_back(bpe_vocab.at(char_str));
                }
            }
        }
    }
    return token_ids;
}

// Driver code
int main() {
    string vocab_file = "vocab.txt";
    unordered_map<string, int> bpe_vocab = load_vocab(vocab_file);

    string text;
    cout << "Enter text to tokenize: ";
    getline(cin, text);

    vector<int> tokens = tokenize(text, bpe_vocab);

    cout << "Token IDs: ";
    for (int id : tokens) {
        cout << id << " ";
    }
    cout << endl;

    return 0;
}
