#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <sstream>
using std::vector;
using std::string;

class Solution {
public:
    vector<string> uncommonFromSentences(const string& A, const string& B) {
        // word状态
        // +n出现在A中n次
        // 0 同时出现在A B中
        // -n出现在B中n次
        std::unordered_map<std::string, int> word_stats;
        std::istringstream issa(A);
        std::string word;
        while (! issa.eof()) {
            issa >> word;
            word_stats[word]++;
        }
        
        std::istringstream issb(B);
        while (! issb.eof()) {
            issb >> word;
            auto mit = word_stats.find(word);
            if (mit == word_stats.end()) {
                word_stats.insert(std::make_pair(word, -1));
                continue;
            }
            
            int old = mit->second;
            if (old > 0) {
                mit->second = 0;
            } else if (old < 0) {
                mit->second = --old;
            }
        }
        
        std::vector<std::string> ret;
        for (const auto& pair: word_stats) {
            if (pair.second == 1 || pair.second == -1) {
                ret.push_back(pair.first);
            }
        }
        return ret;
    }
};

int main() {
    /*
    std::string A = "this apple is sweet";
    std::string B = "this apple is sour";
    */
    std::string A = "apple apple";
    std::string B = "banana";
    auto ret = Solution().uncommonFromSentences(A, B) ;
    std::for_each(ret.begin(), ret.end(), [](const string& a) {std::cout << a << std::endl;});
    return 0;
}

