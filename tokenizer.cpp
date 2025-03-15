#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class BPETokenizer{
private:
    unordered_map<string,int> vocab; //For storing -> Token(string) -> id(int)

public:
    //load_vocab_from_file
    void load_vocabfile(const string& vocab_file){
        ifstream file(vocab_file);
        if(!file.is_open()){
            cerr<<"File is not opened";
            return;
        }
        string token;
        int id;
        while(file >> token >> id){
            vocab[token] = id;
        }
        file.close();
        cout<<"Vocab created successfully";
    }
    
    vector<int> tokenize(const string& text){
        vector<int> token_id;
        istringstream ss(text);
        string word;
        while(ss >> word){
            if (vocab.find(word) != vocab.end() ){
                token_id.push_back(vocab[word]);
            }
            else{
                for(char c: word){
                    string char_str(1,c);
                    if (vocab.find(char_str) != vocab.end() ){
                        token_id.push_back(vocab[char_str]);
                    }
                }
            }


        }
        return token_id;

    }

    void save_token(const string& output_file,const vector<int>& tokens){
        ofstream file(output_file);
        if (!file.is_open()){
            cerr<< "File is not opend";
            return;
        }
        for (int a:tokens){
            file<<a<<" ";
        }
        file.close();
        cout<<"Token saved in file";
    }
};

int main(){
    BPETokenizer tokenizer;
    
    tokenizer.load_vocabfile("vocab.txt");

    string input_text;
    cout<<"ENter text  you want to convert";
    getline(cin,input_text);

    vector<int> token_id = tokenizer.tokenize(input_text);
    for(int a:token_id){
        cout<<a<<" ";
    }

    tokenizer.save_token("output_file",token_id);
    return 0;

}