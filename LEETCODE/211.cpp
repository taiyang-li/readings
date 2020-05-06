#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
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
        /*
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
        */
        return doSearch(_root, word, 0);
    }

    bool doSearch(TrieNode* curr, const string& word, int start) {
        const int len = word.size();
        char ch = 0;
        int idx = 0;
        int i = 0;
        for (i=start; i<len && word[i] != '.'; ++i) {
            ch = word[i];
            idx = ch - 'a';
            if (curr->next[idx] == NULL) {
                return false;
            }
            curr = curr->next[idx];
        }
        if (i == len) {
            return curr->exist;
        }

        bool ret = false;
        start = i+1;
        for (i=0; i<26; ++i) {
            if (curr->next[i] == NULL) {
                continue;
            }
            TrieNode* new_curr = curr->next[i];
            ret = ret || doSearch(new_curr, word, start);
        }
        return ret;
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

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
    }
    
    /** Adds a word into the data structure. */
    void addWord(const string& word) {
        _trie.insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(const string& word) {
        return _trie.search(word);
    }

protected:
    Trie _trie;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */

int main() {
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    std::cout << dict.search("pad") << std::endl;
    std::cout << dict.search("bad") << std::endl;
    std::cout << dict.search(".ad") << std::endl;
    std::cout << dict.search("b..") << std::endl;
    return 0;
}
