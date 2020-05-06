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
    string shortestCompletingWord(const string& licensePlate, vector<string>& words) {
        int plate_count[26] = {0};
        count_letter(licensePlate, plate_count);
        
        int min_match_len = INT_MAX;
        int min_match_idx = -1;
        const int len = words.size();
        for (int i=0; i<len; ++i) {
            int word_count[26] = {0};
            count_letter(words[i], word_count);

            if (match(plate_count, word_count)) {
                if (int(words[i].size()) < min_match_len) {
                    min_match_len = words[i].size();
                    min_match_idx = i;
                }
            }
        }
        return words[min_match_idx];
    }

    inline bool match(int* plate_count, int* word_count) {
        for (int i=0; i<26; ++i) {
            if (word_count[i] < plate_count[i]) {
                return false;
            }
        }
        return true;
    }

    inline void count_letter(const string& str, int* counts) {
        for (auto ch: str) {
            if (ch >= 'a' && ch <= 'z') {
                counts[ch - 'a']++;
            } else if (ch >= 'A' && ch <= 'Z') {
                counts[ch - 'A']++;
            }
        }
    }
};

int main() {
    return 0;
}

