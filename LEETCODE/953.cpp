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
    bool isAlienSorted(vector<string>& words, const string& order) {
        int8_t tb[26];
        int rank = 0;
        for (auto ch: order) {
            tb[ch-'a'] = rank++;
        }

        const int words_len = words.size();
        for (int i=0; i<words_len-1; ++i) {
            if (alien_compare(words[i], words[i+1], tb) == 1) {
                return false;
            }
        }
        return true;
    }

    int alien_compare(const string& left, const string& right, int8_t* tb) {
        const int left_len = left.size();
        const int right_len = right.size();
        for (int i=0; i<left_len && i < right_len; ++i) {
            if (left[i] == right[i]) {
                continue;
            }
            return tb[left[i] - 'a'] < tb[right[i] - 'a'] ? -1 : 1;
        }
        if (left_len == right_len) {
            return 0;
        }
        return left_len < right_len ? -1 : 1;
    }
};

int main() {
    return 0;
}

