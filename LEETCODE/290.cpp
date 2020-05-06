#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
#include <sstream>
#include <unordered_map>
using std::vector;
using std::string;

class Solution {
public:
    bool wordPattern(const string& pattern, const string& str) {
        std::istringstream iss(str);
        std::vector<std::string> words;
        while (! iss.eof()) {
            std::string tmp;
            iss >> tmp;
            words.push_back(tmp);
        }
        if (pattern.size() != words.size()) {
            return false;
        }
        
        std::unordered_map<char, std::string> table;
        std::unordered_map<std::string, char> revert_table;
        for (int i=0; i<pattern.size(); ++i) {
            auto mit = table.find(pattern[i]);
            if (mit == table.end()) {
                table.insert(std::make_pair(pattern[i], words[i]));
            } else if (mit->second != words[i]) {
                return false;
            } 
            
            auto revert_mit = revert_table.find(words[i]);
            if (revert_mit == revert_table.end()) {
                revert_table.insert(std::make_pair(words[i], pattern[i]));
            } else if (revert_mit->second != pattern[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    return 0;
}

