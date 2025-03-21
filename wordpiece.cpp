#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Function to load WordPiece vocabulary from file
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

// Function to tokenize text using WordPiece
vector<int> tokenize_wordpiece(const string& word, const unordered_map<string, int>& vocab) {
    vector<int> token_ids;
    int len = word.size();
    int start = 0;

    while (start < len) {
        int end = len;
        string subword;
        bool found = false;

        while (end > start) {
            subword = (start > 0 ? "##" : "") + word.substr(start, end - start);
            if (vocab.find(subword) != vocab.end()) {
                token_ids.push_back(vocab.at(subword));
                start = end;
                found = true;
                break;
            }
            --end;
        }

        // If no match, split character by character
        if (!found) {
            string char_str(1, word[start]);
            if (vocab.find(char_str) != vocab.end()) {
                token_ids.push_back(vocab.at(char_str));
            }
            start++;
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
    cin >> text;

    vector<int> tokens = tokenize_wordpiece(text, vocab);

    cout << "Token IDs: ";
    for (int id : tokens) {
        cout << id << " ";
    }
    cout << endl;

    return 0;
}
