#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Function to load vocabulary from a file
unordered_map<string, int> load_vocab(const string& filename) {
    unordered_map<string, int> vocab;
    ifstream file(filename);
    string word;
    int id;

    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    while (file >> word >> id) {
        vocab[word] = id;
    }
    file.close();
    return vocab;
}

// Function to tokenize text based on whitespace and assign token IDs
vector<int> tokenize_whitespace(const string& text, const unordered_map<string, int>& vocab, int unknown_id = -1) {
    vector<int> token_ids;
    istringstream ss(text);
    string word;

    while (ss >> word) {
        if (vocab.find(word) != vocab.end()) {
            token_ids.push_back(vocab.at(word));  // Use token ID from vocab
        } else {
            token_ids.push_back(unknown_id);  // Assign unknown token ID
        }
    }
    return token_ids;
}

// Driver code
int main() {
    string vocab_file = "vocab.txt";
    unordered_map<string, int> vocab = load_vocab(vocab_file);

    string text;
    cout << "Enter text to tokenize: ";
    getline(cin, text);  // Read full input

    vector<int> tokens = tokenize_whitespace(text, vocab);

    cout << "Token IDs: ";
    for (int id : tokens) {
        cout << id << " ";
    }
    cout << endl;

    return 0;
}
