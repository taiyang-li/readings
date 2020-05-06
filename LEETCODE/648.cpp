#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
using namespace std;

struct TrieNode {
    bool exist;
    TrieNode* next[26];
    TrieNode(bool e = false) : exist(e) {
        for (int i=0; i<26; ++i) {
            next[i] = NULL;
        }
    }

    ~TrieNode() {
        for (int i=0; i<26; ++i) {
            if (next[i] != NULL) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        _root = new TrieNode();
    }

    ~Trie() {
        delete _root;
    }

    /** Inserts a word into the trie. */
    void insert(const string& word) {
        TrieNode* curr = _root;
        int index = 0;
        for (auto ch : word) {
            index = ch - 'a';
            if (curr->next[index] == NULL) {
                curr->next[index] = new TrieNode();
            }
            curr = curr->next[index];
        }
        curr->exist = true;
    }

    /** Returns if the word is in the trie. */
    bool search(const string& word) {
        TrieNode* curr = _root;
        int index = 0;
        for (auto ch : word) {
            index = ch - 'a';
            if (curr->next[index] == NULL) {
                return false;
            }
            curr = curr->next[index];
        }
        return curr->exist;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string& prefix) {
        TrieNode* curr = _root;
        int index = 0;
        for (auto ch : prefix) {
            index = ch - 'a';
            if (curr->next[index] == NULL) {
                return false;
            }
            curr = curr->next[index];
        }
        return true;
    }
    
protected:
    TrieNode* _root;
};



class Solution {
public:
    string replaceWords(vector<string>& dict, const string& sentence) {
        if (dict.empty() || sentence.empty()) { 
            return sentence;
        }

        Trie trie;
        for (const auto& root : dict) {
            trie.insert(root);
        }

        // split sentence
        std::istringstream iss(sentence);
        std::vector<std::string> split_results;
        while (iss.good()) {
            split_results.push_back(std::string());
            iss >> *split_results.rbegin();
        }

        std::string ret;
        for (auto it=split_results.begin(); it!=split_results.end(); ++it) {
            bool found = false;
            std::string root;
            for (size_t len=1; len<it->size(); ++len) {
                root = it->substr(0, len);
                if (trie.search(root)) {
                    found = true;
                    break;
                }
            }

            if (it != split_results.begin()) {
                ret.append(" ");
            }
            if (found) {
                ret.append(root);
            } else {
                ret.append(*it);
            }
        }
        return ret;
    }
};

int main() {
    std::vector<std::string> dict = {"cat", "bat", "rat"};
    std::string sentence = "the cattle was rattled by the battery";
    std::cout << Solution().replaceWords(dict, sentence) << std::endl;
    return 0;
}
