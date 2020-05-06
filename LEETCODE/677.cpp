#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <queue>
#include <functional>
using namespace std;

const int MaxBranchNum = 26;
class TrieNode
{
public:
    bool exist;
    int value;  
    TrieNode* next[MaxBranchNum];

public:
    TrieNode() : exist(false), value(0)
    {
        for (size_t i=0; i<MaxBranchNum; ++i) {
            next[i] = NULL;
        }
    }

    ~TrieNode() {
        for (size_t i=0; i<MaxBranchNum; ++i) {
            if (next[i] != NULL) {
                delete next[i];
                next[i] = NULL;
            }
        }
    }
};

typedef function<void (int value)> CallBack;

class Trie {
    public:
        Trie() {
            _root = new TrieNode();
        }

        ~Trie() {
            delete _root;
        }

        void insert(const char* s, int value = 0) {
            if (s == NULL || *s == 0) {
                return;
            }

            TrieNode* p = _root;
            int idx = 0;
            while (*s != 0)  {
                idx = *s - 'a';
                if (p->next[idx] == NULL) {
                    p->next[idx] = new TrieNode();
                }
                p = p->next[idx];
                s++;
            }
            p->exist = true;
            p->value = value;
        }

        void visit_all_by_prefix(const char* prefix, const CallBack& callback) {
            if (callback == NULL) {
                return;
            }

            if (prefix == NULL || *prefix == 0) {
                return;
            }

            TrieNode* p = _root;
            while (p != NULL && *prefix != 0) {
                p = p->next[*prefix - 'a'];
                prefix++;
            }

            if (p != NULL) {
                queue<TrieNode*> q;
                q.push(p);
            
                TrieNode* node = NULL;
                while (! q.empty()) {
                    node = q.front();
                    callback(node->value);
                    q.pop();
                    for (size_t i=0; i<MaxBranchNum; ++i) {
                        if (node->next[i] != NULL) {
                            q.push(node->next[i]);
                        }
                    }
                }
            }
        }

    protected:
        TrieNode* _root;
};

class MapSum {
public:
    MapSum() {
    }
    
    void insert(string key, int val) {
        _trie.insert(key.c_str(), val);
    }
    
    int sum(string prefix) {
        int sum = 0;
        CallBack callback = bind(&do_sum, ref(sum), std::placeholders::_1);
        _trie.visit_all_by_prefix(prefix.c_str(), callback);
        return sum;
    }

protected:
    static void do_sum(int& sum, int val) {
        sum += val;
    }
    Trie _trie;
};

int main() {
    MapSum obj;
    obj.insert("apple", 3);
    std::cout << obj.sum("ap") << std::endl;
    
    obj.insert("apple", 2);
    std::cout << obj.sum("ap") << std::endl;
    return 0;
}

