#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    string longestWord(vector<string>& words) {
        std::sort(words.begin(), words.end(), [](const string& lhs, const string& rhs) -> bool {return lhs.size() < rhs.size();});
        size_t curr_len = words[0].size();
        std::set<std::string> tmp;
        std::set<std::string> res;
        for (const auto& word: words) {
            size_t len = word.size();
            if (len > curr_len) {
                if (tmp.empty() || len > curr_len + 1) {
                    break;
                }
                res = tmp;
                tmp.clear();
                ++curr_len;
            }
            if (len == 1 || res.count(word.substr(0, len-1)) > 0) {
                tmp.insert(word);
            }
        }
        if (! tmp.empty()) {
            res = tmp;
        }
        return *(res.begin());
    }
};

int main() {
    std::vector<std::string> words = {"y", "yo", "yod", "yodn","ew", "eww", "ewww"};
    std::cout << Solution().longestWord(words) << std::endl;
    return 0;
}

