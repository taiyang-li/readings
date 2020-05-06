#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string mostCommonWord(const string& paragraph, vector<string>& banned) {
        std::set<std::string> banned_set(banned.begin(), banned.end());
        int pos = 0;
        const int len = paragraph.size();
        std::string word;
        int max_freq = 0;
        std::string max_freq_word;
        std::map<std::string, int> frequencies;
        while (pos < len) {
            pos = next_word(paragraph, pos, word);
            // std::cout << word << std::endl;
            if (! word.empty() && banned_set.count(word) == 0) {
                frequencies[word]++;
                if (frequencies[word] > max_freq) {
                    max_freq = frequencies[word];
                    max_freq_word = word;
                }
            }
        }
        return max_freq_word;
    }

    int next_word(const string& paragraph, int pos, string& word) {
        const int len = paragraph.size();
        while (pos < len && symbols.count(paragraph[pos]) > 0) {
            pos++;
        }
        int start = pos;
        while (pos < len && std::isalpha(paragraph[pos])) {
            pos++;
        }
        word = paragraph.substr(start, pos-start);
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        return pos;
    }
    
    static const std::set<char> symbols;
};
const std::set<char> Solution::symbols = {'!', '?', ',', ';', '.', ' ', '\n', '\''};

int main() {
    std::string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    std::vector<std::string> banned = {"hit"};
    std::cout << Solution().mostCommonWord(paragraph, banned);
    return 0;
}
