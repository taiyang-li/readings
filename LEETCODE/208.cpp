#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <string>
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



int main() {
    Trie trie;
    trie.insert("apple") ;
    std::cout << trie.search("apple");   // returns true
    std::cout << trie.search("app");     // returns false
    std::cout << trie.startsWith("app"); // returns true
    trie.insert("app");
    std::cout << trie.search("app");     // returns true
    return 0;
}
