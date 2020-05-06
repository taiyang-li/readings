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
using std::vector;
using std::string;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        std::vector<std::string> ret;
        for (const auto& word: words) {
            const int len = word.size();
            int line = LETTER2LINE[std::tolower(word[0]) - 'a'];
            int i = 1;
            for (; i<len; ++i) {
                if (line != LETTER2LINE[std::tolower(word[i]) - 'a']) break;
            }

            if (i == len) {
                ret.push_back(word);
            }
        }
        return ret;
    }
    
    static std::vector<int> init() {
        std::vector<int> ret(26, 0);
        const int len = LINES.size();
        for (int i=0; i<len; ++i) {
            for (auto ch: LINES[i]) {
                ret[ch - 'a'] = i;
            }
        }
        return ret;
    }

    static const std::vector<std::string> LINES ;
    static const std::vector<int> LETTER2LINE;
};
const std::vector<std::string> Solution::LINES = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
const std::vector<int> Solution::LETTER2LINE = Solution::init();

int main() {
    return 0;
}

